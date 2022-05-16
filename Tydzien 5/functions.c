#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

typedef enum Day Day;
typedef enum Action Action;

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

char* Action_toString(Action action) {
    char* res = malloc(32 * sizeof(char));
    switch(action) {
        case DAY_EARLIER:
            strncpy(res, "Dzien w tyl", 32);
            return res;
        case DAY_LATER:
            strncpy(res, "Dzien w przod", 32);
            return res;
        case TIME_EARLIER:
            strncpy(res, "Termin w tyl", 32);
            return res;
        case TIME_LATER:
            strncpy(res, "Termin w przod", 32);
            return res;
        default:
            strncpy(res, "Invalid arg", 32);
            return res;
    }
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

Day shift(Day start_day, Action* actions, int n) {
    for(int i = 0; i < n; i++) {
        Action action = actions[i];
        if(action == 0) {
            start_day = Day_prevDay(start_day);
        }
        else if(action == 1) {
            start_day = Day_nextDay(start_day);
        }
        else {
            continue;
        }
    }
    return start_day;
}

Day string_to_day(char* in) {
    Day res;
    if(strcmp(in, "Mon") == 0) {
        res = MON;
        return res;
    }
    if(strcmp(in, "Tue") == 0) {
        res = TUE;
        return res;
    }
    if(strcmp(in, "Wed") == 0) {
        res = WED;
        return res;
    }
    if(strcmp(in, "Thu") == 0) {
        res = THU;
        return res;
    }
    if(strcmp(in, "Fri") == 0) {
        res = FRI;
        return res;
    }
    if(strcmp(in, "Sat") == 0) {
        res = SAT;
        return res;
    }
    if(strcmp(in, "Sun") == 0) {
        res = SUN;
        return res;
    }
    else return 0;
}