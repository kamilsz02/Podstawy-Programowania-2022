#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 10

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

void rand_dim(int min, int max, int* col, int* row) {
    *col = min + random() % (max + 1 - min);
    *row = min + random() % (max + 1 - min);
}

void randomize(FILE* file, int col, int row) {
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int val = random() % N;
            fprintf(file, "%i ", val);
        }
        fprintf(file, "%c", '\n');
    }
}

int main(int argc, char** argv) {
    srandom(time(NULL));
    FILE* file_A;
    FILE* file_B;
    file_A = fopen("m1.txt", "w+");
    file_B = fopen("m2.txt", "w+");

    if(argc != 3){
        printf("Invalid number of args.");
        return 1;
    }

    int min = stoi(argv[1]);
    int max = stoi(argv[2]);
 
    int col_A, col_B, row_A, row_B;
    rand_dim(min, max, &col_A, &row_A);
    rand_dim(min, max, &col_B, &row_B); 

    row_B = col_A;

    randomize(file_A, col_A, row_A);
    randomize(file_B, col_B, row_B);

    fclose(file_A);
    fclose(file_B);

    return 0;
}