//--------------------------------------------------------------------------
//
//  File:       PrestormParticleSystem.h
//
//  Contents:   Declaration of PrestormParticleSystem
//
//	To do:		
//
//	Note:		This isn't a good example of a Class
//				I chose not to use access routines because of how often I change the data.  
//				I just gave the CMyD3DApplication full access to PrestormParticleSystem
//
//---------------------------------------------------------------------------

#ifndef __PrestormParticleSYSTEM_H_
#define __PrestormParticleSYSTEM_H_

#pragma once

//necessary defines
#include "..\include-windows.h"
#include "..\include-direct3d.h"
/*
#include <D3DApp.h>
#include <D3DMath.h>
#include <D3DTextr.h>
#include <D3DUtil.h>
*/
//#include "PrestormParticle.h"
#include "..\vertices\vertices.h"
#include "..\vektoren\vector3.h"


/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/

class PrestormParticleSystem;


class PrestormParticle
{

friend class PrestormParticleSystem;

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














/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/

// RANDOM_NUM returns a float in the range 0.0f - 1.0f
#define RANDOM_NUM      (((FLOAT)rand()-(FLOAT)rand())/RAND_MAX)

// RANDOM_VECTOR returns a VECTOR3 whose components (x,y,Z) are between 0.0f and 1.0f 
// remember that this is not a normalized vector.
#define RANDOM_VECTOR   VECTOR3(RANDOM_NUM,RANDOM_NUM,RANDOM_NUM)

// max number of particles our ParticleSystem can support
#define MAX_PARTICLES	10000 

// some defines for our ParticleSystem.   This makes it easy to change settings
// by using defines and putting them all in one place
#define MIN_SPEED		0.0f	// in world units / sec
#define MIN_LIFETIME	0.1f	// in seconds
#define MIN_SPREAD		0.01f	// in degrees
#define MIN_EMISSION	1.0f	// in particles / sec
#define MIN_SIZE		0.5f	// in world units
#define MIN_GRAVITY		-5.0f	// as a multiple of normal gravity 
#define MIN_ALPHA		0.0f	// as a ratio 

#define MAX_SPEED		250.0f	// in world units / sec
#define MAX_LIFETIME	10.0f	// in seconds
#define MAX_SPREAD		180.0f	// in degrees
#define MAX_EMISSION    1000.0f	// in particles / sec
#define MAX_SIZE		10.0f	// in world units
#define MAX_GRAVITY		5.0f	// as a multiple of normal gravity 
#define MAX_ALPHA		1.0f	// as a ratio 

// button type defines
#define ID_BUTTON_SPEED			0
#define ID_BUTTON_LIFETIME		1
#define ID_BUTTON_SPREAD		2
#define ID_BUTTON_EMISSION		3
#define ID_BUTTON_SIZE_START	4
#define ID_BUTTON_SIZE_END		5
#define ID_BUTTON_ALPHA_START	6
#define ID_BUTTON_ALPHA_END		7
#define ID_BUTTON_GRAVITY_START	8
#define ID_BUTTON_GRAVITY_END	9

#define ID_BUTTON_MOVING		10
#define ID_BUTTON_ATTRACTIVE	11
#define ID_BUTTON_COLLIDING		12

#define ID_BUTTON_TEXTURE		13
#define ID_BUTTON_PRESETS		14

#define ID_BUTTON_MAX			15

#define TOOLBAR_WIDTH			128

#define MAX_TEXTURES			5

// change this if you add new presets !!!!
#define MAX_PRESETS				9


// useful macro to guarantee that values are within a given range
#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);

// Our ParticleSystem class
class PrestormParticleSystem
{
	// this is so that our specific application class can have access to
	// the private members of our ParticleSystem.
	//friend class CMyD3DApplication;

public:
    PrestormParticleSystem();
   ~PrestormParticleSystem();

	// Update the system and all particles with the given time delta
	bool		Update(float fTimeDelta);
	// render the system
	void		Draw(LPDIRECT3DDEVICE8 lpd3dDevice);
	// unused.  Could be used to move the system
	void		Move(VECTOR3 vLocation);
	// pass in keystrokes that may effect the current system parameters.
	// this is bad.. Normally you would access routines to change the data
	void		ChangeParams(const BYTE Keys[]);
	
	// 3 access routines to check if the system is moving, attractive, or 
	// if the particles collide with a ground plane
	bool		IsMoving();
	bool		IsColliding();
	bool		IsAttractive();

	// find out where the system is in world space
	void		 GetLocation(VECTOR3& vLocation);
	// how many particles are active ?
	unsigned int NumParticles();
	// Load the current system texture into d3d
	HRESULT		 LoadCurrentTexture(LPDIRECT3DDEVICE8 lpd3dDevice);

private:
	// pointer back to main application in case we need to reference somethinng
	void*	m_pApplication;

	// An internal ID for us to remember which texture the system is using
	unsigned int	m_uTextureID;

	// Particles Per Second to emit.
	unsigned int	m_uParticlesPerSec;

	// Particles currently active
	unsigned int	m_uParticlesAlive;

	// Last known location of System ( used for interpolation ).
	VECTOR3		m_d3dvPrevLocation;
	// current location of system in world space
	VECTOR3		m_d3dvLocation;
	// currentt velocity as a Vector ( cause that's what velocity is )   :)
	VECTOR3		m_d3dvVelocity;
	// current Direction of System.  Particles are emitted using this vector + some variation
	VECTOR3		m_d3dvDirection;

	//General comment on my Start,Var,End system of parameter calculation.
	//As the particle ages, we keep interpolating between the Start and End parameters. 
	//The Var parameter is always there to keep things a little randomized.
	//It is useful to change particle parameters over time to simulate various natural phenomenon
	//For example, Gas expands as it dissipates and as such takes up more screen space but also
	//becomes more transparent.  
	//So in this instance we might use a SizeStart of 1.0f and a SizeEnd of 4.0f (depending on what looks best).
	//And then we might set AlphaStart to 0.8f and AlphaEnd to 0.0f.

	// used as a percentage of normal gravity.   Note: to simulate wind or other forces you could make Gravity a Vector
	// which could have components 
	float m_fGravityStart;
	float m_fGravityVar;
	float m_fGravityEnd;

	// Size of the particles in World units
	float m_fSizeStart;
	float m_fSizeVar;
	float m_fSizeEnd;

	// Translucency of particles. Alpha 0 = invisible, Alpha 1 = full visibility
	float m_fAlphaStart;
	float m_fAlphaVar;
	float m_fAlphaEnd;

	// Color of particles, the color of the particles when they start and end.
	// The color is interpolated linearly between these 2 values over time.
	D3DCOLORVALUE	m_d3dcColorStart;
	D3DCOLORVALUE	m_d3dcColorVar;
	D3DCOLORVALUE	m_d3dcColorEnd;

	// Speed is a scalar and is combined with the normalized direction vector of the system to get a 
	// Velocity vector.
	float m_fSpeed;
	float m_fSpeedVar;

	// Life of the particle in seconds, 
	float m_fLife;
	float m_fLifeVar;

	// Picture a vector in space with a start and an end
	// now picture that the vector goes through the center of a Cone such
	// that the tip of the cone is at the start of the vector and the bottom of the cone is at the end of the vector
	// Now picture the angle from the vector out to the edge of the cone.  This is m_fTheta.
	// If it were Zero, the cone would collapse down to the vector and be a line.
	// If it were 90 degrees, then the cone would turn into a hemisphere ( half of a sphere ) 
	// ANd finally if this value were 180 degrees, then the cone would turn into a Sphere

	// this values defines how much randomness the particles have in their directional vector
	float m_fTheta;

	// whether or not the system is moving autonomously
	bool m_bIsMoving;
	// whether or not the particles are attracted to the system
	bool m_bIsAttractive;

	// whether or not we are allowed to emit particles or whether they build up
	bool m_bIsSuppressed;

	// whether or not our particles collide with the ground plane
	bool m_bIsColliding;

	// age in seconds of the system
	float m_fAge;
	
	// last moment in time that we updated the system
	float m_fTimeLastUpdate;

	// this is a value that allows us to emit very precise amounts of particles.
	// what if we want 0.5 particles per second ?    0.5 is not a full particle ( we don't round up ) so we can't emit one yet
	// so we remember what we wanted to emit and add that next time we try to emit some more particles.
	// Think about a faucet that is leaking very slowly.  The drop slowly gets bigger and bigger till there is enough mass to allow
	// it to break free.
	float m_fEmissionResidue;

	// a fixed array of particles.
	// there are many ways to do this, some are better in certain situations.
	// this version keeps us from dynamically allocating and freeing memory
	// but also limits us to MAX_PARTICLES and also always costs us MAX_PARTICLES
	// some people use linked lists of Live Particles and Free Particles.
	PrestormParticle	m_rParticles[MAX_PARTICLES];

    // Geometry
	// These are the 4 vertices of our Quad.  Notice that they are D3DLVertices, which means that we will handle the lighting.
	VSD3DLVERTEX   m_Mesh[4];

};


#endif