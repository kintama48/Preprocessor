#include "string.h"
#include <stdio.h>
#include <stdlib.h>

int write_to_buff (char** buff, char* str, int buff_index) {
    buff[buff_index] = malloc(strlen(str) + 1);
    strcpy(buff[buff_index], str);
    return buff_index++;
}

int main () {
    char str[] = "#   define msg \"This is some value \"\n";

    if (str[strlen(str)-1] == '\n') {       // remove newline character if any
        str[strlen(str)-1] = '\0';
    }

    // init vars
    char* temp = strtok(str, " ");
    char *buff[100] = {};
    char *macro_head[100] = {};
    char *macro_body[100] = {};
    int buff_index = 0;
    int macro_head_index = 0;
    int macro_body_index = 0;

    /*
     this while loop splits the macro string on a blank space and extracts macro head & body. ignores #,
     #define and define directives
    */
    while (temp != NULL)
    {
        if (strcmp(temp, "#") != 0 && strcmp(temp, "#define") !=0 && strcmp(temp, "define")!=0) {
            buff_index = write_to_buff(buff, temp, buff_index);
//            buff[buff_index] = malloc(strlen(temp) + 1);
//            strcpy(buff[buff_index], temp);
//            buff_index++;
        }
        temp = strtok (NULL, " ");
    }

    // add
    write_to_buff(buff, "./././", buff_index);
//    buff[buff_index] = malloc(strlen("./././")+1);
//    strcpy(buff[buff_index], "./././");


    macro_head_index = write_to_buff(macro_head, buff[0], macro_head_index);
//    macro_head[macro_head_index] = malloc(strlen(buff[0])+1);
//    strcpy(macro_head[macro_head_index], buff[0]);
//    macro_head_index++;

    for (int i=1; strcmp(buff[i], "./././") != 0; i++) {
        macro_body_index = write_to_buff(macro_body, buff[i], macro_body_index);
    }

//    int index = 1;
//    while (strcmp(buff[index], "./././") != 0) {
//        index = write_to_buff(macro_body, buff[index], index);
//        macro_body[macro_body_index] = malloc(strlen(buff[index]+1));
//        strcpy(macro_body[macro_body_index], buff[index]);
//        macro_body_index ++;
//        index++;
//    }

    macro_body_index = write_to_buff(macro_body, "./././", macro_body_index);
//    macro_body[macro_body_index] = malloc(strlen("./././")+1);
//    strcpy(macro_body[macro_body_index], "./././");
//    index++;


// alternative

//
//    // add a string to indicate end of buffer list
//    write_to_buff(buff, "./././", buff_index);
//
//    // copy macro head to a list of strings and return the next index to write to macro_head
//    macro_head_index = write_to_buff(macro_head, buff[0], macro_head_index);
//
//    // copy macro body to a list of strings and return the next index to write to macro_body
//    for (int i=1; strcmp(buff[i], "./././") != 0; i++) {
//
//        macro_body_index = write_to_buff(macro_body, buff[i], macro_body_index);
//    }
//
//    macro_body_index = write_to_buff(macro_body, "./././", macro_body_index);


    return 0;
}