#include <stdio.h>
#include <stdlib.h>

void show_matrix(int **matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%-3d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

int is_lower_triangular(int **matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if((*(*(matrix + i) + j) != 0)){
                return 0;
            }
        }
    }
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);

    int** matrix = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        *(matrix + i) = (int*)malloc(n * sizeof(int));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", (*(matrix + i) + j));
        }
    }

    show_matrix(matrix, n);

    int res = is_lower_triangular(matrix, n);

    if(res){
        printf("Given matrix is lower triangular \n");
    }
    else{
        printf("Given matrix is not lower triangular \n");
    }

    for(int i = 0; i < n; i++){
        free(*(matrix + i));
    }

    free(matrix);

    return 0;
}