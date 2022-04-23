#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 128

int read(FILE* file, int pos) {
    rewind(file);
    int res;
    for(int i = 0; i <= pos; i++) {
        fscanf(file, "%i", &res);
    }
    return res;
}

void multiply_matrix(FILE* A, FILE* B, FILE* C, int col_A, int row_B, int row_A, int col_B){
   int res = 0;
   for(int i = 0; i < row_A; i++){
       for(int j = 0; j < col_B; j++){
           res = 0;
           for(int k = 0; k < col_A; k++){
               res += read(A, i * col_A + k) * read(B, k * col_B + j); 
           }
           fprintf(C, "%i ", res);
       }
       fprintf(C, "%c", '\n');
   }
}

void get_dim(FILE* file, int* col, int* row){
    char* first_line = NULL;
    size_t size = MAX_LINE_LEN;
    *(col) = 0;
    *(row) = 1;
    int r_val = getline(&first_line, &size, file);
    int i = 0;
    while(*(first_line + i) != '\0') {
        if(*(first_line + i) == ' ') {
            (*col)++;
        }
        i++;
    }

    while(getline(&first_line, &size, file) != -1) {
        (*row)++;
    }

    free(first_line);
}