/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2002, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		memmanager.h
	Beschreibung:	Memory Manager Defined
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 05:56
	Copyright:		Dieser Code stammt ursprünglich von Mason McKuskey @ Spin Studios

	Changelog:
	[1]		20. Juli 2002 05:56
			Erstellt

===========================================================================*/

#pragma once

#ifndef MEMMANAGER_DEFINED
#define MEMMANAGER_DEFINED
#endif

#include "..\defines.h"
#include <stdexcept>
#include <vector>

/*---------------------------------------------------------------------------
	Copyrecht
---------------------------------------------------------------------------*/
// Dieser Code stammt ursprünglich von Mason McKuskey @ Spin Studios

/*---------------------------------------------------------------------------
	Strukturen für die Vertices
---------------------------------------------------------------------------*/
template <class TArrayElement, int iNumElements> class MEMMANAGER {
protected:
	int					m_iUsedElements;
	TArrayElement		m_aElements[iNumElements]; 
	bool				m_bAlive[iNumElements];
	int					m_iLastNew;
	TArrayElement		m_NewTemplate;

public:
	VSINLINE MEMMANAGER() {
		/*
		for(int q=0; q < iNumElements; q++) {
			m_bAlive[q] = false;
		}
		*/
		int q = iNumElements-1;
		do {
			m_bAlive[q] = false;
			q--;
		} while(q>=0);

		m_iUsedElements = 0;
		m_iLastNew = 0;						
	};

	VSINLINE virtual ~MEMMANAGER() {};
		
	VSINLINE TArrayElement *New() {
		// assert that we have space for this one
		if (GetNumFreeElements() < 1) throw(std::out_of_range("MEMMANAGER::New: too many objects!"));

		// find first element not in use.  as an optimization, we start at
		// the position that was allocated last, in the hopes that the next position
		// will be free.
		/*
		int i = m_iLastNew;
		for (int q=0; q < iNumElements; q++) {
			if (!m_bAlive[i]) {
				// we've found our free spot!  use it!
				break;
			} else {
				i++; if (i >= iNumElements) i = 0;
			}
		}
		*/

		int i = m_iLastNew;
		//for (int q=0; q < iNumElements; q++) {
		q = iNumElements - 1;
		do {
			if (!m_bAlive[i]) {
				// we've found our free spot!  use it!
				break;
			} else {
				i++; if (i >= iNumElements) i = 0;
			}
			q--;
		} while(q>=0);

		if (m_bAlive[i]) {
			// huh? if we got here, there are no free elements in the list... yet 
			// GetNumFreeElements didn't tell us that in the beginning.  Logic error.
			throw(std::logic_error("MEMMANAGER::New(): internal error."));
		}

		// clear it
		m_aElements[i] = m_NewTemplate;

		// increment used count
		m_iUsedElements++;
		m_bAlive[i] = true;
		m_iLastNew = i;
	    
		// return it
		return(&m_aElements[i]);
	}

	VSINLINE bool Delete(int index) {
		if (index < 0 || index >			= iNumElements || !m_bAlive[index]) return false;
		// don't actually delete element at index;
		// just mark it free.
		m_bAlive[index] = false;
		m_iUsedElements--;
		return true;
	}

	VSINLINE bool Delete(TArrayElement *elem) {
		if (m_iUsedElements == 0) return(false);
		int iElem = reinterpret_cast<int>(elem);
		iElem -= reinterpret_cast<int>(&m_aElements[0]);
		int index = iElem / sizeof(TArrayElement);
		if (index < 0 || index >= iNumElements || !m_bAlive[index]) return(false);
		m_bAlive[index] = false;
		m_iUsedElements--;
		return(true);
	}

	VSINLINE int GetNumFreeElements(void) { 
		return(iNumElements-GetNumUsedElements()); 
	}

	VSINLINE int GetNumUsedElements(void) { 
		return(m_iUsedElements); 
	}

	VSINLINE int GetTotalElements(void) { 
		return(iNumElements); 
	}

	VSINLINE TArrayElement& GetAt(int index) { 
		return(m_aElements[index]); 
	}

	VSINLINE bool IsAlive(int index) { 
		return(m_bAlive[index]); 
	}

	VSINLINE void DeleteAll(void) {
		//for (int q=0; q < iNumElements; q++) {
		int q = iNumElements-1;
		do {
			m_bAlive[q] = false;
			q--;
		} while(q>=0);
		m_iUsedElements = 0;
		m_iLastNew = 0;
	}

};