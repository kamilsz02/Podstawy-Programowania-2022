#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum Day{
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
};

typedef enum Day Day;

struct Lesson{
    char* name;
    Day day;
    int hour;
    int minute;
    int duration;
};

typedef struct Lesson Lesson;

struct Node{
    Lesson lesson;
    struct Node* next;
};

typedef struct Node Node;

struct List{
    Node* head;
};

typedef struct List List;

void Node_Insert(Node* node, Lesson lesson) {
    if(node == NULL) {
        fprintf(stderr, "Wezel nie istnieje\n");
    }
    node->lesson.name = lesson.name;
    node->lesson.day = lesson.day;
    node->lesson.hour = lesson.hour;
    node->lesson.minute = lesson.minute;
    node->lesson.duration = lesson.duration;
}

void List_Insert(List* list, Lesson lesson, bool front){
    if(list == NULL) {
        fprintf(stderr, "Lista nie istnieje\n");
        exit(EXIT_FAILURE);
    }
    Node* node = NULL;
    node = malloc(sizeof(Node));
    Node_Insert(node, lesson);
    node->next = NULL;
    if(list->head == NULL) {
        list->head = node;
        list->head->next = NULL;
    }
    else {
        if(front == true) {
            node->next = list->head;
            list->head = node;
        }
        else {
            Node* cur = list->head;
            while(cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = node;
        }
    }
}

bool Lesson_Equals(Lesson lesson1, Lesson lesson2) {
    return (lesson1.name == lesson2.name) && 
           (lesson1.day == lesson2.day) &&
           (lesson1.hour == lesson2.hour) &&
           (lesson1.minute == lesson2.minute) &&
           (lesson1.duration == lesson2.duration)
           ? true : false;
}

void List_Remove(List* list, Lesson lesson) {
    if(list == NULL) {
        fprintf(stderr, "Lista nie istnieje\n");
        exit(EXIT_FAILURE);
    }
    Node* cur = list->head;
    if(Lesson_Equals(cur->lesson, lesson)) {
        list->head = list->head->next;
        free(cur);
        return;
    }
    Node* prev = NULL;
    while(cur != NULL && Lesson_Equals(cur->lesson, lesson) != true) {
        prev = cur;
        cur = cur->next;
    }
    if(cur == NULL) {
        return;
    }
    prev->next = cur->next;
    free(cur);
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

char* Lesson__toString(Lesson lesson) {
    char* res = malloc(128 * sizeof(char));
    char* day_name = Day_toString(lesson.day);
    sprintf(res, "\"%s, %s %d:%d [%d]\"", lesson.name, day_name, lesson.hour, lesson.minute, lesson.duration);
    free(day_name);
    return res;
}

void List_Print(List* list) {
    if(list == NULL) {
        fprintf(stderr, "Lista nie istnieje\n");
        exit(EXIT_FAILURE);
    }
    char* out = NULL;
    for(Node* cur = list->head; cur != NULL; cur = cur->next) {
        out = Lesson__toString(cur->lesson);
        printf("%s\n", out);
        free(out);
    }
}

void List_Destroy(List** list) {
    if(*list == NULL) {
        fprintf(stderr, "Lista nie istnieje\n");
        exit(EXIT_FAILURE);
    }
    Node* cur = (*list)->head;
    Node* prev = NULL;
    while(cur != NULL) {
        prev = cur;
        free(prev);
        cur = cur->next;
    }
    free(*list);
    *list = NULL;
}

int main() {
    List* list = NULL;
    list = malloc(sizeof(List));
    list->head = NULL;
    Lesson lesson1;
    lesson1.name = "Podstawy Programowania";
    lesson1.day = THU;
    lesson1.hour = 12;
    lesson1.minute = 0;
    lesson1.duration = 90;

    Lesson lesson2;
    lesson2.name = "Analiza 2";
    lesson2.day = MON;
    lesson2.hour = 9;
    lesson2.minute = 35;
    lesson2.duration = 90;

    Lesson lesson3;
    lesson3.name = "PiS";
    lesson3.day = TUE;
    lesson3.hour = 10;
    lesson3.minute = 15;
    lesson3.duration = 90;

    List_Insert(list, lesson1, true);
    List_Insert(list, lesson2, false);
    List_Insert(list, lesson3, false);
    List_Print(list);
    List_Remove(list, lesson1);
    List_Print(list);
    List_Destroy(&list);
    List_Print(list);

    return 0;
}

