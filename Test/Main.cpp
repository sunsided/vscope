#include <vscope.h>


BOOL g_bRunning = TRUE;
BOOL g_bPaused = FALSE;

#include "Main.h"
#include "windowproc.h"

#include "scene.h"







/********************************************************************************************/
// ------------------------------------------------------------------------------------------------
// ---- Basic types
/*
typedef long int32;
typedef unsigned long uint32;
typedef float real32;
typedef double real64;
typedef unsigned char uint8;
typedef const char *cpointer;
*/
// ------------------------------------------------------------------------------------------------
// Configuration/Testing

// ---- number of elements to test (shows tradeoff of histogram size vs. sort size)
/*const uint32 ct = 65536;*/

// ---- really, a correctness check, not correctness itself ;)
#define CORRECTNESS	1

// ---- use SSE prefetch (needs compiler support), not really a problem on non-SSE machines.
//		need http://msdn.microsoft.com/vstudio/downloads/ppack/default.asp
//		or recent VC to use this

#define VS_RADIX_PREFETCH_OPTIMIZATION 1

#if VS_RADIX_PREFETCH_OPTIMIZATION
#include <xmmintrin.h>	// for prefetch
#define pfval	64
#define pfval2	128
#define pf(x)	_mm_prefetch((const char *)(x + i + pfval), 0)
#define pf2(x)	_mm_prefetch((const char *)(x + i + pfval2), 0)
#else
#define pf(x)
#define pf2(x)
#endif

// ------------------------------------------------------------------------------------------------
// ---- Visual C++ eccentricities

#if _WINDOWS
#define finline __forceinline
#else
#define finline inline
#endif
/*
// ================================================================================================
// flip a float for sorting
//  finds SIGN of fp number.
//  if it's 1 (negative float), it flips all bits
//  if it's 0 (positive float), it flips the sign only
// ================================================================================================
finline uint32 FloatFlip(uint32 f)
{
	uint32 mask = -int32(f >> 31) | 0x80000000;
	return f ^ mask;
}

finline void FloatFlipX(uint32 &f)
{
	uint32 mask = -int32(f >> 31) | 0x80000000;
	f ^= mask;
}

// ================================================================================================
// flip a float back (invert FloatFlip)
//  signed was flipped from above, so:
//  if sign is 1 (negative), it flips the sign bit back
//  if sign is 0 (positive), it flips all bits back
// ================================================================================================
finline uint32 IFloatFlip(uint32 f)
{
	uint32 mask = ((f >> 31) - 1) | 0x80000000;
	return f ^ mask;
}*/

// ---- utils for accessing 11-bit quantities
#define _0(x)	(x & 0x7FF)
#define _1(x)	(x >> 11 & 0x7FF)
#define _2(x)	(x >> 22 )



// And the code comes from ... "file:\L:\Dokumente\radix sort, tricks\stereopsis  graphics  radix tricks.htm"



class DASDING : /*public IVSFloatComparable,*/ public PARTICLE {
public:
	VSINLINE			DASDING() { 
							this->m_vPosition.x = (float)rand() / 102.4f;
							this->m_vPosition.y = (float)rand() / 102.4f;
							this->m_vPosition.z = (float)rand() / 102.4f;
						
						}
	VSINLINE VSFLOAT	GetComparableFloat(void) const { 
							return VSFLOAT(this->m_vPosition.GetLengthSquared()); 
						}
};



//#define VS_RADIX_LOOP_OPTIMIZATION


#define ELEMENT_COUNT 20000
DASDING *m_array = NULL;
DASDING *m_out = NULL;

#pragma intrinsic(memset)

// ================================================================================================
// Main radix sort
// ================================================================================================
void VSFASTCALL WideFloatRadixSort(const unsigned long elements)
{
	unsigned long i;
#ifdef VS_RADIX_LOOP_OPTIMIZATION
	unsigned long c;
#endif

	DASDING *sort = (DASDING*)m_out;
	DASDING *array = (DASDING*)m_array;

	// 3 histograms on the stack:
	const unsigned long kHist = 2048;
	unsigned long b0[6144];
	unsigned long *b1 = b0 + kHist;
	unsigned long *b2 = b1 + kHist;

	memset(b0, 0, 24576);

	// 1.  parallel histogramming pass
	//
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	for (i = 0; i < elements; ++i) {
#else
	c = elements;
	do {
		i = elements - c;
#endif
		pf(array);
		unsigned long fi = array[i].GetComparableFloat().GetFlipped();
		++b0[_0(fi)];
		++b1[_1(fi)];
		++b2[_2(fi)];
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	}
#else
	} while(--c>0);
#endif
	
	// 2.  Sum the histograms -- each histogram entry records the number of values preceding itself.
	{
		unsigned long sum0 = 0, sum1 = 0, sum2 = 0;
#ifndef VS_RADIX_LOOP_OPTIMIZATION
		for (i = 0; i < kHist; ++i) {
#else //VS_RADIX_LOOP_OPTIMIZATION
		c = kHist;
		do {
			i = kHist - c;
#endif //VS_RADIX_LOOP_OPTIMIZATION
			unsigned long tsum;

			tsum = b0[i] + sum0;
			b0[i] = sum0 - 1;
			sum0 = tsum;

			tsum = b1[i] + sum1;
			b1[i] = sum1 - 1;
			sum1 = tsum;

			tsum = b2[i] + sum2;
			b2[i] = sum2 - 1;
			sum2 = tsum;

#ifndef VS_RADIX_LOOP_OPTIMIZATION
		}
#else //VS_RADIX_LOOP_OPTIMIZATION
		} while(--c>0);
#endif //VS_RADIX_LOOP_OPTIMIZATION
	}

	// byte 0: floatflip entire value, read/write histogram, write out flipped
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	for (i = 0; i < elements; ++i) {
#else
	c = elements;
	do {
		i = elements - c;
#endif
		pf(array);	//UNDONE: Prefetch-Performance prüfen (byte 0 radix)
		unsigned long fi = array[i].GetComparableFloat().GetFlipped();
		unsigned long pos = _0(fi);
		pf2(array);
		sort[++b0[pos]] = *(DASDING*)&array[i];
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	}
#else
	} while(--c>0);
#endif

	// byte 1: read/write histogram, copy
	//   sorted -> array
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	for (i = 0; i < elements; ++i) {
#else
	c = elements;
	do {
		i = elements - c;
#endif
		pf(sort);	//UNDONE: Prefetch-Performance prüfen (byte 1 radix)
		unsigned long si = sort[i].GetComparableFloat().GetFlipped();
		unsigned long pos = _1(si);
		pf2(sort);
		array[++b1[pos]] = *(DASDING*)&sort[i];
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	}
#else
	} while(--c>0);
#endif

	// byte 2: read/write histogram, copy & flip out
	//   array -> sorted
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	for (i = 0; i < elements; ++i) {
#else
	c = elements;
	do {
		i = elements - c;
#endif
		pf(array);	//UNDONE: Prefetch-Performance prüfen (byte 2 radix)
		unsigned long ai = array[i].GetComparableFloat().GetFlipped();
		unsigned long pos = _2(ai);
		pf2(array);
		sort[++b2[pos]] = *(DASDING*)&array[i];
#ifndef VS_RADIX_LOOP_OPTIMIZATION
	}
#else
	} while(--c>0);
#endif
}

/********************************************************************************************/



typedef class KOMPASS {
private:
	LPDIRECT3DTEXTURE9				m_pTexRing;
	LPDIRECT3DTEXTURE9				m_pTexArrow;
	static unsigned int				m_iInitialized;
	static LPDIRECT3DVERTEXBUFFER9	m_pVBKompass;
	PIPED3D2						*m_pPipe;
	VECTOR2							m_vPosition;

private:
	void							CreateVB();
	void							LoadTextures();
public:
									KOMPASS(PIPED3D2 &Pipe);
									~KOMPASS();
	void							Release();
	void							SetPosition(const float in_x, const float in_y);
	void							Render(const float in_fAngle = 0.f);
	void							Render(const float in_x, const float in_y, const float in_fAngle = 0.f);

} KOMPASS;

unsigned int				KOMPASS::m_iInitialized = 0;
LPDIRECT3DVERTEXBUFFER9		KOMPASS::m_pVBKompass = NULL;

void KOMPASS::CreateVB() {
	HRESULT retval;
	retval = m_pPipe->GetDirect3DDevice()->CreateVertexBuffer(sizeof(VSD3DTLVERTEX)*4, D3DUSAGE_WRITEONLY, VS_D3DFVF_TLVERTEX, D3DPOOL_DEFAULT, &m_pVBKompass, NULL);
	if(FAILED(retval)) {
		dprintf("Compass creation: Erzeugung des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return;
	}

	VSD3DTLVERTEX verts[4];
	
	//float rhw=1.0f/(in_zDist*990.0f+10.0f);
	float rhw		= 0.001f;
	float in_zDist	= 0.f;
	float left		= -64.f;
	float top		= -64.f;
	float right		= 64.f;
	float bottom	= 64.f;
	D3DCOLOR in_Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	verts[0]=VSD3DTLVERTEX(D3DXVECTOR3(left,  top,	in_zDist), rhw, in_Color, 0.0f, 0.0f); 
	verts[1]=VSD3DTLVERTEX(D3DXVECTOR3(right, top,    in_zDist), rhw, in_Color, 1.0f, 0.0f);
	verts[2]=VSD3DTLVERTEX(D3DXVECTOR3(right, bottom, in_zDist), rhw, in_Color, 1.0f, 1.0f); 
	verts[3]=VSD3DTLVERTEX(D3DXVECTOR3(left,  bottom, in_zDist), rhw, in_Color, 0.0f, 1.0f);	

	// Den Vertexpuffer mit Daten füllen
	void* ptr = NULL;
	retval = m_pVBKompass->Lock(0, sizeof(VSD3DTLVERTEX)*4, (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("Compass creation: Lock des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return;
	}
	memcpy(ptr, verts, sizeof(VSD3DTLVERTEX)*4);
	m_pVBKompass->Unlock();

}

void KOMPASS::LoadTextures() {
	CreateTexture(m_pPipe->GetDirect3DDevice(), "textures\\comp_arr.dds", &m_pTexArrow, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(0, 0, 0));
	CreateTexture(m_pPipe->GetDirect3DDevice(), "textures\\comp_rng.dds", &m_pTexRing, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(0, 0, 0));
}

void KOMPASS::SetPosition(const float in_x, const float in_y){
	m_vPosition.x = in_x;
	m_vPosition.y = in_y;
}

KOMPASS::KOMPASS(PIPED3D2 &Pipe) {
	m_pPipe = &Pipe;
	m_pTexRing = NULL;
	m_pTexArrow = NULL;
	LoadTextures();
	m_vPosition.Assign(74.f, 74.f);
	if(m_iInitialized == 0) {
		CreateVB();
		m_iInitialized = 1;
	}
}

void KOMPASS::Release() {
	SAFE_RELEASE(m_pTexRing);
	SAFE_RELEASE(m_pTexArrow);
	if(m_iInitialized != 0) {
		SAFE_RELEASE(m_pVBKompass);
		m_iInitialized = 0;
	}
}

KOMPASS::~KOMPASS() {
	this->Release();
}

void KOMPASS::Render(const float in_fAngle) {
	Render(m_vPosition.x, m_vPosition.y, in_fAngle);
}

void KOMPASS::Render(const float in_x, const float in_y, const float in_fAngle) {
	MATRIX4 matRot;
	//matRot.Identity();

	VSD3DTLVERTEX verts[8];
	
	//float rhw=1.0f/(in_zDist*990.0f+10.0f);
	float rhw		= 0.001f;
	float in_zDist	= 0.f;

	float left		= -64.f;
	float top		= -64.f;
	float right		= 64.f;
	float bottom	= 64.f;

	VECTOR3 v1(left, top, in_zDist);
	VECTOR3 v2(right, top, in_zDist);
	VECTOR3 v3(right, bottom, in_zDist);
	VECTOR3 v4(left, bottom, in_zDist);

	matRot.RotateZ(-in_fAngle);

	v1 *= matRot;
	v2 *= matRot;
	v3 *= matRot;
	v4 *= matRot;

	v1.x += in_x;	v2.x += in_x;
	v1.y += in_y;	v2.y += in_y;
	v3.x += in_x;	v4.x += in_x;
	v3.y += in_y;	v4.y += in_y;

	D3DCOLOR in_Color = D3DCOLOR_ARGB(150, 255, 255, 255);
	verts[0]=VSD3DTLVERTEX((D3DXVECTOR3)v1, rhw, in_Color, 0.0f, 0.0f); 
	verts[1]=VSD3DTLVERTEX((D3DXVECTOR3)v2, rhw, in_Color, 1.0f, 0.0f);
	verts[2]=VSD3DTLVERTEX((D3DXVECTOR3)v3, rhw, in_Color, 1.0f, 1.0f); 
	verts[3]=VSD3DTLVERTEX((D3DXVECTOR3)v4, rhw, in_Color, 0.0f, 1.0f);	

	left		+= in_x;
	top			+= in_y;
	right		+= in_x;
	bottom		+= in_y;

	verts[4]=VSD3DTLVERTEX(D3DXVECTOR3(left,  top,		in_zDist), rhw, in_Color, 0.0f, 0.0f); 
	verts[5]=VSD3DTLVERTEX(D3DXVECTOR3(right, top,		in_zDist), rhw, in_Color, 1.0f, 0.0f);
	verts[6]=VSD3DTLVERTEX(D3DXVECTOR3(right, bottom,	in_zDist), rhw, in_Color, 1.0f, 1.0f); 
	verts[7]=VSD3DTLVERTEX(D3DXVECTOR3(left,  bottom,	in_zDist), rhw, in_Color, 0.0f, 1.0f);	

	/*
		m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 
		m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pPipe->GetDirect3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		*/
		m_pPipe->SelectAlphaBlendEnabled();
		m_pPipe->SelectBlendSrcAlpha();

	unsigned long int iSize = sizeof(VSD3DTLVERTEX);

	m_pPipe->GetDirect3DDevice()->SetFVF(VS_D3DFVF_TLVERTEX);
	m_pPipe->GetDirect3DDevice()->SetStreamSource(0, this->m_pVBKompass, 0, iSize);
	//m_pPipe->GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

	m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_pTexRing);
	m_pPipe->GetDirect3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, verts, iSize);
	
	m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_pTexArrow);
	m_pPipe->GetDirect3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &verts[4], iSize);

		m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}





int APIENTRY WinMain(HINSTANCE whInstance, HINSTANCE whPrevInstance, LPSTR wlpCmdLine, int wpShow) {


/*
	POLYGON3 poly(7);

	poly.pList[0] = VECTOR3(3.f, 9.f, 0.f);
	poly.pList[1] = VECTOR3(7.f, 7.f, 0.f);
	poly.pList[2] = VECTOR3(8.f, 4.f, 0.f);
	poly.pList[3] = VECTOR3(6.f, 0.f, 0.f);
	poly.pList[4] = VECTOR3(3.f, 0.f, 0.f);
	poly.pList[5] = VECTOR3(0.f, 3.f, 0.f);
	poly.pList[6] = VECTOR3(0.f, 6.f, 0.f);
	poly.m_iElementCount = 7;

	unsigned int i;

	dprintf("Vor der Optimierung:\n");
	for(i=0; i<poly.m_iElementCount; i++) {
		dprintf("poly.List[%d] =\t%01.3f\t%01.3f\t%01.3f\n", i, poly.pList[i].x, poly.pList[i].y, poly.pList[i].z);
	}

	poly.Optimize();

	dprintf("\nNach der Optimierung:\n");
	for(i=0; i<poly.m_iElementCount; i++) {
		dprintf("poly.List[%d] =\t%01.3f\t%01.3f\t%01.3f\n", i, poly.pList[i].x, poly.pList[i].y, poly.pList[i].z);
	}


	TRIANGLE3	*pTris = new TRIANGLE3[10];
	memset(pTris, 0, sizeof(TRIANGLE3)*10);

	poly.Triangulate(pTris);

	dprintf("\nNach der Triangulierung:\n");
	//unsigned int i;
	for(i=0; i<poly.TriangulationCost(); i++)
		dprintf("%d -\t%1.3f\t%1.3f\t%1.3f\t\t%1.3f\t%1.3f\t%1.3f\t\t%1.3f\t%1.3f\t%1.3f\n", i, pTris[i].v0.x, pTris[i].v0.y, pTris[i].v0.z, pTris[i].v1.x, pTris[i].v1.y, pTris[i].v1.z, pTris[i].v2.x, pTris[i].v2.y, pTris[i].v2.z);
	
	delete[] pTris;
	//return 0;
*/

	AABBOX3 Box(VECTOR3(1.f, 1.f, 1.f), 2.f);
	AABSPHERE3 Sphere;

	Box.Convert(Sphere);
	//dprintf("--> %1.3f\n", Sphere.m_radius);


	//return 0;

	ApplicationStart(VSCOPE_VER_BUILD);

	char Title[255];
	sprintf(Title, "v-scope engine (build %da)\0", VSCOPE_VER_BUILD);
	WINDOW			Win(Title, 800, 600, whInstance, (WNDPROC)WindowProc, TRUE);
	PIPED3D2		Pipe(Win, 800, 600, D3DFMT_A8R8G8B8, 1, TRUE, D3DMULTISAMPLE_NONE, D3DFMT_D24S8);
	ENGINELOGO		Logo(Pipe);

	CAMERA2			Kamera(Pipe);//, Kamera2(Pipe);
	VIEWCONE		Viewcone(Pipe);


	KOMPASS			Kompass(Pipe);



	if(FAILED(DirectInput8Create(whInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpDI8, NULL)))
		return -19;

	if(FAILED(lpDI8->CreateDevice(GUID_SysKeyboard, &lpKeyboard, NULL)))
		return -20;

	if(FAILED(lpKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		return -21;

	if(FAILED(lpKeyboard->SetCooperativeLevel(Win, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return -22;

	if(FAILED(lpKeyboard->Acquire()))
		return -23;

	Initialize();




	DLLIST List;


	LPDIRECT3DTEXTURE9 pFloor = NULL;
	CreateTexture(Pipe, "textures\\new-floor.dds", &pFloor, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 pCeiling = NULL;
	CreateTexture(Pipe, "textures\\new-ceiling.dds", &pCeiling, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 pWall = NULL;
	CreateTexture(Pipe, "textures\\new-wall.dds", &pWall, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(0, 0, 0));
	
	unsigned int iTriCount = CreateScene(&Pipe);

	MATRIX4 World;
	World.Identity();

	float fWinkel = 0;
	

	Kamera.TranslateToWorldXYZ(26.f, 1.5f, -9.f);
	Kamera.SetViewMatrix();


	SPHERE dome;
	dome.Create(Pipe, 64, 32, 3.f, 1.f);


	AABBOX3 domeBox;
	domeBox.Create(VECTOR3(0.f, 0.f, 0.f), 3.f);
	

/*	
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(D3DMATERIAL9));
	mat.Ambient.a = 1.f;
	mat.Ambient.r = 1.f;
	mat.Ambient.g = 1.f;
	mat.Ambient.b = 1.f;
	mat.Diffuse.a = 1.f;
	mat.Diffuse.r = 1.f;
	mat.Diffuse.g = 1.f;
	mat.Diffuse.b = 1.f;
*/
	MATERIAL mat;
	mat.SetAmbient(COLOR4(1.f, 1.f, 1.f, 1.f));
	mat.SetDiffuse(COLOR4(1.f, 1.f, 1.f, 1.f));

	
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Diffuse.a = 1.f;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	light.Specular.a = 1.f;
	light.Specular.r = 1.f;
	light.Specular.g = 1.f;
	light.Specular.b = 1.f;

	light.Phi = 1.f;
	light.Theta = 1.f;
	light.Type = D3DLIGHT_POINT;
	light.Range = 10.f;
	light.Falloff = 1.f;
	light.Attenuation0 = 1.f;


	TIMER t;
	unsigned int iCount = 0;

	while(g_bRunning) {
		do {
			Win.CheckMessageQeue();
			DIGetKeys(lpKeyboard);
		} while(g_bPaused);

		SpielerBewegen(Kamera);
		Kamera.SetViewMatrix();

		//fWinkel+= 0.01f;
		//fWinkel+= DEG2RAD(10);
		//if(fWinkel>PIx2) fWinkel = 0.f;

		World.Identity();
		Pipe.SetWorldMatrix(&World);

		Pipe.BeginScene();
		Pipe.Clear(D3DCOLOR_XRGB(200, 200, 200));


		//Win.SetTitle("%1.3f, %1.3f, %1.3f", Kamera.GetObjectDirectionVec().x, Kamera.GetObjectDirectionVec().y, Kamera.GetObjectDirectionVec().z);

		Kamera.GetObjectDirectionVec((VECTOR3*)&light.Direction);
		Kamera.GetPosition((VECTOR3*)&light.Position);

		Win.SetTitle("%1.3f, %1.3f, %1.3f - %1.3f, %1.3f, %1.3f - %1.3f, %1.3f, %1.3f", light.Direction.x, light.Direction.y, light.Direction.z, light.Position.x, light.Position.y, light.Position.z, Kamera.GetPosition().x, Kamera.GetPosition().y, Kamera.GetPosition().z);

		/*light.Position.x = light.Position.x + light.Direction.x * 2.f;
		light.Position.y = light.Position.y + light.Direction.y * 2.f;
		light.Position.z = light.Position.z + light.Direction.z * 2.f;*/

		//Pipe.GetDirect3DDevice()->SetMaterial(&mat);
		Pipe.SetMaterial(mat);

		Pipe.GetDirect3DDevice()->SetLight(1, &light);

		Pipe.SelectLightingEnabled(true);
		Pipe.SelectLightEnabled(1, true);
		Pipe.SetAmbientColor(0x00202020);
		Pipe.SelectNormalizeNormals(true);

		Viewcone.Update();
		if ( Viewcone.GetLocation(domeBox) != LOC_OUTSIDE ) {
			dome.Render();
		}

		Pipe.GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		Pipe.GetDirect3DDevice()->SetTexture(0, pWall);
		RenderSceneWall(Pipe);
		Pipe.GetDirect3DDevice()->SetTexture(0, pFloor);
		RenderSceneFloor(Pipe);
		Pipe.GetDirect3DDevice()->SetTexture(0, pCeiling);
		RenderSceneCeiling(Pipe);

		Pipe.GetDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		RenderSceneNormals(Pipe);

		Kompass.Render(800-74, 74, -Kamera.GetObjectRotationY());
		Logo.Render(Pipe, 192);
		Pipe.EndScene();

		Pipe.Present();

		if((++iCount) == 50) {
			Win.SetTitle("v-scope engine (build %da) - %1.2f FPS\0", VSCOPE_VER_BUILD, 50.f / t.GetElapsedTime());
			iCount = 0;
			t.Hit();
		}


	}

	dome.Release();

	SAFE_RELEASE(pFloor);
	SAFE_RELEASE(pCeiling);
	SAFE_RELEASE(pWall);

	Logo.Release();
	Kompass.Release();

	DeleteScene();


	Pipe.Release();
	Win.Release();


	delete[] m_out;
	delete[] m_array;

	lpKeyboard->Unacquire();
	lpKeyboard->Release();
	lpDI8->Release();


	return ApplicationEnd();
}