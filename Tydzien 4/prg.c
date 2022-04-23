#include <stdio.h>

int main() {
    int a;
    FILE* file;
    file = fopen("test.txt", "r");
    for(int i = 0; i < 10; i++){
        fscanf(file, "%i", &a);
        printf("%i ", a);
    }
    fclose(file);
    return 0;
}