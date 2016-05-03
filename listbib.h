#ifndef LISTBIB
#define LISTBIB
#include <stdio.h>
#include <stdlib.h>

//Text in Listenelementen
typedef struct lin_list_lower
{
	char *payload; //mehr als char??
	struct lin_list_lower *next; // Zeiger auf das nächste Element
} LinListCell_lower, *LinList_lower_p;

//Terme als Listenelemente
typedef struct lin_list_upper
{
	char *payloadU;
	LinList_lower_p lowerList;
	struct lin_list_upper *next; // Zeiger auf das nächste Element
} LinListCell_upper, *LinList_upper_p;

LinList_upper_p upperlist_p = null;

// erstelle Liste mit erstem Element
LinList_upper_p createList(char *payloadU){
	LinList_upper_p list_p;
	list_p = (LinList_upper_p) malloc(sizeof(LinListCell_upper));
	list_p->payloadU = payloadU;
	list_p->next = NULL;
	//printf("%s", list_p->payloadU);
	
 	return list_p;
}

// übergeben werden der Beginn der Liste und ein Wert. Erstellt wird ein neues Listenelement, das den Wert enthält. Dieses wird der Liste angehängt
void appendUpper(LinList_upper_p anchor, LinList_upper_p item)
{
	while (anchor->next != NULL)
	{
		anchor = anchor->next;
	}
	anchor->next = item;	
}

void printUpper(LinList_upper_p list) 
{
	while (list->next != NULL)
	{
		printf("%s", list->payloadU);
		list = list->next;
	}
}







/*
LinList_p LinListAllocCell(char *payload)
{
	LinList_p list_p;
	list_p = (LinList_p) malloc(sizeof(LinListCell));
	list_p->payload = payload;
	list_p.next = null;
	return list_p;
}

void LinListFreeCell(LinList_p junk)
{
	printf(junk->payload);
	free(junk);
}

void LinListFree(LinList_p junk)
{
	LinList_p next;
	next = junk->next;
	
	while (next)
	{
		next = junk->next;
		LinListFreeCell(junk);
		junk = next;
	}
}

LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell)
{
	newcell->next = *anchor;
	*anchor = newcell;
	
	return newcell;
}

LinList_p LinListInsertLast(LinList_p *anchor, LinList_p newcell)
{
	while (anchor != );
	*anchor = newcell;
	
	return newcell;
}

LinList_p LinListExtractFirst(LinList_p anchor)
{
	LinList_p first = anchor;
	anchor = anchor->next;
	
	return first;
}

LinList_p NewLinList()
{
	return LinListAllocCell(null);
}
*/

#endif
