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

	Dateiname:		primitives_circle.cpp
	Beschreibung:	Primitive: Kreis
	Revision:		1
	Erstellt:		MMT, 29. Mai 2003 08:13

	Changelog:
	[1]		29. Mai 2003 08:13
			Erstellt

===========================================================================*/

#include "primitives_circle.h"
#include "primitives_circle.inl.h"
#include "..\vektoren\vector2.h"
#include "..\matrix\matrix4.h"
#include "..\matrix\matrix4.inl.h"
#include "..\enums-math.h"
#include "..\fastmath\fasttrig.h"
#include "..\debug\debug.h"
#include "..\common\common.h"

#pragma intrinsic(memset, memcpy)

//	Diese Funktion gibt Cosinus- und Sinuswerte für die Koordinaten des Punktes zurück
VECTOR2 VSFASTCALL _CircleGetAngle(const unsigned int iSegments, const unsigned int iRow, const unsigned int iPointNumber) {
	if(iRow==0) {
		return VECTOR2(0.f, 0.f);
	}
	float fAngle = PIx2-DEG2RAD(360.f / (iRow*iSegments)) * iPointNumber;
	return VECTOR2(fastcos(fAngle), fastsin(fAngle));
}

HRESULT	VSFASTCALL PRIMITIVE_CIRCLE::Create(const float in_fRadius, const unsigned int in_iSegments, const unsigned int in_iRows, const bool in_bFirstVertexUp) {
	// Array für Vertices erzeugen
	/* Benötigter Speicher
		innerer Fan:	Segmente+2 (Start- und Endvertex!) 
		äußere Reihen:	2*Segmente+2
	*/
	unsigned int iItemCount = /* unten */ (in_iSegments+2) + /* je Reihe */ (in_iRows-1)*(2*in_iSegments+2);
	this->m_CircleVertices = new VSD3DVERTEX[iItemCount];
#ifdef _DEBUG
	memset(this->m_CircleVertices, 0, iItemCount*sizeof(VSD3DVERTEX));
#endif

#ifdef _DEBUG
	dprintf("Circle creation: allocated %d bytes (%1.1f KB) for %d items (%d bytes each).\n", iItemCount * sizeof(VSVERTEX_XYZ_TEX1),(float)(iItemCount * sizeof(VSVERTEX_XYZ_TEX1))/1024, iItemCount, sizeof(VSVERTEX_XYZ_TEX1));
#endif

	float fSizeFactor = in_fRadius / in_iRows;

	// Dies ist der Mittelpunkt des Kreises
	this->m_CircleVertices[0] = VSD3DVERTEX( VECTOR3(0.f, 0.f, 0.f), VECTOR3(0.f, 0.f, -1.f), 0.5f, 0.5f);

	// Den Vertex-Fan der ersten Kreisreihe erzeugen
	float fStepsRad = DEG2RAD(360.f / in_iSegments);
	float fAngle = DEG2RAD(360);
	unsigned int iBase = in_iSegments+2;
	for(unsigned int i=1; i<iBase; i++) {	// beginnend bei 1, da Vertex[0]==Mittelpunkt
		float fSin = fastsin(fAngle);
		float fCos = fastcos(fAngle);
		float fPosX = 0.f;
		float fPosY = 0.f;
		if(!in_bFirstVertexUp) {
			fPosX = fCos;	// Achtung: x=cos(n), y=sin(n), sonst 90° Linksdrehung
			fPosY = fSin;
		} else {
			fPosX = fSin;	// Achtung: x=cos(n), y=sin(n), sonst 90° Linksdrehung
			fPosY = fCos;
		}
		this->m_CircleVertices[i] = VSD3DVERTEX( VECTOR3(fPosX*fSizeFactor, fPosY*fSizeFactor, 0.f), VECTOR3(0.f, 0.f, -1.f), (fPosX*fSizeFactor+in_fRadius)/(2*in_fRadius), 1-((fPosY*fSizeFactor+in_fRadius)/(2*in_fRadius)));
		fAngle -= fStepsRad;
	}

	// Nun die folgenden Reihen
	unsigned int iVertexCount = 2*in_iSegments;
	unsigned int iStepper = in_iSegments+2;
	for(unsigned int iR=2; iR<=in_iRows; iR++) {
		float fUpperRowSizeFactor = fSizeFactor*iR;
		float fLowerRowSizeFactor = fSizeFactor*(iR-1);
		unsigned int iPointIdx = 0;
		
		iBase = (in_iSegments+2) + (iR-2)*iVertexCount;
		unsigned int iFirst = iStepper;

		for(unsigned int iItem=0; iItem<iVertexCount; iItem+=2) {
			VECTOR2 Point = _CircleGetAngle(in_iSegments, 1, iPointIdx++);
			
			float fSin = Point.y;
			float fCos = Point.x;
			float fPosX = fCos;
			float fPosY = fSin;

			// Unterer Vertex
			this->m_CircleVertices[iStepper++] = VSD3DVERTEX( VECTOR3(fPosX*fLowerRowSizeFactor, fPosY*fLowerRowSizeFactor, 0.f), VECTOR3(0.f, 0.f, -1.f), (fPosX*fLowerRowSizeFactor+in_fRadius)/(2*in_fRadius), 1-((fPosY*fLowerRowSizeFactor+in_fRadius)/(2*in_fRadius)));
			// Oberer Vertex
			this->m_CircleVertices[iStepper++] = VSD3DVERTEX( VECTOR3(fPosX*fUpperRowSizeFactor, fPosY*fUpperRowSizeFactor, 0.f), VECTOR3(0.f, 0.f, -1.f), (fPosX*fUpperRowSizeFactor+in_fRadius)/(2*in_fRadius), 1-((fPosY*fUpperRowSizeFactor+in_fRadius)/(2*in_fRadius)));
		}
		// Letzter, unterer Vertex
		this->m_CircleVertices[iStepper++] = this->m_CircleVertices[iFirst];
		// Letzter, oberer Vertex
		this->m_CircleVertices[iStepper++] = this->m_CircleVertices[iFirst+1];
	}

	// Den Vertex-Puffer erzeugen
	HRESULT retval;
	retval = this->m_pd3dDevice->CreateVertexBuffer(sizeof(VSD3DVERTEX)*iItemCount, D3DUSAGE_WRITEONLY, VS_D3DFVF_VERTEX, D3DPOOL_DEFAULT, &this->m_CircleVB, NULL);
	if(FAILED(retval)) {
		dprintf("Circle creation: Erzeugung des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return retval;
	}

	// Den Vertexpuffer mit Daten füllen
	void*	ptr;
	retval = this->m_CircleVB->Lock(0, sizeof(VSD3DVERTEX)*iItemCount, (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("Circle creation: Lock des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return retval;
	}
	memcpy(ptr, this->m_CircleVertices, sizeof(VSD3DVERTEX)*iItemCount);
	this->m_CircleVB->Unlock();

	// Speicher für Array freigeben
	SAFE_DELETE_ARRAY(this->m_CircleVertices);

	return S_OK;
}

HRESULT	VSFASTCALL PRIMITIVE_CIRCLE::Create(const LPDIRECT3DDEVICE9 in_Device, const float in_fRadius, const unsigned int in_iSegments, const unsigned int in_iRows, const bool in_bFirstVertexUp) {
	// Variablen setzen
	this->m_iSegments = in_iSegments;
	this->m_iRows = in_iRows;
	this->m_pd3dDevice = in_Device;
	// Create-Funktion aufrufen
	return this->Create(in_fRadius, in_iSegments, in_iRows, in_bFirstVertexUp);
}

int VSFASTCALL PRIMITIVE_CIRCLE::Render() {
	//this->m_pd3dDevice->SetVertexShader(VS_D3DFVF_VERTEX);
	this->m_pd3dDevice->SetFVF(VS_D3DFVF_VERTEX);
	this->m_pd3dDevice->SetStreamSource(0, m_CircleVB, 0, sizeof(VSD3DVERTEX));
	// Der innere Fan	
	this->m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, this->m_iSegments);	
	// Die äußeren Reihen
	unsigned int iDoubleSegs = this->m_iSegments*2;
	for(unsigned int i=2; i<=this->m_iRows; i++) {
		this->m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (this->m_iSegments+2) + ((iDoubleSegs+2)*(i-2)), iDoubleSegs);
	}
	return 0;
}

unsigned int VSFASTCALL PRIMITIVE_CIRCLE::ExportVertices(VSVERTEX_XYZ_TEX1 *out_VertexArray, const float in_fRadius, const unsigned int in_iSegments, const unsigned int in_iRows, const bool in_bFirstVertexUp) {
	// Array für Vertices erzeugen
	/* Benötigter Speicher
		innerer Fan:	Segmente+2 (Start- und Endvertex!) 
		äußere Reihen:	2*Segmente+2
	*/
	unsigned int iItemCount = /* unten */ (in_iSegments+2) + /* je Reihe */ (in_iRows-1)*(2*in_iSegments+2);
	out_VertexArray = new VSVERTEX_XYZ_TEX1[iItemCount];
#ifdef _DEBUG
	memset(out_VertexArray, 0, iItemCount*sizeof(VSVERTEX_XYZ_TEX1));
#endif

#ifdef _DEBUG
	dprintf("Circle export: allocated %d bytes (%1.1f KB) for %d items (%d bytes each).\n", iItemCount * sizeof(VSVERTEX_XYZ_TEX1),(float)(iItemCount * sizeof(VSVERTEX_XYZ_TEX1))/1024, iItemCount, sizeof(VSVERTEX_XYZ_TEX1));
#endif

	float fSizeFactor = in_fRadius / in_iRows;

	// Dies ist der Mittelpunkt des Kreises
	out_VertexArray[0] = VSVERTEX_XYZ_TEX1( VECTOR3(0, 0, 0), VECTOR3(0.f, 0.f, -1.f), 0.5f, 0.5f);

	// Den Vertex-Fan der ersten Kreisreihe erzeugen
	float fStepsRad = DEG2RAD(360.f / in_iSegments);
	float fAngle = DEG2RAD(360);
	unsigned int iBase = in_iSegments+2;
	for(unsigned int i=1; i<iBase; i++) {	// beginnend bei 1, da Vertex[0]==Mittelpunkt
		float fSin = fastsin(fAngle);
		float fCos = fastcos(fAngle);
		float fPosX = 0.f;
		float fPosY = 0.f;
		if(!in_bFirstVertexUp) {
			fPosX = fCos;	// Achtung: x=cos(n), y=sin(n), sonst 90° Linksdrehung
			fPosY = fSin;
		} else {
			fPosX = fSin;	// Achtung: x=cos(n), y=sin(n), sonst 90° Linksdrehung
			fPosY = fCos;
		}
		out_VertexArray[i] = VSVERTEX_XYZ_TEX1( VECTOR3(fPosX*fSizeFactor, fPosY*fSizeFactor, 0.f), VECTOR3(0.f, 0.f, -1.f), (fPosX*fSizeFactor+in_fRadius)/(2*in_fRadius), 1-((fPosY*fSizeFactor+in_fRadius)/(2*in_fRadius)));
		fAngle -= fStepsRad;
	}

	// Nun die folgenden Reihen
	unsigned int iVertexCount = 2*in_iSegments;
	unsigned int iStepper = in_iSegments+2;
	for(unsigned int iR=2; iR<=in_iRows; iR++) {
		float fUpperRowSizeFactor = fSizeFactor*iR;
		float fLowerRowSizeFactor = fSizeFactor*(iR-1);
		unsigned int iPointIdx = 0;
		
		iBase = (in_iSegments+2) + (iR-2)*iVertexCount;
		unsigned int iFirst = iStepper;

		for(unsigned int iItem=0; iItem<iVertexCount; iItem+=2) {
			VECTOR2 Point = _CircleGetAngle(in_iSegments, 1, iPointIdx++);
			
			float fSin = Point.y;
			float fCos = Point.x;
			float fPosX = fCos;
			float fPosY = fSin;

			// Unterer Vertex
			out_VertexArray[iStepper++] = VSVERTEX_XYZ_TEX1( VECTOR3(fPosX*fLowerRowSizeFactor, fPosY*fLowerRowSizeFactor, 0.f), VECTOR3(0.f, 0.f, -1.f), (fPosX*fLowerRowSizeFactor+in_fRadius)/(2*in_fRadius), 1-((fPosY*fLowerRowSizeFactor+in_fRadius)/(2*in_fRadius)));
			// Oberer Vertex
			out_VertexArray[iStepper++] = VSVERTEX_XYZ_TEX1( VECTOR3(fPosX*fUpperRowSizeFactor, fPosY*fUpperRowSizeFactor, 0.f), VECTOR3(0.f, 0.f, -1.f), (fPosX*fUpperRowSizeFactor+in_fRadius)/(2*in_fRadius), 1-((fPosY*fUpperRowSizeFactor+in_fRadius)/(2*in_fRadius)));
		}
		// Letzter, unterer Vertex
		out_VertexArray[iStepper++] = out_VertexArray[iFirst];
		// Letzter, oberer Vertex
		out_VertexArray[iStepper++] = out_VertexArray[iFirst+1];
	}

	return iItemCount;
}