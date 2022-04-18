#include "zad2.c"

int main(int argc, char* argv[]){
    int flag = 0;

    if(argc > 1){
        if(strcmp(argv[1], "--decompress") == 0){
            flag = 1;
        }
        else if(strcmp(argv[1], "--compress") == 0){
            flag = 0;
        }
    }

    int lines;
    char** data = getData(&lines);
    char* output;

    if(flag == 0){
        output = compress(data, lines);
    }
    else{
        output = decompress(data, lines);
    }

    printf("\n%s", output);

    free_double_ptr(data, lines);
    free(output);

    return 0;
}