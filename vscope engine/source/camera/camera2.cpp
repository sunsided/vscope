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

	Dateiname:		camera2.cpp
	Beschreibung:	Kamera
	Revision:		1
	Erstellt:		MMT, 07. Juni 2003 06:49

	Changelog:
	[1]		07. Juni 2003 06:49
			Erstellt

===========================================================================*/

#include "camera2.h"
#include "camera2.inl.h"
#include "..\debug\debug.h"
#include "..\piped3d2\piped3d2.inl.h"

#pragma intrinsic(memset)

// Konstruktoren ............................................................

void CAMERA2::Initialize() {
	// Winkel leeren
	//memset(&this->m_vRotation, 0, sizeof(VECTOR3));
	memset(&this->m_vPosition, 0, sizeof(VECTOR3));
	this->m_pPipe = NULL;
	//memset(&this->m_vRotationAngles, 0, sizeof(VECTOR3));

	// Richtungen vorgeben
	this->m_vRight.x = 1.f;			this->m_vRight.y = 0.f;			this->m_vRight.z = 0.f;
	this->m_vUp.x = 0.f;			this->m_vUp.y = 1.f;			this->m_vUp.z = 0.f;
	this->m_vDirection.x = 0.f;		this->m_vDirection.y = 0.f;		this->m_vDirection.z = 1.f;
}

CAMERA2::CAMERA2(PIPED3D2 &in_pPipe) {
	Initialize();
	SetPipe(in_pPipe);
}

CAMERA2::CAMERA2(const VECTOR3 &Position, PIPED3D2 &in_pPipe) {
	Initialize();
	SetPipe(in_pPipe);
	this->m_vPosition.x = Position.x;
	this->m_vPosition.y = Position.y;
	this->m_vPosition.z = Position.z;
}

CAMERA2::CAMERA2(const VECTOR3 &Position, const VECTOR3 &Rotation, PIPED3D2 &in_pPipe) {
	Initialize();
	SetPipe(in_pPipe);
	this->m_vPosition.x = Position.x;
	this->m_vPosition.y = Position.y;
	this->m_vPosition.z = Position.z;
	this->RotateObjectXYZ(Rotation);
}

CAMERA2::CAMERA2(const VECTOR3 &Direction, const VECTOR3 &Right, const VECTOR3 &Up, PIPED3D2 &in_pPipe) {
	Initialize();
	SetPipe(in_pPipe);
	this->m_vDirection	= Direction;
	this->m_vRight		= Right;
	this->m_vUp			= Up;
}

CAMERA2::CAMERA2(const VECTOR3 &in_vPosition, const VECTOR3 &in_vDirection, const VECTOR3 &in_vRight, const VECTOR3 &in_vUp, PIPED3D2 &in_pPipe) {
	Initialize();
	SetPipe(in_pPipe);	
	this->m_vPosition	= in_vPosition;
	this->m_vDirection	= in_vDirection;
	this->m_vRight		= in_vRight;
	this->m_vUp			= in_vUp;
}

// Normalisierung der Positionsvektoren .....................................

void CAMERA2::Normalize() {
	// Direction
	D3DXVec3Normalize((D3DXVECTOR3*)&m_vDirection, (D3DXVECTOR3*)&m_vDirection);
	D3DXVec3Cross((D3DXVECTOR3*)&this->m_vRight, (D3DXVECTOR3*)&this->m_vUp, (D3DXVECTOR3*)&this->m_vDirection);
	// Right
	D3DXVec3Normalize((D3DXVECTOR3*)&m_vRight, (D3DXVECTOR3*)&m_vRight);
	D3DXVec3Cross((D3DXVECTOR3*)&this->m_vUp, (D3DXVECTOR3*)&this->m_vDirection, (D3DXVECTOR3*)&this->m_vRight);
	// Up
	D3DXVec3Normalize((D3DXVECTOR3*)&m_vUp, (D3DXVECTOR3*)&m_vUp);
}


// Funktionen: absolute Translation: World Space ........................

/*------------------------------------------------------------
/|	Funktion:		GenerateViewMatrix()
/|	Beschreibung:	Erzeugt die Viewmatrix basierend auf den Kamerawerten
/|	Parameter:		n/a
/|	Rückgabe:		Viewmatrix (MATRIX4)
/|  2002-06-07 12:18 MMT
/+------------------------------------------------------------*/
MATRIX4 CAMERA2::GenerateViewMatrix() {
	MATRIX4 matView;
	matView._11 = this->m_vRight.x;
	matView._21 = this->m_vRight.y;
	matView._31 = this->m_vRight.z;
	matView._41 = - this->m_vRight DOT this->m_vPosition;
	matView._12 = this->m_vUp.x;
	matView._22 = this->m_vUp.y;
	matView._32 = this->m_vUp.z;
	matView._42 = - this->m_vUp DOT this->m_vPosition;
	matView._13 = this->m_vDirection.x;
	matView._23 = this->m_vDirection.y;
	matView._33 = this->m_vDirection.z;
	matView._43 = - this->m_vDirection DOT this->m_vPosition;
	matView._14 = 0;
	matView._24 = 0;
	matView._34 = 0;
	matView._44 = 1;
	return matView;
}


/*------------------------------------------------------------
/|	Funktion:		GenerateViewMatrix()
/|	Beschreibung:	Erzeugt die Viewmatrix basierend auf den Kamerawerten
/|	Parameter:		OUT: Viewmatrix (*MATRIX4)
/|	Rückgabe:		Viewmatrix als Parameter
/|  2002-06-07 12:18 MMT
/+------------------------------------------------------------*/
void CAMERA2::GenerateViewMatrix(MATRIX4 *out_Matrix) {
	out_Matrix->_11 = this->m_vRight.x;
	out_Matrix->_21 = this->m_vRight.y;
	out_Matrix->_31 = this->m_vRight.z;
	out_Matrix->_41 = - this->m_vRight DOT this->m_vPosition;
	out_Matrix->_12 = this->m_vUp.x;
	out_Matrix->_22 = this->m_vUp.y;
	out_Matrix->_32 = this->m_vUp.z;
	out_Matrix->_42 = - this->m_vUp DOT this->m_vPosition;
	out_Matrix->_13 = this->m_vDirection.x;
	out_Matrix->_23 = this->m_vDirection.y;
	out_Matrix->_33 = this->m_vDirection.z;
	out_Matrix->_43 = - this->m_vDirection DOT this->m_vPosition;
	out_Matrix->_14 = 0;
	out_Matrix->_24 = 0;
	out_Matrix->_34 = 0;
	out_Matrix->_44 = 1;
}

/*------------------------------------------------------------
/|	Funktion:		SetViewMatrix()
/|	Beschreibung:	Erzeugt die Viewmatrix basierend auf den Kamerawerten
/|					und setzt sie für das gegebene Device
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-07-09 10:00 MMT
/+------------------------------------------------------------*/
void CAMERA2::SetViewMatrix() {
	MATRIX4 matView;
	matView._11 = this->m_vRight.x;
	matView._21 = this->m_vRight.y;
	matView._31 = this->m_vRight.z;
	matView._41 = - this->m_vRight DOT this->m_vPosition;
	matView._12 = this->m_vUp.x;
	matView._22 = this->m_vUp.y;
	matView._32 = this->m_vUp.z;
	matView._42 = - this->m_vUp DOT this->m_vPosition;
	matView._13 = this->m_vDirection.x;
	matView._23 = this->m_vDirection.y;
	matView._33 = this->m_vDirection.z;
	matView._43 = - this->m_vDirection DOT this->m_vPosition;
	matView._14 = 0;
	matView._24 = 0;
	matView._34 = 0;
	matView._44 = 1;
	//in_Device->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&matView);
	m_pPipe->SetViewMatrix(&matView);
}

/*------------------------------------------------------------
/|	Funktion:		SetViewMatrix()
/|	Beschreibung:	Erzeugt die Viewmatrix basierend auf den Kamerawerten
/|					und setzt sie für das gegebene Device
/|	Parameter:		LPPIPED3D2 in_pPipe
/|	Rückgabe:		n/a
/|  2003-07-09 10:00 MMT
/+------------------------------------------------------------*/
void CAMERA2::SetViewMatrix(PIPED3D2 &in_pPipe) {
	MATRIX4 matView;
	matView._11 = this->m_vRight.x;
	matView._21 = this->m_vRight.y;
	matView._31 = this->m_vRight.z;
	matView._41 = - this->m_vRight DOT this->m_vPosition;
	matView._12 = this->m_vUp.x;
	matView._22 = this->m_vUp.y;
	matView._32 = this->m_vUp.z;
	matView._42 = - this->m_vUp DOT this->m_vPosition;
	matView._13 = this->m_vDirection.x;
	matView._23 = this->m_vDirection.y;
	matView._33 = this->m_vDirection.z;
	matView._43 = - this->m_vDirection DOT this->m_vPosition;
	matView._14 = 0;
	matView._24 = 0;
	matView._34 = 0;
	matView._44 = 1;
	in_pPipe.SetViewMatrix(&matView);
}


// Funktionen: Erweiterte ...............................................
/*------------------------------------------------------------
/|	Funktion:		LookAt()
/|	Beschreibung:	Rotiert die Kamera, so dass sie auf den Punkt in_vTarget blickt
/|	Parameter:		Ziel (VECTOR)
/|	Rückgabe:		n/a
/|  2002-06-07 14:26 MMT
/+------------------------------------------------------------*/
 void CAMERA2::LookAt(const VECTOR3 &in_vTarget) {
	/*
	MATRIX4 matLA;
	VECTOR3 vNewCam = m_vPosition - in_vTarget;

	// ZX-Rotation
	float fAngleCamXZ = fastatan(vNewCam.z / vNewCam.x);				//float fAngleCamXZDeg = RAD2DEG(fAngleCamXZ);
	float fAngleDirXZ = fastatan(m_vDirection.z / m_vDirection.x);		//float fAngleDirXZDeg = RAD2DEG(fAngleDirXZ);

	if(vNewCam.x < 0) fAngleCamXZ += PI;
	if(m_vDirection.x < 0) fAngleDirXZ += PI;

	float fAngle = RAD180 - fAngleDirXZ + fAngleCamXZ;

	matLA.RotateY(-fAngle);
	
	m_vDirection	*= matLA;	//m_vDirection.Normalize();
	m_vRight		*= matLA;	//m_vRight.Normalize();
	//m_vRight		= m_vDirection.Cross(VECTOR3::j);
	m_vUp			*= matLA;	//m_vUp.Normalize();
	//m_vUp			= m_vDirection.Cross(m_vRight);
	//this->RotateObjectAxisAngle(VECTOR3::j, -fAngle);

	// YZ-Rotation
	float fAngleCamYZ = fastatan(vNewCam.y / vNewCam.z);				//float fAngleCamXZDeg = RAD2DEG(fAngleCamXZ);
	float fAngleDirYZ = fastatan(m_vDirection.y / m_vDirection.z);		//float fAngleDirXZDeg = RAD2DEG(fAngleDirXZ);

	if(vNewCam.z < 0) fAngleCamYZ += PI;
	if(m_vDirection.z < 0) fAngleDirYZ += PI;

	fAngle = RAD180 - fAngleDirYZ + fAngleCamYZ;

	matLA.RotateX(-fAngle);
	
	m_vDirection	*= matLA;
	m_vRight		*= matLA;
	m_vUp			*= matLA;
	//m_vUp			= m_vDirection.Cross(m_vRight);
	//m_vDirection	*= matLA;
	//m_vDirection	= m_vRight.Cross(m_vUp);

	//this->RotateObjectAxisAngle(VECTOR3::i, -fAngle);

	m_vRight.Normalize();
	m_vUp.Normalize();
	m_vDirection.Normalize();
	*/
	MATRIX4 matLA;
	D3DXMatrixLookAtLH((D3DXMATRIX*)&matLA, (D3DXVECTOR3*)&m_vPosition, (D3DXVECTOR3*)&in_vTarget, (D3DXVECTOR3*)&VECTOR3(0.f, 1.f, 0.f));

	m_vRight = VECTOR3(matLA._11, matLA._21, matLA._31);
	m_vUp = VECTOR3(matLA._12, matLA._22, matLA._32);
	m_vDirection = VECTOR3(matLA._13, matLA._23, matLA._33);
}