/**************************************************
* Ragnar Winblad von Walter, rwr21002, 199702221798
* DVA244
* Laboration 2.1
***************************************************/

#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*Det Šr helt tillŒtet att lŠgga till egna hjŠlpfunktioner men de befintliga funktionerna fŒr inte Šndras*/

/*Hjalpfunktion till add
  Allokerar minne for en ny nod
  om allokeringen lyckades initieras data samt pekare (pekare initieras till NULL).
  Den nya noden (eller NULL) returneras.*/
static struct node* createListNode(const Data data)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp != NULL)
    {
        temp->data = data;
        temp->next = NULL;      
        temp->previous = NULL;
        // Pekarna next och previous initieras som NULL for att sedan kunna pekas om utifran behov.

        return temp;
    }
    else
    {
        return NULL;
    }
}

/*Returnera en tom lista - funktionen ar fardig*/
List createEmptyList(void)
{
    return NULL;
}


/*Ar listan tom?
  Returnerar 1 om den Šr tom, annars 0*/
int isEmpty(const List list)
{
    if (list == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*Lagg till nod forst i listan*/
/*Postcondition: Det nya datat ligger forst i listan (testa med assert)*/
void addFirst(List *list, const Data data)
{
    //Anropa createListNode for att skapa den nya noden
    //Glom inte att testa att den nya noden faktiskt kunde skapas/tilldelas minne innan du fortsatter
    //Tank pa att listan kan vara tom nar en ny nod laggs till

    List newNode = createListNode(data);
    if (newNode != NULL)
    {
        // Om det redan finns en nod pa forsta platsen maste den frigoras.
        if (*list != NULL) 
        {
			newNode->next = *list;
			(*list)->previous = newNode;
        }
		*list = newNode;
    }

	// Om allokeringen misslyckas kommer den forsta noden var som tidigare, dvs inte forrandras men ett felmeddelande printas.
	// OBS! Kan behova andras till en assert istallet.
	else
	{
		printf("Failed to add new node. ");
	}

    assert((*list)->data == data); // Postcondition: Det nya datat ligger forst i listan
}

/*Lagg till nod sist i listan
  Tips, nar du hittat ratt plats kan du anvanda funktionen addFirst for att lagga till*/
void addLast(List *list, const Data data)
{
	List temp = *list;

	if (isEmpty(temp))	//Antar att det ska vara mojligt att anvanda funktionen trots att listan ar tom.
	{
		addFirst(&temp, data);
		*list = temp;

	}
	else
	{
        List newNode = createListNode(data);
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
        temp->next = newNode;
        newNode->previous = temp;
	}
}

/*Ta bort forsta noden i listan
  Precondition: listan ar inte tom (testa med assert)
  Noden ska lankas ur och minnet frigoras, resten av listan ska finnas kvar*/
void removeFirst(List *list)
{
    //Glom inte att frigora minnet for den nod som lankas ur listan.
    //Tank pa att listans huvud efter bortlankningen maste peka pa den nod som nu ar forst.

	assert(*list != NULL);	// Precondition: listan ar inte tom.
    
    List current = *list;
    if (current->next == NULL)
    {
        free(current);
        *list = NULL;
    }
    else
    {
        (*list) = current->next;
        free(current);
        (*list)->previous = NULL;
    }
}

/*Ta bort sista noden i listan
  Precondition: listan ar inte tom (testa med assert)t*/
void removeLast(List *list)
{
    //Glom inte att frigora minnet for den nod som lankas ur listan.
    //Tank pa att den nod som nu ar sist inte pekar nagonstans, dess pekare maste nollstallas
	assert(*list != NULL);

	List temp = *list;
	if (temp->next == NULL && temp->previous == NULL)	//Om det bara finns en enda nod ska den frigoras direkt.
	{
		free(temp);
		*list = NULL;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->previous->next = NULL;
		free(temp);
	}
}

/*Ta bort data ur listan (forsta forekomsten)
  Returnera 1 om datat finns, annars 0
  Tips, nar du hittar ratt nod kan du anvanda en av de ovanstaende funktionerna for att ta bort noden*/
int removeElement(List *list, const Data data)
{
    if (*list == NULL)
        return 0;

    List temp = *list;

    while (temp->data != data && temp->next != NULL)    
    {
        temp = temp->next;
    }
    if (temp->data != data)
        return 0;
    else if (temp->next == NULL && temp->previous == NULL)  // Om det ar enda noden.
    {
        free(temp);
        *list = NULL;
    }
    else if (temp->next == NULL)                            // Om det ar sista noden.
    {
        removeLast(&temp);  
    }
    else if (temp->previous == NULL)                        // Om det ar forsta noden.
    {
        *list = temp->next;
        removeFirst(&temp); 
    }
    else                                                    // Om noden ar mellan tva noder.
    {
        List toRemove = temp;
        temp = toRemove->next;
        temp->previous = toRemove->previous;
        temp->previous->next = temp;
        free(toRemove);
        toRemove = NULL;
    }    
    return 1;
}

/*Finns data i listan?
  Om datat finns returneras 1, annars 0
  Tank pa att listan kan vara tom*/
int search(const List list, const Data data)
{
    if (list == NULL)
        return 0;
    else if (list->data == data)
        return 1;
    return search(list->next, data);
}

/*Returnera antalet noder i listan*/
int numberOfNodesInList(const List list)
{
    if (list == NULL)
        return 0;
    return 1 + numberOfNodesInList(list->next);
}

/*Ta bort alla noder ur listan
  Glom inte att frigora minnet
  Postcondition: Listan ar tom, *list Šr NULL (testa med assert)*/
void clearList(List *list)
{
    //Alla noder maste tas avallokeras en och en, det racker inte att endast frigora list.
    List current = *list;
    while (*list != NULL)
    {
        if (current->next == NULL)
        {
            free(current);
            *list = NULL;
        }
        else
        {
            current = current->next;
            free(current->previous);
            current->previous = NULL;
        }
    }
    assert(*list == NULL);
}

/*Skriv ut listan
  Vid anropet kan man ange stdout som argument 2 for att skriva ut pŒ skarmen.
  Anvanda fprintf for att skriva ut.
  Den har typen av utskriftfunktion blir mer generell da man kan valja att skriva ut till skarmen eller till fil.*/
void printList(const List list, FILE *textfile)
{
    // Antar att strommen oppnas och stangs utanfor funktionen.
    if (list == NULL)
        return;
    fprintf(textfile, "%d ", list->data);
    printList(list->next, textfile);
}

/*Returnera forsta datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getFirstElement(const List list)
{
    assert(list != NULL);
    if (list->previous == NULL)
        return list->data;

    // Head-pekaren pekar alltid på forsta noden men utifall en funktion skickar in en nod-pekare
    // som inte ar den forsta noden kan satsen under vara anvandbar.
    return getFirstElement(list->previous); //Stegar bakat till forsta noden.
}

/*Returnera sista datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getLastElement(const List list)
{
    assert(list != NULL);
    if (list->next == NULL)
        return list->data;
    return getLastElement(list->next);
}
