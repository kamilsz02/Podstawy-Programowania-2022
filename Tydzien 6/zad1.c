#include <stdio.h>
#include <stdlib.h>
#define INT_MIN -2147483648

struct Stack{
    int* elements;
    int size;
    int top;
};

typedef struct Stack Stack;

Stack* Stack__create(int size) {
    if(size <= 0) {
        fprintf(stderr, "Nie mogę utworzyć stosu o podanym rozmiarze\n");
        exit(EXIT_FAILURE);
    }
    int* content = NULL;
    content = malloc(size * sizeof(int));
    if(content == NULL) {
        fprintf(stderr, "Nie udalo sie utworzyc stosu\n");
        exit(EXIT_FAILURE);
    }
    Stack* stack = malloc(sizeof(Stack));
    stack->elements = content;
    stack->top = -1;
    stack->size = size;
    return stack;
}

void Stack__destroy(Stack** stack) {
    if((*stack) == NULL) {
        fprintf(stderr, "Stos, ktorego pamiec chcesz zwolnic nie istnieje\n");
        return;
    }
    free((*stack)->elements);
    free((*stack));
    (*stack) = NULL;
}

void Stack__push(Stack* stack, int number) {
    if(stack == NULL) {
        fprintf(stderr, "Stos, do ktorego chcesz dodac element nie istnieje\n");
        return;
    }
    else if(stack->top + 1 == stack->size) {
        fprintf(stderr, "Na stosie nie ma juz miejsca\n");
        return;
    }
    stack->top++;
    stack->elements[(stack->top)] = number;
}

int Stack__pop(Stack* stack) {
     if(stack == NULL) {
        fprintf(stderr, "Stos, z ktorego chcesz usunac element nie istnieje\n");
        exit(EXIT_FAILURE);
    }
    else if(stack->top == -1) {
        fprintf(stderr, "Stos jest pusty\n");
        return INT_MIN;
    }
    int n = stack->elements[(stack->top)];
    stack->top--;
    return n;
}

int isEmpty(Stack* stack){
    return stack->top == -1 ? 1 : 0;
}

void Stack__print(Stack* stack) {
    Stack* stack2 = Stack__create(stack->size);
    while(isEmpty(stack) == 0){
        int n = Stack__pop(stack);
        printf("%d\n", n);
        Stack__push(stack2, n);
    }
    while(isEmpty(stack2) == 0){
        int n = Stack__pop(stack2);
        Stack__push(stack, n);
    }
    Stack__destroy(&stack2);
}

int main() {
    Stack* stack = NULL;

    Stack__destroy(&stack); // Wypisuje: "Stos nie istnieje"
    stack = Stack__create(3); // Utworzenie stosu o rozmiarze 3
    Stack__push(stack, 3); // Dodanie liczby 3 na stos
    Stack__push(stack, 5);
    Stack__push(stack, 2);
    Stack__push(stack, 4); // Przekraczamy rozmiar stosu — funkcja nie powinna na to pozwolić
    Stack__print(stack); // Funkcja powinna wypisać:
                         // 2
                         // 5
                         // 3
    printf("%d\n", Stack__pop(stack)); // Wypisuje 2
    Stack__print(stack); // Funkcja powinna wypisać:
                         // 5
                         // 3
    printf("%d\n", Stack__pop(stack)); // Wypisuje 5
    printf("%d\n", Stack__pop(stack)); // Wypisuje 3
    int liczba = Stack__pop(stack); // Próbujemy zdjąć wartość z pustego stosu  — funkcja nie powinna na to pozwolić — powinna zwrócić wartość specjalną, na przykład INT_MIN
    printf("%d\n", liczba);
    Stack__destroy(&stack); // Likwidacja stosu
    Stack__destroy(&stack); // Wypisuje: "Stos nie istnieje"
    return 0;
}