# Compiler and flags
CC = gcc
FLEX = flex
FLEX_FLAGS = -o

# Files
LEX_FILE = stats.l
MAIN_FILE = main.c
LEX_OUTPUT = lex.yy.c
EXECUTABLE = stats

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(LEX_OUTPUT) $(MAIN_FILE)
	$(CC) -o $@ $(LEX_OUTPUT) $(MAIN_FILE) -lfl

$(LEX_OUTPUT): $(LEX_FILE)
	$(FLEX) $(FLEX_FLAGS) $@ $(LEX_FILE)

clean:
	rm -f $(LEX_OUTPUT) $(EXECUTABLE)

