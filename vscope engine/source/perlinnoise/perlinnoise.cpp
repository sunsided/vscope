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

	Dateiname:		perlinnoise.cpp
	Beschreibung:	Perlin Noise Kontainer
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 18:55

	Changelog:
	[1]		07. Juli 2002 16:59

===========================================================================*/

#include "perlinnoise.h"
#include "perlinnoise.inl.h"
#include "..\fastmath\fastexp.h"
#include "..\fastmath\fastfabs.h"
#include "..\random\random.h"
#include "..\interpolation\interpolation.h"
#include "..\debug\debug.h"


float VSFASTCALL PERLINNOISE::SmoothedNoise( const unsigned int x ) const {
	return (frand_1(x) * 0.5f)  +  (frand_1(x-1) * 0.25f)  +  (frand_1(x+1) * 0.25f);
}


float VSFASTCALL PERLINNOISE::SmoothedNoise( const unsigned int x, const unsigned int y ) const {
    float corners	= ( frand_1(x-1, y-1)	+ frand_1(x+1, y-1)	+ frand_1(x-1, y+1)	+ frand_1(x+1, y+1) ) * 0.0625f;
    float sides		= ( frand_1(x-1, y  )	+ frand_1(x+1, y  )	+ frand_1(x  , y-1)	+ frand_1(x  , y+1) ) * 0.125f;
    float center	=  frand_1(x, y) * 0.25f;
    return corners + sides + center;
}


float VSFASTCALL PERLINNOISE::InterpolatedNoise( const float x ) const {
	unsigned int integer_X	= (unsigned int)x;
	float fractional_X		= x - (float)integer_X;

	float v1 = this->SmoothedNoise(integer_X);
	float v2 = this->SmoothedNoise(integer_X + 1);

	float ret = INTERPOLATION::InterpolateCosine(v1, v2, fractional_X);
	ret = (ret + 1.f) * 0.5f;
	return ret;
}


float VSFASTCALL PERLINNOISE::InterpolatedNoise( const float x, const float y ) const {
	unsigned int integer_X	= (unsigned int)x;
	float fractional_X		= x - (float)integer_X;

	unsigned int integer_Y	= (unsigned int)y;
	float fractional_Y		= y - (float)integer_Y;

	float v1 = this->SmoothedNoise(integer_X,     integer_Y);
	float v2 = this->SmoothedNoise(integer_X + 1, integer_Y);
	float v3 = this->SmoothedNoise(integer_X,     integer_Y + 1);
	float v4 = this->SmoothedNoise(integer_X + 1, integer_Y + 1);

	float i1 = INTERPOLATION::InterpolateCosine(v1, v2, fractional_X);
	float i2 = INTERPOLATION::InterpolateCosine(v3, v4, fractional_X);
	  
	float ret = INTERPOLATION::InterpolateCosine(i1 , i2 , fractional_Y);
	ret = (ret + 1.f) * 0.5f;
	return ret;
}

float VSFASTCALL PERLINNOISE::GetNoise( const float x ) const {
	float total = 0;
	float i = this->octaves -1;
	do {
		float frequency = fastpow((float)2.f, i);
		float amplitude = fastpow(this->persistence, i);
		total += total + this->InterpolatedNoise(x * frequency) * amplitude;
		i--;
	} while(i>=0);
	return total;
}

float VSFASTCALL PERLINNOISE::GetNoise( const float x, const float y ) const {
	float total = 0;
	float i = this->octaves -1;
	do {
		float frequency = fastpow((float)2.f, i);
		float amplitude = fastpow(this->persistence, i);
		total += total + this->InterpolatedNoise(x * frequency, y*frequency) * amplitude;
		i--;
	} while(i>=0);
	return total;
}