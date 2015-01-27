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

	Dateiname:		vsfloat.h
	Beschreibung:	VSFLOAT Definition
	Revision:		1
	Erstellt:		MMT, 21. Juni 2003 06:52

	Changelog:
	[1]		21. Juni 2003 06:52
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "vsfloat.h"

namespace TYPES {

VSINLINE VSFLOAT::operator float(){ 
	return this->value.f; 
}

VSINLINE VSFLOAT::operator float&()	{ 
	return *((float *) &this->value.f); 
}

VSINLINE float& VSFLOAT::operator = (float f) { 
	this->value.f = f; return *((float *) &this->value.f); 
}

VSINLINE float& VSFLOAT::operator = (VSFLOAT vsf)	{ 
	this->value.f=vsf.value.f; return *((float *) &this->value.f); 
}

VSINLINE float& VSFLOAT::operator = (unsigned long ul)	{ 
	this->value.uLong=ul; return *((float *) &this->value.f); 
}

VSINLINE VSFLOAT& VSFLOAT::operator--() { 
	this->value.f -= 1.f; return *this; 
}

VSINLINE VSFLOAT VSFLOAT::operator--(int) {
	VSFLOAT temp = *this; this->value.f -= 1.f; return temp; 
}

VSINLINE VSFLOAT& VSFLOAT::operator++() { 
	this->value.f += 1.f; return *this; 
}

VSINLINE VSFLOAT VSFLOAT::operator++(int) { 
	VSFLOAT temp = *this; this->value.f += 1.f; return temp; 
}

VSINLINE float VSFLOAT::operator()() { 
	return this->value.f; 
}

VSINLINE float VSFLOAT::GetFloat() const { 
	return this->f; 
}

VSINLINE unsigned long VSFLOAT::GetFloatAsInt() const { 
	return this->value.uLong; 
}

VSINLINE unsigned long VSFLOAT::GetFlipped() {
	unsigned long mask = -(signed long)(this->value.uLong >> 31) | 0x80000000;
	return this->value.uLong ^ mask;
}

VSINLINE void VSFLOAT::Flip() {
	unsigned long mask = -(signed long)(this->value.uLong >> 31) | 0x80000000;
	this->value.uLong ^= mask;
}

VSINLINE unsigned long VSFLOAT::GetInverseFlipped() {
	unsigned long mask = ((this->value.uLong >> 31) - 1) | 0x80000000;
	return this->value.uLong ^ mask;
}

VSINLINE void VSFLOAT::InverseFlip() {
	unsigned long mask = ((this->value.uLong >> 31) - 1) | 0x80000000;
	this->value.uLong ^= mask;
}


#pragma warning(push)
#pragma warning(disable : 4800)
VSINLINE bool VSFLOAT::IsNegative() {
	//return (this->value.bits._32 == 1);
	return (bool)(this->value.uLong & 0x80000000);
}

VSINLINE bool VSFLOAT::IsPositive() {
	return (bool)!(this->value.uLong & 0x80000000);
}
#pragma warning(pop)

} // namespace
using namespace TYPES;