#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define N 4

void fill_matrix(int matrix[N][N]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = (random() % 10) + 1;
        }
    }
}

void sums(int matrix[N][N]){
    int diagonal_res = 0;
    int i = 0, j = 0;
    while(i < 4 && j < 4){
        diagonal_res += matrix[i][j];
        i++;
        j++;
    }

    printf("The sum of all elements on the diagonal is %d \n", diagonal_res);

    int all_res = 0;
    int column_res = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            column_res += matrix[j][i];
        }
        printf("The sum of all elements in column %d is %d \n", i + 1, column_res);
        all_res += column_res;
        column_res = 0;
    }

    printf("The sum of all matrix elements is %d \n", all_res);
}

void show_matrix(int matrix[N][N]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiplay(int matrix1[N][N], int matrix2[N][N], int result[N][N]){
    memset(*result, 0, N * N * 4);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main(){

    srandom(time(NULL));
    int matrix1[N][N];
    int matrix2[N][N];
    int res_matrix[N][N];

    fill_matrix(matrix1);
    fill_matrix(matrix2);

    show_matrix(matrix1);
    show_matrix(matrix2);

    sums(matrix1);
    multiplay(matrix1, matrix2, res_matrix);
    show_matrix(res_matrix);

    return 0;   
}