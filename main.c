#include <stdio.h>
#include <stdlib.h>
#include "string.h"

# define MAX_CHARS 1024


// function declarations
void display_file (char *filename);
void remove_commments(char* filename);
void remove_blank_lines (char* filename);
void macro_expansion (char* filename);

// helper functions
void identify_macros(char *filename);
void extract_macros(char *str);
int write_to_buff(char **buff, char *str, int buff_index);
void print_buff(char **buff);


char *macro_head[MAX_CHARS] = {};
char *macro_body[MAX_CHARS] = {};
char ** macros[2] = {macro_head, macro_body};
int macro_head_index = 0;
int macro_body_index = 0;


int main(int argc, char *argv[]) {
    printf("\n__________________________________________\n\n"
                    "             Abdullah Baig          \n"
                    "               231485698          \n"
                    "             Assignment 1          \n"
                  "\n__________________________________________\n\n");
    if (argc == 2) {
        char *file_name = argv[1];
        FILE *in_file = fopen(file_name, "r");

        if (in_file == NULL) {
            printf("Error opening file!");
            exit(-1);
        } else {
            fclose(in_file);
        }
        // 1 - Display File
        printf("------------------ Input File ------------------\n\n");
        display_file(file_name);
        printf("\n__________________________________________\n\n");

        // 2 - Remove Blank Lines
        char* file_without_blanks = strcat(file_name, "_without_blanks.txt");
        remove_blank_lines(file_without_blanks);

        printf("------------------ File Without Blank Lines ------------------\n\n");
        display_file(file_without_blanks);
        printf("\n__________________________________________\n\n");

        // 3 - Strip comments
        char* file_without_comments = strcat(file_name, "_without_comments.txt");
        remove_commments(file_without_comments);

        printf("------------------ File Without Comments ------------------\n\n");
        display_file(file_without_comments);
        printf("\n__________________________________________\n\n");

        // 4 - Macro Expansion
        char* file_with_macro_expansion = strcat(file_name, "_out.txt");
        macro_expansion(file_with_macro_expansion);

        printf("------------------ File Without Comments ------------------\n\n");
        display_file(file_without_comments);
        printf("\n__________________________________________\n\n");


    } else {
        printf("\nInvalid arguments\n");
        exit(0);
    }
}



void macroExpansion(char* filename) {
    FILE *write_file = fopen(strcat(filename, "_out.c"), "w");
    identify_macros(filename);
    FILE *read_file = fopen(strcat(filename, "_removed_macros.c"), "r");
    char buff[MAX_CHARS];

    for (int i = 0; i < macro_head_index; i++) {
        int macro_head_len = strlen(macro_head[i]);
        int c;
        int body_counter = 0;
        int body_start_index = 0;
        int body_end_index = 0;

        while ((fgets(buff, MAX_CHARS, read_file))) {
            for (int i = 0; i < strlen(buff); i++) {
                if (buff[i] == macro_head[i]) {
                    int j = 0;
                    while (j < macro_head_len) {
                        if (buff[i + j] == macro_head[i + j]) {
                            j++;
                        } else {
                            break;
                        }
                    }
                    if (j == macro_head_len) {
                        while (body_counter != i) {

                            fputc(macro_body[i][body_counter], write_file);
                            body_counter++;
                        }
                        fprintf(write_file, "%s", macro_body[i]);
                    }
                }
            }
        }
    }

}


void remove_commments(char* filename) {
    FILE *read_file = fopen(filename, "r");
    FILE *write_file = fopen(strcat(filename, "_without_comments.txt"), "w");
    char buff[MAX_CHARS];

    int comment_start = 0;

    while ((fgets(buff, MAX_CHARS, read_file))) {

        for (int i = 0; i < strlen(buff); i++) {
            switch (buff[i]) {
                case ('/') :{
                    if (buff[i+1] == '/') {
                        break;
                    }
                }

                case ('*'): {
                    if (buff[i - 1] == '/') {
                        comment_start = 1;
                    }
                    if (buff[i + 1] == '/') {
                        comment_start = 0;
                        continue;
                    }
                }

                default: {
                    if (comment_start == 0) {
                        fputc(buff[i], write_file);
                    }
                }
            }
        }
    }
    fclose(read_file);
    fclose(write_file);
}

void display_file (char *filename) {
    FILE *fp = fopen(filename, "r");
    int c;
    while ( (c = getc(fp)) != EOF) {
        printf("%c", c);
    }
    fclose(fp);
    printf("\n\n");
}

void write_line_no(FILE *write_file, int line_no) {
    char buff[256];
    sprintf(buff, "%d. ", line_no);
    fputs(buff, write_file);
}


void remove_blank_lines (char* filename) {
    FILE *read_file = fopen(filename, "r");
    FILE *write_file = fopen(strcat(filename, "_without_blanks.txt"), "w");
    char buff[MAX_CHARS];

    while ( (fgets(buff, MAX_CHARS, read_file))) {
        int char_detected = 0;

        for (int i=0; i < strlen(buff); i++) {

            if (char_detected == 1) {
                fputc(buff[i], write_file);
            } else {
                switch (buff[i]) {
                    case ('\t'): {
                        if (char_detected == 0) {
                            continue;
                        }
                    }

                    case ('\n'): {
                        if (char_detected == 0) {
                            continue;
                        }
                    }

                    default: {
                        fputc(buff[i], write_file);
                        char_detected = 1;
                    }
                }
            }
        }
    }
    fclose(read_file);
    fclose(write_file);
}


void identify_macros(char *filename) {
    FILE *read_file = fopen(filename, "r");
    FILE *write_file = fopen(strcat(filename, "_removed_macros.c"), "w");
    char str[MAX_CHARS];

    while ( (fgets(str, MAX_CHARS, read_file))) {

        for (int i=0; i < strlen(str); i++) {
            switch (str[i]) {
                case ('#'): {

                    for (int j=i; j < strlen(str); j++) {
                        switch (str[j]) {
                            case ('d'): {
                                if (str[j+1] == 'e' && str[j+2] == 'f' && str[j+3] == 'i' && str[j+4] == 'n' && str[j+5] == 'e' && str[j+6] == '\t') {
                                    extract_macros(str);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                default: {
                    fputc(str[i], write_file);
                }
            }
        }
    }
}

void extract_macros(char *str) {
    if (str[strlen(str) - 1] == '\n') {       // remove newline character if any
        str[strlen(str) - 1] = '\0';
    }

    // init vars
    char *temp_str = strtok(str, " ");

    int head_written = 0;

    /*
     this while loop splits the macro string on a blank space and extracts macro head & body. ignores #,
     #define and define directives
    */
    while (temp_str != NULL) {
        if (strcmp(temp_str, "#") != 0 && strcmp(temp_str, "#define") != 0 && strcmp(temp_str, "define") != 0) {
            if (head_written == 0) {
                macro_head_index = write_to_buff(macro_head, temp_str, macro_head_index);
                head_written = 1;
            } else {
                macro_body_index = write_to_buff(macro_body, temp_str, macro_body_index);
                macro_body_index = write_to_buff(macro_body, " ", macro_body_index);
            }
        }
        temp_str = strtok(NULL, " ");
    }

    macro_body_index = write_to_buff(macro_body, "./././", macro_body_index);
//    printf("\nMacro Head: \n");
//    print_buff(macro_head);
//    printf("\nMacro Body: \n");
//    print_buff(macro_body);
//    macros[0] = macro_head;
//    macros[1] = macro_body;
}

void print_buff(char **buff) {
    for (int i = 0; buff[i] != NULL; i++) {
        printf("%s\n", buff[i]);
    }
}

int write_to_buff(char **buff, char *str, int buff_index) {
    buff[buff_index] = malloc(strlen(str) + 1);
    strcpy(buff[buff_index], str);
    buff_index++;
    return buff_index;
}
