/**************************************************
* Ragnar Winblad von Walter, rwr21002, 199702221798
* DVA244
* Laboration 2.2
***************************************************/

#include "queue.h"
#include<assert.h>

/*Har ar det viktigt att ateranvanda koden som du redan skrivit for den lankade listan.
  Ateranvandning betyder inte att man kopierar koden eller skriver av den, ateranvander
  gor man genom att anropa redan implementerade funktioner.*/

/*Funktionen ar fardig*/
Queue initializeQueue(void)
{
    return NULL;
}

int queueIsEmpty(const Queue queue)
{
    return isEmpty(queue);
}

/*Postcondition: data ar tillagt sist i kon*/
void enqueue(Queue* queue, const Data data)
{
   //Tips: Att lagga till i en ko implementerad som en lankad lista ar precis som att lagga till forst eller sist i en lankad lista
    addLast(queue, data);
    assert(getLastElement(*queue) == data);
}

/* Precondition: kon är ej tom */
void dequeue(Queue* queue)
{
    //Tips: Att ta bort fran en ko implementerad som en lankad lista ar precis som att ta bort sist eller forst i en lankad lista.
    assert(isEmpty(*queue) != 1);
    removeFirst(queue);
}

/* Precondition: kon är ej tom */
Data peekQueue(const Queue queue)
{
    assert(isEmpty(queue) != 1);
    return getFirstElement(queue);
}


/* Anvands for testning och felsokning
   Tips: det kan vara bra att ocksa notera i utskriften vart borjan respektive slutet på kon är */
void printQueue(const Queue queue, FILE *textfile)
{
    printf("\nFirst to last: ");
    printList(queue, textfile);
}


