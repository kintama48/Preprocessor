#include <stdio.h>
#include "string.h"
#define MAX_WORDS 5000
#define MAX_CHARS 5000

void removeComments(FILE *read_file,FILE *out_file){
    char str[MAX_WORDS];
    while ((fgets(str, MAX_CHARS, read_file))) {
        int char_detected = 0;
        int comment_detected = 0;

        for (int i=0; i < strlen(str); i++) {
            if (str[i] == '/' && str[i+1] == '/'){
                if (char_detected == 1){
                    fputc('\n', out_file);
                }
                break;
            } else if (str[i] == '/' && str[i+1] == '*'){
                if (char_detected == 1){
                    fputc('\n', out_file);
                }
                comment_detected = 0;
                break;
            } else if (str[i] == '*' && str[i+1] == '/'){
                if (char_detected == 1){
                    fputc('\n', out_file);
                }
                comment_detected = 0;
                break;
            } else if (comment_detected == 0) {
                char_detected = 1;
                fputc(str[i], out_file);
            }

        }
    }
    fclose(read_file);
    fclose(out_file);
}