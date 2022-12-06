#include <stdio.h>
#include <stdlib.h>
#include "string.h"

# define MAX_CHARS 1024
#define MSG "This is some msg"

// function declarations
void macroExpansion();
void getMacroHeadBody();

void display_file(char *filename);

void remove_commments(char *filename);

void remove_blank_lines(char *filename);

void identify_macros(char *filename);

void extract_macros(char *str);

void macro_expansion(char *filename);

// helper functions


int write_to_buff(char **buff, char *str, int buff_index);

void print_buff(char **buff);

void get_body_indexes (int head_index );

// init vars
char *macro_head[MAX_CHARS] = {};
char *macro_body[MAX_CHARS] = {};
int macro_head_index = 0;
int macro_head_size = 0;
int macro_body_index = 0;


int main(int argc, char *argv[]) {

    printf("%d\n", MAX_CHARS);
    printf(MSG);

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

        // 2 - Remove Blank Lines
        remove_blank_lines(file_name);
        char *file_without_blanks = "_without_blanks.txt";
        printf("------------------ File Without Blank Lines ------------------\n\n");
        display_file(file_without_blanks);
        printf("\n__________________________________________\n\n");

        // 3 - Strip comments
        remove_commments(file_without_blanks);
        char *file_without_comments = "_without_comments.txt";
        printf("------------------ File Without Comments ------------------\n\n");
        display_file(file_without_comments);
        printf("\n__________________________________________\n\n");

        // 4 - Macro Expansion
        macroExpansion();
        char *file_with_macro_expansion = "_removed_macros.txt";
        printf("------------------ Macro Expansion ------------------\n\n");
        display_file("out.c");
        printf("\n__________________________________________\n\n");
    } else {
        printf("\nInvalid arguments\n");
        exit(0);
    }
}


void macro_expansion(char *filename) {
    FILE *write_file = fopen("out.c", "w");
    identify_macros(filename);
    FILE *read_file = fopen("_removed_macros.txt", "r");
    char buff[MAX_CHARS];
    macro_body_index;
    macro_head;
    macro_body;

    for (int i = 0; i < macro_head_index; i++) {
        int macro_head_len = strlen(macro_head[i]);
        int macro_detected = 0;

        while ((fgets(buff, MAX_CHARS, read_file))) {
            for (int j = 0; j < strlen(buff); j++) {
                if (buff[j] == macro_head[i][0]) {
                    int k = 0;
                    while (k < macro_head_len) {
                        if (buff[j + k] == macro_head[i][k]) {
                            k++;
                        } else {
                            macro_detected = 1;
                            break;
                        }
                    }
                    if (macro_detected == 1) {
                        int body_start_index = 0;
                        int body_stop_index = 0;
                        int body_index = 0;
                        int body_counter = 0;

                        while (body_counter < i) {
                            if (strcmp(macro_body[body_index], "./././") == 0) {
                                body_counter++;
                            }
                            body_index++;
                        }
                        body_start_index = body_index + 1;
                        while (strcmp(macro_body[body_index], "./././") != 0) {
                            body_index++;
                        }
                        body_stop_index = body_index - 1;

                        for (int l = body_start_index; l < body_stop_index; l++) {
                            fprintf(write_file, "%s", macro_body[l]);
                        }
                        break;
                    } else {
                        fputc(buff[j], write_file);
                    }
                } else {
                    fputc(buff[j], write_file);
                }
            }
        }
    }
}

void macroExpansion(){
    /*
        All macros are expanded in the file
    */

    getMacroHeadBody(); // files are created with the macro heads and bodies respectively

    FILE *SourceFile;
    FILE *HeadFile;
    FILE *BodyFile;
    FILE *OutFile;

    SourceFile = fopen("TempOut2.c","r"); // Temp file from getMacroHeadBody() is opened to be read
    OutFile = fopen("out.c","w+");  // out2.c is created to be written to
    HeadFile = fopen("TempHead","r");
    BodyFile = fopen("TempBody","r");

    char* buff = (char*) malloc(sizeof(char)*100000);
    char* buffAfterBodyStr = (char*) malloc(sizeof(char)*100000);

    char* buffHead = (char*) malloc(sizeof(char)*100000);
    char* buffHeadTemp = (char*) malloc(sizeof(char)*100000);

    char* buffBody = (char*) malloc(sizeof(char)*100000);
    char* buffBodyTemp = (char*) malloc(sizeof(char)*100000);


    int i = 0;
    int j = 0;
    int newLineFlag = 0;
    char *test;
    int val;
    char headLastChar = ' ';


    while(fgets(buff,100000,SourceFile) != NULL){ // Each line is read from the source file
        // This will allow us to check each macro head, whether its written in each single line thats being read

        while(fgets(buffHead,100000,HeadFile) != NULL){ // Each macro head from the macro head file is read
            newLineFlag++;

            fgets(buffBody,100000,BodyFile); // We read the body file and check its first character
            val = atoi(&buffBody[0]); // its first char is the number of line its written on
            // This allows us to pick the correct macro body, according to the macro head being considered
            while(val != newLineFlag){
                printf("%d",newLineFlag);
                fgets(buffBody,100000,BodyFile);
                val = atoi(&buffBody[0]);
            }

            i = 1;
            j = 0;
            while(buffBody[i] != '\n'){ // We remove the first char(line number) and skip the \n and writes
                buffBodyTemp[j] = buffBody[i];// the body to a buffer
                i++;
                j++;
            }            // buffBodyTemp == BODY of macro in question


            i = 0;
            j = 0;
            while(buffHead[i] != '\n'){ // skips \n and writes the macro head to a buffer
                buffHeadTemp[j] = buffHead[i];
                i++;
                j++;
            }
            // buffHeadTemp == HEAD of macro in question

            headLastChar = buffHeadTemp[i-1]; // To keep track of the last char of the macro head


            test = strstr(buff,buffHeadTemp); // Gives us a pointer to the first char of the macro head, if it is in the,
            i = 0;                             // current line from the source file
            j = 0;

            if(test){ // Current macro is in the current line

                while(test[i] != headLastChar){ // It gets to the last character of the macro head
                    i++;
                }
                i++;
                while(test[i] != '\n'){ // now that the index (i) is at the end of the macro head,
                    buffAfterBodyStr[j] = test[i]; // we then store the chars after macro head in a buffer
                    i++;
                    j++;
                }
                buffAfterBodyStr[j] = '\n';

                strcpy(test,buffBodyTemp); // the pointer test is at the start of the macro head
                // we copy the macro body onto that pointer. So all the chars from the start
                // of the macro head till end of line is replaced with the macro body

                strcat(test,buffAfterBodyStr); // To restore the text after the macro body that was removed,
                // we concat the macro body with the buffer, in which we previously stored the
                // text after the macro head

            }

            // Buffers are reset to write the next iteration of items
            memset(buffHeadTemp,0,100000);
            memset(buffBodyTemp,0,100000);
            memset(buffAfterBodyStr,0,100000);


            j = 0;
            i = 0;

        }
        newLineFlag = 0;
        memset(buffBody,0,100000);

        // rewind the files to recheck every head with the new line from fgets
        rewind(HeadFile);
        rewind(BodyFile);

        fputs(buff,OutFile); // buffer with the updated line, with macro body replaced with head(if head was in the line)
        // is written to out2.c

    }
    fclose(OutFile);
}

void getMacroHeadBody()
{
    /*
        This will write the macro Heads to a file and macro Bodys to a seperate file.
        They will be placed in order in each file, so the head and macro are mapped to the same lines.
    */
    FILE *SourceFile;
    FILE *TempOutFile;
    FILE *HeadFile;
    FILE *BodyFile;

    SourceFile = fopen("_without_comments.txt","r"); // out1.c from prev fucntion is opened to be read
    TempOutFile = fopen("TempOut2.c","w+"); // a temp file is opened to be written
    HeadFile = fopen("TempHead","w+");
    BodyFile = fopen("TempBody","w+");

    char* buff = (char*) malloc(sizeof(char)*100000);
    int i = 0;
    int bodyLineCount = 1; // Will track the line number the macro body is stored on

    while(fgets(buff,100000,SourceFile) != NULL){

        // Reads the input file line by line. line with #define will be caught
        if((buff[0] == '#' && buff[1] == 'd' && buff[2] == 'e' && buff[3] == 'f' && buff[4] == 'i' && buff[5] == 'n' && buff[6] == 'e') || (buff[0] == '#' && buff[1] == 'D' && buff[2] == 'E' && buff[3] == 'F' && buff[4] == 'I' && buff[5] == 'N' && buff[6] == 'E')) {

            i = 7;
            while(buff[i] == ' ' || buff[i] == '\t'){ //Skips spaces after #define
                i++;
            }

            while(buff[i] != ' '){ // Its at the Macro head now, itll be written to its file
                fputc(buff[i],HeadFile);
                i++;
            }
            fputc('\n',HeadFile);

            while(buff[i] == ' ' ){ // Spaces after the macro head are skipped
                i++;
            }
            fprintf(BodyFile,"%d",bodyLineCount);
            bodyLineCount++;

            while(buff[i] != '\n'){     // Its at the macro body.itll written to its file
                fputc(buff[i],BodyFile);
                i++;
            }
            fputc('\n',BodyFile);
        }
        else{
            fputs(buff,TempOutFile); // It wont write the #define to the the tempOut2 file
        }


    }
    fclose(SourceFile);
    fclose(TempOutFile);
    fclose(HeadFile);
    fclose(BodyFile);
}


void identify_macros(char *filename) {
    FILE *read_file = fopen(filename, "r");
    FILE *write_file = fopen("_removed_macros.txt", "w");
    char str[MAX_CHARS];

    while ((fgets(str, MAX_CHARS, read_file))) {

        for (int i = 0; i < strlen(str); i++) {
            switch (str[i]) {
                case ('#'): {

                    for (int j = i; j < strlen(str); j++) {
                        switch (str[j]) {
                            case ('d'): {
                                if (str[j + 1] == 'e' && str[j + 2] == 'f' && str[j + 3] == 'i' && str[j + 4] == 'n' &&
                                    str[j + 5] == 'e' && str[j + 6] == '\t') {
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
                macro_head_size++;
            } else {
                macro_body_index = write_to_buff(macro_body, "./././", macro_body_index);
                macro_body_index = write_to_buff(macro_body, temp_str, macro_body_index);
                macro_body_index = write_to_buff(macro_body, " ", macro_body_index); // TODO: Check this space
            }
        }
        temp_str = strtok(NULL, " ");
    }
    macro_body_index = write_to_buff(macro_body, "./././", macro_body_index);
}


void remove_commments(char *filename) {
    FILE *read_file = fopen(filename, "r");
    FILE *write_file = fopen("_without_comments.txt", "w");
    char buff[MAX_CHARS];

    int comment_start = 0;

    while ((fgets(buff, MAX_CHARS, read_file))) {
        int char_detected = 0;
        for (int i = 0; i < strlen(buff); i++) {
            if (buff[i] == '/' && buff[i+1] == '/'){
                if (char_detected == 1){
                    fputc('\n', write_file);
                }
                break;
            } else if (buff[i] == '/' && buff[i+1] == '*'){
                comment_start = 1;
                break;
            } else if (buff[i] == '*' && buff[i+1] == '/'){
                comment_start = 0;
                break;
            } else if (comment_start == 0) {
                char_detected = 1;
                fputc(buff[i], write_file);
            }
        }
    }
    fclose(read_file);
    fclose(write_file);
}

void display_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    int c;
    while ((c = getc(fp)) != EOF) {
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


void remove_blank_lines(char *filename) {
    FILE *read_file = fopen(filename, "r");
    FILE *write_file = fopen("_without_blanks.txt", "w");
    char buff[MAX_CHARS];

    while ((fgets(buff, MAX_CHARS, read_file))) {
        int char_detected = 0;
        for (int i = 0; i < strlen(buff); i++) {
            switch (buff[i]) {
                case ('\t'): {
                    continue;
                }

                case ('\n'): {
                    if (char_detected == 1) {
                        fputc(buff[i], write_file);
                        break;
                    } else {
                        continue;
                    }
                }

                default: {
                    char_detected = 1;
                    for (int j = 0; j < strlen(buff); j++) {
                        fputc(buff[i], write_file);
                        break;
                    }
                }
            }
        }
    }
    fclose(read_file);
    fclose(write_file);
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
