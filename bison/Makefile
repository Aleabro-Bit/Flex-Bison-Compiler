CC = gcc
FLEX = flex
BISON = bison

TARGET = guess_number
LEX_FILE = lexer.l
YACC_FILE = parser.y

OBJS = lex.yy.o parser.tab.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lfl -lm  # Link the math library

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) -c $<

parser.tab.o: parser.tab.c parser.tab.h
	$(CC) -c $<

lex.yy.c: $(LEX_FILE)
	$(FLEX) -o $@ $<

parser.tab.c parser.tab.h: $(YACC_FILE)
	$(BISON) -d -o parser.tab.c $<

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h


