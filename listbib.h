#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @param payload Variable
 * @param next    Pointer auf nächstes Listenelement
 */
typedef struct varlist
{
	char *payload;
	struct varlist *next;
	struct varlist *previous;
} VarlistCell, *Varlist_p;

/**
 * @param function Funktion
 * @param varlist  Pointer auf Variablenliste (bzw. erste Zelle der Liste)
 * @param next     Pointer auf nächstes Listenelement
 */
typedef struct termlist
{
	char *function;
	VarlistCell *varlist;
	struct termlist *next;
	struct termlist *previous;
} TermlistCell, *Termlist_p;

/**
 * @param termlist Liste der Terme in der Klausel (Zeile)
 * @param next     Pointer auf nächstes Listenelement
 */
typedef struct clause
{
	TermlistCell *termlist;
	struct clause *next;
	struct clause *previous;
} ClauseCell, *Clause_p;


// ---------- Varlist ----------

/**
 * @param  payload    Variable/Parameter
 * @return newVarlist Pointer auf neu erstellte Varlist
 */
Varlist_p createVarlistCell(char *payload) 
{
	Varlist_p newVarlist;
	newVarlist = malloc(sizeof(VarlistCell));
	
	newVarlist->payload = strdup(payload);
	newVarlist->next = NULL;
	newVarlist->previous = NULL;

	return newVarlist;
}

/**
 * Neue Zelle wird einer Variabel-Liste vorne angehängt
 * @param anchor  Erstes Listenelement
 * @param newVar  Listenelement das angehängt werden soll
 * @return anchor Pointer 
 */
Varlist_p addVarlistCell(Varlist_p *anchor, Varlist_p newVar)
{
	newVar->next = *anchor;
	newVar->previous = NULL;
	if (*anchor != NULL)
		(*anchor)->previous = newVar;	
		
	return newVar;
}

/**
 * Weil alle Listen von hinten nach vorne gefüllt werden, kann eine Liste
 * einer anderen einfach vorne angehängt werden
 * @param  anchorList Pointer auf aktuelle Varlist
 * @param  appendList Pointer auf Liste die an Varlist angehängt werden soll
 * @return appendList Pointer auf erstes Listenelement der neuen Liste
 */
Varlist_p appendVarlist(Varlist_p anchorList, Varlist_p appendList)
{
	if (anchorList == NULL)
		return appendList;
	if (appendList == NULL)
		return anchorList;

	Varlist_p current = appendList;
	while (current->next != NULL)
		current = current->next;
	current->next = anchorList;

	return appendList;
}


// ---------- Termlist ----------

/**
 * @param  varlistAnchor Pointer auf Varlist
 * @param  function      Funktion zu der die Termliste gehört
 * @return newTermlist   Neue Termliste
 */
Termlist_p createTermlistCell(Varlist_p varlistAnchor, char *function)
{
	Termlist_p newTermlist;
	newTermlist = malloc(sizeof(TermlistCell));
	
	newTermlist->function = strdup(function);
	newTermlist->varlist = varlistAnchor;
	newTermlist->next = NULL;
	newTermlist->previous = NULL;

	return newTermlist;
}

/**
 * @param  anchor  Beginn der Termliste
 * @param  newTerm Zelle, die der Termliste vorne angehängt wird
 * @return anchor  Neuer Beginn der Termliste
 */
Termlist_p addTermlistCell(Termlist_p *anchor, Termlist_p newTerm)
{
	newTerm->next = *anchor;
	newTerm->previous = NULL;
	if (*anchor != NULL)
		(*anchor)->previous = newTerm;
	*anchor = newTerm;

	return *anchor;
}


/**
 * @param  anchorList Aktueller Listenbeginn
 * @param  appendList Liste die angehängt werden soll
 * @return appendList Neuer Listenbeginn
 */
Termlist_p appendTermlist(Termlist_p anchorList, Termlist_p appendList)
{
	if (anchorList == NULL)
		return appendList;
	if (appendList == NULL)
		return anchorList;

	Termlist_p current = appendList;
	while (current->next != NULL)
		current = current->next;
	current->next = anchorList;
	anchorList->previous = current;

	return appendList;
}


// ---------- Clauselist ----------

// Globale Anker-Deklaration
Clause_p clauseAnchor = NULL;

/**
 * @param  anchorTermlist Termliste der Klausel
 * @return newClause      Neue Klausel
 */
Clause_p createClause(Termlist_p anchorTermlist)
{
	Clause_p newClause;
	newClause = malloc(sizeof(ClauseCell));

	newClause->termlist = anchorTermlist;	
	newClause->next = NULL;
	newClause->previous = NULL;
	
	return newClause;
}

/**
 * @param  anchorClauselist Beginn der Klauselliste
 * @param  newClause        Neue Klausel die der Klauselliste angehängt werden soll
 * @return anchorClauselist Neuer Beginn der Klauselliste
 */
Clause_p addClause(Clause_p *anchorClauselist, Clause_p newClause)
{
	newClause->next = *anchorClauselist;
	newClause->previous = NULL;
	if (*anchorClauselist != NULL)
		(*anchorClauselist)->previous = newClause;
	*anchorClauselist = newClause;

	return *anchorClauselist;
}

