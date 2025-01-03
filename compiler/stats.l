%{
#include <stdio.h>
#include <ctype.h>

/* Global counters */
int line_count = 0;
int word_count = 0;
int char_count = 0;

/* External declaration for accessing filenames */
extern char **file_list;
extern int file_index;
extern int num_files;

/* Function declarations */
int process_file();
%}

%%

\n              { line_count++; char_count++; }
[ \t]+          { char_count += yyleng; }
[^\n \t]+       { word_count++; char_count += yyleng; }
.               { char_count++; }

%%

int yywrap() {
    file_index++;
    if (file_index < num_files) {
        FILE *next_file = fopen(file_list[file_index], "r");
        if (!next_file) {
            fprintf(stderr, "Error opening file: %s\n", file_list[file_index]);
            return 1; /* End lexing if file can't be opened */
        }
        yyin = next_file;
        return 0; /* Continue lexing */
    }
    return 1; /* End of input */
}

