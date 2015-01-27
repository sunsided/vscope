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

	Dateiname:		cpucaps.h
	Beschreibung:	CPU-Caps Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 19:35

	Changelog:
	[1]		10. Juli 2002 19:35
			Erstellt

===========================================================================*/

#pragma once

#ifndef CPUCAPS_DEFINED
#define CPUCAPS_DEFINED
#endif

#include "..\defines.h"
#include "cpucapsSSE2.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#define vs__CPU_FEATURE_MMX    0x0001
#define vs__CPU_FEATURE_SSE    0x0002
#define vs__CPU_FEATURE_SSE2   0x0004
#define vs__CPU_FEATURE_3DNOW  0x0008

#define vs__MAX_VNAME_LEN  13
#define vs__MAX_MNAME_LEN  30

struct CPUFEATURES {				// CPU Features
	bool _MMX;
	bool _SSE;
	bool _SSE2;
	bool _3DNOW;
};

struct CPUINFO {
	char sVendorName[vs__MAX_VNAME_LEN];	// vendor name
	char sModelName[vs__MAX_MNAME_LEN];		// name of iModel e.g. Intel Pentium-Pro
	int iFamily;							// iFamily of the processor e.g. 6 = Pentium-Pro architecture
	int iModel;								// iModel of processor e.g. 1 = Pentium-Pro for iFamily = 6
	int iRevision;							// processor revision number
	int iFeatureBits;						// processor iFeatureBits (same as return value from GetCPUInfo)
	int iOSSupportBits;						// does OS Support the iFeatureBits?
	int iCheckBits;							// mask of checked bits in iFeatureBits and iOSSupportBits fields
	CPUFEATURES Features;					// CPU Features
};

/*---------------------------------------------------------------------------
	Strukturen für die Vertices
---------------------------------------------------------------------------*/
class CPUCAPS {
public:
	int	VSFASTCALL			GetCPUInfo(CPUINFO *);
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef CPUCAPS				*LPCPUCAPS;
typedef CPUINFO				*LPCPUINFO;
typedef CPUFEATURES			*LPCPUFEATURES;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*
typedef _ALIGN_16 CPUCAPS		CPUCAPSA16;
typedef _ALIGN_16 CPUCAPS		*LPCPUCAPSA16;
typedef _ALIGN_16 CPUINFO		CPUINFOA16;
typedef _ALIGN_16 CPUINFO		*LPCPUINFOA16;
typedef _ALIGN_16 CPUFEATURES	CPUFEATURESA16;
typedef _ALIGN_16 CPUFEATURES	*LPCPUFEATURESA16;

typedef _ALIGN_32 CPUCAPS		CPUCAPSA32;
typedef _ALIGN_32 CPUCAPS		*LPCPUCAPSA32;
typedef _ALIGN_32 CPUINFO		CPUINFOA32;
typedef _ALIGN_32 CPUINFO		*LPCPUINFOA32;
typedef _ALIGN_32 CPUFEATURES	CPUFEATURESA32;
typedef _ALIGN_32 CPUFEATURES	*LPCPUFEATURESA32;

typedef _CACHEALIGN CPUCAPS		CPUCAPSAC;
typedef _CACHEALIGN CPUCAPS		*LPCPUCAPSAC;
typedef _CACHEALIGN CPUINFO		CPUINFOAC;
typedef _CACHEALIGN CPUINFO		*LPCPUINFOAC;
typedef _CACHEALIGN CPUFEATURES	CPUFEATURESAC;
typedef _CACHEALIGN CPUFEATURES	*LPCPUFEATURESAC;*/