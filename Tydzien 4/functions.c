#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#define MAX_LINE_LEN 128

int stoi(char* num) {
    int res = 0;
    int len = 0;
    while(num[len] != '\0'){
        res += (num[len] - 48);
        res *= 10;
        len++;
    }
    res /= 10;
    return res;
}

int read(FILE* file, int pos) {
    rewind(file);
    int res;
    for(int i = 0; i <= pos; i++) {
        fscanf(file, "%i", &res);
    }
    return res;
}

void multiply_and_fill_matrix(FILE* A, FILE* B, FILE* C, int col_A, int row_B, int row_A, int col_B, int offset_1, int offset_2){
    int res = 0;
    for(int i = 0; i < row_A; i++){
        for(int j = 0; j < col_B; j++){
            if(offset_2 == 0) {
                if(j < offset_1) {
                    res = 0;
                    for(int k = 0; k < col_A; k++){
                        res += read(A, i * col_A + k) * read(B, k * (offset_1 + offset_1) + j + offset_2); 
                    }
                    fprintf(C, "%i ", res);
                }
                else { 
                    fprintf(C, "X ");
                }
            }
            else {
                if(j >= offset_1) {
                    res = 0;
                    for(int k = 0; k < col_A; k++){
                        res += read(A, i * col_A + k) * read(B, k * (offset_1 + offset_1) + (j - offset_1) + offset_2); 
                    }
                    fprintf(C, "%i ", res);
                }
                else { 
                    fprintf(C, "X ");
                }
            }
        }
        fprintf(C, "%c", '\n');
   }
}

void multiply_matrix(FILE* A, FILE* B, FILE* C, int col_A, int row_B, int row_A, int col_B, int offset_1, int offset_2){ 
   int res = 0;
   char* buf = NULL;
   size_t size = MAX_LINE_LEN;
   FILE* result = fopen("res.txt", "w");
   for(int i = 0; i < row_A; i++){
       char* out = calloc(MAX_LINE_LEN, sizeof(char)); 
       char* help = calloc(MAX_LINE_LEN, sizeof(char));
       int c = getline(&buf, &size, C);
       int itr = 0;
       int ctr = 0;
       for(int j = 0; j < col_B; j++){
           res = 0;
           for(int k = 0; k < col_A; k++){
               if(offset_2 == 0) res += read(A, i * col_A + k) * read(B, k * (col_B + offset_1) + j + offset_2); 
               else {
                res += read(A, i * col_A + k) * read(B, k * col_B + offset_1 + j);
                //printf("%d %d %d\n", read(A, i * col_A + k), read(B, k * col_B + offset_1), res);
               }
            }
            //printf("%d\n", res);
            while(buf[itr] != '\0'){
                if(buf[itr] == 'X') {
                    ctr++;
                    sprintf(help, "%d", res); 
                    if(out == NULL) {
                        strcpy(out, help);
                    }
                    else{
                        strcat(out, help);
                    }
                    if(ctr < offset_1){
                        itr++;
                        break;
                    }
                    else {
                        itr++;
                        continue;
                    }
                }   
                else{
                    sprintf(help, "%c", *(buf + itr));
                    if(out == NULL) {
                        strcpy(out, help);
                    }
                    else{
                        strcat(out, help);
                    }
                }
                itr++;
            }
        }
        fprintf(result, "%s", out);
        free(out);
        free(help);
    }
    fclose(result);
    free(buf);
}


void get_dim(FILE* file, int* col, int* row) {
    char* first_line = NULL;
    size_t size = MAX_LINE_LEN;
    (*col) = 0;
    (*row) = 1;
    int r_val = getline(&first_line, &size, file);
    if(r_val == -1){
        free(first_line);
        return;
    }
    int i = 0;
    int j = 0;

    while(*(first_line + i) == 32){ //strip off leading spaces
        i++;
    }

    while(*(first_line + i) != '\0') {
        if(*(first_line + i) == ' ' && (*(first_line + i + 1) != ' ' && *(first_line + i + 1) != '\0' && *(first_line + i + 1) != '\n')){
            (*col)++;
        }
        i++;
    }

    (*col)++;

    while(getline(&first_line, &size, file) != -1) {
        (*row)++;
    }

    free(first_line);
}