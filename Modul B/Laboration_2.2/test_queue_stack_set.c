/*******************************************************************/
/* Kon, stacken och settet ska implementeras som lankade listor    */
/* De olika interfacen hittar du i queue.h, stack.h och set.h      */
/*******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "stack.h"
#include "set.h"

// EXAMINATION
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*Gor anrop i main till den meny du vill kora*/
void menuQueue();
void menuStack();
void menuSet();

/*Kor dessa testfunktioner for att verifiera att dina ADT:er fungerar som de ska*/
void testFunctionQueue();
void testFunctionStack();
void testFunctionSet();

// EXAMINATION
void calculatePostfixExpression(char str[]);

int main(void)
{
    //testFunctionQueue();
    //testFunctionStack();
    //testFunctionSet();

    // EXAMINATION
    // Testar alla postfixa uttryck i tabellen
    printf("Test: %s", "4 8 3 * +");
    calculatePostfixExpression("4 8 3 * +");

    printf("Test: %s", "4 8 + 3 *");
    calculatePostfixExpression("4 8 + 3 *");

    printf("Test: %s", "4 8 - 3 +");
    calculatePostfixExpression("4 8 - 3 +");

    printf("Test: %s", "8 4 / 3 +");
    calculatePostfixExpression("8 4 / 3 +");

    printf("Test: %s", "2 3 1 * + 9 -");
    calculatePostfixExpression("2 3 1 * + 9 -");

    printf("Test: %s", "6 2 / 1 2 + *");
    calculatePostfixExpression("6 2 / 1 2 + *");

    return 0;
}

// EXAMINATION
// Initierar en stack och loopar sedan igenom hela strängen med en for-loop.
// Kollar först om indexet innehåller en siffra, isåfall ska den pushas till stacken.
// Om det inte är en siffra kollar jag om det är en av operatörerna som ska hanteras,
// isåfall poppas två från stacken, operatören utförs på dem och resultatet av detta pushas till stacken.
// Om det varken är en operator eller en siffra kommer loopen hoppa vidare till nästa index.
// När loopen har gått igenom hela strängen kommer stacken endast innehålla ett element, detta kan då poppas för att få slutresultatet.
void calculatePostfixExpression(char str[])
{
    Stack myStack = initializeStack();
    int len = strlen(str), result = 0, var1, var2;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            // Använder atoi för att konvertera char till int och pushar det till stacken
            push(&myStack, atoi(&str[i]));

            // Utifall ett tal som är större än 9 har pushats måste loopen flytta sig framåt till talets avslut
            // Detta förutsätter att whitespace används för att skilja tal och operatorer åt
            while (str[i] != ' ')
                i++;
        }
        else if (str[i] == '*' || str[i] == '+' || str[i] == '-' || str[i] == '/')
        {
            // Poppar två, räknar ut resultated av operatorn på dessa och pushar resultatet till stacken

            var1 = peekStack(myStack);
            pop(&myStack);
            var2 = peekStack(myStack);
            pop(&myStack);
            if (str[i] == '*')
                result = var2 * var1;
            else if (str[i] == '+')
                result = var2 + var1;
            else if (str[i] == '-')
                result = var2 - var1;
            else
                result = var2 / var1;
            push(&myStack, result);
        }
    }
    result = peekStack(myStack);
    pop(&myStack);
    printf("\nResult: %d\n\n", result);
}


void menuQueue()
{
    int choice;
    char c;
    Data data;
    Queue myQueue = initializeQueue();
    
    do
    {
        printf("\n\n---------MENU QUEUE--------\n"
               "1 - Add to queue (enqueue)\n"
               "2 - Remove from queue (dequeue)\n"
               "3 - Peek at front in queue\n"
               "4 - Is queue empty?\n"
               "5 - Quit queue menu\n"
               "--------------------------------\n"
               "Choice: ");
        scanf("%d", &choice);
        while((c = getchar()) != '\n' && c != EOF);
        
        switch(choice)
        {
            case 1: printf("Data to add: ");
                    scanf("%d", &data);
                    enqueue(&myQueue, data);
                    printf("Queue: ");
                    printQueue(myQueue, stdout);
                    break;
            case 2: dequeue(&myQueue);
                    printf("The first element in queue is removed\n");
                    printf("Queue: ");
                    printQueue(myQueue, stdout);
                    break;
            case 3: printf("First element in queue: %d\n", peekQueue(myQueue));
                    printf("Queue: ");
                    printQueue(myQueue, stdout);
                    break;
            case 4: if(queueIsEmpty(myQueue) == 1)
                        printf("Queue is empty\n");
                    else
                        printf("Queue is not empty\n");
                    break;
            case 5: printf("Ending menu\n"); break;
            default: printf("Wrong input\n");
        }
        
    }while(choice != 5);
    
}

void menuStack()
{
    int choice;
    char c;
    Data data;
    Stack myStack = initializeStack();
    
    do
    {
        printf("\n\n---------MENU STACK--------\n"
               "1 - Add to stack (push)\n"
               "2 - Remove from stack (pop)\n"
               "3 - Peek at top in stack\n"
               "4 - Is stack empty?\n"
               "5 - Quit stack menu\n"
               "--------------------------------\n"
               "Choice: ");
        scanf("%d", &choice);
        while((c = getchar()) != '\n' && c != EOF);
        
        switch(choice)
        {
            case 1: printf("Data to push: ");
                    scanf("%d", &data);
                    push(&myStack, data);
                    printf("Stack: ");
                    printStack(myStack, stdout);
                    break;
            case 2: pop(&myStack);
                    printf("The top in stack is removed\n");
                    printf("Stack: ");
                    printStack(myStack, stdout);
                    break;
            case 3: printf("Top element in stack: %d\n", peekStack(myStack));
                    printf("Stack: ");
                    printStack(myStack, stdout);
                    break;
            case 4: if(stackIsEmpty(myStack) == 1)
                    printf("Stack is empty\n");
            else
                printf("Stack is not empty\n");
                break;
            case 5: printf("Ending menu\n"); break;
            default: printf("Wrong input\n");
        }
        
    }while(choice != 5);
}

void menuSet()
{
    int choice;
    char c;
    Data data;
    Set mySet = initializeSet();
    
    do
    {
        printf("\n\n---------MENU SET----------\n"
               "1 - Add to set\n"
               "2 - Remove from set\n"
               "3 - Is data in set?\n"
               "4 - Quit set menu\n"
               "--------------------------------\n"
               "Choice: ");
        scanf("%d", &choice);
        while((c = getchar()) != '\n' && c != EOF);
        
        switch(choice)
        {
            case 1: printf("Data to add: ");
                    scanf("%d", &data);
                    addToSet(&mySet, data);
                    printf("Set: ");
                    printSet(mySet, stdout);
                    break;
            case 2: printf("Data to remove: ");
                    scanf("%d", &data);
                    removeFromSet(&mySet, data);
                    printf("Data %d is removed from set\n", data);
                    printf("Set: ");
                    printSet(mySet, stdout);
                    break;
            case 3: printf("Data to search for: ");
                    scanf("%d", &data);
                    if(isInSet(mySet, data) == 1)
                        printf("%d found in set\n", data);
                    else
                        printf("%d not found in set", data);
                    printf("Set: ");
                    printSet(mySet, stdout);
                    break;
            case 4: printf("Ending menu\n"); break;
            default: printf("Wrong input\n");
        }
        
    }while(choice != 5);
}

void testFunctionQueue()
{
    Queue myQueue = initializeQueue();
    
    assert(queueIsEmpty(myQueue));
    enqueue(&myQueue, 5);
    enqueue(&myQueue, 7);
    enqueue(&myQueue, 3);
    assert(!queueIsEmpty(myQueue));
    assert(peekQueue(myQueue) == 5);
    dequeue(&myQueue);
    assert(peekQueue(myQueue) == 7);
    dequeue(&myQueue);
    assert(peekQueue(myQueue) == 3);
    dequeue(&myQueue);
    assert(queueIsEmpty(myQueue));
    enqueue(&myQueue, 8);
    assert(peekQueue(myQueue) == 8);

    printf("Congratulations, your Queue passed the test program\n\n");
}

void testFunctionStack()
{
    Stack myStack = initializeStack();
    
    assert(stackIsEmpty(myStack));
    push(&myStack, 5);
    push(&myStack, 2);
    push(&myStack, 9);
    assert(!stackIsEmpty(myStack));
    assert(peekStack(myStack) == 9);
    pop(&myStack);
    assert(peekStack(myStack) == 2);
    pop(&myStack);
    assert(peekStack(myStack) == 5);
    push(&myStack, 4);
    assert(peekStack(myStack) == 4);
    pop(&myStack);
    pop(&myStack);
    assert(stackIsEmpty(myStack));
    push(&myStack, 8);
    assert(peekStack(myStack) == 8);
    
    printf("Congratulations, your Stack passed the test program\n\n");
}

void testFunctionSet()
{
    Set mySet = initializeSet();
    
    assert(isEmpty(mySet));
    addToSet(&mySet, 4);
    addToSet(&mySet, 1);
    addToSet(&mySet, 8);
    assert(!isEmpty(mySet));
    assert(isInSet(mySet, 1));
    assert(isInSet(mySet, 4));
    assert(isInSet(mySet, 8));
    addToSet(&mySet, 1);
    
    int occurances = 0;
    for(struct node *current = mySet; current != NULL; current = current->next)
        if(current->data == 1)
            occurances++;
    assert(occurances == 1);
    
    removeFromSet(&mySet, 8);
    assert(!isInSet(mySet, 8));
    removeFromSet(&mySet, 1);
    removeFromSet(&mySet, 4);
    assert(isEmpty(mySet));
    addToSet(&mySet, 3);
    assert(isInSet(mySet, 3));
    
    printf("Congratulations, your Set passed the test program\n\n");
}
