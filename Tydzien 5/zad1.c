#include "functions.c"

int main(int argc, char** argv) {
    if(argc < 2) {
        return 1;
    }

    Day start = string_to_day(argv[1]);
    int len;
    Action* tab = parse(argc, argv, &len);
    char* res;

    for(int i = 0; i < len; i++) {
        res = Action_toString(tab[i]);
        printf("%s\n", res);
    }

    Day final = shift(start, tab, len);
    char* out = Day_toString(final);

    printf("Wynik przesuniecia: \"%s\"\n", out);
    
    free(res);
    free(tab);
    free(out);

    return 0;
}