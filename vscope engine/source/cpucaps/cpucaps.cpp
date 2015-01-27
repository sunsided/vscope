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

	Dateiname:		cpucaps.cpp
	Beschreibung:	CPU-Caps
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 19:35

	Changelog:
	[1]		10. Juli 2002 19:35
			Erstellt

===========================================================================*/

#include "cpucaps.h"
#include "..\include-windows.h"
#pragma intrinsic(memcpy, memset)

// These are the bit flags that get set on calling cpuid
// with register eax set to 1
#define vs__MMX_FEATURE_BIT        0x00800000
#define vs__SSE_FEATURE_BIT        0x02000000
#define vs__SSE2_FEATURE_BIT       0x04000000

// This bit is set when cpuid is called with
// register set to 80000001h (only applicable to AMD)
#define vs__3DNOW_FEATURE_BIT      0x80000000

int vs_IsCPUID() {
	__try {
		_asm {
			xor eax, eax
			cpuid
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return 0;
	}
	return 1;
}


/***
* int vs__os_support(int iFeatureBits)
*   - Checks if OS Supports the capablity or not
*
* Entry:
*   iFeatureBits: the iFeatureBits we want to check if OS supports it.
*
* Exit:
*   Returns 1 if OS support exist and 0 when OS doesn't support it.
*
****************************************************************/

int vs__os_support(int iFeatureBits) {
	__try {
		switch (iFeatureBits) {
		case vs__CPU_FEATURE_SSE:
			__asm {
				xorps xmm0, xmm0        // executing SSE instruction
			}
			break;
		case vs__CPU_FEATURE_SSE2:
			__asm {
				xorpd xmm0, xmm0        // executing SSE2 instruction
			}
			break;
		case vs__CPU_FEATURE_3DNOW:
			__asm {
				pfrcp mm0, mm0          // executing 3DNow! instruction
				emms
			}
			break;
		case vs__CPU_FEATURE_MMX:
			__asm {
				pxor mm0, mm0           // executing MMX instruction
				emms
			}
			break;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		if (_exception_code() == STATUS_ILLEGAL_INSTRUCTION) {
			return 0;
		}
		return 0;
	}
	return 1;
}


/***
*
* void vs_map_mname(int, int, const char *, char *)
*   - Maps iFamily and iModel to processor name
*
****************************************************/


void vs_map_mname(int iFamily, int iModel, const char *sVendorName, char *m_name) {
	// Default to name not known
	m_name[0] = '\0';

	if (!strncmp("AuthenticAMD", sVendorName, 12)) {
		switch (iFamily) { // extract iFamily code
		case 4: // Am486/AM5x86
			strcpy (m_name, "AMD Am486");
			break;

		case 5: // K6
			switch (iModel) { // extract iModel code
			case 0:
			case 1:
			case 2:
			case 3:
				strcpy (m_name, "AMD K5");
				break;
			case 6:
			case 7:
				strcpy (m_name, "AMD K6");
				break;
			case 8:
				strcpy (m_name, "AMD K6-2");
				break;
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				strcpy (m_name, "AMD K6-3");
				break;
			}
			break;

		case 6: // Athlon
			// No iModel numbers are currently defined
			strcpy (m_name, "AMD ATHLON");
			break;
		}
	}
	else if (!strncmp("GenuineIntel", sVendorName, 12)) {
		switch (iFamily) { // extract iFamily code
		case 4:
			switch (iModel) { // extract iModel code
			case 0:
			case 1:
				strcpy (m_name, "INTEL 486DX");
				break;
			case 2:
				strcpy (m_name, "INTEL 486SX");
				break;
			case 3:
				strcpy (m_name, "INTEL 486DX2");
				break;
			case 4:
				strcpy (m_name, "INTEL 486SL");
				break;
			case 5:
				strcpy (m_name, "INTEL 486SX2");
				break;
			case 7:
				strcpy (m_name, "INTEL 486DX2E");
				break;
			case 8:
				strcpy (m_name, "INTEL 486DX4");
				break;
			}
			break;

		case 5:
			switch (iModel) { // extract iModel code
			case 1:
			case 2:
			case 3:
				strcpy (m_name, "INTEL Pentium");
				break;
			case 4:
				strcpy (m_name, "INTEL Pentium-MMX");
				break;
			}
			break;

		case 6:
			switch (iModel) { // extract iModel code
			case 1:
				strcpy (m_name, "INTEL Pentium-Pro");
				break;
			case 3:
			case 5:
				strcpy (m_name, "INTEL Pentium-II");
				break;  // actual differentiation depends on cache settings
			case 6:
				strcpy (m_name, "INTEL Celeron");
				break;
			case 7:
			case 8:
			case 10:
				strcpy (m_name, "INTEL Pentium-III");
				break;  // actual differentiation depends on cache settings
			}
			break;

		case 15 | (0x00 << 4): // iFamily 15, extended iFamily 0x00
			switch (iModel) {
			case 0:
				strcpy (m_name, "INTEL Pentium-4");
				break;
			}
			break;
		}
	}
	else if (!strncmp("CyrixInstead", sVendorName, 12)) {
		strcpy (m_name, "Cyrix");
	}
	else if (!strncmp("CentaurHauls", sVendorName, 12)) {
		strcpy (m_name, "Centaur");
	}

	if (!m_name[0]) {
		strcpy (m_name, "unbekannt");
	}
}



// Überprüft CPU-Features
void vs_cpuflags(CPUINFO *CPU) {
	if (CPU->iCheckBits & vs__CPU_FEATURE_MMX)
		CPU->Features._MMX = CPU->iFeatureBits & vs__CPU_FEATURE_MMX ? true : false;
	if (CPU->iCheckBits & vs__CPU_FEATURE_SSE)
		CPU->Features._SSE = CPU->iFeatureBits & vs__CPU_FEATURE_SSE ? true : false;
	if (CPU->iCheckBits & vs__CPU_FEATURE_SSE2)
		CPU->Features._SSE2 = CPU->iFeatureBits & vs__CPU_FEATURE_SSE2 ? true : false;
	if (CPU->iCheckBits & vs__CPU_FEATURE_3DNOW)
		CPU->Features._3DNOW = CPU->iFeatureBits & vs__CPU_FEATURE_3DNOW ? true : false;
}


/***
*
* int vs_GetCPUID (vs_CPUINFO *pinfo)
*
* Entry:
*
*   pinfo: pointer to _p_info.
*
* Exit:
*
*   Returns int with capablity bit set even if pinfo = NULL
*
****************************************************/


int VSFASTCALL CPUCAPS::GetCPUInfo (CPUINFO *pinfo) {
	DWORD dwStandard = 0;
	DWORD dwFeature = 0;
	DWORD dwMax = 0;
	DWORD dwExt = 0;
	int iFeatureBits = 0;
	int iOSSupportBits = 0;
	union {
		char cBuf[12+1];
		struct {
			DWORD dw0;
			DWORD dw1;
			DWORD dw2;
		} s;
	} Ident;

	if (!vs_IsCPUID()) {
		return 0;
	}

	__asm {
		push ebx
		push ecx
		push edx

		// get the vendor string
		xor eax, eax
		cpuid
		mov dwMax, eax
		mov Ident.s.dw0, ebx
		mov Ident.s.dw1, edx
		mov Ident.s.dw2, ecx

		// get the Standard bits
		mov eax, 1
		cpuid
		mov dwStandard, eax
		mov dwFeature, edx

		// get AMD-specials
		mov eax, 80000000h
		cpuid
		cmp eax, 80000000h
		jc notamd
		mov eax, 80000001h
		cpuid
		mov dwExt, edx

notamd:
		pop ecx
		pop ebx
		pop edx
	}

	if (dwFeature & vs__MMX_FEATURE_BIT) {
		iFeatureBits |= vs__CPU_FEATURE_MMX;
		if (vs__os_support(vs__CPU_FEATURE_MMX))
			iOSSupportBits |= vs__CPU_FEATURE_MMX;
	}
	if (dwExt & vs__3DNOW_FEATURE_BIT) {
		iFeatureBits |= vs__CPU_FEATURE_3DNOW;
		if (vs__os_support(vs__CPU_FEATURE_3DNOW))
			iOSSupportBits |= vs__CPU_FEATURE_3DNOW;
	}
	if (dwFeature & vs__SSE_FEATURE_BIT) {
		iFeatureBits |= vs__CPU_FEATURE_SSE;
		if (vs__os_support(vs__CPU_FEATURE_SSE))
			iOSSupportBits |= vs__CPU_FEATURE_SSE;
	}
	if (dwFeature & vs__SSE2_FEATURE_BIT) {
		iFeatureBits |= vs__CPU_FEATURE_SSE2;
		if (vs__os_support(vs__CPU_FEATURE_SSE2))
			iOSSupportBits |= vs__CPU_FEATURE_SSE2;
	}

	if (pinfo) {
		memset(pinfo, 0, sizeof(CPUINFO));

		pinfo->iOSSupportBits = iOSSupportBits;
		pinfo->iFeatureBits = iFeatureBits;
		pinfo->iFamily = (dwStandard >> 8) & 0xF; // retrieve iFamily
		if (pinfo->iFamily == 15) {               // retrieve extended iFamily
			pinfo->iFamily |= (dwStandard >> 16) & 0xFF0;
		}
		pinfo->iModel = (dwStandard >> 4) & 0xF;  // retrieve iModel
		if (pinfo->iModel == 15) {                // retrieve extended iModel
			pinfo->iModel |= (dwStandard >> 12) & 0xF;
		}
		pinfo->iRevision = (dwStandard) & 0xF;    // retrieve iRevision

		Ident.cBuf[12] = 0;
		strcpy(pinfo->sVendorName, Ident.cBuf);

		vs_map_mname(pinfo->iFamily, 
				pinfo->iModel,
				pinfo->sVendorName,
				pinfo->sModelName);

		pinfo->iCheckBits = vs__CPU_FEATURE_MMX |
						vs__CPU_FEATURE_SSE |
						vs__CPU_FEATURE_SSE2 |
						vs__CPU_FEATURE_3DNOW;
	}

	vs_cpuflags(pinfo);

	return iFeatureBits;
}