#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Term {
    int hour;
    int minute;
    int duration;
};

typedef struct Term Term;

int hour_addition(Term* term1, Term* term2) {
    return (term2->hour * 60 + term2->minute) - (term1->hour * 60 + term1->minute);
}

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

bool Term__earlierThan(Term* term1, Term *term2) {
    if(term1->hour < term2->hour) {
        return true;
    }
    else if(term1->hour == term2->hour && term1->minute < term2->minute) {
        return true;
    }
    return false;
}

bool Term__laterThan(Term* term1, Term *term2) {
    if(term1->hour > term2->hour) {
        return true;
    }
    else if(term1->hour == term2->hour && term1->minute > term2->minute) {
        return true;
    }
    return false;
}

bool Term__equals(Term* term1, Term *term2) {
    return (term1->hour == term2->hour) && (term1->minute == term2->minute) && (term1->duration == term2->duration) ? true : false;
}

Term* Term__endTerm(Term* term1, Term *term2) {
    if(Term__earlierThan(term1, term2)) {
        Term* res_term = Term__create(term1->hour, term1->minute, hour_addition(term1, term2));
        return res_term;
    }
    else return Term__create(-1, -1, -1); 
}

/*int main(int argc, char** argv) {
    Term* new_term = Term__create(14, 30, 90);
    char* out = Term__toString(new_term);

    printf("%s\n", out);

    Term__destroy(new_term);
    free(out);

    return 0;
}*/