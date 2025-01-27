CC = gcc
FLEX = flex
BISON = bison

TARGET = compiler
LEX_FILE = lexer.l
YACC_FILE = parser.y
AST_FILE = abstract_syntax_tree.c
SYM_FILE = symbol_table.c

OBJS = lex.yy.o parser.tab.o abstract_syntax_tree.o symbol_table.o

# Directory include
INCLUDE_DIR = -I.

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lfl -lm   

abstract_syntax_tree.o: abstract_syntax_tree.c abstract_syntax_tree.h
	$(CC) -c $(INCLUDE_DIR) $<

symbol_table.o: symbol_table.c
	$(CC) -c $(INCLUDE_DIR) $<

lex.yy.o: lex.yy.c parser.tab.h abstract_syntax_tree.h
	$(CC) -c $(INCLUDE_DIR) $<

parser.tab.o: parser.tab.c parser.tab.h abstract_syntax_tree.h
	$(CC) -c $(INCLUDE_DIR) $<

lex.yy.c: $(LEX_FILE)
	$(FLEX) -o $@ $<

parser.tab.c parser.tab.h: $(YACC_FILE)
	$(BISON) -d --verbose -o parser.tab.c $< 

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h



