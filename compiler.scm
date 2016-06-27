;************************** parser ******************************
(load "pattern-matcher.scm")
(load "naive-qq.scm")

(print-graph #f) ; display circular structures
(print-gensym #f) ; print gensym as g1234
(case-sensitive #f) ; ditto
(print-brackets #f) ; do not use brackets when pretty-printing

(revert-interaction-semantics) ; allow built ins to be redefined

;;; fix bug in optimizer
(#%$sputprop 'append '*flags* 122)
(#%$sputprop 'append! '*flags* 34)
(#%$sputprop 'list* '*flags* 1250)
(#%$sputprop 'cons* '*flags* 1250)

;;; And just for good luck :-)

(define beginify
	(lambda (ls)
		(append '(begin) ls)))

(define beginiLambda
	(lambda (ls)
		(append '(lambda_begin) ls)))			
		
(define findTheSame
	(lambda (pairs)
		(if (null? pairs) #t
			(let* ((cars (map (lambda (p) (car p)) pairs))
			  (len (length (filter (lambda(p) (equal? (car p) (car cars))) pairs)))
			  (rest (remp (lambda(p) (equal? (car p) (car cars))) pairs)))
			  (if (> len 1) #f (findTheSame rest))))))
			  

		

(define with (lambda (s f) (apply f s)))

(define map_sub_lists 
	(lambda (f l)
		(if (null? l)
			'()
			(cons 
				(if (pair? (car l)) (map_sub_lists f (car l)) (f (car l)))
				(if (pair? (cdr l)) (map_sub_lists f (cdr l)) (f (cdr l)))))))

(define expand-letrec 
	(lambda (exp)
		(let* ((arg-exp-list (cadr exp))
			   (bodies (cddr exp))
			   (args-list (map (lambda (x) (car x)) arg-exp-list))
			   (exp-list (map (lambda (x) (cadr x)) arg-exp-list))
			   (new-bodies (map_sub_lists (lambda (x) (if (member x args-list) `(,x ,@args-list) x)) bodies))
			   (new-exps (map_sub_lists (lambda (x) (if (member x args-list) `(,x ,@args-list) x)) exp-list)))
                          (append `((lambda ,args-list ,@new-bodies))
                                  (map (lambda (x) `(lambda ,args-list ,x)) new-exps)))))
		
(define makeIf
	(lambda (lst)
		(cond ((null? (cdr lst)) (car lst))
		(else
			`(if ,(car lst) ,(makeIf (cdr lst)) ,#f)))))
			

(define seq_map 
	(lambda (f l . rev)
		(letrec ((helper (lambda (func lst acc)
							(cond 
								((null? lst) acc) 																			;()
								((and (pair? lst) (null? (cdr lst))) (append acc (list (func (car lst)))))								;(3)
								((and (pair? lst) (not (pair? (cdr lst)))) (append acc (list (func (car lst)) (func (cdr lst)))))		;(1 . 2)
								(else (helper func (cdr lst) (append acc (list (func (car lst))))))))))							;(1 . ( ...))
			(if (null? rev)
				(helper f l '())
				(reverse (helper f l '()))))))


(define *reserved-words*
  '(and begin cond define do else if lambda
    let let* letrec or quasiquote unquote 
    unquote-splicing quote set!))

(define simple-const?
	(lambda (exp)
		(or (boolean? exp) 
			(char? exp) 
			(number? exp) 
			(string? exp)
			(vector? exp)
			(eq? (*void-object*) exp)
			)))


(define RightFromPoint
	(lambda (lst)
		(cond ((pair? lst) (RightFromPoint (cdr lst)))
			(else lst))))

(define LeftFromPoint
	(lambda (lst)
		(cond ((pair? lst) 
		(append (list (car lst)) (LeftFromPoint (cdr lst))))
		(else 
		'()))))
		
(define var?
	(lambda (exp)
		(and (symbol? exp) (not (member exp *reserved-words*)))))

(define *void-object*
			(lambda()
				(if #f #t)))
		
(define parse
  (let ((run
	 (compose-patterns
	  (pattern-rule
	   (? 'c  null?)
	   (lambda (c) (eq? c '())))
	  (pattern-rule
	   (? 'c simple-const?)
	   (lambda (c) `(const ,c)))
	  (pattern-rule
	   `(quote ,(? 'c))
	   (lambda (c) `(const ,c)))
	  (pattern-rule
	   (? 'v var?)
	   (lambda (v) `(var ,v)))
	  (pattern-rule
	   `(if ,(? 'test) ,(? 'dit))
	   (lambda (test dit)
	     `(if3 ,(parse test) ,(parse dit) (const ,(*void-object*)))))
	  (pattern-rule
	   `(if ,(? 'test) ,(? 'dit) ,(? 'dif))
	   (lambda (test dit dif)
	     `(if3 ,(parse test) ,(parse dit) ,(parse dif))))
	 
;;lambda 
	   (pattern-rule
	   `(lambda ,(? 'param) ,(? 'body1) . ,(? 'body2))
	   (lambda (param body1 body2)
			(cond ((list? param)					
					`(lambda-simple ,param ,@(parse (beginiLambda (append (list body1) body2)))))
				  ((pair? param)
					`(lambda-opt ,(LeftFromPoint param) ,(RightFromPoint param) 
						,@(parse (beginiLambda (append (list body1) body2)))))
				(else 
					`(lambda-variadic ,param ,@(parse (beginiLambda (append (list body1) body2))))))))				
	 
;;sequence 
	  (pattern-rule
	   `(begin . ,(? 'en))
	   (lambda (en)
		(if (null? en)
		(void)
	     `(seq (,@(map parse en))))))

;;lambda-sequence 
	  (pattern-rule
	   `(lambda_begin . ,(? 'en))
	   (lambda (en)
		(if (null? en)
		(void)
		(if (>= (length en) 2) 
	        `((seq,(map parse en)))
			`(,@(map parse en))))))
 

;;define
	  (pattern-rule
		`(define ,(? 'variable var?) ,(? 'value (lambda (x) (not (member x *reserved-words*)))))
		(lambda (variable value)
			`(define ,(parse variable) ,(parse value)))) 
				
;;application1
	  (pattern-rule
		`(,(? 'func var?) . ,(? 'args))
		(lambda (func args)
			(if (not (member func *reserved-words*))
			`(applic ,(parse func) (,@(map parse args))))))
			
;;application2
		 (pattern-rule
		  `(,(? 'func list?) . ,(? 'args))
		(lambda (func args)
			(if (not (member func *reserved-words*))
			`(applic ,(parse func) (,@(map parse args))))))

;;quasiquote			
		(pattern-rule 
		`(,'quasiquote ,(? 'arg)) 
		(lambda (arg) 
			(parse (expand-qq arg))))
			
		 
;or
	(pattern-rule
		`(or . ,(? 'en))
			(lambda (en)
			(cond
				((null? en) (parse #f))
				((null? (cdr en)) (parse (car en)))
				(else `(or ,(map parse en))))))			
				

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;			
;;Macro Expansions:	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;define - MIT style
	  (pattern-rule
		`(define ,(? 'var-list pair?) ,(? 'body1) . ,(? 'body-rest))
		(lambda (var-list body1 body-rest)
			(let ((bodies (append (list body1) body-rest)))
				(parse `(define ,(car var-list) (lambda ,(cdr var-list) ,@bodies))))))

				


;;cond
	  (pattern-rule
		`(cond ,(? 'clause1) . ,(? 'clauses pair?))
		(lambda (clause1 clauses)
			(let ((clauses (append (list clause1) clauses)))
				(letrec ((makeCond 
							(lambda (clauses)							
								(let* ((first-clause (car clauses))
									   (rest-clause (cdr clauses))
									   (test (car first-clause))
									   (dit (cadr first-clause)))
									(if (null? rest-clause)
										(if (equal? 'else test) 
											dit
											`(if ,test ,dit))
										`(if ,test ,dit ,(makeCond rest-clause)))))))
						(parse (makeCond clauses))))))

;;and
	  (pattern-rule
	   `(and . ,(? 'en))
	   (lambda (en)
		(if (null? en)
		`(const ,#t)
		(if (= 1 (length en))
			(parse (car en))
			(parse `(if ,(car en) ,(makeIf (cdr en)) ,#f))))))

;;let
		(pattern-rule
		  `(let ,(? 'bindings findTheSame) ,(? 'body) . ,(? 'rest))
		   (lambda (bindings body rest)			
			(parse `((lambda ,(map car bindings) 
				   ,@(append (list body) rest)) 
				   ,@(map cadr bindings)))))

	
;;let*
	  (pattern-rule
	   `(let* () ,(? 'expr) . ,(? 'exprs))
	   (lambda (expr exprs)
		(if (null? exprs) (parse expr)
	     (parse (beginify (cons expr exprs))))))
		 
	  (pattern-rule
	   `(let* ((,(? 'var var?) ,(? 'val)) . ,(? 'rest)) . ,(? 'exprs))
	   (lambda (var val rest exprs)
	     (parse `(let ((,var ,val))
		       (let* ,rest . ,exprs)))))
	  ;; add more rules here


;;letrec
		(pattern-rule
		  `(letrec ,(? 'bindings) ,(? 'body) . ,(? 'rest))
		   (lambda (bindings body rest)
		   (parse (expand-letrec `(letrec ,bindings ,body , rest)))))

	  )))
    (lambda (e)
      (run e
	   (lambda ()
	     (error 'parse
		    (format "I can't recognize this: ~s" e)))))))


(define extend-env
	(lambda (args env)
		(cons args env)))

(define search-in-params
	(lambda (p params found not_found)
		(cond ((null? params) (not_found))
				((eq? (car params) p) (found 0))
			(else (search-in-params p (cdr params)
					(lambda (mini) (found (+ 1 mini)))
					not_found)))))
					
(define search-in-env
	(lambda (p env found not_found)
		(if (null? env)
			(not_found)
			(search-in-params p (car env)
				(lambda (mini) (found 0 mini))
				(lambda () 
					(search-in-env p (cdr env)
						(lambda (maj mini)
							(found (+ 1 maj) mini))
						not_found))))))

(define unite-length 
	(lambda (toUnite len)
		(make-list (length len) toUnite)))

(define pe->lex-pe (letrec ((run (lambda(pe params env)
                                   (cond  ((not (pair? pe)) '())   
                                          ;CONST
                                          ((eq? (car pe) 'const) pe)
                                          ;IF
                                          ((eq? (car pe) 'if3) 
                                           (with pe (lambda(_ test dit dif)
                                                      `(if3 ,(run test params env)
                                                             ,(run dit params env)
                                                             ,(run dif params env)))))
                                          ;SEQ
                                          ((eq? (car pe) 'seq)
                                           (with pe (lambda(_ bodies)
                                                      `(seq ,(map (lambda(pe)(run pe params env)) bodies)))))
                                          ;DEFINE
                                          ((eq? (car pe) 'define)
                                           (with pe (lambda(_ var def)
                                                      `(define ,(run var params env) ,(run def params env)))))
                                          ;OR
                                          ((eq? (car pe) 'or) 
                                           (with pe (lambda(_ conditions)
                                                      `(or ,(map (lambda(pe)(run pe params env)) conditions)))))
                                          ;APPLIC
                                          ((eq? (car pe) 'applic)
                                           (with pe (lambda(_ fun args)
                                                      `(applic ,(run fun params env) ,(run args params env)))))
                                          ;VAR                                          
                                          ((eq? (car pe) 'var) 
                                           (with pe (lambda(_ v)
                                                      (search-in-rib v params
                                                                     (lambda(min) `(pvar ,v ,min))
                                                                     (lambda() (search-in-ribs v env
                                                                                               (lambda(maj min)
                                                                                                 `(bvar ,v ,maj ,min))
                                                                                               (lambda() `(fvar ,v))))))))
                                          ;LAMBDA-SIMPLE
                                          ((eq? (car pe) 'lambda-simple)
                                           (with pe (lambda(_ argl body)
                                                      `(lambda-simple ,argl ,(run body argl (cons params env))))))
                                          ;LAMBDA-OPT
                                          ((eq? (car pe) 'lambda-opt)
                                           (with pe (lambda(_ argl opt body)
                                                      (let ((args `(,@argl ,opt)))
                                                        `(lambda-opt ,argl ,opt ,(run body args (cons params env)))))))
                                          ;LAMBDA-VARIADIC
                                          ((eq? (car pe) 'lambda-variadic)
                                           (with pe (lambda(_ v body)
                                                      `(lambda-variadic ,v ,(run body (cons v '()) (cons params env))))))
                                          ;LIST
                                          (else `,(map (lambda(pe)(run pe params env)) pe))
                                          ))))
                     (lambda(pe)
                       (run pe '() '()))))



(define search-in-rib (lambda (v rib ret-min ret-nf)
                        (cond ((null? rib) (ret-nf))
                              ((eq? (car rib) v) (ret-min 0))
                              (else (search-in-rib v 
                                                   (cdr rib) 
                                                   (lambda(min) (ret-min (+ 1 min)))
                                                   ret-nf)))))

(define search-in-ribs (lambda(v env ret-maj-min ret-nf)
                         (if (null? env)
                             (ret-nf)
                             (search-in-rib v (car env)
                                            (lambda(min)(ret-maj-min 0 min))
                                            (lambda() (search-in-ribs v 
                                                                      (cdr env)
                                                                      (lambda(maj min)
                                                                        (ret-maj-min (+ 1 maj) min))
                                                                      ret-nf))))))

(define annotate-tc
  (letrec ((run 
	(lambda (pe in_tp?)
		(cond 	
			((not (list? pe)) pe)
			((null? pe) pe)
			((or
				 (eq? (car pe) 'var)
				 (eq? (car pe) 'fvar)
				 (eq? (car pe) 'bvar)
				 (eq? (car pe) 'pvar)) pe)
			;;;;const
			((eq? (car pe) 'const) (map add-to-constant-table (reverse (topo-const-sort (cadr pe)))) pe) ;add-to-constant-table and then retrns it regulaly
			;;;;or
			((eq? (car pe) 'or)
				(with pe 
					(lambda (first expr)
						(let ((last_expr (car (reverse expr)))
						    (first_exprs (reverse (cdr (reverse expr)))))
							`(or ,(append (map (lambda (pe tp) (run pe tp)) first_exprs (unite-length #f first_exprs)) (list (run last_expr in_tp?))))))))
							
			;;;;seq					
			((eq? (car pe) 'seq)
				(with pe 
					(lambda (first expr)
						(let ((last_expr (car (reverse expr)))
							(first_exprs (reverse (cdr (reverse expr)))))
							`(seq ,(append (map (lambda (pe tp) (run pe tp)) first_exprs (unite-length #f first_exprs))	(list (run last_expr in_tp?))))))))
			;;;;define (define x 4) => (define (fvar x) 4)
			((eq? (car pe) 'define)
				(with pe (lambda (first fvar expr)									
								 (add-to-fvar-table (cadr fvar)) ;(fvar x)								 
								`(define ,fvar ,(run expr #f)))))
			;;;;lambda-simple				
			((eq? (car pe) 'lambda-simple)
				(with pe (lambda (first args body)
								`(lambda-simple ,args ,(run body #t)))))
			;;;;lambda-opt				
			((eq? (car pe) 'lambda-opt)
				(with pe (lambda (first args rest body)
								`(lambda-opt ,args ,rest ,(run body #t)))))
			;;;;lambda-variadic				
			((eq? (car pe) 'lambda-variadic)
				(with pe (lambda (first args body)
								`(lambda-variadic ,args ,(run body #t)))))			
			;;;;if
			((eq? (car pe) 'if3)
				(with pe (lambda (first test dit dif)
							`(if3 ,(run test #f)
							,(run dit in_tp?)
							,(run dif in_tp?))))) 							
			;;;;applic
			((eq? (car pe) 'applic)
				(with pe (lambda (first app args)
							(let ((new_app (run app #f))
								 (new_args (map (lambda (arg) (run arg #f)) args)))
							`(,(if in_tp? `tc-applic `applic) 
								,new_app ,new_args)))))
	 			))))
  (lambda (pe)
	(run pe #f) )))
	
;********************* end of parser ******************

;********************* file handlers *****************
(define file->sexprs
	(lambda (fileName)
		(let ((input (open-input-file fileName)))
			(letrec ((run	
						(lambda ()
							(let ((e (read input)))
								(if (eof-object? e)
									(begin (close-input-port input)
										   '())
									(cons e (run)))))))
				(run)))))
				
(define code->file
	(lambda (code fileName)
		(if (file-exists? fileName)
			(delete-file fileName)
			#f)
			(let ((outFile (open-output-file fileName)))
				(display code outFile)
				(close-output-port outFile))))

				 
			
(define full-parse
  (lambda (e)
    (annotate-tc
      (pe->lex-pe
		(parse e)))))
		


		
;******************************* fvar table ************************;
;******************************* constant table ************************;
(define heap-counter 10)
(define constant-table `())
(define fvar-table `())
(define primitive-table `())

(define initialize-constant-table
	(lambda ()
		(set! constant-table `(
							(10 ,(void) ("T_VOID"))
							(11 () ("T_NIL"))
							(12 #f ("T_BOOL" 0))
							(14 #t ("T_BOOL" 1))))
		(set! heap-counter 16)))
		
;;primitives: 
;;support code: error display < >
  

		
(define primitive-table-names '(
list?
>
<
=
*
/
-
+
display
eq?
string->symbol 
apply
vector-ref 
string-ref
remainder
vector-set!
string-set!
bin<?
bin=?
bin+
bin-
bin*
bin/
symbol->string
make-vector
integer->char
char->integer
make-string 
string-length
set-cdr!
set-car!
vector-length
zero?
cons
car
cdr
boolean?
char?
integer?
null?
number?
pair?
procedure?
symbol?
vector?
string?
))		

(define initialize-primitive-table
	(lambda ()
		(map add-to-primitive-table primitive-table-names)))

(define labelize
	(lambda (symb)
		(let ((lst (string->list (symbol->string symb))))
			(list->string (map (lambda (char) (cond 
									((equal? #\? char) #\_)
									((equal? #\- char) #\_)
									((equal? #\! char) #\_)
									((equal? #\= char) #\E)
									((equal? #\> char) #\X)
									((equal? #\< char) #\x)
									((equal? #\+ char) #\A)
									((equal? #\- char) #\S)
									((equal? #\* char) #\M)
									((equal? #\/ char) #\D)
									(else char))) lst)))))

				
		
(define add-to-primitive-table
	(lambda (expr)
		(set! primitive-table (append primitive-table (list `(,heap-counter ,expr ("T_CLOSURE" "301858270" ,(string-append "LABEL(PRIM_" (labelize expr) ")"))))))
		(set! heap-counter (+ 3 heap-counter))))
		
(define add-to-fvar-table
	(lambda (expr)
		(if (not (lookup expr fvar-table))
			(begin
				(set! fvar-table (append fvar-table (list `(,heap-counter ,expr ("T_UNDEF")))))
				(set! heap-counter (+ 1 heap-counter))))))

(define add-to-constant-table
	(lambda (expr) ;if fvar = null? normal constant. if not- it is a fvar.
		(cond 
			((lookup expr constant-table) '())
			((number? expr)  (add-number expr))
			((string? expr) (add-string expr))
			((pair? expr) (add-pair expr))
			((char? expr) (add-char expr))
			((symbol? expr) (add-string (symbol->string expr)) (add-symbol expr))
			((vector? expr) (map add-to-constant-table (vector->list expr)) (add-vector expr))			
			(else (format "unknown constant: ~s" expr)))))		

(define add-vector
	(lambda (expr)
		(set! constant-table (append constant-table (list `(,heap-counter ,expr ("T_VECTOR" ,(vector-length expr) ,@(vector-addresses (vector->list expr)))))))
		(set! heap-counter (+ 2 (vector-length expr) heap-counter))))
			
(define add-symbol
	(lambda (expr)
		(set! constant-table (append constant-table (list `(,heap-counter ,expr ("T_SYMBOL" ,(lookup (symbol->string expr) constant-table))))))
		(set! heap-counter (+ 2 heap-counter))))
			
(define add-char 
	(lambda (expr)
		(set! constant-table (append constant-table (list `(,heap-counter ,expr ("T_CHAR" ,(char->integer expr))))))
		(set! heap-counter (+ 2 heap-counter))))
			
(define add-pair
	(lambda (expr)
		(set! constant-table (append constant-table (list `(,heap-counter ,expr ("T_PAIR" ,(lookup (car expr) constant-table ) ,(lookup (cdr expr) constant-table))))))
		(set! heap-counter (+ 3 heap-counter))))
			
(define add-number
	(lambda (expr)
		(set! constant-table (append constant-table (list `(,heap-counter ,expr ("T_INTEGER" ,expr)))))
		(set! heap-counter (+ 2 heap-counter))))
		
(define add-string
	(lambda (expr)
		(set! constant-table (append constant-table (list `(,heap-counter ,expr ("T_STRING" ,(string-length expr) ,@(map char->integer (string->list expr)))))))
		(set! heap-counter (+ 2 (string-length expr) heap-counter))))
		

(define lookup
	(lambda (expr lst)
		(cond
			((null? lst) #f)
			((equal? expr (cadr (car lst))) (caar lst))				
			(else (lookup expr (cdr lst))))))
		
(define topo-const-sort
  (lambda (e)
    (cond ((pair? e) `(,@(topo-const-sort (car e)),@(topo-const-sort(cdr e)),e))
          ((vector? e) `(,@(apply append (map topo-const-sort (vector->list e))) ,e))
          (else `(,e)))))


;assumes all the vector elements are in the constant list already. returns a list of ordered addresses of the vector elements.
(define vector-addresses
	(lambda (lst)
		(if (null? lst)
			'()
			(cons (lookup (car lst) constant-table) (vector-addresses (cdr lst))))))
			
;******************************* constant table end ************************;			


;******************************* code generator ******************;
(define nl (list->string (list #\newline)))
(define tb (list->string (list #\tab)))
(define ntb (list->string (list #\newline #\tab)))

	
(define list->cArray
  (lambda (consts)    
    ;(apply string-append (cdr (apply append (map (lambda (v) (list ", " (number->string v))) (apply append (map caddr consts))))))))
	(apply string-append (cdr (apply append (map (lambda (v) (list ", " 
	(cond 
		((number? v) (number->string v))
		((symbol? v) (display "hi\n") (symbol->string v))
		(else v)))) (apply append (map caddr consts))))))))
	
(define make-skeleton-up
	(lambda ()
		(string-append
			"#include <stdio.h>" nl
			"#include <stdlib.h>" nl
			"#include \"arch/cisc.h\"" nl nl 
			
			"/* change to 0 for no debug info to be printed: */" nl
			"#define DO_SHOW 1" nl nl					
			
			"int main(){" nl
				"START_MACHINE;" nl nl
				
				"JUMP(CONTINUE);" nl nl
				"#include \"arch/debug.h\"" nl
				"#include \"arch/char.lib\"" nl
				"#include \"arch/io.lib\"" nl
				"#include \"arch/math.lib\"" nl
				"#include \"arch/string.lib\"" nl
				"#include \"arch/system.lib\"" nl
				"#include \"arch/scheme.lib\"" nl
				"#include \"arch/init.h\"" nl	
				"#include \"arch/errors.h\"" nl
				"#include \"arch/primitives.h\"" nl		
	
				"CONTINUE:" nl	
				"INIT_ENVIRONMENT;" nl ;create the first frame.	
				
				;"printf(\"initial SP = %ld\\n\", SP);" nl
				;"printf(\"initial FP = %ld\\n\", FP);" nl
				"const long a[]= { " (list->cArray (sort (lambda (x y) (<= (car x) (car y))) (append constant-table fvar-table primitive-table))) "};" nl 
				"memcpy(&(IND(10)),a,sizeof(a));"nl
				"MOV(IND(0), IMM(" (number->string heap-counter) ")); //next free address" nl				
				"INIT_TOP_LEVEL;" nl
				"MOV(R0,SOB_VOID);" nl
				
				
				
				
				
				
				

	
				)))


(define make-skeleton-down
	(lambda ()
		(string-append		
			;"printf(\"final SP = %ld\\n\", SP);" nl
			;"printf(\"final FP = %ld\\n\", FP);" nl
			;"printStack(machine, 20);" nl
			;"printMemory(machine, 200);" nl
			"PUSH(R0);" nl
			"CALL(WRITE_SOB);" nl
			"DROP(1);" nl
			"STOP_MACHINE;" nl	
			"return 0;" nl
			"}" nl
			)))

(define ^^label
	(lambda (name)
		(let ((n 0))
			(lambda ()
				(set! n (+ n 1))
				(string-append name
							   (number->string n))))))
;labels:
(define ^label-if3start (^^label "Lif3start"))
(define ^label-if3else (^^label "Lif3else"))
(define ^label-if3exit (^^label "Lif3exit"))
(define ^label-or-exit (^^label "orExit"))
(define ^label-or-start (^^label "orStart"))

                    

(define cg-if 
  (lambda (e)
    (with e
          (lambda (tag test do-if-true do-if-false)		                		  
            (let ((code-test (code-gen test))
                  (code-dit (code-gen do-if-true))
                  (code-dif (code-gen do-if-false))
                  (label-if (^label-if3start))
                  (label-else (^label-if3else))
                  (label-exit (^label-if3exit)))

			  (string-append
               label-if ":" nl
               code-test nl ; when run, the result of the test will be in R0
               "CMP(R0, SOB_BOOLEAN_FALSE);" nl
               "JUMP_EQ(" label-else ");" nl
               code-dit nl
               "JUMP(" label-exit ");" nl
               label-else ":" nl
               code-dif nl
               label-exit ":" nl))))))
				
					
(define cg-const	
	(lambda (e)
		(with e
			(lambda (tag const)
				(string-append
					"			//const-start" nl
					"MOV(R0," (number->string (lookup const constant-table)) ");" nl
					"			//const-end" nl)))))
	
(define cg-seq 
	(lambda (e)
		(with e
			(lambda (tag bodies)			
				(apply string-append (map code-gen bodies))))))

(define cg-or 
	(lambda (e)
		(with e 
			(lambda (tag or_exps)
				(let* ((label-start (^label-or-start))
					   (label-end  (^label-or-exit))
					   (op (string-append "CMP (R0,SOB_BOOLEAN_FALSE);" nl
										  "JUMP_NE (" label-end ");" nl)))
				  (string-append label-start ":" nl
								 (apply string-append (map (lambda (or_exp)
                                                                     (string-append (code-gen or_exp)  op))
                                                                   or_exps)) nl 
								label-end ":" nl))))))

						
(define cg-define
	(lambda (e)
		(with e
			(lambda (tag var definition)							
				(string-append					
					"			//define start" nl					
					(code-gen definition) nl					
					"MOV(IND(" (number->string (lookup (cadr var) fvar-table)) "), R0);" nl ;'free_var flag because not to mix with other constants.
					"MOV(R0,SOB_VOID);" nl
					"			//define end" nl 
					)))))

;problem: this allows define within define. 				

(define cg-applic
	(lambda (e)		
		(with e
			(lambda (tag procedure args)
				
				(string-append
					"			//applic start" nl
					"PUSH(SOB_NIL);" nl
					(apply string-append (seq_map (lambda (arg) (string-append arg "PUSH(R0);" nl)) (map code-gen args) 'reverse_flag)); push args backwards
					"PUSH(IMM(" (number->string (length args)) "));" nl
					(code-gen procedure) nl										
					"CMP(INDD(R0,0), T_CLOSURE);" nl
					"JUMP_NE ( error_not_a_procedure );" nl
					"PUSH(INDD(R0,1));" nl
					"CALLA(INDD(R0,2));" nl
					"DROP(STARG(0)+3);" nl
					"			//applic end" nl
					)))))
					
(define ^shift_stack_loop_start (^^label "shift_stack_loop_start"))
(define ^shift_stack_loop_end (^^label "shift_stack_loop_end"))
					
(define cg-tc-applic
	(lambda (e)		
		(with e
			(lambda (tag procedure args)
				(if (equal? (cadr procedure) 'apply) 
					(cg-applic e)
				(let ((shift_stack_loop_start (^shift_stack_loop_start))
					  (shift_stack_loop_end (^shift_stack_loop_end)))				
				(string-append
					"			//tc-applic start" nl
					"PUSH(SOB_NIL);" nl
					(apply string-append (seq_map (lambda (arg) (string-append arg "PUSH(R0);" nl)) (map code-gen args) 'reverse_flag)); push args backwards
					"PUSH(IMM(" (number->string (length args)) "));" nl
					(code-gen procedure) nl
					"CMP(INDD(R0,0), T_CLOSURE);" nl
					"JUMP_NE ( error_not_a_procedure );" nl
					"PUSH (INDD(R0,1));" nl 
					"PUSH(FPARG(-1));//push the return address so that after overriding the frame there will be the ret " nl
					"MOV(R3," (number->string (+ (length args) 4)) ");" nl
					;SHIFT STACK
					"MOV(R15,FPARG(-2));" nl
					"MOV(R14,FPARG(1) + 2);" nl
					"MOV(R2,0);	" nl
					shift_stack_loop_start ":" nl
					"CMP(R2,R3);" nl
					"JUMP_EQ(" shift_stack_loop_end ");" nl			
					"MOV(FPARG(R14 - R2), STACK(SP -(R3-R2)));" nl
					"INCR(R2);"
					"JUMP( " shift_stack_loop_start ");" nl										
					shift_stack_loop_end ":" nl
					"MOV(SP,FP -3 -(R14 - R2));" nl
					"MOV(FP , R15);" nl
					"JUMPA(INDD(R0,2));" nl
					)))))))
					
					
;;lambda simple
(define env-size 1)
(define ^closure_simple_start (^^label "closure_simple_start"))
(define ^closure_simple_exit (^^label "closure_simple_exit")) 
(define ^closure_simple_code (^^label "closure_simple_code")) 			
(define ^loop1_simple_start (^^label "loop1_simple_start"))
(define ^loop1_simple_end (^^label "loop1_simple_end"))
(define ^loop2_simple_start (^^label "loop2_simple_start"))
(define ^loop2_simple_end (^^label "loop2_simple_end"))

(define cg-lambda-simple
  (lambda (e)	
    (with e (lambda (tag args body) 
				(let* ((loop1_simple_start (^loop1_simple_start))
					  (loop1_simple_end (^loop1_simple_end))
					  (loop2_simple_start (^loop2_simple_start))
					  (loop2_simple_end (^loop2_simple_end))
					  (closure_simple_start (^closure_simple_start))
					  (closure_simple_exit (^closure_simple_exit))
					  (closure_simple_code (^closure_simple_code))					  
					  (delayed_code (lambda () (code-gen body)))
					  (increase-env-size (set! env-size (+ env-size 1)))
					  (code (delayed_code))					  
					  (decrease-env-size (set! env-size (- env-size 1))))				
					(string-append					
						"			//closure code gen start" nl
						closure_simple_start ":" nl nl
						"			//R1 <= malloc(|env|+1) new env" nl
						"PUSH(" (number->string (+ 1 env-size)) ");" nl
						"CALL(MALLOC);" nl
						"DROP(1);" nl
						"MOV(R1,R0);" nl nl
						
						"			//R2 <= old env" nl
						"MOV(R2, FPARG(0));" nl nl
						
						"			//reserve registers" nl

						
						"			//copy old env to new env" nl
						"MOV(R10,IMM(0));" nl ;i=0
						"MOV(R11,IMM(1));" nl ;j=1
						loop1_simple_start ":" nl
						"CMP(R10," (number->string env-size) ");" nl
						"JUMP_EQ(" loop1_simple_end ");" nl
						"MOV(INDD(R1,R11), INDD(R2,R10));" nl
						"ADD(R10, IMM(1));" nl
						"ADD(R11, IMM(1));" nl
						"JUMP( " loop1_simple_start ");" nl						
						loop1_simple_end ":" nl nl
						
						"			//R3 <= malloc(|n|); the new cell " nl
						"PUSH(FPARG(1));" nl
						"CALL(MALLOC);" nl
						"DROP(IMM(1));" nl
						"MOV(R3,R0);" nl
						"MOV(INDD(R1,0), R3);" nl 
						
						"			//copy parameters fro stack to be new bound variables" nl
						"MOV(R10, IMM(0));" nl
						loop2_simple_start ":" nl
						"CMP(R10, FPARG(1));" nl
						"JUMP_EQ(" loop2_simple_end ");" nl
						"MOV(INDD(R3,R10), FPARG(2+R10));" nl
						"ADD(R10,IMM(1));" nl
						"JUMP( " loop2_simple_start ");" nl
						loop2_simple_end ":" nl nl
						
						"			//begin closure construction" nl
						"PUSH(IMM(3));" nl
						"CALL(MALLOC);" nl
						"DROP(IMM(1));" nl
						"MOV(INDD(R0,0), T_CLOSURE);" nl
						"MOV(INDD(R0,1), R1);" nl
						"MOV(INDD(R0,2), LABEL(" closure_simple_code "));" nl nl
						
						"			//restore register" nl

						
						"			//finish closure construction" nl
						"JUMP(" closure_simple_exit ");" nl
						"			//begin closure code" nl
						closure_simple_code ":" nl
						"PUSH(FP);" nl
						"MOV(FP, SP);" nl
						
						
						code
						
						"POP(FP);" nl
						"RETURN" nl
						"			//finish closure code" nl
						"			//closure code gen end" nl
						closure_simple_exit ":" nl))))))
						
						

(define ^closure_opt_start (^^label "closure_opt_start"))
(define ^closure_opt_exit (^^label "closure_opt_exit")) 
(define ^closure_opt_code (^^label "closure_opt_code")) 			
(define ^loop1_opt_start (^^label "loop1_opt_start"))
(define ^loop1_opt_end (^^label "loop1_opt_end"))
(define ^loop2_opt_start (^^label "loop2_opt_start"))
(define ^loop2_opt_end (^^label "loop2_opt_end"))	
(define ^loop3_opt_start (^^label "loop3_opt_start"))
(define ^loop3_opt_end (^^label "loop3_opt_end"))
(define ^loop4_opt_start (^^label "loop4_opt_start"))
(define ^loop4_opt_end (^^label "loop4_opt_end"))
(define ^fix_opt_start (^^label "fix_opt_start"))
(define ^fix_opt_end (^^label "fix_opt_end"))						
						
(define cg-lambda-opt
  (lambda (e)	
    (with e (lambda (tag params opt_param body)
				(let* ((loop1_opt_start (^loop1_opt_start))
					  (loop1_opt_end (^loop1_opt_end))
					  (loop2_opt_start (^loop2_opt_start))
					  (loop2_opt_end (^loop2_opt_end))
					  (loop3_opt_start (^loop3_opt_start))
					  (loop3_opt_end (^loop3_opt_end))
					  (loop4_opt_start (^loop4_opt_start))
					  (loop4_opt_end (^loop4_opt_end))
					  (fix_opt_start (^fix_opt_start))
					  (fix_opt_end (^fix_opt_end))
					  (closure_opt_start (^closure_opt_start))
					  (closure_opt_exit (^closure_opt_exit))
					  (closure_opt_code (^closure_opt_code))					  
					  (delayed_code (lambda () (code-gen body)))
					  (increase-env-size (set! env-size (+ env-size 1)))
					  (code (delayed_code))					  
					  (decrease-env-size (set! env-size (- env-size 1))))
					  
					(string-append					
						"			//closure code gen start" nl
						closure_opt_start ":" nl nl
						"			//R1 <= malloc(|env|+1) new env" nl
						"PUSH(" (number->string (+ 1 env-size)) ");" nl
						"CALL(MALLOC);" nl
						"DROP(1);" nl
						"MOV(R1,R0);" nl nl
						
						"			//R2 <= old env" nl
						"MOV(R2, FPARG(0));" nl nl
						
						"			//reserve registers" nl

						
						"			//copy old env to new env" nl
						"MOV(R10,IMM(0));" nl ;i=0
						"MOV(R11,IMM(1));" nl ;j=1
						loop1_opt_start ":" nl
						"CMP(R10," (number->string env-size) ");" nl
						"JUMP_EQ(" loop1_opt_end ");" nl
						"MOV(INDD(R1,R11), INDD(R2,R10));" nl
						"ADD(R10, IMM(1));" nl
						"ADD(R11, IMM(1));" nl
						"JUMP( " loop1_opt_start ");" nl						
						loop1_opt_end ":" nl nl
						
						"			//R3 <= malloc(|n|); the new cell " nl
						"PUSH(FPARG(1));" nl
						"CALL(MALLOC);" nl
						"DROP(IMM(1));" nl
						"MOV(R3,R0);" nl
						"MOV(INDD(R1,0), R3);" nl 
						
						"			//copy parameters fro stack to be new bound variables" nl
						"MOV(R10, IMM(0));" nl
						loop2_opt_start ":" nl
						"CMP(R10, FPARG(1));" nl
						"JUMP_EQ(" loop2_opt_end ");" nl
						"MOV(INDD(R3,R10), FPARG(2+R10));" nl
						"ADD(R10,IMM(1));" nl
						"JUMP( " loop2_opt_start ");" nl
						loop2_opt_end ":" nl nl
						
						"			//begin closure construction" nl
						"PUSH(IMM(3));" nl
						"CALL(MALLOC);" nl
						"DROP(IMM(1));" nl
						"MOV(INDD(R0,0), T_CLOSURE);" nl
						"MOV(INDD(R0,1), R1);" nl
						"MOV(INDD(R0,2), LABEL(" closure_opt_code "));" nl nl
						
						"			//restore register" nl
						
						
						"			//finish closure construction" nl
						"JUMP(" closure_opt_exit ");" nl
						"			//begin closure code" nl
						closure_opt_code ":" nl
						"PUSH(FP);" nl
						"MOV(FP, SP);" nl

						
						"			//fix stack start" nl
						fix_opt_start ":" nl
						"MOV(R2, FPARG(1));" nl
						"MOV(R3," (number->string (length params)) ");" nl
						"CMP(R3,R2);" nl
						"JUMP_EQ(" fix_opt_end ")" nl
						"MOV(R1,FPARG(R2+1));" nl ;fix nesting
						"PUSH(IMM(SOB_NIL));" nl
						"PUSH(R1);" nl
						"CALL(MAKE_SOB_PAIR);" nl
						"DROP(IMM(2));" nl
						"MOV(R1,R0);" nl
												
						"MOV(R10,R2);" nl		
						loop3_opt_start ":" nl
						"CMP(R10,(R3+1));" nl ;fix nesting
						"JUMP_EQ(" loop3_opt_end ");" nl
						"PUSH(R1);" nl
						"PUSH(FPARG(R10));" nl ;fix nesting
						"CALL(MAKE_SOB_PAIR);" nl
						"DROP(IMM(2));" nl
						"MOV(R1,R0);" nl
						"DECR(R10);" nl
						"JUMP(" loop3_opt_start ");" nl
						loop3_opt_end ":" nl nl
						
						"MOV(FPARG(R2+2), R1);" nl
						
						"MOV(R10,(R2+1));" nl ;nesting
						"MOV(R11,(R3+1));" nl ;nesting
						loop4_opt_start ":" nl
						"CMP(R11,IMM(-2));" nl
						"JUMP_EQ(" loop4_opt_end ");" nl
						"MOV(FPARG(R10), FPARG(R11));" nl ;nesting
						"DECR(R10);" nl
						"DECR(R11);" nl
						"JUMP(" loop4_opt_start ");" nl
						loop4_opt_end ":" nl nl
						
						
						"SUB(R2,R3);" nl
						"DROP(R2);" nl
						"MOV(FP,SP);" nl
						"MOV(FPARG(1), R3);" nl
						fix_opt_end ":" nl
						"			//fix stack end" nl						

						code
						
						
						"POP(FP);" nl
						"RETURN" nl
						"			//finish closure code" nl
						"			//closure code gen end" nl
						closure_opt_exit ":" nl))))))	

(define ^closure_variadic_start (^^label "closure_variadic_start"))
(define ^closure_variadic_exit (^^label "closure_variadic_exit")) 
(define ^closure_variadic_code (^^label "closure_variadic_code")) 			
(define ^loop1_variadic_start (^^label "loop1_variadic_start"))
(define ^loop1_variadic_end (^^label "loop1_variadic_end"))
(define ^loop2_variadic_start (^^label "loop2_variadic_start"))
(define ^loop2_variadic_end (^^label "loop2_variadic_end"))	
(define ^loop3_variadic_start (^^label "loop3_variadic_start"))
(define ^loop3_variadic_end (^^label "loop3_variadic_end"))
(define ^loop4_variadic_start (^^label "loop4_variadic_start"))
(define ^loop4_variadic_end (^^label "loop4_variadic_end"))
(define ^fix_variadic_start (^^label "fix_variadic_start"))
(define ^fix_variadic_end (^^label "fix_variadic_end"))						
						
(define cg-lambda-variadic
  (lambda (e)	
    (with e (lambda (tag variadic_param body)
	
				(let* ((loop1_variadic_start (^loop1_variadic_start))
					  (loop1_variadic_end (^loop1_variadic_end))
					  (loop2_variadic_start (^loop2_variadic_start))
					  (loop2_variadic_end (^loop2_variadic_end))
					  (loop3_variadic_start (^loop3_variadic_start))
					  (loop3_variadic_end (^loop3_variadic_end))
					  (loop4_variadic_start (^loop4_variadic_start))
					  (loop4_variadic_end (^loop4_variadic_end))
					  (fix_variadic_start (^fix_variadic_start))
					  (fix_variadic_end (^fix_variadic_end))
					  (closure_variadic_start (^closure_variadic_start))
					  (closure_variadic_exit (^closure_variadic_exit))
					  (closure_variadic_code (^closure_variadic_code))					  
					  (delayed_code (lambda () (code-gen body)))
					  (increase-env-size (set! env-size (+ env-size 1)))
					  (code (delayed_code))					  
					  (decrease-env-size (set! env-size (- env-size 1))))
					 
					(string-append					
						"			//closure code gen start" nl
						closure_variadic_start ":" nl nl
						"			//R1 <= malloc(|env|+1) new env" nl
						"PUSH(" (number->string (+ 1 env-size)) ");" nl
						"CALL(MALLOC);" nl
						"DROP(1);" nl
						"MOV(R1,R0);" nl nl
						
						"			//R2 <= old env" nl
						"MOV(R2, FPARG(0));" nl nl
						
						"			//reserve registers" nl

						
						"			//copy old env to new env" nl
						"MOV(R10,IMM(0));" nl ;i=0
						"MOV(R11,IMM(1));" nl ;j=1
						loop1_variadic_start ":" nl
						"CMP(R10," (number->string env-size) ");" nl
						"JUMP_EQ(" loop1_variadic_end ");" nl
						"MOV(INDD(R1,R11), INDD(R2,R10));" nl
						"ADD(R10, IMM(1));" nl
						"ADD(R11, IMM(1));" nl
						"JUMP( " loop1_variadic_start ");" nl						
						loop1_variadic_end ":" nl nl
						
						"			//R3 <= malloc(|n|); the new cell " nl
						"PUSH(FPARG(1));" nl
						"CALL(MALLOC);" nl
						"DROP(IMM(1));" nl
						"MOV(R3,R0);" nl
						"MOV(INDD(R1,0), R3);" nl 
						
						"			//copy parameters fro stack to be new bound variables" nl
						"MOV(R10, IMM(0));" nl
						loop2_variadic_start ":" nl
						"CMP(R10, FPARG(1));" nl
						"JUMP_EQ(" loop2_variadic_end ");" nl
						"MOV(INDD(R3,R10), FPARG(2+R10));" nl
						"ADD(R10,IMM(1));" nl
						"JUMP( " loop2_variadic_start ");" nl
						loop2_variadic_end ":" nl nl
						
						"			//begin closure construction" nl
						"PUSH(IMM(3));" nl
						"CALL(MALLOC);" nl
						"DROP(IMM(1));" nl
						"MOV(INDD(R0,0), T_CLOSURE);" nl
						"MOV(INDD(R0,1), R1);" nl
						"MOV(INDD(R0,2), LABEL(" closure_variadic_code "));" nl nl
						
						"			//restore register" nl
						
						
						"			//finish closure construction" nl
						"JUMP(" closure_variadic_exit ");" nl
						"			//begin closure code" nl
						closure_variadic_code ":" nl
						"PUSH(FP);" nl
						"MOV(FP, SP);" nl	

					
						"			//fix stack start" nl
						fix_variadic_start ":" nl
						"MOV(R2, FPARG(1));" nl						
						"CMP(R2,IMM(0));" nl
						"JUMP_EQ(" fix_variadic_end ")" nl
						"MOV(R1,FPARG(R2+1));" nl ;fix nesting
						"PUSH(IMM(SOB_NIL));" nl
						"PUSH(R1);" nl
						"CALL(MAKE_SOB_PAIR);" nl
						"DROP(IMM(2));" nl
						"MOV(R1,R0);" nl
												
						"MOV(R10,R2);" nl		
						loop3_variadic_start ":" nl
						"CMP(R10,IMM(1));" nl 
						"JUMP_EQ(" loop3_variadic_end ");" nl
						"PUSH(R1);" nl
						"PUSH(FPARG(R10));" nl ;fix nesting
						"CALL(MAKE_SOB_PAIR);" nl
						"DROP(IMM(2));" nl
						"MOV(R1,R0);" nl
						"DECR(R10);" nl
						"JUMP(" loop3_variadic_start ");" nl
						loop3_variadic_end ":" nl nl
						
						"MOV(FPARG(R2+2), R1);" nl ;NESTING
						
						;FIX STACK
						"MOV(FPARG(R2+2), R1);" nl
						"MOV(FPARG(R2+1), IMM(0));" nl
						"MOV(FPARG(R2), FPARG(0));" nl
						"MOV(FPARG(R2-1), FPARG(-1));" nl
						"MOV(FPARG(R2-2), FPARG(-2));" nl																		
						"DROP(R2);" nl
						"MOV(FP,SP);" nl						
						fix_variadic_end ":" nl
						"			//fix stack end" nl						

						code
						
						
						"POP(FP);" nl
						"RETURN;" nl
						"			//finish closure code" nl
						"			//closure code gen end" nl
						closure_variadic_exit ":" nl))))))	

						
(define cg-pvar
	(lambda (e)
		(with e
			(lambda (tag var index)
				(string-append 
					"MOV(R0,FPARG(2+" (number->string index) "));" nl)))))
					
(define cg-bvar
	(lambda (e)
		(with e
			(lambda (tag var major minor)
				(string-append
					"MOV(R0, FPARG(0));" nl
					"MOV(R0, INDD(R0, " (number->string major) "));" nl
					"MOV(R0, INDD(R0, " (number->string minor) "));" nl)))))
					
(define cg-fvar
	(lambda (e)
		(with e
			(lambda (tag fvar)				
				(let ((address_in_fvar_table (lookup fvar fvar-table))
					  (address_in_primitive_table (lookup fvar primitive-table)))
					(cond
						(address_in_fvar_table 	(string-append "MOV(R0, IND(" (number->string address_in_fvar_table) "));" nl))
						(address_in_primitive_table (string-append "MOV(R0, " (number->string address_in_primitive_table) ");" nl))
					    (else (error 'code-gen  (format "Undefined variable: \"~a\"" fvar)))))))))
					
			
(define code-gen
	(lambda (pe)			
	    (cond			
			((not (pair? pe)) "")
			((eq? 'const (car pe)) (cg-const pe))
			((eq? 'if3 (car pe)) (cg-if pe))
			((eq? 'seq (car pe)) (cg-seq pe))			
			((eq? 'or (car pe)) (cg-or pe))
			((eq? 'define (car pe)) (cg-define pe))
			((eq? 'applic (car pe)) (cg-applic pe))		
			((eq? 'tc-applic (car pe)) (cg-tc-applic pe))		;test
			((eq? 'lambda-simple (car pe)) (cg-lambda-simple pe))
			((eq? 'lambda-opt (car pe)) (cg-lambda-opt pe))
			((eq? 'lambda-variadic (car pe)) (cg-lambda-variadic pe))
			((eq? 'pvar (car pe)) (cg-pvar pe))
			((eq? 'bvar (car pe)) (cg-bvar pe))
			((eq? 'fvar (car pe)) (cg-fvar pe))
			(else (error 'code-gen  (format "Can't handle the expression: \"~a\"" pe)) ""))
))
	

;******************************* Main **********************;

(define compile-scheme-file 
	(lambda (inFile outFile)
		(let* ((sexprs (file->sexprs inFile))
			   (init_consts (initialize-constant-table))
			   (init_primitives (initialize-primitive-table))
			   (pe (map full-parse sexprs))
			   (body-code (apply string-append (map code-gen pe)))
			   (skeleton-up (make-skeleton-up))
			   (skeleton-down (make-skeleton-down))
			   (code (string-append skeleton-up body-code skeleton-down))
			   (write-to-file (code->file code outFile)))
			pe)))

;******************************* Main - end **********************;		

	