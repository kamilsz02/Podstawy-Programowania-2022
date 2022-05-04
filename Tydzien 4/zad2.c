#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LEN 128

int read(FILE* file, int pos) {
    rewind(file);
    int res = 0;
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

int main(int argc, char** argv){
    if(argc != 4){
        printf("Invalid number of args.");
        return 1;
    }

    FILE* file_A;
    FILE* file_B;
    FILE* file_C;
    file_A = fopen(argv[1], "r");
    file_B = fopen(argv[2], "r");
    file_C = fopen(argv[3], "w");

    int col_A = 0, col_B = 0, row_A = 0, row_B = 0;
    get_dim(file_A, &col_A, &row_A);
    get_dim(file_B, &col_B, &row_B);

    if(col_A != row_B){
        //printf("%d %d", col_A, col_B);
        printf("Cannot multiply matrices - mismatching dimensions.");
        fclose(file_A);
        fclose(file_B);
        fclose(file_C);
        return 1;
    }

    multiply_matrix(file_A, file_B, file_C, col_A, row_B, row_A, col_B); 
    
    fclose(file_A);
    fclose(file_B);
    fclose(file_C);

    return 0;
}