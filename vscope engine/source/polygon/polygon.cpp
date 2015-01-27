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

	Dateiname:		polygon.h
	Beschreibung:	Polygon (Template) Kontainer
	Revision:		1
	Erstellt:		MMT, 08. Juli 2002 01:43

	Changelog:
	[1]		08. Juli 2002 01:43

===========================================================================*/

#include "polygon.h"
#include "polygon.inl.h"
#include "..\lines\linemath.inl.h"

/*------------------------------------------------------------
/|	Funktion:		Optimize()
/|	Beschreibung:	Optimiert das Polygon durch Entfernen
/|					identischer, sowie kolinearer Punkte
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-07-21 23:50 MMT
/+------------------------------------------------------------*/
void VSFASTCALL POLYGON3::Optimize() {
	unsigned long iPointsRemoved = 0;
	
	/*
	 * Identische Punkte werden entfernt
	 */
	if ( this->m_iElementCount >= 2 ) {
		unsigned long	iCount = this->m_iElementCount;
		POLYGON3		temp(iCount);	// Zielpolygon erstellen
						temp.m_iElementCount = 0;
		unsigned long	iStep = 0;

		for( unsigned long iCoIncident = 0; iCoIncident < iCount; ++iCoIncident) {	// über alle Punkte
			VECTOR3 vP0 = this->pList[(iCoIncident+iCount-1) % iCount];
			VECTOR3 vP1 = this->pList[iCoIncident];

			if ( (vP1 - vP0).GetMag() != 0 ) { 
				temp.pList[iStep++] = vP1;
				++temp.m_iElementCount;
			}
		} // for ( iCoIncident )

		VSASSERT(temp.m_iElementCount <= this->m_iElementCount); // "Break if" mehr neue Punkte als alte vorhanden sind.
		if ( temp.m_iElementCount < this->m_iElementCount ) {
			//this->pList = temp.pList;
			this->CloneData(temp);
			//this->m_iElementCount = temp.m_iElementCount;
		}
		
	} // if ( this->m_iElementCount >= 2 ) {


	/*
	 * kolineare Punkte werden entfernt
	 */
	if ( this->m_iElementCount >= 3 ) {
		unsigned long	iCount = this->m_iElementCount;
		POLYGON3		temp(iCount);	// Zielpolygon erstellen
						temp.m_iElementCount = 0;
		unsigned long	iStep = 0;

		for( unsigned long iCoLinear = 0; iCoLinear < iCount; ++iCoLinear) {	// über alle Punkte
			VECTOR3 vP0 = this->pList[(iCoLinear+iCount-1) % iCount];	// der Punkt vorher
			VECTOR3 vP1 = this->pList[iCoLinear];						// der aktuelle Punkt
			VECTOR3 vP2 = this->pList[(iCoLinear+1) % iCount];			// der Nachfolger

			//TODO: Determinante berechnen!
			float fDistance = GetDistancePointLine(vP1, vP0, vP2);
			if(!ISZERO(fDistance)) {
				temp.pList[iStep++] = vP1;
				++temp.m_iElementCount;
			}

		} // for ( iCoIncident )

    	VSASSERT(temp.m_iElementCount <= this->m_iElementCount); // "Break if" mehr neue Punkte als alte vorhanden sind.
		if ( temp.m_iElementCount < this->m_iElementCount ) {
			/*this->pList = temp.pList;
			this->m_iElementCount = temp.m_iElementCount;
			*/
			this->CloneData(temp);
		}
	} // if ( this->m_iElementCount >= 2 ) {

	CalculateCenter();
}