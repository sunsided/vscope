//--------------------------------------------------------------------------
//
//  File:       PrestormParticle.h
//
//  Contents:   Declaration of PrestormParticle
//
//	To do:		
//
//	Note:		This isn't a good example of a Class
//				I chose not to use access routines because of how often I change the data.  
//				I just gave the ParticleSystem full access to PrestormParticle
//
//---------------------------------------------------------------------------

#ifndef __PrestormParticle_H_
#define __PrestormParticle_H_

#pragma once

#include "..\include-direct3d.h"
#include "..\vektoren\vector3.h"
//#include <D3DTypes.h>
//#include "PrestormParticleSystem.h"

class PrestormParticleSystem;
friend class PrestormParticleSystem;


class PrestormParticle {
	
public:

	// usual suspects, Constructor and Destructor
	PrestormParticle();
	~PrestormParticle();

	// Update method with TimeDelta for time-based movement
	bool Update( float fTimeDelta );
	
	// Location of particle at last update
	VECTOR3		m_d3dvPrevLocation;
	
	// Current location of particle
	VECTOR3		m_d3dvLocation;

	// Current velocity of particle
	VECTOR3		m_d3dvVelocity;

	// Current Color and how much color to add over time
	D3DCOLORVALUE	m_d3dcColor;
	D3DCOLORVALUE	m_d3dcColorDelta;

	// Age of particle in seconds
	float		m_fAge;
	
	// Age at which particle dies
	float		m_fLifetime;
	
	// size of particle in world units and delta to add over time	
	float		m_fSize;
	float		m_fSizeDelta;

	// translucency and delta to add over time
	// this may seem counter-intuitive, but 0.0f Alpha is transparent
	float		m_fAlpha;
	float		m_fAlphaDelta;

	// gravity ratio and delta to add over time
	// this is a proportion of normal gravity and can go negative
	float		m_fGravity;
	float		m_fGravityDelta;
	
	//fix not used anymore
	float		m_bOrbiting;

	// Set ParticleSystem as parent of particle
	void		SetParent(PrestormParticleSystem* Parent){ m_pParent = Parent;}

private:
	// our parent
	PrestormParticleSystem* m_pParent;
	

};

#endif