CC = gcc
FLEX = flex
BISON = bison

TARGET = guess_number
LEX_FILE = lexer.l
YACC_FILE = parser.y

OBJS = lex.yy.o parser.tab.o

# Aggiungi la directory corrente alle directory di include
INCLUDE_DIR = -I.

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lfl -lm   # Link the math library

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


