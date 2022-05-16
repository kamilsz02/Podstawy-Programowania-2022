#include <stdio.h>
#include <stdlib.h>

struct Term {
    int hour;
    int minute;
    int duration;
};

typedef struct Term Term;

void Term__init(Term* term, int hour, int minute, int duration) {
    term->hour = hour;
    term->minute = minute;
    term->duration = duration;
}

Term* Term__create(int hour, int minute, int duration) {
    Term* term = malloc(sizeof(Term));
    Term__init(term, hour, minute, duration);
    return term;
}

void Term__destroy(Term* term) {
    free(term);
}

char* Term__toString(Term* term) {
    char* res = malloc(64 * sizeof(char));
    sprintf(res, "\"%d:%d [%d]\"", term->hour, term->minute, term->duration);
    return res;
}

/*int main(int argc, char** argv) {
    Term* new_term = Term__create(14, 30, 90);
    char* out = Term__toString(new_term);

    printf("%s\n", out);

    Term__destroy(new_term);
    free(out);

    return 0;
}*/