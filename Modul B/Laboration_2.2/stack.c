#include "stack.h"
#include<assert.h>

/*Funktionen ar fardig*/
Stack initializeStack(void)
{
    return createEmptyList();
}

int stackIsEmpty(const Stack stack)
{
    return 0; // Ersatt denna rad med ratt returvarde
}

/* Postcondition 'data' ligger overst på stacken */
void push(Stack* stack, const Data data)
{
    
}

/* Precondition: stacken far inte vara tom */
void pop(Stack* stack)
{
    
}

/* Precondition: stacken far inte vara tom */
Data peekStack(const Stack stack)
{
     return 0; // Ersatt denna rad med ratt returvarde
}

/* Anvands for testning och felsokning
 Tips: det kan vara bra att ocksa notera i urskriften vart toppen pa stacken ar */
void printStack(const Stack stack, FILE *textFile)
{
    
}
