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

	Dateiname:		vscope.h
	Beschreibung:	Nutzerschnittstelle zu v-scope
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 16:19

	Changelog:
	[1]		05. Juli 2002 16:19

===========================================================================*/

#pragma once

#ifndef DONT_LINK_VSCOPE
#pragma comment(lib, "vscope")
#endif
#pragma comment( user, "vscope engine library kompiliert am " __DATE__ " um " __TIME__ ) 

//#define ENABLE_RDTSCTIMER

/*---------------------------------------------------------------------------
	Einbinden der Header
---------------------------------------------------------------------------*/

// Versionskontrolle
#include "version\vscope-version.h"
#include "version\versionstruct.h"

// SDK-Header
#include "include-windows.h"
#include "include-direct3d.h"

// Defines, Makros, globales
#include "defines.h"
#include "common\common.h"
#include "enums-math.h"

// Hilfsbibliothek: Debugger
#include "debug\debug.h"
#include "debug\debugassert.h"

// DirectX-Commob
#include "dxcommon\dxcommon.h"

// Fastmath-Bibliothek
#include "fastmath\fastassort.h"
#include "fastmath\fastexp.h"
#include "fastmath\fastfabs.h"
#include "fastmath\fastsqrt.h"
#include "fastmath\fasttrig.h"

// CPU-Caps
#include "cpucaps\cpucapsSSE2.h"

// Programmlauf
#include "programerror\programrun.h"

// Mathematische Bibliothek: Vektoren
#include "vektoren\vector2.h"
#include "vektoren\vector3.h"
#include "vektoren\vector4.h"
#include "vektoren\vector2.inl.h"
#include "vektoren\vector3.inl.h"
#include "vektoren\vector4.inl.h"
#include "vektoren\vectormath.inl.h"

// Mathematische Bibliothek: Matrix
#include "matrix\matrix4.h"
#include "matrix\matrix4.inl.h"

// Mathematische Bibliothek: Quaternion
#include "quaternion\quaternion.h"
#include "quaternion\quaternion.inl.h"

// Mathematische Bibliothek: Liniensegmente
#include "lines\lineseg.h"
#include "lines\lineseg.inl.h"
#include "lines\linemath.inl.h"

// Mathematische Bibliothek: Polygone und Dreiecke
#include "triangle\triangle.h"
#include "triangle\triangle3.h"
#include "triangle\triangle3.inl.h"
#include "triangle\trianglemath.h"
#include "polygon\polygon.h"
#include "polygon\polygon.inl.h"

// Mathematische Bibliothek: Bounding ...
#include "bounding\aabbox.h"
#include "bounding\aabbox.inl.h"
#include "bounding\aabsphere.h"
#include "bounding\aabsphere.inl.h"

// Mathematische Bibliothek: Plane
#include "plane\plane.h"
#include "plane\plane.inl.h"

// Mathematische Bibliothek: Zusatz
#include "interpolation\interpolation.h"
#include "random\random.h"

// Grafische Bibliothek: Color
#include "color\color3.h"
#include "color\color3.inl.h"
#include "color\color4.h"
#include "color\color4.inl.h"

// Grafische Bibliothek: Vertices
#include "vertices\vertices.h"

// Grafische Bibliothek: Blitten, Texturen+Materialien
#include "blit\blit2d.h"

// Grafische Bibliothek: EngineLogo
#include "enginelogo\enginelogo.h"
#include "enginelogo\enginelogo.inl.h"

// Grafische Bibliothek: Viewcone/View Frustrum
#include "viewcone\viewcone.h"
#include "viewcone\viewcone.inl.h"

// Grafische Bibliothek: Kamera
/*
#include "camera\camera.h"
#include "camera\camera.inl.h"
*/
#include "camera\camera2.h"
#include "camera\camera2.inl.h"

// Grafische Bibliothek: GDI-Bitmap
#include "gdibitmap\gdibitmap.h"
#include "gdibitmap\gdibitmap.inl.h"

// Grafische Bibliothek: Skybox
#include "skybox\skybox.h"
#include "skybox\skybox.inl.h"

// Hilfsbibliothek: CPU-Caps
#include "cpucaps\cpucaps.h"

// Hilfsbibliothek: Timer
#include "timer\timer.h"
#include "timer\timer.inl.h"
#include "timer\fpstimer.h"
#include "timer\fpstimer.inl.h"

// Hilfsbibliothek: Window
#include "window\window.h"
#include "window\window.inl.h"

// Grafische Bibliothek: Direct3D-Pipeline
#include "piped3d\pipedescriptor.h"
//#include "piped3d\piped3d.h"
//#include "piped3d\piped3d.inl.h"

// Grafische Bibliothek: Direct3D-Pipeline 2
#include "piped3d2\piped3d2.h"
#include "piped3d2\piped3d2.inl.h"

// Special Effects 2D: FireEffect
/*
#include "fireeffect\fireeffect.h"
#include "fireeffect\fireeffect.inl.h"
*/

// Special Effects 2D: PerlinNoiseEffect
#include "perlinnoiseeffect\perlinnoiseeffect.h"
#include "perlinnoiseeffect\perlinnoiseeffect.inl.h"

// Special Effects 2D: WaterEffect
#include "watereffect\watereffect.h"
#include "watereffect\watereffect.inl.h"

// Special Effects 2D: FlagEffect und FlagWrapEffect
#include "flageffect\flageffect.h"
#include "flageffect\flageffect.inl.h"
#include "flageffect\flagwrapeffect.h"
#include "flageffect\flagwrapeffect.inl.h"

// Grafische Bibliothek: TextureLockKit
#include "texturelockkit\texturelockkit.h"
#include "texturelockkit\texturelockkit.inl.h"

// Grafische Bibliothek: ParticleStorm
#include "particlestorm\particle.h"
#include "particlestorm\particle.inl.h"
#include "particlestorm\particlestorm.h"
#include "particlestorm\particlestorm.inl.h"
#include "particlestorm\basicemitter.h"
#include "particlestorm\basicemitter.inl.h"

// Controller: Kreiscontroller
#include "circularcontroller\circularcontroller.h"
#include "circularcontroller\circularcontroller.inl.h"

// Primitives: Kreis
#include "primitives_circle\primitives_circle.h"
#include "primitives_circle\primitives_circle.inl.h"

// Primitives: Ring
#include "primitives_ring\primitives_ring.h"
#include "primitives_ring\primitives_ring.inl.h"

// Primitives: Dome
#include "primitives_dome\primitives_dome.h"
#include "primitives_dome\primitives_dome.inl.h"

// Primitives: Sphere
#include "primitives_sphere\primitives_sphere.h"
#include "primitives_sphere\primitives_sphere.inl.h"

// Manager: Materialien
#include "material\material.h"
#include "material\material.inl.h"
#include "material\materialman.h"
#include "material\materialman.inl.h"

// Timer: RDTSC
#ifdef ENABLE_RDTSCTIMER
#include "timer\rdtsctimer.h"
#include "timer\rdtsctimer.inl.h"
#endif

// Linked List
#include "linked\dllist.h"
#include "linked\dllist.inl.h"

// Datentypen
#include "vsfloat\vsfloat.h"
#include "vsfloat\vsfloat.inl.h"