CC = gcc
FLEX = flex
BISON = bison

TARGET = guess_number
LEX_FILE = lexer.l
YACC_FILE = parser.y

OBJS = lex.yy.o parser.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lfl

lex.yy.o: lex.yy.c parser.h
	$(CC) -c $<

parser.o: parser.c parser.h
	$(CC) -c $<

lex.yy.c: $(LEX_FILE)
	$(FLEX) -o $@ $<

parser.c parser.h: $(YACC_FILE)
	$(BISON) -d $<

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.c parser.h

