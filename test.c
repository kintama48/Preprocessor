#include "string.h"
#include <stdio.h>
#include <stdlib.h>

int write_to_buff(char **buff, char *str, int buff_index);

void print_buff(char **buff);

int main() {
    char str[] = "#   define msg \"This is some value \"\n";

    if (str[strlen(str) - 1] == '\n') {       // remove newline character if any
        str[strlen(str) - 1] = '\0';
    }

    // init vars
    char *temp_str = strtok(str, " ");
    char *macro_head[100] = {};
    char *macro_body[100] = {};
    int macro_head_index = 0;
    int macro_body_index = 0;

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
//    // "./././" indicates end of macro body and head
//    macro_body_index = write_to_buff(macro_body, "./././", macro_body_index);

    printf("\nMacro Head: \n");
    print_buff(macro_head);
    printf("\nMacro Body: \n");
    print_buff(macro_body);

    return 0;
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

{"\"This", "is", "val", "./././", "2", "./././"}