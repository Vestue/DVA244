#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "BSTree.h"

/*Det är helt tillåtet att lägga till egna hjälpfunktioner men de befintliga funktionerna får inte ändras*/

/* Statiska hjalpfunktioner anvands av andra funktioner i tradet och ska inte ligga i interfacet (anvandaren behover inte kanna till dessa) */


/* Skapar en tradnod med det givna datat genom att allokera minne for noden. Glom inte att initiera pekarna*/
static struct treeNode* createNode(int data)
{
	// Glom inte att testa sa att allokeringen lyckades
	struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));

	if (newNode != NULL)
	{
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else
		return NULL;
}

/* Returnerar en dynamiskt allokerad array som innehaller tradets data sorterat */
static int* writeSortedToArray(const BSTree tree)
{
	/* Skapa en dynamisk array men ratt storlek

	   Skriv datat från tradet sorterat till arrayen (minsta till storsta)
	   - till detta kanske du behover en hjalpfunktion */

	return NULL; //Ersatt med korrekt returvarde
}

/* Bygger upp ett sorterat, balanserat trad fran en sorterad array */
static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)
{
	/* Bygg rekursivt fran mitten.
	   Mittenelementet i en delarray skapar rot i deltradet
	   Vanster delarray bygger vanster deltrad
	   Hoger delarray bygger hoger deltrad*/
}


/* Implementation av tradet, funktionerna i interfacet */

/* Skapar ett tomt trad - denna funktion ar fardig */
BSTree emptyTree(void)
{
	return NULL;
}

/* Returnerar 1 ifall tradet ar tomt, 0 annars */
int isEmpty(const BSTree tree)
{
	if (tree == NULL)
		return 1;
	else
		return 0;
}

/* Satter in 'data' sorterat i *tree
 Post-condition: data finns i tradet*/
void insertSorted(BSTree* tree, int data)
{
	/*Tank pa att tradet kan vara tomt vid insattning
	  Du bestammer sjalv hur dubletter ska hanteras, ska de inte accepteras eller
	  ska de laggas till vanster/hoger?.
	  Post-condition kan verifieras med hjalp av find(...)*/

	if ((*tree) == NULL)
	{
		*tree = createNode(data);
	}
	else if ((*tree)->data == data)
	{
		printf("Data already in tree. ");	// Dubletter accepteras ej.
		return;
	}
	else if ((*tree)->data > data)
	{
		if ((*tree)->left == NULL)
			(*tree)->left = createNode(data);
		else
			insertSorted((*tree)->left, data);
	}
	else if ((*tree)->data < data)
	{
		if ((*tree)->right == NULL)
			(*tree)->right = createNode(data);
		else
			insertSorted((*tree)->right, data);
	}
	else
		printf("\nUnexpected behaviour in insertSorted");
}

/* Utskriftsfunktioner
   Vid anrop: anvand stdio som andra argument for att skriva ut på skarmen
   Det racker att ni implementerar LR ordningarna*/
void printPreorder(const BSTree tree, FILE *textfile)
{

}

void printInorder(const BSTree tree, FILE *textfile)
{

}

void printPostorder(const BSTree tree, FILE *textfile)
{

}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
    // Tank pa att tradet kan vara tomt
	return -1; //Ersatt med korrekt returvarde
}

/* Tar bort 'data' fran tradet om det finns */
void removeElement(BSTree* tree, int data)
{
	/* Inget data ska/kan tas bort fran ett tomt trad
     Tre fall: Ett lov (inga barn), ett barn (vanster eller hoger), tva barn
     
     Glom inte att frigora noden nar den lankats ur tradet*/
}

/* Returnerar hur manga noder som totalt finns i tradet */
int numberOfNodes(const BSTree tree)
{
	return -1; //Ersatt med korrekt returvarde
}

/* Returnerar hur djupt tradet ar */
int depth(const BSTree tree)
{
	return -1; //Ersatt med korrekt returvarde
}

/* Returnerar minimidjupet for tradet
   Se math.h for anvandbara funktioner*/
int minDepth(const BSTree tree)
{
	return -1; //Ersatt med korrekt returvarde
}

/* Balansera tradet sa att depth(tree) == minDepth(tree) */
void balanceTree(BSTree* tree)
{
	/* Forslag pa algoritm:
	   - overfor tradet till en dynamiskt allokerad array med writeSortedToArray()
	   - tom tradet med freeTree()
	   - bygg upp tradet rekursivt fran arrayen med buildTreeSortedFromArray()
	   - frigor minne for den dynamiskt allokerade arrayen


	   Post-conditions:
	   - tree har lika manga noder som tidigare
	   - djupet for tradet ar samma som minimumdjupet for tradet */
}

/* Tom tradet och frigor minnet for de olika noderna */
void freeTree(BSTree* tree)
{
	// Post-condition: tradet ar tomt
}