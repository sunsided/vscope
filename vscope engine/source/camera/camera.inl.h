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

	Dateiname:		camera.inl.h
	Beschreibung:	Viewcone Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 00:57

	Changelog:
	[1]		10. Juli 2002 00:57
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "camera.h"
#include "..\vektoren\vector3.h"
#include "..\matrix\matrix4.h"
#include "..\quaternion\quaternion.h"

#include "..\matrix\matrix4.inl.h"
#include "..\vektoren\vector3.inl.h"

#pragma intrinsic(memset)

VSINLINE CAMERA::CAMERA(const VECTOR3 *Position) {
	Initialize();
	this->vPosition.x = Position->x;
	this->vPosition.y = Position->y;
	this->vPosition.z = Position->z;
}

VSINLINE CAMERA::CAMERA(const VECTOR3 &Position) {
	Initialize();
	this->vPosition.x = Position.x;
	this->vPosition.y = Position.y;
	this->vPosition.z = Position.z;
}

VSINLINE CAMERA::CAMERA(const VECTOR3 *Position, const VECTOR3 *Rotation) {
	Initialize();
	this->vPosition.x = Position->x;
	this->vPosition.y = Position->y;
	this->vPosition.z = Position->z;
	this->vRotation.x = Rotation->x;
	this->vRotation.y = Rotation->y;
	this->vRotation.z = Rotation->z;
}

VSINLINE CAMERA::CAMERA(const VECTOR3 &Position, const VECTOR3 &Rotation) {
	Initialize();
	this->vPosition.x = Position.x;
	this->vPosition.y = Position.y;
	this->vPosition.z = Position.z;
	this->vRotation.x = Rotation.x;
	this->vRotation.y = Rotation.y;
	this->vRotation.z = Rotation.z;
}

VSINLINE CAMERA::CAMERA(const VECTOR3 &Direction, const VECTOR3 &Right, const VECTOR3 &Up) {
	Initialize();
	this->vDirection = Direction;
	this->vRight = Right;
	this->vUp = Up;
}

VSINLINE void CAMERA::Initialize() {
	memset(&this->vRotation, 0, sizeof(VECTOR3));
	memset(&this->vPosition, 0, sizeof(VECTOR3));
	this->vRight.x = 1.f;		this->vRight.y = 0.f;		this->vRight.z = 0.f;
	this->vUp.x = 0.f;			this->vUp.y = 1.f;			this->vUp.z = 0.f;
	this->vDirection.x = 0.f;	this->vDirection.y = 0.f;	this->vDirection.z = 1.f;
	this->vRotation = VECTOR3::Zero;
}

VSINLINE CAMERA::CAMERA() {
	Initialize();
}


// ===============--------------------------- Rotationen ------------------------

VSINLINE void CAMERA::ToRotateX(const float value) {
	if(value==0.f) return;
	MATRIX4 matRotX;
	QUATERNION Quat;
	Quat.Rotate(this->vRight, value);
	Quat.ToMatrix(&matRotX);
	this->vUp *= matRotX;
	this->vDirection *= matRotX;
}


VSINLINE void CAMERA::ToRotateY(const float value) {
	if(value==0.f) return;
	MATRIX4 matRotY;
	QUATERNION Quat;
	Quat.Rotate(this->vUp, value);
	Quat.ToMatrix(&matRotY);
	this->vRight *= matRotY;
	this->vDirection *= matRotY;
}


VSINLINE void  CAMERA::ToRotateZ(const float value) {
	if(value==0.f) return;
	MATRIX4 matRotZ;
	QUATERNION Quat;
	Quat.Rotate(this->vDirection, value);
	Quat.ToMatrix(&matRotZ);
	this->vRight *= matRotZ;
	this->vUp *= matRotZ;
}

VSINLINE CAMERA CAMERA::RotateX(const float value) {
	CAMERA Kamera;
	Kamera.ToRotateX(value);
	return Kamera;
}

VSINLINE CAMERA CAMERA::RotateY(const float value) {
	CAMERA Kamera;
	Kamera.ToRotateY(value);
	return Kamera;
}

VSINLINE CAMERA CAMERA::RotateZ(const float value) {
	CAMERA Kamera;
	Kamera.ToRotateZ(value);
	return Kamera;
}

VSINLINE void CAMERA::AddRotationX(const float value) {
	this->vRotation.x+=value;
}

VSINLINE void CAMERA::AddRotationY(const float value) {
	this->vRotation.y+=value;
}

VSINLINE void CAMERA::AddRotationZ(const float value) {
	this->vRotation.z+=value;
}


VSINLINE void CAMERA::ToRotate(const float x, const float y, const float z) {
	this->ToRotateX(x);
	this->ToRotateY(y);
	this->ToRotateZ(z);
}

VSINLINE void CAMERA::ToRotate() {
	this->ToRotateX(this->vRotation.x);
	this->ToRotateY(this->vRotation.y);
	this->ToRotateZ(this->vRotation.z);
}

VSINLINE CAMERA	CAMERA::Rotate(const float x, const float y, const float z) {
	CAMERA Kamera;
	Kamera.ToRotate(x, y, z);
	return Kamera;
}

VSINLINE CAMERA	CAMERA::Rotate() {
	CAMERA Kamera;
	Kamera.ToRotate();
	return Kamera;
}


// ===============--------------------------- View-Matrix erstellen ------------------------

VSINLINE MATRIX4 CAMERA::ViewMatrix() {
	MATRIX4 matView;
	matView._11 = this->vRight.x;
	matView._21 = this->vRight.y;
	matView._31 = this->vRight.z;
	matView._41 = - this->vRight DOT this->vPosition;
	matView._12 = this->vUp.x;
	matView._22 = this->vUp.y;
	matView._32 = this->vUp.z;
	matView._42 = - this->vUp DOT this->vPosition;
	matView._13 = this->vDirection.x;
	matView._23 = this->vDirection.y;
	matView._33 = this->vDirection.z;
	matView._43 = - this->vDirection DOT &this->vPosition;
	matView._14 = 0;
	matView._24 = 0;
	matView._34 = 0;
	matView._44 = 1;
	return matView;
}

VSINLINE void	CAMERA::ViewMatrix(MATRIX4 *out_Matrix) {
	out_Matrix->_11 = this->vRight.x;
	out_Matrix->_21 = this->vRight.y;
	out_Matrix->_31 = this->vRight.z;
	out_Matrix->_41 = - this->vRight DOT this->vPosition;
	out_Matrix->_12 = this->vUp.x;
	out_Matrix->_22 = this->vUp.y;
	out_Matrix->_32 = this->vUp.z;
	out_Matrix->_42 = - this->vUp DOT this->vPosition;
	out_Matrix->_13 = this->vDirection.x;
	out_Matrix->_23 = this->vDirection.y;
	out_Matrix->_33 = this->vDirection.z;
	out_Matrix->_43 = - this->vDirection DOT this->vPosition;
	out_Matrix->_14 = 0;
	out_Matrix->_24 = 0;
	out_Matrix->_34 = 0;
	out_Matrix->_44 = 1;
}

VSINLINE void	CAMERA::ViewMatrixSetzen(LPDIRECT3DDEVICE9 in_Device) {
	MATRIX4 matView;
	matView._11 = this->vRight.x;
	matView._21 = this->vRight.y;
	matView._31 = this->vRight.z;
	matView._41 = - this->vRight DOT this->vPosition;
	matView._12 = this->vUp.x;
	matView._22 = this->vUp.y;
	matView._32 = this->vUp.z;
	matView._42 = - this->vUp DOT this->vPosition;
	matView._13 = this->vDirection.x;
	matView._23 = this->vDirection.y;
	matView._33 = this->vDirection.z;
	matView._43 = - this->vDirection DOT this->vPosition;
	matView._14 = 0;
	matView._24 = 0;
	matView._34 = 0;
	matView._44 = 1;
	in_Device->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&matView);
}


// ===============--------------------------- Translationen ------------------------

VSINLINE void	 CAMERA::ToMoveDirection(const float value) {
	this->vPosition.x += this->vDirection.x * value;
	this->vPosition.y += this->vDirection.y * value;
	this->vPosition.z += this->vDirection.z * value;
}

VSINLINE void	 CAMERA::ToMoveRight(const float value) {
	this->vPosition.x += this->vRight.x * value;
	this->vPosition.y += this->vRight.y * value;
	this->vPosition.z += this->vRight.z * value;
}

VSINLINE void	 CAMERA::ToMoveUp(const float value) {
	this->vPosition.x += this->vUp.x * value;
	this->vPosition.y += this->vUp.y * value;
	this->vPosition.z += this->vUp.z * value;
}

VSINLINE void	 CAMERA::ToMoveObjectX(const float value) {
	this->vPosition.x += this->vRight.x * value;
	this->vPosition.y += this->vRight.y * value;
	this->vPosition.z += this->vRight.z * value;	
}

VSINLINE void	 CAMERA::ToMoveObjectY(const float value) {
	this->vPosition.x += this->vUp.x * value;
	this->vPosition.y += this->vUp.y * value;
	this->vPosition.z += this->vUp.z * value;
}

VSINLINE void	 CAMERA::ToMoveObjectZ(const float value) {
	this->vPosition.x += this->vDirection.x * value;
	this->vPosition.y += this->vDirection.y * value;
	this->vPosition.z += this->vDirection.z * value;	
}

VSINLINE void	CAMERA::ToPosition(const float x, const float y, const float z) {
	this->vPosition.x = x;
	this->vPosition.y = y;
	this->vPosition.z = z;
}

VSINLINE void	CAMERA::ToPosition(const VECTOR3 *Position) {
	this->vPosition.x = Position->x;
	this->vPosition.y = Position->y;
	this->vPosition.z = Position->z;
}

VSINLINE void	CAMERA::ToPosition(const VECTOR3 &Position) {
	this->vPosition.x = Position.x;
	this->vPosition.y = Position.y;
	this->vPosition.z = Position.z;
}


VSINLINE void  CAMERA::ToMoveWorldX(const float value) {
	this->vPosition.x += value;
}

VSINLINE void  CAMERA::ToMoveWorldY(const float value) {
	this->vPosition.y += value;
}

VSINLINE void  CAMERA::ToMoveWorldZ(const float value) {
	this->vPosition.z += value;
}

// ===============--------------------------- Aufräumen ------------------------

VSINLINE void CAMERA::Normalize() {
	//this->vDirection.Normalize();
	D3DXVec3Normalize((D3DXVECTOR3*)&vDirection, (D3DXVECTOR3*)&vDirection);
	D3DXVec3Cross((D3DXVECTOR3*)&this->vRight, (D3DXVECTOR3*)&this->vUp, (D3DXVECTOR3*)&this->vDirection);
	//this->vRight.Normalize();
	D3DXVec3Normalize((D3DXVECTOR3*)&vRight, (D3DXVECTOR3*)&vRight);
	D3DXVec3Cross((D3DXVECTOR3*)&this->vUp, (D3DXVECTOR3*)&this->vDirection, (D3DXVECTOR3*)&this->vRight);
	//this->vUp.Normalize();
	D3DXVec3Normalize((D3DXVECTOR3*)&vUp, (D3DXVECTOR3*)&vUp);
}


VSINLINE void CAMERA::ResetRotation() {
	/*
	this->vRotation.x = 0;
	this->vRotation.y = 0;
	this->vRotation.z = 0;
	*/
	memset(&this->vRotation, 0, sizeof(VECTOR3));
}

VSINLINE VECTOR3 CAMERA::GetDirectionVec() const {
	return this->vDirection;
}

VSINLINE VECTOR3 CAMERA::GetUpVec() const {
	return this->vUp;
}

VSINLINE VECTOR3 CAMERA::GetRightVec() const {
	return this->vRight;
}

VSINLINE void CAMERA::GetDirectionVec(VECTOR3 *Vektor) const {
	Vektor->Assign(this->vDirection.x, this->vDirection.y, this->vDirection.z);
}

VSINLINE void CAMERA::GetUpVec(VECTOR3 *Vektor) const {
	Vektor->Assign(this->vUp.x, this->vUp.y, this->vUp.z);
}

VSINLINE void CAMERA::GetRightVec(VECTOR3 *Vektor) const {
	Vektor->Assign(this->vRight.x, this->vRight.y, this->vRight.z);
}