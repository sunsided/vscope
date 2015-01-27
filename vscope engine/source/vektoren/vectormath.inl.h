/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2003, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		vectormath.inl.h
	Beschreibung:	Berechnungen für Vektoren
	Revision:		1
	Erstellt:		MMT, 24. Juni 2003 14:29

	Changelog:
	[1]		24. Juni 2003 14:29

===========================================================================*/

#pragma once

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "..\fastmath\fastassort.h"
#include "..\fastmath\fastsqrt.h"
#include "..\enums-math.h"

// ===== Addition =====--------------------------------------------------------------------

// ... 2D

VSINLINE VECTOR2 VecAdd(const VECTOR2& in_v1, const VECTOR2& in_v2) {
	return VECTOR2(in_v1.x + in_v2.x, in_v1.y + in_v2.y);
}

VSINLINE void VecAdd(VECTOR2 *out_vResult, const VECTOR2& in_v1, const VECTOR2& in_v2) {
	out_vResult->x = in_v1.x + in_v2.x;
	out_vResult->y = in_v1.y + in_v2.y;
}

// ... 3D

VSINLINE VECTOR3 VecAdd(const VECTOR3& in_v1, const VECTOR3& in_v2) {
	return VECTOR3(in_v1.x + in_v2.x, in_v1.y + in_v2.y, in_v1.z + in_v2.z);
}

VSINLINE void VecAdd(VECTOR3 *out_vResult, const VECTOR3& in_v1, const VECTOR3& in_v2) {
	out_vResult->x = in_v1.x + in_v2.x;
	out_vResult->y = in_v1.y + in_v2.y;
	out_vResult->z = in_v1.z + in_v2.z;
}

// ... 4D

VSINLINE VECTOR3 VecAdd(const VECTOR4& in_v1, const VECTOR4& in_v2) {
	return VECTOR4(in_v1.x + in_v2.x, in_v1.y + in_v2.y, in_v1.z + in_v2.z, in_v1.w + in_v2.w);
}

VSINLINE void VecAdd(VECTOR4 *out_vResult, const VECTOR4& in_v1, const VECTOR4& in_v2) {
	out_vResult->x = in_v1.x + in_v2.x;
	out_vResult->y = in_v1.y + in_v2.y;
	out_vResult->z = in_v1.z + in_v2.z;
	out_vResult->w = in_v1.w + in_v2.w;
}

// ===== Punkt =====--------------------------------------------------------------------

VSINLINE float VecDot(const VECTOR2& in_v1, const VECTOR2& in_v2) {
	return (in_v1.x * in_v2.x) + (in_v2.y * in_v2.y);
}

VSINLINE float VecDot(const VECTOR3& in_v1, const VECTOR3& in_v2) {
	return (in_v1.x * in_v2.x) + (in_v2.y * in_v2.y) + (in_v2.z * in_v2.z);
}

VSINLINE float VecDot(const VECTOR4& in_v1, const VECTOR4& in_v2) {
	return (in_v1.x * in_v2.x) + (in_v2.y * in_v2.y) + (in_v2.z * in_v2.z) + (in_v2.w * in_v2.w);
}

// ===== Cross =====--------------------------------------------------------------------

VSINLINE VECTOR3 VecCross(const VECTOR3& in_v1, const VECTOR3& in_v2) {
	return VECTOR3((in_v1.y*in_v2.z - in_v1.z*in_v2.y), (in_v1.z*in_v2.x - in_v1.x*in_v2.z), (in_v1.x*in_v2.y - in_v1.y*in_v2.x));
}

VSINLINE void VecCross(VECTOR3* out_vResult, const VECTOR3& in_v1, const VECTOR3& in_v2) {
	out_vResult->x = in_v1.y*in_v2.z - in_v1.z*in_v2.y;
	out_vResult->y = in_v1.z*in_v2.x - in_v1.x*in_v2.z;
	out_vResult->z = in_v1.x*in_v2.y - in_v1.y*in_v2.x;
}

// ===== Magnitude =====--------------------------------------------------------------------

VSINLINE float VecMagnitude(const VECTOR2& in_v) {
	return fastsqrt(in_v.x * in_v.x + in_v.y * in_v.y);
}

VSINLINE float VecMagnitudeSquared(const VECTOR2& in_v) {
	return in_v.x * in_v.x + in_v.y * in_v.y;
}

VSINLINE float VecMagnitude(const VECTOR3& in_v) {
	return fastsqrt(in_v.x * in_v.x + in_v.y * in_v.y + in_v.z * in_v.z);
}

VSINLINE float VecMagnitudeSquared(const VECTOR3& in_v) {
	return in_v.x * in_v.x + in_v.y * in_v.y + in_v.z * in_v.z;
}

VSINLINE float VecMagnitude(const VECTOR4& in_v) {
	return fastsqrt(in_v.x * in_v.x + in_v.y * in_v.y + in_v.z * in_v.z + in_v.w * in_v.w);
}

VSINLINE float VecMagnitudeSquared(const VECTOR4& in_v) {
	return in_v.x * in_v.x + in_v.y * in_v.y + in_v.z * in_v.z + in_v.w * in_v.w;
}

// ===== Orientierung =====--------------------------------------------------------------------
VSINLINE ORIENTATION __declspec(deprecated) Orientation(const VECTOR3 &in_V1, const VECTOR3 &in_V2, const VECTOR3 &in_V3) {
	float fLength = VecMagnitude(VecCross( in_V2 - in_V1, in_V2 - in_V3));
	if ( fLength < -EPSILON )	return OR_CW;
	if ( fLength > EPSILON )	return OR_CCW;
	return OR_COLINEAR;
}