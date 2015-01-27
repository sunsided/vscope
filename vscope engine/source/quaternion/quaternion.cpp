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

	Dateiname:		quaternion.cpp
	Beschreibung:	Quaternion Kontainer
	Revision:		1
	Erstellt:		MMT, 07. Juli 2002 18:56

	Changelog:
	[1]		07. Juli 2002 18:56

===========================================================================*/

#include "quaternion.h"
#include "quaternion.inl.h"

#include "..\fastmath\fastsqrt.h"
#include "..\fastmath\fasttrig.h"

QUATERNION::QUATERNION( const MATRIX4& inMat ) {

	float  tr, s;
	float  q[4];
	int	i, j, k;

	int nxt[3] = {1, 2, 0};

	tr = inMat.m[0][0] + inMat.m[1][1] + inMat.m[2][2];

	// die Diagonale prüfen

	if (tr > 0.0)  {

		s = fastsqrt (tr + 1.0f);
		w = s  * 0.5f;
		s = 0.5f / s;

		x = (inMat.m[2][1] - inMat.m[1][2]) * s;
		y = (inMat.m[0][2] - inMat.m[2][0]) * s;
		z = (inMat.m[1][0] - inMat.m[0][1]) * s;

	} else {		

		// Diagonale ist negativ
		
		i = 0;

		if (inMat.m[1][1] > inMat.m[0][0]) i = 1;
		if (inMat.m[2][2] > inMat.m[i][i]) i = 2;
		
		j = nxt[i];
		k = nxt[j];

		s = fastsqrt ((inMat.m[i][i] - (inMat.m[j][j] + inMat.m[k][k])) + 1.0f);
			
		q[i] = s * 0.5f;

		if (s != 0.0) s = 0.5f / s;

		q[3] = (inMat.m[k][j] - inMat.m[j][k]) * s;
		q[j] = (inMat.m[j][i] + inMat.m[i][j]) * s;
		q[k] = (inMat.m[k][i] + inMat.m[i][k]) * s;

		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}
}


QUATERNION::QUATERNION( float roll, float pitch, float yaw ) {
	float cr, cp, cy, sr, sp, sy, cpcy, spsy;

	cr = fastcos(roll * 0.5f);
	cp = fastcos(pitch * 0.5f);
	cy = fastcos(yaw * 0.5f);

	sr = fastsin(roll * 0.5f);
	sp = fastsin(pitch * 0.5f);
	sy = fastsin(yaw * 0.5f);

	cpcy = cp * cy;
	spsy = sp * sy;

	w = cr * cpcy + sr * spsy;
	x = sr * cpcy - cr * spsy;
	y = cr * sp * cy + sr * cp * sy;
	z = cr * cp * sy - sr * sp * cy;
}


QUATERNION::QUATERNION( const VECTOR3& axis, float angle ) {
	VECTOR3 v(axis);
	v.Normalize();

	v *= fastsin(angle * 0.5f);
	x = v.x;
	y = v.y;
	z = v.z;
	w = fastcos(angle * 0.5f);
}


void QUATERNION::ToMatrix(MATRIX4* mat) const {
#ifdef VSCOPE_NATIVE	
	float xx = this->x*this->x; float yy = this->y*this->y; float zz = this->z*this->z;
	float xy = this->x*this->y; float xz = this->x*this->z; float yz = this->y*this->z;
	float wx = this->w*this->x; float wy = this->w*this->y; float wz = this->w*this->z;

	mat->_11 = /*1*/ - 2 * (yy + zz); 
	mat->_12 =     2 * (xy - wz);
	mat->_13 =     2 * (xz + wy);
	mat->_21 =     2 * (xy + wz);
	mat->_22 = /*1*/ - 2 * (xx + zz);
	mat->_23 =     2 * (yz - wx);
	mat->_31 =     2 * (xz - wy);
	mat->_32 =     2 * (yz + wx);
	mat->_33 = /*1*/ - 2 * (xx + yy);
	mat->_14 = mat->_24 = mat->_34 = 0.0f;
	mat->_41 = mat->_42 = mat->_43 = 0.0f;
	mat->_44 = 1.0f;
#else if
	D3DXMatrixRotationQuaternion((D3DXMATRIX*)mat, (D3DXQUATERNION*)this);
#endif
}

MATRIX4 QUATERNION::ToMatrix() const {
	MATRIX4 mat;
#ifdef VSCOPE_NATIVE
	float xx = this->x*this->x; float yy = this->y*this->y; float zz = this->z*this->z;
	float xy = this->x*this->y; float xz = this->x*this->z; float yz = this->y*this->z;
	float wx = this->w*this->x; float wy = this->w*this->y; float wz = this->w*this->z;

	mat._11 = /*1*/ - 2 * (yy + zz); 
	mat._12 =     2 * (xy - wz);
	mat._13 =     2 * (xz + wy);
	mat._21 =     2 * (xy + wz);
	mat._22 = /*1*/ - 2 * (xx + zz);
	mat._23 =     2 * (yz - wx);
	mat._31 =     2 * (xz - wy);
	mat._32 =     2 * (yz + wx);
	mat._33 = /*1*/ - 2 * (xx + yy);
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._41 = mat._42 = mat._43 = 0.0f;
	mat._44 = 1.0f;
#else
	D3DXMatrixRotationQuaternion((D3DXMATRIX*)&mat, (D3DXQUATERNION*)this);
#endif
	return mat;
}