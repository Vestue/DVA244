#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "BSTree.h"

/*Det Šr helt tillŒtet att lŠgga till egna hjŠlpfunktioner men de befintliga funktionerna fŒr inte Šndras*/
int findBiggestInLeft(BSTree*);
int fillArrayInOrder(int**, BSTree, int);
BSTree buildSortedHelp(const int arr[], int min, int max);


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

	   Skriv datat frŒn tradet sorterat till arrayen (minsta till storsta)
	   - till detta kanske du behover en hjalpfunktion */

	int size = numberOfNodes(tree);
	int* temp = (int*)malloc(size * sizeof(int));

	if (temp != NULL)
	{
		(void)fillArrayInOrder(&temp, tree, 0);	// Rekursiv funktion som fyller arrayen. 
		// (void) anvands da index som ska anvandas returneras fran funktionen, detta ar ej nodvandigt utanför funktionen

		return temp;
	}
	else
		return NULL;
}

/* Bygger upp ett sorterat, balanserat trad fran en sorterad array */
static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)
{
	/* Bygg rekursivt fran mitten.
	   Mittenelementet i en delarray skapar rot i deltradet
	   Vanster delarray bygger vanster deltrad
	   Hoger delarray bygger hoger deltrad*/

	// Kallar pa en funktion som rekursivt bygger upp tradet och returnerar en adress till roten
	*tree = buildSortedHelp(arr, 0, size - 1);
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
			insertSorted(&(*tree)->left, data);
	}
	else if ((*tree)->data < data)
	{
		if ((*tree)->right == NULL)
			(*tree)->right = createNode(data);
		else
			insertSorted(&(*tree)->right, data);
	}
	assert(find(*tree, data) == 1); // Post-condition: data finns i tradet
}

/* Utskriftsfunktioner
   Vid anrop: anvand stdio som andra argument for att skriva ut pŒ skarmen
   Det racker att ni implementerar LR ordningarna*/
void printPreorder(const BSTree tree, FILE *textfile)
{
	if (tree == NULL)
		return;
	fprintf(textfile, "%d ", tree->data);
	printPreorder(tree->left, textfile);
	printPreorder(tree->right, textfile);
}

void printInorder(const BSTree tree, FILE *textfile)
{
	if (tree == NULL)
		return;
	printInorder(tree->left, textfile);
	fprintf(textfile, "%d ", tree->data);
	printInorder(tree->right, textfile);
}

void printPostorder(const BSTree tree, FILE *textfile)
{
	if (tree == NULL)
		return;
	printPostorder(tree->left, textfile);
	printPostorder(tree->right, textfile);
	fprintf(textfile, "%d ", tree->data);
}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
    // Tank pa att tradet kan vara tomt

	if (tree == NULL)
		return 0;
	else if (tree->data == data)
		return 1;
	
	if (tree->data > data)
		return find(tree->left, data);
	else
		return find(tree->right, data);
}

/* Tar bort 'data' fran tradet om det finns */
void removeElement(BSTree* tree, int data)
{
	/* Inget data ska/kan tas bort fran ett tomt trad
     Tre fall: Ett lov (inga barn), ett barn (vanster eller hoger), tva barn
     
     Glom inte att frigora noden nar den lankats ur tradet*/
	
	if (*tree != NULL)
	{
		BSTree cur = *tree, prev = cur;
		char path = 'U';	// Denna anvands for att avgora om noden med datat naddes genom hoger eller vanster vag. U = Unset

		while (cur != NULL && cur->data != data)
		{
			prev = cur;
			if (cur->data > data)
			{
				cur = cur->left;
				path = 'L';
			}
			else
			{
				cur = cur->right;
				path = 'R';
			}
		}

		if (cur == NULL)	// Utifall datat inte hittas dar det forvantas kommer cur peka pa null
		{
			printf("\nCan't find data.");
			return;
		}

		if (cur->left == NULL && cur->right == NULL)	// Om det ar ett lov
		{
			free(cur);
			if (path == 'R')
				prev->right = NULL;
			else if (path == 'L')
				prev->left = NULL;
			else if (path == 'U')	// Om sista noden tas bort
				*tree = NULL;
		}
		else if (cur->left != NULL && cur->right != NULL)	// Om noden har tva barn
		{
			int newData = findBiggestInLeft(&cur);	// Hittar storsta vardet i vanster deltrad och frigor den noden
			cur->data = newData;
		}
		else	// Om noden har ett barn
		{
			if (path == 'U')	// Om noden saknar foralder
			{
				if (cur->left == NULL)
					*tree = cur->right;
				else
					*tree = cur->left;
			}
			else if (path == 'R')
			{
				if (cur->left == NULL)
					prev->right = cur->right;
				else
					prev->right = cur->left;
			}
			else if (path == 'L')
			{
				if (cur->left == NULL)
					prev->left = cur->right;
				else
					prev->left = cur->left;
			}
			free(cur);
		}
	}
}

/* Returnerar hur manga noder som totalt finns i tradet */
int numberOfNodes(const BSTree tree)
{
	if (tree == NULL)
		return 0;
	
	int leftNodes = numberOfNodes(tree->left);
	int rightNodes = numberOfNodes(tree->right);

	return 1 + leftNodes + rightNodes;
}

/* Returnerar hur djupt tradet ar */
int depth(const BSTree tree)
{
	if (tree == NULL)
		return 0;
	int leftDepth = depth(tree->left);
	int rightDepth = depth(tree->right);

	if (rightDepth > leftDepth)
		return 1 + rightDepth;
	else
		return 1 + leftDepth;
}

/* Returnerar minimidjupet for tradet
   Se math.h for anvandbara funktioner*/
int minDepth(const BSTree tree)
{
	return ceil(log2(numberOfNodes(tree) + 1));	// Rundar uppat
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

	int oldSize = numberOfNodes(*tree);
	int* arr = writeSortedToArray(*tree);
	freeTree(tree);
	buildTreeSortedFromArray(tree, arr, oldSize);	// Bygger tradet 

	free(arr);
	arr = NULL;

	// Post-conditions:
	assert(oldSize == numberOfNodes(*tree));	// tree har lika manga noder som tidigare
	assert(depth(*tree) == minDepth(*tree));	// djupet for tradet ar samma som minimumdjupet for tradet
}

/* Tom tradet och frigor minnet for de olika noderna */
void freeTree(BSTree* tree)
{
	if (*tree == NULL)
		return;

	// Frigor vanstra deltrad och sen hogra deltrad
	freeTree(&(*tree)->left);
	freeTree(&(*tree)->right);
	free(*tree);
	*tree = NULL;	// For att roten ska peka pa null.
	assert(isEmpty(*tree) == 1);	// Post-condition: tradet ar tomt
}

// Returnerar storsta vardet i vanstra deltrad.
int findBiggestInLeft(BSTree* tree)
{
	BSTree cur = *tree, prev = cur;
	cur = cur->left;

	while (cur->right != NULL)
	{
		prev = cur;
		cur = cur->right;
	}
	
	if (cur->left == NULL)
		prev->right = NULL;
	else
		prev->right = cur->left;	// Utifall storsta noden har en nod till vanster maste den lankas ihop innan cur frigors

	int bigNum = cur->data;
	free(cur);
	return bigNum;
}

int fillArrayInOrder(int** arr, BSTree tree, int i)
{
	if (tree == NULL)
		return i;
	i = fillArrayInOrder(arr, tree->left, i);

	// Varje gang data skrivs in i arrayen okas index vilket sedan returneras 
	// for att anvandas av nasta nod i rekursiva funktionen
	*(*arr + i) = tree->data;
	i++;
	i = fillArrayInOrder(arr, tree->right, i);
	return i;
}

BSTree buildSortedHelp(const int arr[], int min, int max)
{
	if (min > max)
		return NULL;
	int nodeIndex = (min + max) / 2;
	BSTree node = createNode(arr[nodeIndex]);

	node->left = buildSortedHelp(arr, min, nodeIndex - 1);	// Bygger vanster deltrad
	node->right = buildSortedHelp(arr, nodeIndex + 1, max); // Bygger hoger deltrad

	return node;
}