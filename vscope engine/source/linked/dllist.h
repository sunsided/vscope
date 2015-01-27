/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2003, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		dllist.h
	Beschreibung:	Doubly Linked List Definition
	Revision:		1
	Erstellt:		MMT, 26. Juni 2003 09:12

	Changelog:
	[1]		26. Juni 2003 09:12
			Erstellt

===========================================================================*/

#pragma once

#ifndef DLLIST_DEFINED
#define DLLIST_DEFINED

#include "..\defines.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
class DLLIST;

/*---------------------------------------------------------------------------
	Strukturen für den DLLIST-NODE
---------------------------------------------------------------------------*/
class DLLISTNODE {
friend DLLIST;
//:: Die Membervariablen ....................................................
protected:
	DLLISTNODE					*m_pDLListPrevious;
	DLLISTNODE					*m_pDLListNext;

//:: Die Konstruktoren ......................................................
public:
							DLLISTNODE();

//:: Die Destruktoren .......................................................
public:
							~DLLISTNODE();

//:: Akzessor ...............................................................
protected:
	DLLISTNODE*				GetPrevious() const;
	void					GetPrevious(DLLISTNODE* out_pPrevious) const;
	void					SetPrevious(DLLISTNODE* in_pNewPrevious);
	DLLISTNODE*				GetNext() const;
	void					GetNext(DLLISTNODE* out_pNext) const;
	void					SetNext(DLLISTNODE* in_pNewNext);

	void					AttachTo(DLLISTNODE* in_pPrevious);		// Bindet ein Element vor diesem ein
	void					Attach(DLLISTNODE* in_pNext);			// Bindet ein Element nach diesem ein
	
	void					Detach();							// Bindet dieses Element aus
	void					DetachPrevious();					// Bindet das vorgehende Element aus
	void					DetachNext();						// Bindet das Nachfolgeelement aus

	bool					HasPrevious() const;
	bool					HasNext() const;
};


/*---------------------------------------------------------------------------
	Strukturen für den DLLIST-Manager
---------------------------------------------------------------------------*/
class DLLIST {
friend DLLISTNODE;
//:: Die Membervariablen ....................................................
protected:
	DLLISTNODE				*m_pDLListFirst;
	DLLISTNODE				*m_pDLListPointer;

//:: Die Konstruktoren ......................................................
public:
							DLLIST();

//:: Die Destruktoren .......................................................
public:
							~DLLIST();

//:: Akzessor ...............................................................
protected:
/*
	DLLIST*					GetPrevious() const;
	void					GetPrevious(DLLIST* out_pPrevious) const;
	void					SetPrevious(DLLIST* in_pNewPrevious);
	DLLIST*					GetNext() const;
	void					GetNext(DLLIST* out_pNext) const;
	void					SetNext(DLLIST* in_pNewNext);

	void					AttachTo(DLLIST* in_pPrevious);		// Bindet ein Element vor diesem ein
	void					Attach(DLLIST* in_pNext);			// Bindet ein Element nach diesem ein
	
	void					Detach();							// Bindet dieses Element aus
	void					DetachPrevious();					// Bindet das vorgehende Element aus
	void					DetachNext();						// Bindet das Nachfolgeelement aus
*/
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef DLLISTNODE					*LPDLLISTNODE;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 DLLISTNODE		DLLISTNODEA16;
typedef _ALIGN_16 DLLISTNODE		*LPDLLISTNODEA16;

typedef _ALIGN_32 DLLISTNODE		DLLISTNODEA32;
typedef _ALIGN_32 DLLISTNODE		*LPDLLISTNODEA32;

typedef _CACHEALIGN DLLISTNODE		DLLISTNODEAC;
typedef _CACHEALIGN DLLISTNODE		*LPDLLISTNODEAC;*/


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef DLLIST					*LPDLLIST;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 DLLIST		DLLISTA16;
typedef _ALIGN_16 DLLIST		*LPDLLISTA16;

typedef _ALIGN_32 DLLIST		DLLISTA32;
typedef _ALIGN_32 DLLIST		*LPDLLISTA32;

typedef _CACHEALIGN DLLIST		DLLISTAC;
typedef _CACHEALIGN DLLIST		*LPDLLISTAC;*/

#endif