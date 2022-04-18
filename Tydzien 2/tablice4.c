#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_and_print(int** matrix, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            *(*(matrix + i) + j) = random() % 10 + 1;
            printf("%-3d", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

int main(){

    int n, m;
    srandom(time(NULL));

    scanf("%d%d", &n, &m);

    int** matrix = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        *(matrix + i) = (int*)malloc(m * sizeof(int*));
    }

    fill_and_print(matrix, n, m);

    for(int i = 0; i < m; i++){
        free(*(matrix + i));
    }

    free(matrix);


    return 0;
}