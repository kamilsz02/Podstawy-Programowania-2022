#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

enum Day {
    MON, 
    TUE,
    WED, 
    THU,
    FRI,
    SAT,
    SUN
};

enum Action {
    DAY_EARLIER, 
    DAY_LATER, 
    TIME_EARLIER, 
    TIME_LATER
};

struct Term {
    int hour;
    int minute;
    int duration;
    enum Day day;
};

struct Lesson {
    struct Term* term;
    char* name;
};

struct Time_Bounds {
    int s_min;
    int s_hour;
    int f_min;
    int f_hour;
};

typedef struct Term Term;
typedef enum Day Day;
typedef enum Action Action;
typedef struct Lesson Lesson;
typedef struct Time_Bounds Time_Bounds;

void Bounds__init(Time_Bounds* bound, int s_min, int s_hour, int f_min, int f_hour) {
    bound->s_min = s_min;
    bound->s_hour = s_hour;
    bound->f_min = f_min;
    bound->f_hour = f_hour;
}

Time_Bounds* Bounds__create(int s_min, int s_hour, int f_min, int f_hour) {
    Time_Bounds* bound = malloc(sizeof(Time_Bounds));
    Bounds__init(bound, s_min, s_hour, f_min, f_hour);
    return bound;
}

void Bound_destroy(Time_Bounds* bound) {
    free(bound);
}

Time_Bounds** bounds;

void make_bounds() {
    bounds = malloc(8 * sizeof(Time_Bounds*));
    bounds[0] = Bounds__create(0, 8, 0, 20); 
    bounds[1] = Bounds__create(0, 8, 0, 20);
    bounds[2] = Bounds__create(0, 8, 0, 20);
    bounds[3] = Bounds__create(0, 8, 0, 20);
    bounds[4] = Bounds__create(0, 8, 0, 17);
    bounds[5] = Bounds__create(0, -1, 0, -1);
    bounds[6] = Bounds__create(0, -1, 0, -1);
}

Action* parse(int n, char** tab, int* len) {
    int of = 0;
    Action* res = malloc(n * sizeof(Action));
    for(int i = 0; i < n; i++) {
        char* el = *(tab + i);
        if(strcmp(el, "d-") == 0) {
            res[i - of] = DAY_EARLIER;
        }
        else if(strcmp(el, "d+") == 0) {
            res[i - of] = DAY_LATER;
        }
        else if(strcmp(el, "t-") == 0) {
            res[i - of] = TIME_EARLIER;
        }
        else if(strcmp(el, "t+") == 0) {
            res[i - of] = TIME_LATER;
        }
        else {
            of++;
            continue;
        }
    }
    *(len) = n - of;
    return res;
}

char* Day_toString(Day day) {
    char* res = malloc(16 * sizeof(char)); 
    switch(day) {
        case MON:
            strncpy(res, "Poniedzialek", 16);
            return res;
        case TUE:
            strncpy(res, "Wtorek", 16);
            return res;
        case WED:
            strncpy(res, "Sroda", 16);
            return res;
        case THU:
            strncpy(res, "Czwartek", 16);
            return res;
        case FRI:
            strncpy(res, "Piatek", 16);
            return res;
        case SAT:
            strncpy(res, "Sobota", 16);
            return res;
        case SUN:
            strncpy(res, "Niedziela", 16);
            return res;
        default:
            strncpy(res, "Invalid arg", 16);
            return res;
    }
}

int modulo(int x, int N){
    return (x % N + N) % N;
}

Day Day_nextDay(Day day) {
    return modulo(day + 1, 7);
}

Day Day_prevDay(Day day) {
    return modulo(day - 1, 7);
}

void Term__init(Term* term, int hour, int minute, int duration, Day day) {
    term->hour = hour;
    term->minute = minute;
    term->duration = duration;
    term->day = day;
}

Term* Term__create(int hour, int minute, int duration, Day day) {
    Term* term = malloc(sizeof(Term));
    Term__init(term, hour, minute, duration, day);
    return term;
}

void Term__destroy(Term* term) {
    free(term);
}

bool check_bounds(Term* term) {
    int dt_start_day = bounds[term->day]->s_hour * 60 + bounds[term->day]->s_min;
    int dt_fin_day = bounds[term->day]->f_hour * 60 + bounds[term->day]->f_min;
    int dt_start_les = term->hour * 60 + term->minute;
    int dt_fin_les = term->hour * 60 + term->minute + term->duration;
    return dt_start_les >= dt_start_day && dt_fin_les <= dt_fin_day;
}

void Lesson_init(Lesson* les, int hour, int minute, int duration, Day day, char* name) {
    les->term = Term__create(hour, minute, duration, day);
    les->name = name;
}

Lesson* Lesson_create(int hour, int minute, int duration, Day day, char* name) {
    Lesson* les = malloc(sizeof(les));
    Lesson_init(les, hour, minute, duration, day, name);
    return les;
}

void Lesson__earlierDay(Lesson* lesson) {
   lesson->term->day = Day_prevDay(lesson->term->day);
   if(check_bounds(lesson->term) == true) {
       //printf("Dzien w tyl\n");
   }
   else {
       //printf("Zajecia \"%s\" nie moga byc przesuniete na termin \"%s, %d:%d\"\n", lesson->name, Day_toString(lesson->term->day), lesson->term->hour, lesson->term->minute);
       lesson->term->day = Day_nextDay(lesson->term->day);
   }
}

void Lesson__laterDay(Lesson* lesson) {
   lesson->term->day = Day_nextDay(lesson->term->day);
   if(check_bounds(lesson->term) == true) {
       //printf("Dzien w przod\n");
   }
   else {
       //printf("Zajecia \"%s\" nie moga byc przesuniete na termin \"%s, %d:%d\"\n", lesson->name, Day_toString(lesson->term->day), lesson->term->hour, lesson->term->minute);
       lesson->term->day = Day_prevDay(lesson->term->day);
   }
}

void Lesson__earlierTime(Lesson* lesson) {
    int dh = lesson->term->duration / 60;
    int dm = lesson->term->duration % 60;
    lesson->term->hour = lesson->term->hour - dh;
    lesson->term->minute = lesson->term->minute - dm;
    if(lesson->term->minute < 0) {
        lesson->term->hour -= 1;
        lesson->term->minute += 60;
    }
    if(check_bounds(lesson->term) == true) {
        //printf("Termin w tyl\n");
    } 
    else {
        //printf("Zajecia \"%s\" nie moga byc przesuniete na termin \"%s, %d:%d\"\n", lesson->name, Day_toString(lesson->term->day), lesson->term->hour, lesson->term->minute);
        lesson->term->hour = lesson->term->hour + dh;
        lesson->term->minute = lesson->term->minute + dm;
        if(lesson->term->minute >= 60) {
            lesson->term->hour += 1;
            lesson->term->minute %= 60;
        }
    } 
}

void Lesson__laterTime(Lesson* lesson) {
    int dh = lesson->term->duration / 60;
    int dm = lesson->term->duration % 60;
    lesson->term->hour = lesson->term->hour + dh;
    lesson->term->minute = lesson->term->minute + dm;
    if(lesson->term->minute >= 60) {
        lesson->term->hour += 1;
        lesson->term->minute %= 60;
    }
    if(check_bounds(lesson->term) == true) {
        //printf("Termin w przod\n");
    } 
    else {
        //printf("Zajecia \"%s\" nie moga byc przesuniete na termin \"%s, %d:%d\"\n", lesson->name, Day_toString(lesson->term->day), lesson->term->hour, lesson->term->minute);
        lesson->term->hour = lesson->term->hour - dh;
        lesson->term->minute = lesson->term->minute - dm;
        if(lesson->term->minute < 0) {
            lesson->term->hour -= 1;
            lesson->term->minute += 60;
        }
    } 
}

char* Lesson__toString(Lesson* lesson) {
    char* res = malloc(128 * sizeof(char));
    sprintf(res, "\"%s, %s %d:%d [%d]\"", lesson->name, Day_toString(lesson->term->day), lesson->term->hour, lesson->term->minute, lesson->term->duration);
    return res;
}

char* Term__toString(Term* term) {
    char* res = malloc(128 * sizeof(char));
    sprintf(res, "\"%s %d:%d [%d]\"", Day_toString(term->day), term->hour, term->minute, term->duration);
    return res;
}