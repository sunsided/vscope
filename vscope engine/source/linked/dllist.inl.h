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

	Dateiname:		dllist.inl.h
	Beschreibung:	Doubly Linked List Inline-Definition
	Revision:		1
	Erstellt:		MMT, 26. Juni 2003 09:12

	Changelog:
	[1]		26. Juni 2003 09:12
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-windows.h"
#include "dllist.h"

#pragma intrinsic(memset, memcpy)

/*------------------------------------------------------------
/|	Funktion:		Konstruktor()
/|	Beschreibung:	Leert die Struktur
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE DLLISTNODE::DLLISTNODE() {
	m_pDLListPrevious = NULL;
	m_pDLListNext = NULL;
}

/*------------------------------------------------------------
/|	Funktion:		~Destruktor()
/|	Beschreibung:	nichts
/|	Parameter:		PIPED3D2 
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE DLLISTNODE::~DLLISTNODE() {
}

/*------------------------------------------------------------
/|	Funktion:		GetPrevious()
/|	Beschreibung:	Liefert das Vorgängerelement
/|	Parameter:		n/a 
/|	Rückgabe:		DLLISTNODE*
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE DLLISTNODE* DLLISTNODE::GetPrevious() const {
	return this->m_pDLListPrevious;
}

/*------------------------------------------------------------
/|	Funktion:		GetPrevious()
/|	Beschreibung:	Liefert das Vorgängerelement
/|	Parameter:		DLLISTNODE*
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::GetPrevious(DLLISTNODE* out_pPrevious) const {
	out_pPrevious = this->m_pDLListPrevious;
}

/*------------------------------------------------------------
/|	Funktion:		GetNext()
/|	Beschreibung:	Liefert das Nachfolgerelement
/|	Parameter:		n/a 
/|	Rückgabe:		DLLISTNODE*
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE DLLISTNODE* DLLISTNODE::GetNext() const {
	return this->m_pDLListNext;
}

/*------------------------------------------------------------
/|	Funktion:		GetNext()
/|	Beschreibung:	Liefert das Nachfolgerelement
/|	Parameter:		DLLISTNODE*
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::GetNext(DLLISTNODE* out_pNext) const {
	out_pNext = this->m_pDLListNext;
}

/*------------------------------------------------------------
/|	Funktion:		SetPrevious()
/|	Beschreibung:	Setzt das Vorgängerelement
/|	Parameter:		DLLISTNODE*
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::SetPrevious(DLLISTNODE* in_pNewPrevious) {
	this->m_pDLListPrevious = in_pNewPrevious;
}

/*------------------------------------------------------------
/|	Funktion:		SetNext()
/|	Beschreibung:	Setzt das Vorgängerelement
/|	Parameter:		DLLISTNODE*
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::SetNext(DLLISTNODE* in_pNewNext) {
	this->m_pDLListNext = in_pNewNext;
}

/*------------------------------------------------------------
/|	Funktion:		AttachTo()
/|	Beschreibung:	Bindet ein Element vor diesem ein
/|	Parameter:		DLLISTNODE*
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::AttachTo(DLLISTNODE* in_pPrevious) {
	// Neues Element, altes Vorgängerelement
	in_pPrevious->SetPrevious(this->GetPrevious());
	// Neues Element, wir als Nachfolgeelement
	in_pPrevious->SetNext(this);
	// Altes Element, neues Vorgängerelement
	this->SetPrevious(in_pPrevious);
}

/*------------------------------------------------------------
/|	Funktion:		Attach()
/|	Beschreibung:	Bindet ein Element nach diesem ein
/|	Parameter:		DLLISTNODE*
/|	Rückgabe:		n/a
/|  2003-06-26 09:38 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::Attach(DLLISTNODE* in_pNext) {
	// Neues Element, altes Vorgängerelement
	in_pNext->SetNext(this->GetNext());
	// Neues Element, wir als Nachfolgeelement
	in_pNext->SetPrevious(this);
	// Altes Element, neues Vorgängerelement
	this->SetNext(in_pNext);
}

/*------------------------------------------------------------
/|	Funktion:		Detach()
/|	Beschreibung:	Bindet dieses Element aus
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-26 09:38 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::Detach() {
	if(this->HasNext())		this->GetNext()->SetPrevious(this->GetPrevious());
	if(this->HasPrevious())	this->GetPrevious()->SetNext(this->GetNext());
	this->SetPrevious(NULL);
	this->SetNext(NULL);
}

/*------------------------------------------------------------
/|	Funktion:		DetachPrevious()
/|	Beschreibung:	Bindet das vorgehende Element aus
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-26 09:38 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::DetachPrevious() {
	if(!this->HasPrevious()) return;
	this->GetPrevious()->Detach();
}

/*------------------------------------------------------------
/|	Funktion:		DetachNext()
/|	Beschreibung:	Bindet das nachfolgende Element aus
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-26 09:38 MMT
/+------------------------------------------------------------*/
VSINLINE void DLLISTNODE::DetachNext() {
	if(!this->HasNext()) return;
	this->GetNext()->Detach();
}

/*------------------------------------------------------------
/|	Funktion:		HasNext()
/|	Beschreibung:	Existiert ein Nachfolger?
/|	Parameter:		n/a
/|	Rückgabe:		bool
/|  2003-06-26 09:38 MMT
/+------------------------------------------------------------*/
VSINLINE bool DLLISTNODE::HasNext() const {
	return (this->GetNext()!=NULL);
}

/*------------------------------------------------------------
/|	Funktion:		HasPrevious()
/|	Beschreibung:	Existiert ein Vorgänger?
/|	Parameter:		n/a
/|	Rückgabe:		bool
/|  2003-06-26 09:38 MMT
/+------------------------------------------------------------*/
VSINLINE bool DLLISTNODE::HasPrevious() const {
	return (this->GetPrevious()!=NULL);
}





/*------------------------------------------------------------
/|	Funktion:		Konstruktor()
/|	Beschreibung:	Leert die Struktur
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE DLLIST::DLLIST() {
	m_pDLListFirst = new DLLISTNODE;
	m_pDLListPointer = m_pDLListFirst;

	m_pDLListFirst->SetPrevious(NULL);
	m_pDLListFirst->SetNext(NULL);
}

/*------------------------------------------------------------
/|	Funktion:		~Destruktor()
/|	Beschreibung:	nichts
/|	Parameter:		PIPED3D2 
/|	Rückgabe:		n/a
/|  2003-06-26 09:29 MMT
/+------------------------------------------------------------*/
VSINLINE DLLIST::~DLLIST() {
	DLLISTNODE *pCache;
	m_pDLListPointer = m_pDLListFirst;
	do {
		pCache = m_pDLListPointer->GetNext();
		delete m_pDLListPointer;
	} while(pCache!=NULL);
}