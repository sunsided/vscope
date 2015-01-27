//--------------------------------------------------------------------------
//
//  File:       PrestormParticleSystem.cpp
//
//  Contents:   Implementation of PrestormParticleSystem
//
//	To do:		Variance is not accessible through GUI. 
//				Don't forget the importance of the variance variables
//
//---------------------------------------------------------------------------

#include "PrestormParticleSystem.h"
#include "..\blit\blit2d.h"
#include "..\common\common.h"
#include "..\vektoren\vector3.h"
#include "..\matrix\matrix4.h"
#include "..\vektoren\vector3.inl.h"
#include "..\matrix\matrix4.inl.h"
#include "..\vertices\vertices.inl.h"

/*
#include "D3DApp.h"
#include "D3DTextr.h"
#include "D3DUtil.h"
#include "D3DMath.h"
*/

#pragma intrinsic(memset, memcpy)

/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/


#define GRAVITY VECTOR3(0.0f, -9.8f, 0.0f)

//-----------------------------------------------------------------------------
//
//	PrestormParticle::PrestormParticle
//
//-----------------------------------------------------------------------------
PrestormParticle::PrestormParticle()
{
	// should have used the newer C++ method of parameter initialization
	// but wanted to keep it simple for those new to C++
	m_fAge = 0.0f;
	m_fSize = 1.0f;
	m_d3dcColor.r = 1.0f;
	m_d3dcColor.g = 0.0f;
	m_d3dcColor.b = 0.0f;
	m_d3dcColor.a = 0.5f;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticle::~PrestormParticle
//
//-----------------------------------------------------------------------------
PrestormParticle::~PrestormParticle()
{
	// we don't do anything freaky with our particles so nothing to do
	// in the deconstructor
}


//-----------------------------------------------------------------------------
//
//	PrestormParticle::Update
//		
//	Update the given particle with the passed in time delta
//	
//  If the particle dies in the update, False is returned
//
//-----------------------------------------------------------------------------
bool PrestormParticle::Update( float fTimeDelta )
{

	// Some systems may have particles with no Lifetime
	// i.e. they could have to collide with terrain 
	// or they could just always be alive if the system
	// had a fixed # of particles alive
	if ( m_fAge + fTimeDelta >= m_fLifetime ) 
	{
		m_fAge = -1.0f;
		return FALSE;
	}
	else
	{

		// everything ages so add the time elapsed
		m_fAge += fTimeDelta;

		// Our current location will be our previous location next frame
		m_d3dvPrevLocation = m_d3dvLocation;

		// this moves the particle using the last known velocity and the time that has passed
		m_d3dvLocation += m_d3dvVelocity * fTimeDelta;

		// whether or not our parent system allows ground plane collision.
		// this really should be a per particle setting, not an attribute of the parent system
		// This isn't how you would normally do collision.  This snaps any particle below the 
		// ground plane up to ground level.  Ground collision is just to show what a fountain
		// or other effects might look like 
		if ( m_pParent->IsColliding() )
		{
			if ( m_d3dvLocation.y < -25.0f ) 
			{
				// if they are moving at a decent rate vertically reflect them
				if ( m_d3dvVelocity.y > -5.0f )  // -5.0f <= velocity.y <= 0.0f
				{
					m_d3dvLocation.y = -25.0f;
					m_d3dvVelocity.y = 0.0f;
				}
				// otherwise, let them rest on the ground plance
				else
				{
					m_d3dvLocation.y = m_d3dvPrevLocation.y; 
					m_d3dvVelocity.y = -m_d3dvVelocity.y*0.5f;
				}
			}
		}

		// note that GRAVITY is hardcoded up above.  Gravity could be a vector per particle system
		// to simulate a crosswind that blew the particles sideways as well.
		m_d3dvVelocity += ( GRAVITY * m_fGravity * fTimeDelta );

		// if this particle's parent system supports Attraction
		if ( m_pParent->IsAttractive() )
		{

			VECTOR3 AttractLocation;
			
			// Find out where our Parent is located so we can track it
			m_pParent->GetLocation(AttractLocation);

			// The attractors could be points in space to create some cool effects.
			//AttractLocation = VECTOR3(50,50,50);

			// calculate the vector between the particle and the attractor
			VECTOR3 AttractDir = AttractLocation - m_d3dvLocation; 
			
			// We can turn off attraction for certain axes 
			// AttractDir.y = 0; // this would simulate a cyclone type effect
			
			// note that this is NOT accurate gravitation.   We don't even look at the distance
			// between the 2 locations !!!    But what can I say, it looks good. You can find the 
			// formula for Gravitation in any good physics book.  It uses the masses of the 2 objects
			// the distance between them and the Gravitational constant

			// if you decide to use this simple method you really should use a variable multiplier
			// instead of a hardcoded value like 25.0f
			AttractDir.Normalize();
			m_d3dvVelocity += AttractDir * 25.0f * fTimeDelta;
		
		}

		// adjust current Color from calculated Deltas and time elapsed.
		m_d3dcColor.r += m_d3dcColorDelta.r * fTimeDelta;
		m_d3dcColor.g += m_d3dcColorDelta.g * fTimeDelta;
		m_d3dcColor.b += m_d3dcColorDelta.b * fTimeDelta;

		// adjust current Alpha yadda yadda yadda
		m_fAlpha += m_fAlphaDelta * fTimeDelta;
		// adjust current Size
		m_fSize += m_fSizeDelta * fTimeDelta;
		// adjust current Gravity 
		m_fGravity += m_fGravityDelta * fTimeDelta;

	}

	// if we got this far, everything is probably cool
	return TRUE;

}





/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/



//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::PrestormParticleSystem
//
//-----------------------------------------------------------------------------
PrestormParticleSystem::PrestormParticleSystem()
{
	//should have used the new C++ initialization methods for members (which are faster), but I wanted to keep 
	// the code readable to those new to C++
	m_fAge = 0.0f;
	m_fTimeLastUpdate = 0.0f;
	m_fEmissionResidue =  0.0f;
	m_d3dvDirection = VECTOR3(0.f,1.f,0.f);

	// since we have a previous location , we have to set that to the current location, otherwise
	// our first update could have erroneous data in the PrevLocation field
	m_d3dvLocation = VECTOR3( 0.0f, 0.0f, 0.0f);
	//memset(&m_d3dvLocation, 0, sizeof(m_d3dvLocation));
	m_d3dvPrevLocation = VECTOR3( 0.0f, 0.0f, 0.0f);
	//memset(&m_d3dvPrevLocation, 0, sizeof(m_d3dvPrevLocation));

	// Initialize the 4 vertices of our mesh to some acceptable values
	// VECTOR3(-1.0f,-1.0f, 0.0f ) is the location of the vertex in local space
	// 0x40ffffff is the D3DCOLOR value. ( which doesn't matter much since we recalculate it every frame.
	//     basically it's   0xaarrggbb where aa = alpha, rr = red...  so this is white with 0.25 opacity (0x40/0xff) = 64/255 ~= 0.25
	// 0 is the specular value which we don't use
	// 0.0f, 1.0f are the UV coordinates for the vertex.  this tells the renderer how to map the texture onto triangles we render
	/*
	m_Mesh[0] = VSD3DLVERTEX( VECTOR3(-1.0f,-1.0f, 0.0f ), 0x40ffffff, 0.0f, 1.0f );
	m_Mesh[1] = VSD3DLVERTEX( VECTOR3(-1.0f, 1.0f, 0.0f ), 0x40ffffff, 0.0f, 0.0f );
	m_Mesh[2] = VSD3DLVERTEX( VECTOR3( 1.0f,-1.0f, 0.0f ), 0x40ffffff, 1.0f, 1.0f );
	m_Mesh[3] = VSD3DLVERTEX( VECTOR3( 1.0f, 1.0f, 0.0f ), 0x40ffffff, 1.0f, 0.0f );
	*/
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::~PrestormParticleSystem
//
//-----------------------------------------------------------------------------
PrestormParticleSystem::~PrestormParticleSystem()
{
	// sure is empty in here
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::Update
//
//	Always returns TRUE for our version, but there are various reasons why 
//  you may want to bail out and return false.
//
//-----------------------------------------------------------------------------
bool PrestormParticleSystem::Update(float fTime)
{
	// fTime is absolute time.  So we need to calculate the relative time displacement or fTimeDelta that has elapesed
	float fTimeDelta = fTime - m_fTimeLastUpdate;

	m_fTimeLastUpdate = fTime;

	// sort of a hack (or nice screen saver effect) to test out a moving particle system
	if (m_bIsMoving)
	{
		static float fThetaHoriz = 0.0f;
		static float fThetaVert = 180.0f;

		fThetaHoriz += 50.0f * fTimeDelta;
		fThetaVert += 30.0f * fTimeDelta;

		if ( fThetaHoriz > 359.0f ) 
			fThetaHoriz = 0.0f;

		if ( fThetaVert > 359.0f ) 
			fThetaVert = 0.0f;

		m_d3dvLocation.x = 30.0f * (float)cos( fThetaHoriz * 0.01745f );
		m_d3dvLocation.y = 50.0f + 30.0f * (float)sin( fThetaVert * 0.01745f );
		m_d3dvLocation.z = 30.0f * (float)sin( fThetaHoriz * 0.01745f );
		
	}
	else
	{
		// this will reset it every frame, but most importantly it will reset it to the origin if it isn't Moving
		m_d3dvLocation.x = 0.0f;
		m_d3dvLocation.y = 10.0f;
		m_d3dvLocation.z = 0.0f;
		
	}

	// clear our counter variable before counting how many particles are alive
	m_uParticlesAlive = 0;

	// update all particles that we own
	for ( int i=0; i<MAX_PARTICLES; i++ )
	{
		if (m_rParticles[i].m_fAge >= 0.0f )
			if ( m_rParticles[i].Update( fTimeDelta )) // Note that the update function returns FALSE if the particle died
				m_uParticlesAlive++;
	}

	// calculate how many particles we should create from ParticlesPerSec and time elapsed taking the 
	// previous frame's EmissionResidue into account.
	float fParticlesNeeded = m_uParticlesPerSec * fTimeDelta + m_fEmissionResidue;
	
	// cast the float fparticlesNeeded to a INT to see how many particles we really need to create.
	unsigned int uParticlesCreated = (unsigned int)fParticlesNeeded;

	if ( !m_bIsSuppressed )
	{
		// remember the difference between what we wanted to create and how many we created.
		m_fEmissionResidue = fParticlesNeeded - uParticlesCreated;
	}
	else
	{
		m_fEmissionResidue = fParticlesNeeded;
		uParticlesCreated = 0;
	}

	// see if actually have any to create
	if ( uParticlesCreated > 0 )
	{
		// loop through all the particles to see if any are available
		for ( i=0; i<MAX_PARTICLES; i++ )
		{
			// if we have created enough particles, this value will be 0 and we can skip the rest
			// alternatively you could mantain a list of free particles and used particles
			if ( !uParticlesCreated )
				break;

			// of the age is -1.0f then this particle is not in use
			if ( m_rParticles[i].m_fAge < 0.0f ) 
			{
				// New particle so it's age is 0.0f 
				// Actually should be some randomization of fTimeDelta since in a perfect world
				// particles would have been created between our last update and now.
				m_rParticles[i].m_fAge = 0.0f;
				m_rParticles[i].m_fLifetime = m_fLife + RANDOM_NUM * m_fLifeVar;
				Clamp( m_rParticles[i].m_fLifetime, MIN_LIFETIME, MAX_LIFETIME ); 

				// our start color is going to be the System's StartColor + the System's color variation
				m_rParticles[i].m_d3dcColor.r = m_d3dcColorStart.r + RANDOM_NUM * m_d3dcColorVar.r;
				m_rParticles[i].m_d3dcColor.g = m_d3dcColorStart.g + RANDOM_NUM * m_d3dcColorVar.g;
				m_rParticles[i].m_d3dcColor.b = m_d3dcColorStart.b + RANDOM_NUM * m_d3dcColorVar.b;
				// we don't use the alpha value of the color here
				m_rParticles[i].m_d3dcColor.a = 1.0f;

				// with variation, the Color could overflow
				Clamp( m_rParticles[i].m_d3dcColor.r, 0.0f, 1.0f );
				Clamp( m_rParticles[i].m_d3dcColor.g, 0.0f, 1.0f );
				Clamp( m_rParticles[i].m_d3dcColor.b, 0.0f, 1.0f );

				// calculate a delta so that by the time the particle dies, it will have reached it's "ColorEnd"
				m_rParticles[i].m_d3dcColorDelta.r = (m_d3dcColorEnd.r - m_rParticles[i].m_d3dcColor.r) / m_rParticles[i].m_fLifetime;
				m_rParticles[i].m_d3dcColorDelta.g = (m_d3dcColorEnd.g - m_rParticles[i].m_d3dcColor.g) / m_rParticles[i].m_fLifetime;
				m_rParticles[i].m_d3dcColorDelta.b = (m_d3dcColorEnd.b - m_rParticles[i].m_d3dcColor.b) / m_rParticles[i].m_fLifetime;

				// Calculate our Alpha from the system's AlphaStart and AlphaVar
				m_rParticles[i].m_fAlpha = m_fAlphaStart + RANDOM_NUM * m_fAlphaVar;
				// clamp any overflow
				Clamp( m_rParticles[i].m_fAlpha, MIN_ALPHA, MAX_ALPHA );
				// calculate a delta so that by the time the particle dies, it will have reached it's "AlphaEnd"
				m_rParticles[i].m_fAlphaDelta = (m_fAlphaEnd - m_rParticles[i].m_fAlpha) / m_rParticles[i].m_fLifetime;
				
				
				m_rParticles[i].m_fSize = m_fSizeStart + RANDOM_NUM * m_fSizeVar;
				Clamp( m_rParticles[i].m_fSize, MIN_SIZE, MAX_SIZE );
				m_rParticles[i].m_fSizeDelta = (m_fSizeEnd - m_rParticles[i].m_fSize) / m_rParticles[i].m_fLifetime;
				

				m_rParticles[i].m_fGravity = m_fGravityStart*9.8f + RANDOM_NUM * m_fGravityVar*9.8f;
				// yes this is a lot of repetitive calculation ( * 9.8f ), but it keeps the meaning of m_fgravity clear.
				// It's a percentage of normal gravity.
				Clamp( m_rParticles[i].m_fGravity, MIN_GRAVITY*9.8f, MAX_GRAVITY*9.8f );
				m_rParticles[i].m_fGravityDelta = ( m_fGravityEnd*9.8f - m_rParticles[i].m_fGravity ) / m_rParticles[i].m_fLifetime;
				
				// since Velocity is a change in position over time, we calculate a Velocity the particle would have to 
				// have travelled to move from PrevLocation to Location in fTimeDelta seconds.
				// Then we can calculate points in that linear path by passing in different Time deltas (note the 'RANDOM_NUM * fTimeDelta' below)
				VECTOR3 tempVelocity = (m_d3dvLocation - m_d3dvPrevLocation)/fTimeDelta;
				
				// Emit the particles from a location between the last known location and the current location
				m_rParticles[i].m_d3dvLocation = m_d3dvPrevLocation + tempVelocity * RANDOM_NUM * fTimeDelta;
	
				// This is a simple way of randomizing the location a little 
				// You could also emit particles from a source primitive like a Sphere or a Plane instead of a point
				/* 
				m_rParticles[i].m_d3dvLocation.x += 2.0f - RANDOM_NUM * 4.0f;
				m_rParticles[i].m_d3dvLocation.y += 2.0f - RANDOM_NUM * 4.0f;
				m_rParticles[i].m_d3dvLocation.z += 2.0f - RANDOM_NUM * 4.0f;
				*/

				// Update the previous location so the next update we can remember where we were
				m_rParticles[i].m_d3dvPrevLocation = m_d3dvLocation;

				// The emitter has a Direction.  This code adds some randomness to that direction so
				// that we don't emit a Line of particles.  For the demo I always assume a randomess of 
				// 360 degrees in the Yaw direction.  In your code, you really should allow this to be modified
				// separately from the Pitch.  Normally I would define PI 3.14159 and have a DEG_2_RAD macro
				// but it is used so briefly in this app I didn't
				float RandomYaw = RANDOM_NUM * 3.14159f * 2.0f;
				float RandomPitch = RANDOM_NUM * m_fTheta * 3.14159f / 180.0f ;

				//this uses spherical coordinates to randomize the velocity vector ( or the direction ) of the particle
				m_rParticles[i].m_d3dvVelocity.y = cosf( RandomPitch );
				m_rParticles[i].m_d3dvVelocity.x = sinf(RandomPitch) * cosf(RandomYaw);
				m_rParticles[i].m_d3dvVelocity.z = sinf(RandomPitch) * sinf(RandomYaw);

				// Velocity at this point is just a direction (normalized vector ) and needs to be multiplied by 
				// the speed component to be a true velocity
				float fNewSpeed = m_fSpeed + RANDOM_NUM * m_fSpeedVar;
				Clamp( fNewSpeed, MIN_SPEED, MAX_SPEED );
				// Luckily D3D knows how to multiply a Vector by a Scalar
				m_rParticles[i].m_d3dvVelocity *= fNewSpeed ;
				
				// let the particle know who it's Daddy is
				m_rParticles[i].SetParent(this);

				// decrement the number of needed particles
				uParticlesCreated--;
			}
		}
	}

	///set prevlocation to current location so next frame we know where we were
	m_d3dvPrevLocation = m_d3dvLocation;	

    return TRUE;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::Draw
//
//	Renders all active particles as billboards
//
//-----------------------------------------------------------------------------
void PrestormParticleSystem::Draw(LPDIRECT3DDEVICE8 lpd3dDevice)
{

	// Load the texture currently active for this system
	LoadCurrentTexture(lpd3dDevice);
	
    // Render the particles
    for( DWORD i=0; i<MAX_PARTICLES; i++ )
    {

		// if particle is alive, it's age will be nonZero
		if ( m_rParticles[i].m_fAge >= 0.0f )
		{

			// set the mesh's color to the current particles RGBA value
			m_Mesh[0].color = 
			m_Mesh[1].color = 
			m_Mesh[2].color = 
			m_Mesh[3].color = D3DCOLOR_RGBA(	(int)(m_rParticles[i].m_d3dcColor.r * 256), 
												(int)(m_rParticles[i].m_d3dcColor.g * 256), 
												(int)(m_rParticles[i].m_d3dcColor.b * 256), 
												(int)(m_rParticles[i].m_fAlpha * 256));   

			MATRIX4 ViewMatrix;
			// this guarantees a clean Matrix before doing operations with it
			//D3DUtil_SetIdentityMatrix( ViewMatrix );
			ViewMatrix.Identity();
			// get the ViewMatrix from D3D
			//lpd3dDevice->GetTransform( D3DTRANSFORMSTATE_VIEW, &ViewMatrix );
			lpd3dDevice->GetTransform( D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix );

			MATRIX4 InvViewMatrix;
			// this guarantees a clean Matrix before doing operations with it
			//D3DUtil_SetIdentityMatrix( InvViewMatrix );
			InvViewMatrix.Identity();
			// get the Inverse of the ViewMatrix, kinda like your reflection looking at you in the mirror
			//D3DMath_MatrixInvert( InvViewMatrix, ViewMatrix );
			InvViewMatrix.Inverse(ViewMatrix);

			// set the translation portion of the InvViewMatrix to the location of the particles in world space
			InvViewMatrix._41 = m_rParticles[i].m_d3dvLocation.x;
			InvViewMatrix._42 = m_rParticles[i].m_d3dvLocation.y;
			InvViewMatrix._43 = m_rParticles[i].m_d3dvLocation.z;

			// set the scale of the particles in local space so when they are transformed they will be the right size
			m_Mesh[0].x = -m_rParticles[i].m_fSize;
			m_Mesh[0].y = -m_rParticles[i].m_fSize;
			
			m_Mesh[1].x = -m_rParticles[i].m_fSize;
			m_Mesh[1].y =  m_rParticles[i].m_fSize;
			
			m_Mesh[2].x =  m_rParticles[i].m_fSize;
			m_Mesh[2].y = -m_rParticles[i].m_fSize;
			
			m_Mesh[3].x =  m_rParticles[i].m_fSize;
			m_Mesh[3].y =  m_rParticles[i].m_fSize;

			// Set the new world transform and render the particle
			//lpd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &InvViewMatrix );
			lpd3dDevice->SetTransform( D3DTS_WORLD, (D3DXMATRIX*)&InvViewMatrix );

			// Note: Should accumulate polygons in an array and then pass them all at once as a D3DPT_TRIANGLELIST
			//lpd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, VS_D3DFVF_LVERTEX, m_Mesh, 4, 0 );
			lpd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 4, &m_Mesh, sizeof(VSD3DLVERTEX) );

		}
    }

}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::Move
//
//-----------------------------------------------------------------------------
void PrestormParticleSystem::Move(VECTOR3 vLocation)
{
	m_d3dvPrevLocation = m_d3dvLocation;
	m_d3dvLocation = vLocation;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::ChangeParams
//
//-----------------------------------------------------------------------------
void PrestormParticleSystem::ChangeParams(const BYTE Keys[])
{ 

	// Color changes
	if ( Keys[VK_INSERT] )
	{	
		if ( Keys[VK_SHIFT] ) 
		{
			m_d3dcColorEnd.r += 0.05f;
		}
		else
		{
			m_d3dcColorStart.r += 0.05f;
		}
	}

	if ( Keys[VK_DELETE] )
	{	
		if ( Keys[VK_SHIFT] ) 
		{
			m_d3dcColorEnd.r -= 0.05f;
		}
		else
		{
			m_d3dcColorStart.r -= 0.05f;
		}
	}

	if ( Keys[VK_HOME] )
	{	
		if ( Keys[VK_SHIFT] ) 
		{
			m_d3dcColorEnd.g += 0.05f;
		}
		else
		{
			m_d3dcColorStart.g += 0.05f;
		}
	}

	if ( Keys[VK_END] )
	{	
		if ( Keys[VK_SHIFT] ) 
		{
			m_d3dcColorEnd.g -= 0.05f;
		}
		else
		{
			m_d3dcColorStart.g -= 0.05f;
		}
	}


	if ( Keys[VK_PRIOR] )
	{	
		if ( Keys[VK_SHIFT] ) 
		{
			m_d3dcColorEnd.b += 0.05f;
		}
		else
		{
			m_d3dcColorStart.b += 0.05f;
		}
	}

	if ( Keys[VK_NEXT] )
	{
		if ( Keys[VK_SHIFT] ) 
		{
			m_d3dcColorEnd.b -= 0.05f;
		}
		else
		{
			m_d3dcColorStart.b -= 0.05f;
		}
	}

	// Make sure that any adjustments that we made
	// stay within valid color limits
	Clamp( m_d3dcColorStart.r, 0.0f, 1.0f );
	Clamp( m_d3dcColorStart.g, 0.0f, 1.0f );
	Clamp( m_d3dcColorStart.b, 0.0f, 1.0f );

	Clamp( m_d3dcColorEnd.r, 0.0f, 1.0f );
	Clamp( m_d3dcColorEnd.g, 0.0f, 1.0f );
	Clamp( m_d3dcColorEnd.b, 0.0f, 1.0f );
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::IsMoving
//
//-----------------------------------------------------------------------------
bool PrestormParticleSystem::IsMoving()
{ 
	return m_bIsMoving; 
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::IsColliding
//
//-----------------------------------------------------------------------------
bool PrestormParticleSystem::IsColliding()
{
	return m_bIsColliding;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::IsAttractive
//
//-----------------------------------------------------------------------------
bool PrestormParticleSystem::IsAttractive()
{
	return m_bIsAttractive;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::GetLocation
//
//-----------------------------------------------------------------------------
void PrestormParticleSystem::GetLocation(VECTOR3& vLocation)
{
	vLocation = m_d3dvLocation;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::NumParticles
//
//-----------------------------------------------------------------------------
unsigned int PrestormParticleSystem::NumParticles()
{
	return m_uParticlesAlive;
}


//-----------------------------------------------------------------------------
//
//	PrestormParticleSystem::LoadCurrentTexture
//
//-----------------------------------------------------------------------------
HRESULT PrestormParticleSystem::LoadCurrentTexture(LPDIRECT3DDEVICE8 lpd3dDevice) {

	static LPDIRECT3DTEXTURE8 Tex = NULL;
	SAFE_RELEASE(Tex);
	//CreateTexture(lpd3dDevice, "flare.tga", &Tex, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));

	switch(m_uTextureID)
	{
		case 0: {
			//lpd3dDevice->SetTexture( 0, D3DTextr_GetSurface("flare.tga") );
			CreateTexture(lpd3dDevice, "flare.tga", &Tex, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
			lpd3dDevice->SetTexture( 0, Tex );

			return TRUE;
		}
		case 1: {
			//lpd3dDevice->SetTexture( 0, D3DTextr_GetSurface("cloud.tga") );
			CreateTexture(lpd3dDevice, "cloud.tga", &Tex, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
			lpd3dDevice->SetTexture( 0, Tex );
			return TRUE;
		}
		case 2: {
			//lpd3dDevice->SetTexture( 0, D3DTextr_GetSurface("bubble.tga") );
			CreateTexture(lpd3dDevice, "bubble.tga", &Tex, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
			lpd3dDevice->SetTexture( 0, Tex );
			return TRUE;
		}
		case 3: {
			//lpd3dDevice->SetTexture( 0, D3DTextr_GetSurface("circle.tga") );
			CreateTexture(lpd3dDevice, "circle.tga", &Tex, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
			lpd3dDevice->SetTexture( 0, Tex );
			return TRUE;
		}
		case 4: {
			//lpd3dDevice->SetTexture( 0, D3DTextr_GetSurface("spark.tga") );
			CreateTexture(lpd3dDevice, "spark.tga", &Tex, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
			lpd3dDevice->SetTexture( 0, Tex );
			return TRUE;
		}
		default:
			return FALSE;
			break;
	}

	return TRUE;

}

