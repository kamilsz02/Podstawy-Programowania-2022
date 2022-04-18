#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char* text){
    int len = strlen(text);
    if(text[len - 1] == '\n'){
        text[len - 1] = '\0';
    }
    int itr = 0;
    while(*(text + itr) == ' '){
        itr++;
    }
    int s = itr;
    while(*(text + s) != ' ' && *(text + s) != '\0'){
        s++;
    }
    s = s - itr;
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
    printf("%s\n", text);
}

char* getEncryptedLine(){
    char* input = NULL;
    int return_value = 0;
    size_t len = 0;
    return_value = getline(&input, &len, stdin);
    if(return_value == -1){
        return NULL;
    }
    else{
        encrypt(input);
        return input;
    }

}

int main(){
 
    char plain_text[] = "abcdefghijklmnopqrstuvwxyz";
    encrypt(plain_text);

    /*char* output = calloc(100, sizeof(char));
    while(1){
        output = getEncryptedLine();
        if(output == NULL){
            break;
        }
        else{
            printf("%s\n", output);
        }
    }

    free(output);*/

    return 0;
}