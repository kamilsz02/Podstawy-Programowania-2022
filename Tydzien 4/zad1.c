#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define width 16

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

void generate(char* name, char* size, char* type) {
    FILE* file;
    file = fopen(name, "wb");
    int lines = stoi(size);
    if(*type == 'i'){
        for(int i = 0; i < lines; i++){
            int buf = random();
            fwrite(&buf, sizeof(int), 1, file);
        }
    }
    else{
        for(int i = 0; i < lines; i++){
            int buf = (random() % 256);
            fwrite(&buf, sizeof(char), 1, file);
        }
    }
    fclose(file);
}

void selection_sort(char* name, char* size, char* type) {
    FILE* file;
    int offset, min_idx;
    int a, b, min_val;
    if(*type == 'c'){
        offset = sizeof(char);
    }
    else{
        offset = sizeof(int);
    } 
    file = fopen(name, "rb+");
    int N = stoi(size);
    for(int i = 0; i < N; i++){
        fseek(file, i * offset, SEEK_SET); 
        fread(&a, offset, 1, file);
        min_idx = i;
        min_val = a;
        for(int j = i + 1; j < N; j++){
            fseek(file, j * offset, SEEK_SET);
            fread(&b, offset, 1, file);
            if(b < min_val){
                min_idx = j;
                min_val = b;
            }
        }
        fseek(file, i * offset, SEEK_SET);
        fwrite(&min_val, offset, 1, file);
        fseek(file, min_idx * offset, SEEK_SET);
        fwrite(&a, offset, 1, file);
    }
    fclose(file);
}

void list(char* name, char* size, char* type) {
    FILE* file;
    file = fopen(name, "rb");
    int offset;
    if(*type == 'c'){
        offset = sizeof(char);
    }
    else{
        offset = sizeof(int);
    }
    int N = stoi(size);
    for(int i = 0; i < N; i++) {
        if(i % (width / offset) == 0 && i > 0){
            printf("%c",'\n');
        }
        int data;
        fseek(file, i * offset, SEEK_SET);
        fread(&data, offset, 1, file);
        if(*type == 'i'){
            printf("%-8x ", data);
        }
        else {
            if(data <= 0xf) {
                printf("0%x ", data);
            }
            else{
                printf("%x ", data);
            }
        }
    }
    printf("%c", '\n');
    fclose(file);
}

int main(int argc, char** argv) {
    srandom(time(NULL));
    int op;

    if(argc != 4) {
        printf("Program was provided with an invalid number of arguments.");
        return 0;
    }

    scanf("%d", &op);

    switch(op) {
        case 1:
            generate(argv[1], argv[2], argv[3]);
            break;
        case 2:
            selection_sort(argv[1], argv[2], argv[3]);
            break;
        case 3:
            list(argv[1], argv[2], argv[3]);
            break;
        default:
            printf("%d is not a valid operation code.", op);
            return 0;
    }


    return 0;
}