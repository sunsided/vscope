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

	Dateiname:		viewcone.cpp
	Beschreibung:	Viewcone
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 00:46

	Changelog:
	[2]		19. Juli 2003 18:34 MMT
			Update(~) hinzugefügt
	[1]		10. Juli 2002 00:46
			Erstellt

===========================================================================*/

#include "viewcone.h"
#include "viewcone.inl.h"
#include "..\piped3d2\piped3d2.inl.h"

VIEWCONE::VIEWCONE(PIPED3D2 &in_pPipe) {
	MATRIX4 matView, matProjection, matViewProj;
	
	this->m_pPipe = &in_pPipe;

	this->m_pPipe->GetProjectionMatrix(&matProjection);
	this->m_pPipe->GetViewMatrix(&matView);
	//in->GetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&matProjection);
	//in->GetTransform(D3DTS_VIEW, (D3DXMATRIX*)&matView);
	matViewProj = matView.GetMultiplied(matProjection);

	VECTOR3 Normal;

	// Linke Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._11), -(matViewProj._24 + matViewProj._21), -(matViewProj._34 + matViewProj._31));
	m_Planes[FRUSTRUMPLANE_LEFT].Assign(Normal, -(matViewProj._44 + matViewProj._41));

	// Rechte Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._11), -(matViewProj._24 - matViewProj._21), -(matViewProj._34 - matViewProj._31));
	m_Planes[FRUSTRUMPLANE_RIGHT].Assign(Normal, -(matViewProj._44 - matViewProj._41));

	// Obere Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._12), -(matViewProj._24 - matViewProj._22), -(matViewProj._34 - matViewProj._32));
	m_Planes[FRUSTRUMPLANE_TOP].Assign(Normal, -(matViewProj._44-matViewProj._42));

	// Untere Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._12), -(matViewProj._24 + matViewProj._22), -(matViewProj._34 + matViewProj._32));
	m_Planes[FRUSTRUMPLANE_BOTTOM].Assign(Normal, -(matViewProj._44+matViewProj._42));

	// Nahe Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._13), -(matViewProj._24 + matViewProj._23), -(matViewProj._34 + matViewProj._33));
	m_Planes[FRUSTRUMPLANE_NEAR].Assign(Normal, -(matViewProj._44+matViewProj._43));

	// Ferne Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._13), -(matViewProj._24 - matViewProj._23), -(matViewProj._34 - matViewProj._33));
	m_Planes[FRUSTRUMPLANE_FAR].Assign(Normal, -(matViewProj._44-matViewProj._43));

	// Normalenvektoren der Ebenen normalisieren
	for (int i=0; i<6; i++) {
		float fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
		m_Planes[i].a *= fBetrag;
		m_Planes[i].b *= fBetrag;
		m_Planes[i].c *= fBetrag;
		m_Planes[i].d  *= fBetrag;
	}
}

VIEWCONE::VIEWCONE(PIPED3D2 &in_pPipe, const MATRIX4 matView, const MATRIX4 matProjection) {
	MATRIX4 matViewProj = matView.GetMultiplied(matProjection);
	VECTOR3 Normal;

	this->m_pPipe = &in_pPipe;

	// Linke Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._11), -(matViewProj._24 + matViewProj._21), -(matViewProj._34 + matViewProj._31));
	m_Planes[FRUSTRUMPLANE_LEFT].Assign(Normal, -(matViewProj._44 + matViewProj._41));

	// Rechte Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._11), -(matViewProj._24 - matViewProj._21), -(matViewProj._34 - matViewProj._31));
	m_Planes[FRUSTRUMPLANE_RIGHT].Assign(Normal, -(matViewProj._44 - matViewProj._41));

	// Obere Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._12), -(matViewProj._24 - matViewProj._22), -(matViewProj._34 - matViewProj._32));
	m_Planes[FRUSTRUMPLANE_TOP].Assign(Normal, -(matViewProj._44-matViewProj._42));

	// Untere Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._12), -(matViewProj._24 + matViewProj._22), -(matViewProj._34 + matViewProj._32));
	m_Planes[FRUSTRUMPLANE_BOTTOM].Assign(Normal, -(matViewProj._44+matViewProj._42));

	// Nahe Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._13), -(matViewProj._24 + matViewProj._23), -(matViewProj._34 + matViewProj._33));
	m_Planes[FRUSTRUMPLANE_NEAR].Assign(Normal, -(matViewProj._44+matViewProj._43));

	// Ferne Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._13), -(matViewProj._24 - matViewProj._23), -(matViewProj._34 - matViewProj._33));
	m_Planes[FRUSTRUMPLANE_FAR].Assign(Normal, -(matViewProj._44-matViewProj._43));

	// Normalenvektoren der Ebenen normalisieren
	for (int i=0; i<6; i++) {
		float fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
		m_Planes[i].a *= fBetrag;
		m_Planes[i].b *= fBetrag;
		m_Planes[i].c *= fBetrag;
		m_Planes[i].d  *= fBetrag;
	}	
}



/*VSINLINE*/ void VSFASTCALL VIEWCONE::Update() {
	MATRIX4 /*matView,*/ matProjection, matViewProj;
	
	this->m_pPipe->GetProjectionMatrix(&matProjection);
	//in->GetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&matProjection);
	//this->m_pPipe->GetViewMatrix(&matView);
	//in->GetTransform(D3DTS_VIEW, (D3DXMATRIX*)&matView);
	//matViewProj = matView * matProjection;
	this->m_pPipe->GetViewMatrix(&matViewProj);
	matViewProj.Multiply(matProjection);

	VECTOR3 Normal;

	// Linke Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._11), -(matViewProj._24 + matViewProj._21), -(matViewProj._34 + matViewProj._31));
	m_Planes[FRUSTRUMPLANE_LEFT].Assign(Normal, -(matViewProj._44 + matViewProj._41));

	// Rechte Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._11), -(matViewProj._24 - matViewProj._21), -(matViewProj._34 - matViewProj._31));
	m_Planes[FRUSTRUMPLANE_RIGHT].Assign(Normal, -(matViewProj._44 - matViewProj._41));

	// Obere Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._12), -(matViewProj._24 - matViewProj._22), -(matViewProj._34 - matViewProj._32));
	m_Planes[FRUSTRUMPLANE_TOP].Assign(Normal, -(matViewProj._44-matViewProj._42));

	// Untere Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._12), -(matViewProj._24 + matViewProj._22), -(matViewProj._34 + matViewProj._32));
	m_Planes[FRUSTRUMPLANE_BOTTOM].Assign(Normal, -(matViewProj._44+matViewProj._42));

	// Nahe Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._13), -(matViewProj._24 + matViewProj._23), -(matViewProj._34 + matViewProj._33));
	m_Planes[FRUSTRUMPLANE_NEAR].Assign(Normal, -(matViewProj._44+matViewProj._43));

	// Ferne Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._13), -(matViewProj._24 - matViewProj._23), -(matViewProj._34 - matViewProj._33));
	m_Planes[FRUSTRUMPLANE_FAR].Assign(Normal, -(matViewProj._44-matViewProj._43));

	// Normalenvektoren der Ebenen normalisieren
	/*
	for (int i=0; i<6; i++) {
		float fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
		m_Planes[i].a *= fBetrag;
		m_Planes[i].b *= fBetrag;
		m_Planes[i].c *= fBetrag;
		m_Planes[i].d  *= fBetrag;
	}
	*/
	unsigned int i = 0;
	float fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;
}


/*VSINLINE*/ void VSFASTCALL VIEWCONE::Update(const MATRIX4 matView, const MATRIX4 matProjection) {
	MATRIX4 matViewProj;
	matViewProj = matView * matProjection;//matView.GetMultiplied(matProjection);
	VECTOR3 Normal;

	// Linke Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._11), -(matViewProj._24 + matViewProj._21), -(matViewProj._34 + matViewProj._31));
	m_Planes[FRUSTRUMPLANE_LEFT].Assign(Normal, -(matViewProj._44 + matViewProj._41));

	// Rechte Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._11), -(matViewProj._24 - matViewProj._21), -(matViewProj._34 - matViewProj._31));
	m_Planes[FRUSTRUMPLANE_RIGHT].Assign(Normal, -(matViewProj._44 - matViewProj._41));

	// Obere Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._12), -(matViewProj._24 - matViewProj._22), -(matViewProj._34 - matViewProj._32));
	m_Planes[FRUSTRUMPLANE_TOP].Assign(Normal, -(matViewProj._44-matViewProj._42));

	// Untere Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._12), -(matViewProj._24 + matViewProj._22), -(matViewProj._34 + matViewProj._32));
	m_Planes[FRUSTRUMPLANE_BOTTOM].Assign(Normal, -(matViewProj._44+matViewProj._42));

	// Nahe Clipping Plane
	Normal.Assign(-(matViewProj._14 + matViewProj._13), -(matViewProj._24 + matViewProj._23), -(matViewProj._34 + matViewProj._33));
	m_Planes[FRUSTRUMPLANE_NEAR].Assign(Normal, -(matViewProj._44+matViewProj._43));

	// Ferne Clipping Plane
	Normal.Assign(-(matViewProj._14 - matViewProj._13), -(matViewProj._24 - matViewProj._23), -(matViewProj._34 - matViewProj._33));
	m_Planes[FRUSTRUMPLANE_FAR].Assign(Normal, -(matViewProj._44-matViewProj._43));

	// Normalenvektoren der Ebenen normalisieren
	/*
	for (int i=0; i<6; i++) {
		float fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
		m_Planes[i].a *= fBetrag;
		m_Planes[i].b *= fBetrag;
		m_Planes[i].c *= fBetrag;
		m_Planes[i].d  *= fBetrag;
	}*/
	unsigned int i = 0;
	float fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d *= fBetrag;
	++i;

	fBetrag = 1.0f / fastsqrt(m_Planes[i].GetNormal() DOT m_Planes[i].GetNormal());
	m_Planes[i].a *= fBetrag;
	m_Planes[i].b *= fBetrag;
	m_Planes[i].c *= fBetrag;
	m_Planes[i].d  *= fBetrag;
	++i;
}