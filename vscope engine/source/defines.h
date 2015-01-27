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

	Dateiname:		defines.h
	Beschreibung:	Definitionen für korrekte Kompilierung
	Revision:		2
	Erstellt:		MMT, 04. Juli 2002 23:30

	Changelog:
	[2]		05. Juli 2002 16:32 MMT
			VSFASTCALL hinzugefügt
	[1]		04. Juli 2002 23:30

===========================================================================*/

#pragma once

// Inlines
#ifdef _MSC_VER
  #if (_MSC_VER >= 1200)
  #define VSINLINE __forceinline
  #else
  #define VSINLINE __inline
  #endif
#else
  #ifdef __cplusplus
  #define VSINLINE inline
  #else
  #define VSINLINE
  #endif
#endif

// Fastcalls
#ifdef _MSC_VER
  #define VSFASTCALL __fastcall
#else
  #define VSFASTCALL
#endif

// Byte Aligning
#if (_MSC_VER >= 1200)
#define _ALIGN_8 __declspec(align(8))
#define _ALIGN_16 __declspec(align(16))
#define _ALIGN_32 __declspec(align(32))
#else
#define _ALIGN_8
#define _ALIGN_16
#define _ALIGN_32
#endif

// Cache Aligning
#define _CACHEALIGN _ALIGN_16