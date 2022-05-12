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

int main(int argc, char** argv) {
    Day day = MON;
    char* out = Day_toString(Day_nextDay(day));
    printf("%s", out);
    free(out);

    return 0;
}