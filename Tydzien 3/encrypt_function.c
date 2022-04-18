#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char* text){
    int itr = 0;
    while(*(text + itr) == ' '){
        itr++;
    }
    int s = itr;
    while(*(text + s) != ' ' && *(text + s) != '\0'){
        s++;
    }
    s = s - itr;
    int len = strlen(text);
    for(int i = 0; i < len; i++){
        if(*(text + i) != ' '){
            if(*(text + i) > 64 && *(text + i) < 91){
                *(text + i) = ((*(text + i) - 65 + s) % 26) + 65;
            } 
            else if(*(text + i) > 96 && *(text + i) < 123){
                *(text + i) = ((*(text + i) - 97 + s) % 26) + 97;
            }
        }
    }
}