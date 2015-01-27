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

	Dateiname:		viewcone.h
	Beschreibung:	Viewcone Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 00:46

	Changelog:
	[1]		10. Juli 2002 00:46
			Erstellt

===========================================================================*/

#pragma once

#ifndef VIEWCONE_DEFINED
#define VIEWCONE_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\plane\plane.h"
#include "..\piped3d2\piped3d2.h"
#include "..\enums-math.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct MATRIX4;
struct VECTOR3;
struct AABBOX3;
//enum LOCATION;

/*---------------------------------------------------------------------------
	Strukturen für die Vertices
---------------------------------------------------------------------------*/
class VIEWCONE {
private:
	PLANE				m_Planes[6];
	LPPIPED3D2			m_pPipe;

public:
						//VIEWCONE() {};
						VIEWCONE(PIPED3D2 &in_Pipe);
						VIEWCONE(PIPED3D2 &in_Pipe, const MATRIX4 matView, const MATRIX4 matProjection);

	void VSFASTCALL		Update();
	void VSFASTCALL		Update(const MATRIX4 matView, const MATRIX4 matProjection);

	LOCATION			GetLocation(AABBOX3& Box) const;
	LOCATION			GetLocation(VECTOR3& Point) const;
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef VIEWCONE				*LPVIEWCONE;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 VIEWCONE		VIEWCONEA16;
typedef _ALIGN_16 VIEWCONE		*LPVIEWCONEA16;

typedef _ALIGN_32 VIEWCONE		VIEWCONEA32;
typedef _ALIGN_32 VIEWCONE		*LPVIEWCONEA32;

typedef _CACHEALIGN VIEWCONE	VIEWCONEAC;
typedef _CACHEALIGN VIEWCONE	*LPVIEWCONEAC;*/