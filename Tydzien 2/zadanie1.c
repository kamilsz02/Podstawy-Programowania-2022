#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    return a > b ? a : b;
}

int find_biggest(int* arr, int n){
    int mx = -1;
    int mx_index = -1;
    for(int i = 0; i < n; i++){
        if(*(arr + i) > mx){
            mx = *(arr + i);
            mx_index = i;
        }
    }
    return mx_index;
}

int main(){
    int n, k;
    FILE *plik;
    plik = fopen("dane.in", "r");
    fscanf(plik, "%d%d", &n, &k);
    int* arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        fscanf(plik, "%d", (arr + i));
    }

    int res = 0;

    for(int i = 0; i < k; i++){
        int kan = find_biggest(arr, n);
        *(arr + kan) = *(arr + kan) / 2;
    } 

    for(int i = 0; i < n; i++){
        res += *(arr + i);
    }

    printf("%d \n", res);

    free(arr);

    return 0;
}