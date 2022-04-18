#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define line_limit 100

char* getHexAscii(char znak){
    char* res = malloc(2 * sizeof(char));
    sprintf(res, "%x", znak);
    return res;
}

int test = 0;

char** getData(int* ctr){
    char** data = calloc(3, sizeof(char*));
    char* input = NULL;
    size_t size = 0;
    int len = 0;
    *(ctr) = 0;
    FILE* in;
    const char* name;
    if(test == 1){
        name = "tests.txt";
        in = fopen(name, "r");
    }
    else{
        in = stdin;
    }
    while(1){
        len = getline(&input, &size, in);
        if(len == -1){
            break;
        }
        if(*ctr > 2){
            data = realloc(data, (*ctr + 1) * sizeof(char*));
        }
        data[*ctr] = malloc(len * sizeof(char));   
        memcpy(data[*ctr], input, len * sizeof(char)); 
        (*ctr)++;    
    }
    if(test == 1){
        fclose(in);
    }
    return data;
}

char* compress(char** text, int n){
    char* result = malloc(line_limit * sizeof(char));
    for(int k = 0; k < n; k++){
        int itr = 0;
        int len = strlen(text[k]);   
        while(text[k][itr] != '\0'){
            int j = itr + 1;
            char* rewrite = calloc(len, sizeof(char));
            int i = 0;
            if(text[k][j - 1] != '(' && text[k][j - 1] != ')' && text[k][j - 1] != '%'){
                while(text[k][j] == text[k][j - 1]){
                    rewrite[i++] = text[k][j - 1];
                    j++;
                }
                if(text[k][j] != text[k][j - 1]){
                    rewrite[i++] = text[k][j - 1];
                }
                if(j - itr > 4){
                    char* buffer = malloc((4 + (j - itr) / 10) * sizeof(char));
                    sprintf(buffer, "%c(%d)", text[k][j - 1], j - itr);     
                if(result == NULL){
                    strcpy(result, buffer);
                }
                else{
                    strcat(result, buffer);
                }
                free(buffer);
                }
                else{
                    strcat(result, rewrite);
                    free(rewrite);
                }
            }
            else{
                while(text[k][j] == text[k][j - 1]){
                    j++;
                }
                char* buffer = malloc((4 + (j - itr) / 10) * sizeof(char));
                char* code = getHexAscii(text[k][j - 1]);
                sprintf(buffer, "%%%s(%d)", code, j - itr);
                if(result == NULL){
                    strcpy(result, buffer);
                }
                else{
                    strcat(result, buffer);
                }
                free(buffer);
                free(code);
            }
            itr = j;
        }
    }    
    return result;
} 

char* decompress(char** text, int n){
    char* result = calloc(line_limit, sizeof(char));
    for(int m = 0; m < n; m++){
        int itr = 0;
        int len = strlen(text[m]);
        while(text[m][itr] != '\0'){
            char* buffer = calloc(100, sizeof(char));
            int i = 0;
            int j = itr;
            while(text[m][j] != '%' && text[m][j] != '(' && text[m][j] != '\0'){
            //write to buffer
                buffer[i++] = text[m][j];
                j++;
            }
            if(text[m][j] == '%'){
                //convert from hex and move the pointer
                j += 2;
                char sign;
                if(text[m][j] == '5'){
                    sign = '%';
                }
                else if(text[m][j] == '8'){
                    sign = '(';
                }
                else if(text[m][j] == '9'){
                    sign = ')';
                }
                int k = j + 1;
                int num = 0;
                while(text[m][k] != ')'){
                    if(text[m][k] > 47 && text[m][k] < 58){
                        num += (int)(text[m][k] - 48);
                        num *= 10;
                    }
                    k++;
                }
                num /= 10;
                for(int l = 0; l < num; l++){
                    buffer[i++] = sign;
                }
                j = k + 1;
            }
            else if(text[m][j] == '('){
                int k = j + 1;
                int num = 0;
                while(text[m][k] != ')'){
                    if(text[m][k] > 47 && text[m][k] < 58){
                        num += (int)(text[m][k] - 48);
                        num *= 10;
                    }
                    k++;
                }
                char sign = text[m][j - 1];
                num /= 10;
                for(int l = 0; l < num - 1; l++){
                    buffer[i++] = sign;
                }
                j = k + 1;
            }
            itr = j;
            if(result == NULL){
                strcpy(result, buffer);
                free(buffer);
            }
            else{
                strcat(result, buffer);
                free(buffer);
            }
        }
    }
    return result;
}

void free_double_ptr(char** data, int lines){
    for(int i = 0; i < lines; i++){
        free(*(data + i));
    }
    free(data);
}

/*int main(){
    
    char** dane = calloc(10, sizeof(char*));
    int len = 0;
    dane = getData(&len);
    //char* out = compress(dane, len);
    printf("%s", *(dane+1));
    free(dane);
    //free(out);
    
    /*char** dane = calloc(line_limit, sizeof(char*));
    *(dane) = "%28(4)a(8) (5)%29(5) \n";
    *(dane + 1) = " (5)a(5) (5)b(5) \n";
    char* out = decompress(dane, 2);
    printf("%s", out);
    free(dane);
    free(out);

    return 0;
}*/