error_empty_string_to_sym:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('O'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM(':'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('X'));
OUT(IMM(2), IMM('P'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('C'));
OUT(IMM(2), IMM('T'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('D'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('A'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('N'));
OUT(IMM(2), IMM('O'));
OUT(IMM(2), IMM('N'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('M'));
OUT(IMM(2), IMM('P'));
OUT(IMM(2), IMM('T'));
OUT(IMM(2), IMM('Y'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('S'));
OUT(IMM(2), IMM('T'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('I'));
OUT(IMM(2), IMM('N'));
OUT(IMM(2), IMM('G'));

OUT(IMM(2), IMM('\n'));
HALT

error_unknown:
OUT(IMM(2), IMM('E'));
OUT(2, IMM('R'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('O'));
OUT(IMM(2), IMM('R'));

OUT(IMM(2), IMM('\n'));
HALT


error_not_a_list:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('O'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM(':'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('X'));
OUT(IMM(2), IMM('P'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('C'));
OUT(IMM(2), IMM('T'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('D'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('A'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('L'));
OUT(IMM(2), IMM('I'));
OUT(IMM(2), IMM('S'));
OUT(IMM(2), IMM('T'));

OUT(IMM(2), IMM('\n'));
HALT


error_not_a_procedure:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('O'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM(':'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('X'));
OUT(IMM(2), IMM('P'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('C'));
OUT(IMM(2), IMM('T'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('D'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('A'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('C'));
OUT(IMM(2), IMM('L'));
OUT(IMM(2), IMM('O'));
OUT(IMM(2), IMM('S'));
OUT(IMM(2), IMM('U'));
OUT(IMM(2), IMM('R'));
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('\n'));
HALT



error_incorrect_amount_args:
OUT(IMM(2), IMM('I'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('g'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('m'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM('l'));
OUT(IMM(2), IMM('l'));
OUT(IMM(2), IMM('\n'));
HALT

error_divide_by_zero:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('v'));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('s'));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('y'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('z'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('\n'));
HALT


error_not_a_pair:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('P'));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('j'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('\n'));
HALT

error_not_a_char:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('C'));
OUT(IMM(2), IMM('h'));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('j'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('\n'));
HALT

error_not_a_symbol:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('S'));
OUT(IMM(2), IMM('y'));
OUT(IMM(2), IMM('m'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('l'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('j'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('\n'));
HALT

error_not_a_vector:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('V'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('j'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('\n'));
HALT

error_not_a_string:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('S'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('g'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('j'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('\n'));
HALT

error_not_a_integer:
OUT(IMM(2), IMM('E'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('I'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('g'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('j'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('\n'));
HALT

error_bad_index:
OUT(IMM(2), IMM('I'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('x'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('f'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM('\n'));
HALT

error_not_a_char_integer:
OUT(IMM(2), IMM('N'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('v'));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM('l'));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('d'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('f'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('g'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM('-'));
OUT(IMM(2), IMM('>'));
OUT(IMM(2), IMM('c'));
OUT(IMM(2), IMM('h'));
OUT(IMM(2), IMM('a'));
OUT(IMM(2), IMM('r'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM(','));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('i'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM('p'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('m'));
OUT(IMM(2), IMM('u'));
OUT(IMM(2), IMM('s'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('b'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('w'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('e'));
OUT(IMM(2), IMM('n'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('0'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('t'));
OUT(IMM(2), IMM('o'));
OUT(IMM(2), IMM(' '));
OUT(IMM(2), IMM('2'));
OUT(IMM(2), IMM('5'));
OUT(IMM(2), IMM('5'));
OUT(IMM(2), IMM('\n'));
HALT


