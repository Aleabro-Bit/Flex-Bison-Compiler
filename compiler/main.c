#include <stdio.h>

/* Globals for file handling */
char **file_list;
int file_index = 0;
int num_files;

/* External declarations from the lexer */
extern int yylex();
extern int line_count;
extern int word_count;
extern int char_count;
extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        return 1;
    }

    /* Initialize file list */
    file_list = argv + 1;
    num_files = argc - 1;

    /* Process the first file */
    FILE *input_file = fopen(file_list[file_index], "r");
    if (!input_file) {
        fprintf(stderr, "Error opening file: %s\n", file_list[file_index]);
        return 1;
    }
    yyin = input_file;

    /* Greet the user */
    printf("Starting lexical analysis...\n");

    /* Start lexing */
    yylex();

    /* Print the results */
    printf("Lines: %d\n", line_count);
    printf("Words: %d\n", word_count);
    printf("Chars: %d\n", char_count);

    return 0;
}

