#pragma once
#include <vscope.h>

#define SCENE_ITEMCOUNT 906
VSD3DVERTEX_DIFFUSE m_pSceneVertices[SCENE_ITEMCOUNT];
VSD3DVERTEX_DIFFUSE m_pSceneNormals[SCENE_ITEMCOUNT];
//void Assign(const VECTOR3& v, VECTOR3 &_vN, D3DCOLOR &color, float _tu=0.f, float _tv=0.f);

unsigned int iNormalCounter;

LPDIRECT3DVERTEXBUFFER9		g_VerticesScene;
LPDIRECT3DVERTEXBUFFER9		g_VerticesNormals;
LPDIRECT3DINDEXBUFFER9		g_IndicesScene;

#define FLOOR_Y			0.f
#define CEILING_Y		3.f
#define GANG_CEILING_Y	2.5f
#define PODEST_Y		1.25f
//#define NORMAL_COLOR		COLOR4(0.f, 1.f, 1.f, 1.f)
#define NORMAL_COLOR		COLOR4(0.f, 0.f, 0.f, 0.f)
#define CEILING_COLOR		COLOR4(1.f, 0.75f, 0.75f, 0.9f)
#define FLOOR_COLOR		COLOR4(1.f, 0.75f, 0.75f, 0.75f)
#define WALL_COLOR		COLOR4(1.f, 0.9f, 0.75f, 0.75f)
#define NORMAL_UP		vNormal
#define NORMAL_DOWN		vNormalDown
VECTOR3	vNormal(0.f, 1.f, 0.f);
VECTOR3	vNormalDown(0.f, -1.f, 0.f);

MATRIX4 Rotate90;

#define NORMAL_SOUTH		vNormalSouth
#define NORMAL_NORTH		vNormalNorth
#define NORMAL_EAST			vNormalEast
#define NORMAL_WEST			vNormalWest
VECTOR3	vNormalNorth(0.f, 0.f, 1.f);
VECTOR3	vNormalSouth(0.f, 0.f, -1.f);
VECTOR3	vNormalEast(1.f, 0.f, 0.f);
VECTOR3	vNormalWest(-1.f, 0.f, 0.f);
#define NORMAL_SOUTHEAST	vNormalSouthEast
#define NORMAL_NORTHWEST	vNormalNorthWest
#define NORMAL_NORTHEAST	vNormalNorthEast
VECTOR3	vNormalNorthWest(-0.7071067811865475244008443621052f, 0.f, 0.7071067811865475244008443621052f);
VECTOR3	vNormalSouthEast(0.7071067811865475244008443621052f, 0.f, -0.7071067811865475244008443621052f);
VECTOR3	vNormalNorthEast(0.7071067811865475244008443621052f, 0.f, 0.7071067811865475244008443621052f);


unsigned int CreateQuadXZ(const unsigned int in_iStartIndex, const VECTOR3 &in_vTopLeft, const VECTOR3 &in_vTopRight, const VECTOR3 &in_vBottomLeft, const VECTOR3 &in_vBottomRight, VECTOR3 &in_vNormal = NORMAL_UP, COLOR4 &in_cColor = FLOOR_COLOR) {
	VECTOR3 vNormal1 = (in_vTopRight-in_vTopLeft) CROSS (in_vBottomLeft-in_vTopLeft);
	VECTOR3 vNormal2 = (in_vBottomLeft-in_vBottomRight) CROSS (in_vTopRight-in_vBottomRight);
	vNormal1.Normalize();
	vNormal2.Normalize();
	vNormal1 *= 0.2f;
	vNormal2 *= 0.2f;

	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vTopLeft, in_vTopRight, in_vBottomLeft, VAL1d3, VAL1d3),					vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vTopLeft, in_vTopRight, in_vBottomLeft, VAL1d3, VAL1d3) + vNormal1,			vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vBottomLeft, in_vTopRight, in_vBottomRight, VAL1d3, VAL1d3),				vNormal1, NORMAL_COLOR,	in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vBottomLeft, in_vTopRight, in_vBottomRight, VAL1d3, VAL1d3) + vNormal2,		vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);

	m_pSceneVertices[in_iStartIndex+0].Assign( VECTOR3( in_vTopLeft.x,		in_vTopLeft.y,		in_vTopLeft.z),		vNormal1, in_cColor,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneVertices[in_iStartIndex+1].Assign( VECTOR3( in_vTopRight.x,		in_vTopRight.y,		in_vTopRight.z),	vNormal1, in_cColor,		in_vTopRight.x,		in_vTopRight.z		);
	m_pSceneVertices[in_iStartIndex+2].Assign( VECTOR3( in_vBottomLeft.x,	in_vBottomLeft.y,	in_vBottomLeft.z),	vNormal1, in_cColor,		in_vBottomLeft.x,	in_vBottomLeft.z	);
	m_pSceneVertices[in_iStartIndex+3].Assign( VECTOR3( in_vTopRight.x,		in_vTopRight.y,		in_vTopRight.z),	vNormal2, in_cColor,		in_vTopRight.x,		in_vTopRight.z		);
	m_pSceneVertices[in_iStartIndex+4].Assign( VECTOR3( in_vBottomRight.x,	in_vBottomRight.y,	in_vBottomRight.z), vNormal2, in_cColor,		in_vBottomRight.x,	in_vBottomRight.z	);
	m_pSceneVertices[in_iStartIndex+5].Assign( VECTOR3( in_vBottomLeft.x,	in_vBottomLeft.y,	in_vBottomLeft.z),	vNormal2, in_cColor,		in_vBottomLeft.x,	in_vBottomLeft.z	);
	return in_iStartIndex+6;
}

unsigned int CreateQuadXY(const unsigned int in_iStartIndex, const VECTOR3 &in_vTopLeft, const VECTOR3 &in_vTopRight, const VECTOR3 &in_vBottomLeft, const VECTOR3 &in_vBottomRight, VECTOR3 &in_vNormal = NORMAL_UP, COLOR4 &in_cColor = FLOOR_COLOR) {
	VECTOR3 vNormal1 = (in_vTopRight-in_vTopLeft) CROSS (in_vBottomLeft-in_vTopLeft);
	VECTOR3 vNormal2 = (in_vBottomLeft-in_vBottomRight) CROSS (in_vTopRight-in_vBottomRight);
	vNormal1.Normalize();
	vNormal2.Normalize();
	vNormal1 *= 0.2f;
	vNormal2 *= 0.2f;

	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vTopLeft, in_vTopRight, in_vBottomLeft, VAL1d3, VAL1d3),					vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vTopLeft, in_vTopRight, in_vBottomLeft, VAL1d3, VAL1d3) + vNormal1,			vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vBottomLeft, in_vTopRight, in_vBottomRight, VAL1d3, VAL1d3),				vNormal1, NORMAL_COLOR,	in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vBottomLeft, in_vTopRight, in_vBottomRight, VAL1d3, VAL1d3) + vNormal2,		vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);

	m_pSceneVertices[in_iStartIndex+0].Assign( VECTOR3( in_vTopLeft.x,		in_vTopLeft.y,		in_vTopLeft.z),		vNormal1, in_cColor,		in_vTopLeft.x,		in_vTopLeft.y		);
	m_pSceneVertices[in_iStartIndex+1].Assign( VECTOR3( in_vTopRight.x,		in_vTopRight.y,		in_vTopRight.z),	vNormal1, in_cColor,		in_vTopRight.x,		in_vTopRight.y		);
	m_pSceneVertices[in_iStartIndex+2].Assign( VECTOR3( in_vBottomLeft.x,	in_vBottomLeft.y,	in_vBottomLeft.z),	vNormal1, in_cColor,		in_vBottomLeft.x,	in_vBottomLeft.y	);
	m_pSceneVertices[in_iStartIndex+3].Assign( VECTOR3( in_vTopRight.x,		in_vTopRight.y,		in_vTopRight.z),	vNormal2, in_cColor,		in_vTopRight.x,		in_vTopRight.y		);
	m_pSceneVertices[in_iStartIndex+4].Assign( VECTOR3( in_vBottomRight.x,	in_vBottomRight.y,	in_vBottomRight.z), vNormal2, in_cColor,		in_vBottomRight.x,	in_vBottomRight.y	);
	m_pSceneVertices[in_iStartIndex+5].Assign( VECTOR3( in_vBottomLeft.x,	in_vBottomLeft.y,	in_vBottomLeft.z),	vNormal2, in_cColor,		in_vBottomLeft.x,	in_vBottomLeft.y	);
	return in_iStartIndex+6;
}

unsigned int CreateQuadYZ(const unsigned int in_iStartIndex, const VECTOR3 &in_vTopLeft, const VECTOR3 &in_vTopRight, const VECTOR3 &in_vBottomLeft, const VECTOR3 &in_vBottomRight, VECTOR3 &in_vNormal = NORMAL_UP, COLOR4 &in_cColor = FLOOR_COLOR) {
	VECTOR3 vNormal1 = (in_vTopRight-in_vTopLeft) CROSS (in_vBottomLeft-in_vTopLeft);
	VECTOR3 vNormal2 = (in_vBottomLeft-in_vBottomRight) CROSS (in_vTopRight-in_vBottomRight);
	vNormal1.Normalize();
	vNormal2.Normalize();
	vNormal1 *= 0.2f;
	vNormal2 *= 0.2f;

	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vTopLeft, in_vTopRight, in_vBottomLeft, VAL1d3, VAL1d3),					vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vTopLeft, in_vTopRight, in_vBottomLeft, VAL1d3, VAL1d3) + vNormal1,			vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vBottomLeft, in_vTopRight, in_vBottomRight, VAL1d3, VAL1d3),				vNormal1, NORMAL_COLOR,	in_vTopLeft.x,		in_vTopLeft.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vBottomLeft, in_vTopRight, in_vBottomRight, VAL1d3, VAL1d3) + vNormal2,		vNormal1, NORMAL_COLOR,		in_vTopLeft.x,		in_vTopLeft.z		);

	m_pSceneVertices[in_iStartIndex+0].Assign( VECTOR3( in_vTopLeft.x,		in_vTopLeft.y,		in_vTopLeft.z),		vNormal1, in_cColor,		in_vTopLeft.z,		in_vTopLeft.y		);
	m_pSceneVertices[in_iStartIndex+1].Assign( VECTOR3( in_vTopRight.x,		in_vTopRight.y,		in_vTopRight.z),	vNormal1, in_cColor,		in_vTopRight.z,		in_vTopRight.y		);
	m_pSceneVertices[in_iStartIndex+2].Assign( VECTOR3( in_vBottomLeft.x,	in_vBottomLeft.y,	in_vBottomLeft.z),	vNormal1, in_cColor,		in_vBottomLeft.z,	in_vBottomLeft.y	);
	m_pSceneVertices[in_iStartIndex+3].Assign( VECTOR3( in_vTopRight.x,		in_vTopRight.y,		in_vTopRight.z),	vNormal2, in_cColor,		in_vTopRight.z,		in_vTopRight.y		);
	m_pSceneVertices[in_iStartIndex+4].Assign( VECTOR3( in_vBottomRight.x,	in_vBottomRight.y,	in_vBottomRight.z), vNormal2, in_cColor,		in_vBottomRight.z,	in_vBottomRight.y	);
	m_pSceneVertices[in_iStartIndex+5].Assign( VECTOR3( in_vBottomLeft.x,	in_vBottomLeft.y,	in_vBottomLeft.z),	vNormal2, in_cColor,		in_vBottomLeft.z,	in_vBottomLeft.y	);
	return in_iStartIndex+6;
}

unsigned int CreateTriXZ(const unsigned int in_iStartIndex, const VECTOR3 &in_vTop, const VECTOR3 &in_vRight, const VECTOR3 &in_vLeft, VECTOR3 &in_vNormal = NORMAL_UP, COLOR4 &in_cColor = FLOOR_COLOR) {
	VECTOR3 vNormal1 = (in_vLeft-in_vTop) CROSS (in_vRight-in_vTop);
	vNormal1.Normalize();
	vNormal1 *= 0.2f;

	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vLeft, in_vTop, in_vRight, VAL1d3, VAL1d3),					vNormal1, NORMAL_COLOR,		in_vTop.x,		in_vTop.z		);
	m_pSceneNormals[iNormalCounter++].Assign( GetBaryCentric(in_vLeft, in_vTop, in_vRight, VAL1d3, VAL1d3) + vNormal1,			vNormal1, NORMAL_COLOR,		in_vLeft.x,		in_vLeft.z		);

	m_pSceneVertices[in_iStartIndex+0].Assign( VECTOR3( in_vTop.x,	in_vTop.y,		in_vTop.z),		vNormal1, in_cColor,		in_vTop.x,		in_vTop.z		);
	m_pSceneVertices[in_iStartIndex+1].Assign( VECTOR3( in_vRight.x, in_vRight.y,		in_vRight.z),	vNormal1, in_cColor,		in_vRight.x,		in_vRight.z		);
	m_pSceneVertices[in_iStartIndex+2].Assign( VECTOR3( in_vLeft.x,	in_vLeft.y,	in_vLeft.z),	vNormal1, in_cColor,		in_vLeft.x,	in_vLeft.z	);
	return in_iStartIndex+3;
}

unsigned int CreateScene(PIPED3D2 *m_pPipe) {
	iNormalCounter = 0;
	
	Rotate90.Identity();

	vNormal				*= Rotate90;
	vNormalDown			*= Rotate90;

	vNormalNorth		*= Rotate90;
	vNormalSouth		*= Rotate90;
	vNormalEast			*= Rotate90;
	vNormalWest			*= Rotate90;
	vNormalSouthEast	*= Rotate90;
	vNormalNorthWest	*= Rotate90;
	vNormalNorthEast	*= Rotate90;

	unsigned int iIndex = 0;
	// Bodenfläche --------------------------------------------------------------------------------------------------------------------------------

	// Beginnend mit Raum 1
	iIndex = CreateQuadXZ(iIndex, VECTOR3(0.f, FLOOR_Y, -1.f), VECTOR3(2.f, FLOOR_Y, -1.f), VECTOR3(0.f, FLOOR_Y, -4.f), VECTOR3(2.f, FLOOR_Y, -4.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(2.f, FLOOR_Y, -1.f), VECTOR3(4.f, FLOOR_Y, -1.f), VECTOR3(2.f, FLOOR_Y, -4.f), VECTOR3(4.f, FLOOR_Y, -4.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(4.f, FLOOR_Y, -1.f), VECTOR3(7.f, FLOOR_Y, -1.f), VECTOR3(4.f, FLOOR_Y, -4.f), VECTOR3(7.f, FLOOR_Y, -4.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(0.f, FLOOR_Y, -4.f), VECTOR3(2.f, FLOOR_Y, -4.f), VECTOR3(0.f, FLOOR_Y, -6.f), VECTOR3(2.f, FLOOR_Y, -6.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(2.f, FLOOR_Y, -4.f), VECTOR3(4.f, FLOOR_Y, -4.f), VECTOR3(2.f, FLOOR_Y, -6.f), VECTOR3(4.f, FLOOR_Y, -6.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(4.f, FLOOR_Y, -4.f), VECTOR3(7.f, FLOOR_Y, -4.f), VECTOR3(4.f, FLOOR_Y, -6.f), VECTOR3(7.f, FLOOR_Y, -6.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(0.f, FLOOR_Y, -6.f), VECTOR3(2.f, FLOOR_Y, -6.f), VECTOR3(0.f, FLOOR_Y, -8.f), VECTOR3(2.f, FLOOR_Y, -8.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(2.f, FLOOR_Y, -6.f), VECTOR3(4.f, FLOOR_Y, -6.f), VECTOR3(2.f, FLOOR_Y, -8.f), VECTOR3(4.f, FLOOR_Y, -8.f), NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(4.f, FLOOR_Y, -6.f), VECTOR3(7.f, FLOOR_Y, -6.f), VECTOR3(4.f, FLOOR_Y, -8.f), VECTOR3(7.f, FLOOR_Y, -8.f), NORMAL_UP, FLOOR_COLOR);
	// ... Raum 3
	iIndex = CreateQuadXZ(iIndex, VECTOR3(6.f, FLOOR_Y, -14.f),		VECTOR3(9.f, FLOOR_Y, -14.f),	VECTOR3(6.f, FLOOR_Y, -16.f),	VECTOR3(9.f, FLOOR_Y, -16.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -14.f),		VECTOR3(11.f, FLOOR_Y, -14.f),	VECTOR3(9.f, FLOOR_Y, -16.f),	VECTOR3(11.f, FLOOR_Y, -16.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, FLOOR_Y, -14.f),	VECTOR3(14.f, FLOOR_Y, -14.f),	VECTOR3(11.f, FLOOR_Y, -16.f),	VECTOR3(14.f, FLOOR_Y, -16.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(6.f, FLOOR_Y, -16.f),		VECTOR3(9.f, FLOOR_Y, -16.f),	VECTOR3(6.f, FLOOR_Y, -18.f),	VECTOR3(9.f, FLOOR_Y, -18.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -16.f),		VECTOR3(11.f, FLOOR_Y, -16.f),	VECTOR3(9.f, FLOOR_Y, -18.f),	VECTOR3(11.f, FLOOR_Y, -18.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, FLOOR_Y, -16.f),	VECTOR3(14.f, FLOOR_Y, -16.f),	VECTOR3(11.f, FLOOR_Y, -18.f),	VECTOR3(14.f, FLOOR_Y, -18.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(6.f, PODEST_Y, -18.f),	VECTOR3(9.f, PODEST_Y, -18.f),	VECTOR3(6.f, PODEST_Y, -21.f),	VECTOR3(9.f, PODEST_Y, -21.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, PODEST_Y, -18.f),	VECTOR3(11.f, PODEST_Y, -18.f),	VECTOR3(9.f, PODEST_Y, -21.f),	VECTOR3(11.f, PODEST_Y, -21.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, PODEST_Y, -18.f),	VECTOR3(14.f, PODEST_Y, -18.f),	VECTOR3(11.f, PODEST_Y, -21.f),	VECTOR3(14.f, PODEST_Y, -21.f),	NORMAL_UP, FLOOR_COLOR);
	// ... Raum 2
	iIndex = CreateQuadXZ(iIndex, VECTOR3(18.f, FLOOR_Y, 0.f),	VECTOR3(20.f, FLOOR_Y, 0.f),	VECTOR3(18.f, FLOOR_Y, -2.f),	VECTOR3(20.f, FLOOR_Y, -2.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(20.f, FLOOR_Y, 0.f),	VECTOR3(23.f, FLOOR_Y, 0.f),	VECTOR3(20.f, FLOOR_Y, -2.f),	VECTOR3(23.f, FLOOR_Y, -2.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(23.f, FLOOR_Y, 0.f),	VECTOR3(26.f, FLOOR_Y, 0.f),	VECTOR3(23.f, FLOOR_Y, -2.f),	VECTOR3(26.f, FLOOR_Y, -2.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(20.f, FLOOR_Y, -2.f),	VECTOR3(23.f, FLOOR_Y, -2.f),	VECTOR3(20.f, FLOOR_Y, -6.f),	VECTOR3(23.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);	
	iIndex = CreateQuadXZ(iIndex, VECTOR3(23.f, FLOOR_Y, -2.f),	VECTOR3(26.f, FLOOR_Y, -2.f),	VECTOR3(23.f, FLOOR_Y, -6.f),	VECTOR3(26.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(20.f, FLOOR_Y, -6.f),	VECTOR3(23.f, FLOOR_Y, -6.f),	VECTOR3(20.f, FLOOR_Y, -10.f),	VECTOR3(23.f, FLOOR_Y, -10.f),	NORMAL_UP, FLOOR_COLOR);	
	iIndex = CreateQuadXZ(iIndex, VECTOR3(23.f, FLOOR_Y, -6.f),	VECTOR3(26.f, FLOOR_Y, -6.f),	VECTOR3(23.f, FLOOR_Y, -10.f),	VECTOR3(26.f, FLOOR_Y, -10.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(16.f, FLOOR_Y, -6.f),	VECTOR3(20.f, FLOOR_Y, -6.f),	VECTOR3(16.f, FLOOR_Y, -8.f),	VECTOR3(20.f, FLOOR_Y, -8.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(16.f, FLOOR_Y, -8.f),	VECTOR3(20.f, FLOOR_Y, -8.f),	VECTOR3(16.f, FLOOR_Y, -10.f),	VECTOR3(20.f, FLOOR_Y, -10.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, FLOOR_Y, -6.f),	VECTOR3(16.f, FLOOR_Y, -6.f),	VECTOR3(14.f, FLOOR_Y, -7.f),	VECTOR3(16.f, FLOOR_Y, -7.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, FLOOR_Y, -7.f),	VECTOR3(16.f, FLOOR_Y, -7.f),	VECTOR3(14.f, FLOOR_Y, -10.f),	VECTOR3(16.f, FLOOR_Y, -10.f),	NORMAL_UP, FLOOR_COLOR);
	// ... Gang 1
	iIndex = CreateQuadXZ(iIndex, VECTOR3(7.f, FLOOR_Y, -4.f),	VECTOR3(9.f, FLOOR_Y, -4.f),	VECTOR3(7.f, FLOOR_Y, -6.f),	VECTOR3(9.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -4.f),	VECTOR3(11.f, FLOOR_Y, -4.f),	VECTOR3(9.f, FLOOR_Y, -6.f),	VECTOR3(11.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, FLOOR_Y, -4.f),	VECTOR3(13.f, FLOOR_Y, -4.f),	VECTOR3(11.f, FLOOR_Y, -6.f),	VECTOR3(13.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(13.f, FLOOR_Y, -4.f),	VECTOR3(14.f, FLOOR_Y, -4.f),	VECTOR3(13.f, FLOOR_Y, -6.f),	VECTOR3(14.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, FLOOR_Y, -4.f),	VECTOR3(16.f, FLOOR_Y, -4.f),	VECTOR3(14.f, FLOOR_Y, -6.f),	VECTOR3(16.f, FLOOR_Y, -6.f),	NORMAL_UP, FLOOR_COLOR);
	// ... Gang 2
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -13.f),	VECTOR3(11.f, FLOOR_Y, -13.f),	VECTOR3(9.f, FLOOR_Y, -14.f),	VECTOR3(11.f, FLOOR_Y, -14.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -11.f),	VECTOR3(11.f, FLOOR_Y, -11.f),	VECTOR3(9.f, FLOOR_Y, -13.f),	VECTOR3(11.f, FLOOR_Y, -13.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -9.f),	VECTOR3(11.f, FLOOR_Y, -9.f),	VECTOR3(9.f, FLOOR_Y, -11.f),	VECTOR3(11.f, FLOOR_Y, -11.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, FLOOR_Y, -6.f),	VECTOR3(13.f, FLOOR_Y, -7.f),	VECTOR3(9.f, FLOOR_Y, -8.f),	VECTOR3(11.f, FLOOR_Y, -9.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(13.f, FLOOR_Y, -6.f),	VECTOR3(14.f, FLOOR_Y, -6.f),	VECTOR3(13.f, FLOOR_Y, -7.f),	VECTOR3(14.f, FLOOR_Y, -7.f),	NORMAL_UP, FLOOR_COLOR);
	// ... Gang 3
	iIndex = CreateQuadXZ(iIndex, VECTOR3(17.f, FLOOR_Y, 0.f),	VECTOR3(18.f, FLOOR_Y, -2.f),	VECTOR3(15.f, FLOOR_Y, -2.f),	VECTOR3(16.f, FLOOR_Y, -4.f),	NORMAL_UP, FLOOR_COLOR);
	// ... Lücken füllen ... im Gang 2
	iIndex = CreateTriXZ(iIndex, VECTOR3(9.f, FLOOR_Y, -8.f),	VECTOR3(11.f, FLOOR_Y, -9.f),	VECTOR3(9.f, FLOOR_Y, -9.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateTriXZ(iIndex, VECTOR3(11.f, FLOOR_Y, -6.f),	VECTOR3(13.f, FLOOR_Y, -6.f),	VECTOR3(13.f, FLOOR_Y, -7.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateTriXZ(iIndex, VECTOR3(13.f, FLOOR_Y, -7.f),	VECTOR3(14.f, FLOOR_Y, -7.f),	VECTOR3(14.f, FLOOR_Y, -8.f),	NORMAL_UP, FLOOR_COLOR);
	// ... Lücken füllen ... im Gang 3
	iIndex = CreateTriXZ(iIndex, VECTOR3(15.f, FLOOR_Y, -2.f),	VECTOR3(16.f, FLOOR_Y, -4.f),	VECTOR3(13.f, FLOOR_Y, -4.f),	NORMAL_UP, FLOOR_COLOR);
	iIndex = CreateTriXZ(iIndex, VECTOR3(17.f, FLOOR_Y, 0.f),	VECTOR3(18.f, FLOOR_Y, 0.f),	VECTOR3(18.f, FLOOR_Y, -2.f),	NORMAL_UP, FLOOR_COLOR);

	// Wände -----------------------------------------------------------------------------------------------------------------------------------
	// Beginnend mit Raum 1
	iIndex = CreateQuadXY(iIndex, VECTOR3(0.f, CEILING_Y, -1.f), VECTOR3(2.f, CEILING_Y, -1.f), VECTOR3(0.f, FLOOR_Y, -1.f), VECTOR3(2.f, FLOOR_Y, -1.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(2.f, CEILING_Y, -1.f), VECTOR3(4.f, CEILING_Y, -1.f), VECTOR3(2.f, FLOOR_Y, -1.f), VECTOR3(4.f, FLOOR_Y, -1.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(4.f, CEILING_Y, -1.f), VECTOR3(7.f, CEILING_Y, -1.f), VECTOR3(4.f, FLOOR_Y, -1.f), VECTOR3(7.f, FLOOR_Y, -1.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(2.f, CEILING_Y, -8.f), VECTOR3(0.f, CEILING_Y, -8.f), VECTOR3(2.f, FLOOR_Y, -8.f), VECTOR3(0.f, FLOOR_Y, -8.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(4.f, CEILING_Y, -8.f), VECTOR3(2.f, CEILING_Y, -8.f), VECTOR3(4.f, FLOOR_Y, -8.f), VECTOR3(2.f, FLOOR_Y, -8.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(7.f, CEILING_Y, -8.f), VECTOR3(4.f, CEILING_Y, -8.f), VECTOR3(7.f, FLOOR_Y, -8.f), VECTOR3(4.f, FLOOR_Y, -8.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(0.f, CEILING_Y, -4.f), VECTOR3(0.f, CEILING_Y, -1.f), VECTOR3(0.f, FLOOR_Y, -4.f), VECTOR3(0.f, FLOOR_Y, -1.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(0.f, CEILING_Y, -6.f), VECTOR3(0.f, CEILING_Y, -4.f), VECTOR3(0.f, FLOOR_Y, -6.f), VECTOR3(0.f, FLOOR_Y, -4.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(0.f, CEILING_Y, -8.f), VECTOR3(0.f, CEILING_Y, -6.f), VECTOR3(0.f, FLOOR_Y, -8.f), VECTOR3(0.f, FLOOR_Y, -6.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(7.f, CEILING_Y, -1.f), VECTOR3(7.f, CEILING_Y, -4.f), VECTOR3(7.f, FLOOR_Y, -1.f), VECTOR3(7.f, FLOOR_Y, -4.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(7.f, CEILING_Y, -4.f), VECTOR3(7.f, CEILING_Y, -6.f), VECTOR3(7.f, GANG_CEILING_Y, -4.f), VECTOR3(7.f, GANG_CEILING_Y, -6.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(7.f, CEILING_Y, -6.f), VECTOR3(7.f, CEILING_Y, -8.f), VECTOR3(7.f, FLOOR_Y, -6.f), VECTOR3(7.f, FLOOR_Y, -8.f), NORMAL_WEST, WALL_COLOR);
	// ... Gang 1
	iIndex = CreateQuadXY(iIndex, VECTOR3(7.f, GANG_CEILING_Y, -4.f), VECTOR3(9.f, GANG_CEILING_Y, -4.f), VECTOR3(7.f, FLOOR_Y, -4.f), VECTOR3(9.f, FLOOR_Y, -4.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -4.f), VECTOR3(11.f, GANG_CEILING_Y, -4.f), VECTOR3(9.f, FLOOR_Y, -4.f), VECTOR3(11.f, FLOOR_Y, -4.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -4.f), VECTOR3(13.f, GANG_CEILING_Y, -4.f), VECTOR3(11.f, FLOOR_Y, -4.f), VECTOR3(13.f, FLOOR_Y, -4.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -6.f), VECTOR3(7.f, GANG_CEILING_Y, -6.f), VECTOR3(9.f, FLOOR_Y, -6.f), VECTOR3(7.f, FLOOR_Y, -6.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -6.f), VECTOR3(9.f, GANG_CEILING_Y, -6.f), VECTOR3(11.f, FLOOR_Y, -6.f), VECTOR3(9.f, FLOOR_Y, -6.f), NORMAL_NORTH, WALL_COLOR);
	// ... Raum 2
	iIndex = CreateQuadXY(iIndex, VECTOR3(6.f, CEILING_Y, -14.f), VECTOR3(9.f, CEILING_Y, -14.f), VECTOR3(6.f, FLOOR_Y, -14.f), VECTOR3(9.f, FLOOR_Y, -14.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(9.f, CEILING_Y, -14.f), VECTOR3(11.f, CEILING_Y, -14.f), VECTOR3(9.f, GANG_CEILING_Y, -14.f), VECTOR3(11.f, GANG_CEILING_Y, -14.f), NORMAL_SOUTH, WALL_COLOR);	
	iIndex = CreateQuadXY(iIndex, VECTOR3(11.f, CEILING_Y, -14.f), VECTOR3(14.f, CEILING_Y, -14.f), VECTOR3(11.f, FLOOR_Y, -14.f), VECTOR3(14.f, FLOOR_Y, -14.f), NORMAL_SOUTH, WALL_COLOR);
	// ... Raum 2 Podest
	iIndex = CreateQuadXY(iIndex, VECTOR3(9.f, PODEST_Y, -18.f), VECTOR3(6.f, PODEST_Y, -18.f), VECTOR3(9.f, FLOOR_Y, -18.f), VECTOR3(6.f, FLOOR_Y, -18.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(11.f, PODEST_Y, -18.f), VECTOR3(9.f, PODEST_Y, -18.f), VECTOR3(11.f, FLOOR_Y, -18.f), VECTOR3(9.f, FLOOR_Y, -18.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(14.f, PODEST_Y, -18.f), VECTOR3(11.f, PODEST_Y, -18.f), VECTOR3(14.f, FLOOR_Y, -18.f), VECTOR3(11.f, FLOOR_Y, -18.f), NORMAL_NORTH, WALL_COLOR);
	// ... Raum 2 Podest
	iIndex = CreateQuadYZ(iIndex, VECTOR3(6.f, PODEST_Y, -18.f), VECTOR3(6.f, PODEST_Y, -16.f), VECTOR3(6.f, FLOOR_Y, -18.f), VECTOR3(6.f, FLOOR_Y, -16.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(6.f, PODEST_Y, -16.f), VECTOR3(6.f, PODEST_Y, -14.f), VECTOR3(6.f, FLOOR_Y, -16.f), VECTOR3(6.f, FLOOR_Y, -14.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(6.f, CEILING_Y, -18.f), VECTOR3(6.f, CEILING_Y, -16.f), VECTOR3(6.f, PODEST_Y, -18.f), VECTOR3(6.f, PODEST_Y, -16.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(6.f, CEILING_Y, -16.f), VECTOR3(6.f, CEILING_Y, -14.f), VECTOR3(6.f, PODEST_Y, -16.f), VECTOR3(6.f, PODEST_Y, -14.f), NORMAL_EAST, WALL_COLOR);	
	iIndex = CreateQuadYZ(iIndex, VECTOR3(6.f, CEILING_Y, -21.f), VECTOR3(6.f, CEILING_Y, -18.f), VECTOR3(6.f, PODEST_Y, -21.f), VECTOR3(6.f, PODEST_Y, -18.f), NORMAL_EAST, WALL_COLOR);

	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, PODEST_Y, -16.f), VECTOR3(14.f, PODEST_Y, -18.f), VECTOR3(14.f, FLOOR_Y, -16.f), VECTOR3(14.f, FLOOR_Y, -18.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, PODEST_Y, -14.f), VECTOR3(14.f, PODEST_Y, -16.f), VECTOR3(14.f, FLOOR_Y, -14.f), VECTOR3(14.f, FLOOR_Y, -16.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, CEILING_Y, -16.f), VECTOR3(14.f, CEILING_Y, -18.f), VECTOR3(14.f, PODEST_Y, -16.f), VECTOR3(14.f, PODEST_Y, -18.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, CEILING_Y, -14.f), VECTOR3(14.f, CEILING_Y, -16.f), VECTOR3(14.f, PODEST_Y, -14.f), VECTOR3(14.f, PODEST_Y, -16.f), NORMAL_WEST, WALL_COLOR);	
	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, CEILING_Y, -18.f), VECTOR3(14.f, CEILING_Y, -21.f), VECTOR3(14.f, PODEST_Y, -18.f), VECTOR3(14.f, PODEST_Y, -21.f), NORMAL_WEST, WALL_COLOR);
	// ... Raum 2 Podest-Wand
	iIndex = CreateQuadXY(iIndex, VECTOR3(9.f, CEILING_Y, -21.f), VECTOR3(6.f, CEILING_Y, -21.f), VECTOR3(9.f, PODEST_Y, -21.f), VECTOR3(6.f, PODEST_Y, -21.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(11.f, CEILING_Y, -21.f), VECTOR3(9.f, CEILING_Y, -21.f), VECTOR3(11.f, PODEST_Y, -21.f), VECTOR3(9.f, PODEST_Y, -21.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(14.f, CEILING_Y, -21.f), VECTOR3(11.f, CEILING_Y, -21.f), VECTOR3(14.f, PODEST_Y, -21.f), VECTOR3(11.f, PODEST_Y, -21.f), NORMAL_NORTH, WALL_COLOR);
	// ... Gang 2
	iIndex = CreateQuadYZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -14.f), VECTOR3(9.f, GANG_CEILING_Y, -13.f), VECTOR3(9.f, FLOOR_Y, -14.f), VECTOR3(9.f, FLOOR_Y, -13.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -13.f), VECTOR3(9.f, GANG_CEILING_Y, -11.f), VECTOR3(9.f, FLOOR_Y, -13.f), VECTOR3(9.f, FLOOR_Y, -11.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -11.f), VECTOR3(9.f, GANG_CEILING_Y, -9.f), VECTOR3(9.f, FLOOR_Y, -11.f), VECTOR3(9.f, FLOOR_Y, -9.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -9.f), VECTOR3(9.f, GANG_CEILING_Y, -8.f), VECTOR3(9.f, FLOOR_Y, -9.f), VECTOR3(9.f, FLOOR_Y, -8.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -13.f), VECTOR3(11.f, GANG_CEILING_Y, -14.f), VECTOR3(11.f, FLOOR_Y, -13.f), VECTOR3(11.f, FLOOR_Y, -14.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -11.f), VECTOR3(11.f, GANG_CEILING_Y, -13.f), VECTOR3(11.f, FLOOR_Y, -11.f), VECTOR3(11.f, FLOOR_Y, -13.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -9.f), VECTOR3(11.f, GANG_CEILING_Y, -11.f), VECTOR3(11.f, FLOOR_Y, -9.f), VECTOR3(11.f, FLOOR_Y, -11.f), NORMAL_WEST, WALL_COLOR);
	// ... Raum 3 Pfeiler
	iIndex = CreateQuadXY(iIndex, VECTOR3(16.f, CEILING_Y, -6.f), VECTOR3(20.f, CEILING_Y, -6.f), VECTOR3(16.f, FLOOR_Y, -6.f), VECTOR3(20.f, FLOOR_Y, -6.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(20.f, CEILING_Y, -6.f), VECTOR3(20.f, CEILING_Y, -2.f), VECTOR3(20.f, FLOOR_Y, -6.f), VECTOR3(20.f, FLOOR_Y, -2.f), NORMAL_EAST, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(20.f, CEILING_Y, -2.f), VECTOR3(18.f, CEILING_Y, -2.f), VECTOR3(20.f, FLOOR_Y, -2.f), VECTOR3(18.f, FLOOR_Y, -2.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(16.f, CEILING_Y, -4.f), VECTOR3(16.f, CEILING_Y, -6.f), VECTOR3(16.f, FLOOR_Y, -4.f), VECTOR3(16.f, FLOOR_Y, -6.f), NORMAL_WEST, WALL_COLOR);
	// ... Raum 3
	iIndex = CreateQuadXY(iIndex, VECTOR3(16.f, CEILING_Y, -10.f), VECTOR3(14.f, CEILING_Y, -10.f), VECTOR3(16.f, FLOOR_Y, -10.f), VECTOR3(14.f, FLOOR_Y, -10.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(20.f, CEILING_Y, -10.f), VECTOR3(16.f, CEILING_Y, -10.f), VECTOR3(20.f, FLOOR_Y, -10.f), VECTOR3(16.f, FLOOR_Y, -10.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(23.f, CEILING_Y, -10.f), VECTOR3(20.f, CEILING_Y, -10.f), VECTOR3(23.f, FLOOR_Y, -10.f), VECTOR3(20.f, FLOOR_Y, -10.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(26.f, CEILING_Y, -10.f), VECTOR3(23.f, CEILING_Y, -10.f), VECTOR3(26.f, FLOOR_Y, -10.f), VECTOR3(23.f, FLOOR_Y, -10.f), NORMAL_NORTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(17.f, CEILING_Y, 0.f), VECTOR3(18.f, CEILING_Y, 0.f), VECTOR3(17.f, FLOOR_Y, 0.f), VECTOR3(18.f, FLOOR_Y, 0.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(18.f, CEILING_Y, 0.f), VECTOR3(20.f, CEILING_Y, 0.f), VECTOR3(18.f, FLOOR_Y, 0.f), VECTOR3(20.f, FLOOR_Y, 0.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(20.f, CEILING_Y, 0.f), VECTOR3(23.f, CEILING_Y, 0.f), VECTOR3(20.f, FLOOR_Y, 0.f), VECTOR3(23.f, FLOOR_Y, 0.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadXY(iIndex, VECTOR3(23.f, CEILING_Y, 0.f), VECTOR3(26.f, CEILING_Y, 0.f), VECTOR3(23.f, FLOOR_Y, 0.f), VECTOR3(26.f, FLOOR_Y, 0.f), NORMAL_SOUTH, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(26.f, CEILING_Y, 0.f), VECTOR3(26.f, CEILING_Y, -2.f), VECTOR3(26.f, FLOOR_Y, 0.f), VECTOR3(26.f, FLOOR_Y, -2.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(26.f, CEILING_Y, -2.f), VECTOR3(26.f, CEILING_Y, -6.f), VECTOR3(26.f, FLOOR_Y, -2.f), VECTOR3(26.f, FLOOR_Y, -6.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(26.f, CEILING_Y, -6.f), VECTOR3(26.f, CEILING_Y, -10.f), VECTOR3(26.f, FLOOR_Y, -6.f), VECTOR3(26.f, FLOOR_Y, -10.f), NORMAL_WEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, CEILING_Y, -10.f), VECTOR3(14.f, CEILING_Y, -8.f), VECTOR3(14.f, FLOOR_Y, -10.f), VECTOR3(14.f, FLOOR_Y, -8.f), NORMAL_EAST, WALL_COLOR);
	// Schräge Wände
	iIndex = CreateQuadYZ(iIndex, VECTOR3(18.f, CEILING_Y, -2.f), VECTOR3(16.f, CEILING_Y, -4.f), VECTOR3(18.f, FLOOR_Y, -2.f), VECTOR3(16.f, FLOOR_Y, -4.f), NORMAL_NORTHWEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(13.f, CEILING_Y, -4.f), VECTOR3(15.f, CEILING_Y, -2.f), VECTOR3(13.f, FLOOR_Y, -4.f), VECTOR3(15.f, FLOOR_Y, -2.f), NORMAL_SOUTHEAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(15.f, CEILING_Y, -2.f), VECTOR3(17.f, CEILING_Y, 0.f), VECTOR3(15.f, FLOOR_Y, -2.f), VECTOR3(17.f, FLOOR_Y, 0.f), NORMAL_SOUTHEAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -8.f), VECTOR3(11.f, GANG_CEILING_Y, -6.f), VECTOR3(9.f, FLOOR_Y, -8.f), VECTOR3(11.f, FLOOR_Y, -6.f), NORMAL_SOUTHEAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(13.f, GANG_CEILING_Y, -7.f), VECTOR3(11.f, GANG_CEILING_Y, -9.f), VECTOR3(13.f, FLOOR_Y, -7.f), VECTOR3(11.f, FLOOR_Y, -9.f), NORMAL_NORTHWEST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(14.f, CEILING_Y, -8.f), VECTOR3(13.f, CEILING_Y, -7.f), VECTOR3(14.f, FLOOR_Y, -8.f), VECTOR3(13.f, FLOOR_Y, -7.f), NORMAL_NORTHEAST, WALL_COLOR);
	iIndex = CreateQuadYZ(iIndex, VECTOR3(13.f, CEILING_Y, -7.f), VECTOR3(13.f, CEILING_Y, -4.f), VECTOR3(13.f, GANG_CEILING_Y, -7.f), VECTOR3(13.f, GANG_CEILING_Y, -4.f), NORMAL_EAST, WALL_COLOR);

	// Decken -----------------------------------------------------------------------------------------------------------------------------------
	// Beginnend mit Raum 1
	iIndex = CreateQuadXZ(iIndex, VECTOR3(2.f, CEILING_Y, -1.f), VECTOR3(0.f, CEILING_Y, -1.f), VECTOR3(2.f, CEILING_Y, -4.f), VECTOR3(0.f, CEILING_Y, -4.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(4.f, CEILING_Y, -1.f), VECTOR3(2.f, CEILING_Y, -1.f), VECTOR3(4.f, CEILING_Y, -4.f), VECTOR3(2.f, CEILING_Y, -4.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(7.f, CEILING_Y, -1.f), VECTOR3(4.f, CEILING_Y, -1.f), VECTOR3(7.f, CEILING_Y, -4.f), VECTOR3(4.f, CEILING_Y, -4.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(2.f, CEILING_Y, -4.f), VECTOR3(0.f, CEILING_Y, -4.f), VECTOR3(2.f, CEILING_Y, -6.f), VECTOR3(0.f, CEILING_Y, -6.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(4.f, CEILING_Y, -4.f), VECTOR3(2.f, CEILING_Y, -4.f), VECTOR3(4.f, CEILING_Y, -6.f), VECTOR3(2.f, CEILING_Y, -6.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(7.f, CEILING_Y, -4.f), VECTOR3(4.f, CEILING_Y, -4.f), VECTOR3(7.f, CEILING_Y, -6.f), VECTOR3(4.f, CEILING_Y, -6.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(2.f, CEILING_Y, -6.f), VECTOR3(0.f, CEILING_Y, -6.f), VECTOR3(2.f, CEILING_Y, -8.f), VECTOR3(0.f, CEILING_Y, -8.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(4.f, CEILING_Y, -6.f), VECTOR3(2.f, CEILING_Y, -6.f), VECTOR3(4.f, CEILING_Y, -8.f), VECTOR3(2.f, CEILING_Y, -8.f), NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(7.f, CEILING_Y, -6.f), VECTOR3(4.f, CEILING_Y, -6.f), VECTOR3(7.f, CEILING_Y, -8.f), VECTOR3(4.f, CEILING_Y, -8.f), NORMAL_DOWN, CEILING_COLOR);
	// ... Raum 2
	iIndex = CreateQuadXZ(iIndex, VECTOR3(20.f, CEILING_Y, 0.f),	VECTOR3(18.f, CEILING_Y, 0.f),	VECTOR3(20.f, CEILING_Y, -2.f),	VECTOR3(18.f, CEILING_Y, -2.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(23.f, CEILING_Y, 0.f),	VECTOR3(20.f, CEILING_Y, 0.f),	VECTOR3(23.f, CEILING_Y, -2.f),	VECTOR3(20.f, CEILING_Y, -2.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(26.f, CEILING_Y, 0.f),	VECTOR3(23.f, CEILING_Y, 0.f),	VECTOR3(26.f, CEILING_Y, -2.f),	VECTOR3(23.f, CEILING_Y, -2.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(23.f, CEILING_Y, -2.f),	VECTOR3(20.f, CEILING_Y, -2.f),	VECTOR3(23.f, CEILING_Y, -6.f),	VECTOR3(20.f, CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);	
	iIndex = CreateQuadXZ(iIndex, VECTOR3(26.f, CEILING_Y, -2.f),	VECTOR3(23.f, CEILING_Y, -2.f),	VECTOR3(26.f, CEILING_Y, -6.f),	VECTOR3(23.f, CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(23.f, CEILING_Y, -6.f),	VECTOR3(20.f, CEILING_Y, -6.f),	VECTOR3(23.f, CEILING_Y, -10.f),	VECTOR3(20.f, CEILING_Y, -10.f),	NORMAL_DOWN, CEILING_COLOR);	
	iIndex = CreateQuadXZ(iIndex, VECTOR3(26.f, CEILING_Y, -6.f),	VECTOR3(23.f, CEILING_Y, -6.f),	VECTOR3(26.f, CEILING_Y, -10.f),	VECTOR3(23.f, CEILING_Y, -10.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(20.f, CEILING_Y, -6.f),	VECTOR3(16.f, CEILING_Y, -6.f),	VECTOR3(20.f, CEILING_Y, -8.f),	VECTOR3(16.f, CEILING_Y, -8.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(20.f, CEILING_Y, -8.f),	VECTOR3(16.f, CEILING_Y, -8.f),	VECTOR3(20.f, CEILING_Y, -10.f),	VECTOR3(16.f, CEILING_Y, -10.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(16.f, CEILING_Y, -6.f),	VECTOR3(14.f, CEILING_Y, -6.f),	VECTOR3(16.f, CEILING_Y, -7.f),	VECTOR3(14.f, CEILING_Y, -7.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(16.f, CEILING_Y, -7.f),	VECTOR3(14.f, CEILING_Y, -7.f),	VECTOR3(16.f, CEILING_Y, -10.f),	VECTOR3(14.f, CEILING_Y, -10.f),	NORMAL_DOWN, CEILING_COLOR);
	// ... Raum 3
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, CEILING_Y, -14.f),	VECTOR3(6.f, CEILING_Y, -14.f),		VECTOR3(9.f, CEILING_Y, -16.f),		VECTOR3(6.f, CEILING_Y, -16.f),		NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, CEILING_Y, -14.f),	VECTOR3(9.f, CEILING_Y, -14.f),	VECTOR3(11.f, CEILING_Y, -16.f),		VECTOR3(9.f, CEILING_Y, -16.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, CEILING_Y, -14.f),	VECTOR3(11.f, CEILING_Y, -14.f),	VECTOR3(14.f, CEILING_Y, -16.f),	VECTOR3(11.f, CEILING_Y, -16.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, CEILING_Y, -16.f),	VECTOR3(6.f, CEILING_Y, -16.f),		VECTOR3(9.f, CEILING_Y, -18.f),		VECTOR3(6.f, CEILING_Y, -18.f),		NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, CEILING_Y, -16.f),	VECTOR3(9.f, CEILING_Y, -16.f),	VECTOR3(11.f, CEILING_Y, -18.f),		VECTOR3(9.f, CEILING_Y, -18.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, CEILING_Y, -16.f),	VECTOR3(11.f, CEILING_Y, -16.f),	VECTOR3(14.f, CEILING_Y, -18.f),	VECTOR3(11.f, CEILING_Y, -18.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, CEILING_Y, -18.f),	VECTOR3(6.f, CEILING_Y, -18.f),		VECTOR3(9.f, CEILING_Y, -21.f),		VECTOR3(6.f, CEILING_Y, -21.f),		NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, CEILING_Y, -18.f),	VECTOR3(9.f, CEILING_Y, -18.f),	VECTOR3(11.f, CEILING_Y, -21.f),		VECTOR3(9.f, CEILING_Y, -21.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, CEILING_Y, -18.f),	VECTOR3(11.f, CEILING_Y, -18.f),	VECTOR3(14.f, CEILING_Y, -21.f),	VECTOR3(11.f, CEILING_Y, -21.f),	NORMAL_DOWN, CEILING_COLOR);
	// ... Gang 1
	iIndex = CreateQuadXZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -4.f),	VECTOR3(7.f, GANG_CEILING_Y, -4.f),	VECTOR3(9.f, GANG_CEILING_Y, -6.f),	VECTOR3(7.f, GANG_CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -4.f),	VECTOR3(9.f, GANG_CEILING_Y, -4.f),	VECTOR3(11.f, GANG_CEILING_Y, -6.f),	VECTOR3(9.f, GANG_CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(13.f, GANG_CEILING_Y, -4.f),	VECTOR3(11.f, GANG_CEILING_Y, -4.f),	VECTOR3(13.f, GANG_CEILING_Y, -6.f),	VECTOR3(11.f, GANG_CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, CEILING_Y, -4.f),	VECTOR3(13.f, CEILING_Y, -4.f),	VECTOR3(14.f, CEILING_Y, -6.f),	VECTOR3(13.f, CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(16.f, CEILING_Y, -4.f),	VECTOR3(14.f, CEILING_Y, -4.f),	VECTOR3(16.f, CEILING_Y, -6.f),	VECTOR3(14.f, CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	// ... Gang 2
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -13.f),	VECTOR3(9.f, GANG_CEILING_Y, -13.f),	VECTOR3(11.f, GANG_CEILING_Y, -14.f),	VECTOR3(9.f, GANG_CEILING_Y, -14.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -11.f),	VECTOR3(9.f, GANG_CEILING_Y, -11.f),	VECTOR3(11.f, GANG_CEILING_Y, -13.f),	VECTOR3(9.f, GANG_CEILING_Y, -13.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -9.f),	VECTOR3(9.f, GANG_CEILING_Y, -9.f),	VECTOR3(11.f, GANG_CEILING_Y, -11.f),	VECTOR3(9.f, GANG_CEILING_Y, -11.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(13.f, GANG_CEILING_Y, -7.f),	VECTOR3(11.f, GANG_CEILING_Y, -6.f),	VECTOR3(11.f, GANG_CEILING_Y, -9.f),	VECTOR3(9.f, GANG_CEILING_Y, -8.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateQuadXZ(iIndex, VECTOR3(14.f, CEILING_Y, -6.f),	VECTOR3(13.f, CEILING_Y, -6.f),	VECTOR3(14.f, CEILING_Y, -7.f),	VECTOR3(13.f, CEILING_Y, -7.f),	NORMAL_DOWN, CEILING_COLOR);
	// ... Gang 3
	iIndex = CreateQuadXZ(iIndex, VECTOR3(18.f, CEILING_Y, -2.f),	VECTOR3(17.f, CEILING_Y, 0.f),	VECTOR3(16.f, CEILING_Y, -4.f),	VECTOR3(15.f, CEILING_Y, -2.f),	NORMAL_DOWN, CEILING_COLOR);


	// ... Lücken füllen ... im Gang 2
	iIndex = CreateTriXZ(iIndex, VECTOR3(9.f, GANG_CEILING_Y, -8.f),	VECTOR3(9.f, GANG_CEILING_Y, -9.f),		VECTOR3(11.f, GANG_CEILING_Y, -9.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateTriXZ(iIndex, VECTOR3(11.f, GANG_CEILING_Y, -6.f),	VECTOR3(13.f, GANG_CEILING_Y, -7.f),	VECTOR3(13.f, GANG_CEILING_Y, -6.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateTriXZ(iIndex, VECTOR3(13.f, CEILING_Y, -7.f),	VECTOR3(14.f, CEILING_Y, -8.f),	VECTOR3(14.f, CEILING_Y, -7.f),	NORMAL_DOWN, CEILING_COLOR);
	// ... Lücken füllen ... im Gang 3
	iIndex = CreateTriXZ(iIndex, VECTOR3(15.f, CEILING_Y, -2.f),	VECTOR3(13.f, CEILING_Y, -4.f),	VECTOR3(16.f, CEILING_Y, -4.f),	NORMAL_DOWN, CEILING_COLOR);
	iIndex = CreateTriXZ(iIndex, VECTOR3(17.f, CEILING_Y, 0.f),		VECTOR3(18.f, CEILING_Y, -2.f),	VECTOR3(18.f, CEILING_Y, 0.f),	NORMAL_DOWN, CEILING_COLOR);


	HRESULT retval;
	g_VerticesScene = NULL;
	retval = m_pPipe->GetDirect3DDevice()->CreateVertexBuffer(sizeof(VSD3DVERTEX_DIFFUSE)*SCENE_ITEMCOUNT, D3DUSAGE_WRITEONLY, VS_D3DFVF_VERTEX_DIFFUSE, D3DPOOL_DEFAULT, &g_VerticesScene, NULL);
	if(FAILED(retval)) {
		dprintf("scene creation: Erzeugung des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return 0;
	}

	void* ptr = NULL;
	retval = g_VerticesScene->Lock(0, sizeof(VSD3DVERTEX_DIFFUSE)*SCENE_ITEMCOUNT, (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("scene creation: Lock des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		SAFE_DELETE(g_VerticesScene);
		return 0;
	}
	memcpy(ptr, m_pSceneVertices, sizeof(VSD3DVERTEX_DIFFUSE)*SCENE_ITEMCOUNT);
	g_VerticesScene->Unlock();



	//--iNormalCounter;
	g_VerticesNormals = NULL;
	retval = m_pPipe->GetDirect3DDevice()->CreateVertexBuffer(sizeof(VSD3DVERTEX_DIFFUSE)*iNormalCounter, D3DUSAGE_WRITEONLY, VS_D3DFVF_VERTEX_DIFFUSE, D3DPOOL_DEFAULT, &g_VerticesNormals, NULL);
	if(FAILED(retval)) {
		dprintf("scene creation: Erzeugung des Normal-Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return 0;
	}

	ptr = NULL;
	retval = g_VerticesNormals->Lock(0, sizeof(VSD3DVERTEX_DIFFUSE)*iNormalCounter, (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("scene creation: Lock des Normal-Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		SAFE_DELETE(g_VerticesNormals);
		return 0;
	}
	memcpy(ptr, m_pSceneNormals, sizeof(VSD3DVERTEX_DIFFUSE)*iNormalCounter);
	g_VerticesNormals->Unlock();




	g_IndicesScene = NULL;
	retval = m_pPipe->GetDirect3DDevice()->CreateIndexBuffer(sizeof(WORD)*SCENE_ITEMCOUNT, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_IndicesScene, NULL);
	if(FAILED(retval)) {
		dprintf("scene creation: Erzeugung des Index-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return 0;
	}

	retval = g_IndicesScene->Lock(0, sizeof(WORD)*SCENE_ITEMCOUNT, (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("scene creation: Lock des Index-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		SAFE_DELETE(g_VerticesScene);
		return 0;
	}

	WORD *iTempIndices = new WORD[SCENE_ITEMCOUNT];
	for(WORD i=0; i<SCENE_ITEMCOUNT; i++) {
		iTempIndices[i] = i;
	}
	memcpy(ptr, iTempIndices, sizeof(WORD)*SCENE_ITEMCOUNT);
	g_IndicesScene->Unlock();
	SAFE_DELETE_ARRAY(iTempIndices);


	//g_VerticesScene->Optimize();


	return (unsigned int)((float)iIndex * VAL1d3);
}

void DeleteScene() {
	SAFE_RELEASE(g_VerticesScene);
	SAFE_RELEASE(g_IndicesScene);
	SAFE_RELEASE(g_VerticesNormals);
}


void RenderSceneNormals(PIPED3D2 &in_Pipe, bool Set = true) {
	if(Set) {
		in_Pipe.GetDirect3DDevice()->SetFVF(VS_D3DFVF_VERTEX_DIFFUSE);
		//in_Pipe.GetDirect3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 85, (void*)&m_pSceneVertices, sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetStreamSource(0, g_VerticesNormals, 0, sizeof(VSD3DVERTEX_DIFFUSE));
	}
	in_Pipe.GetDirect3DDevice()->DrawPrimitive(D3DPT_LINELIST, 0, iNormalCounter/2);
}


void RenderSceneFloor(PIPED3D2 &in_Pipe, bool Set = false) {
	if(Set) {
		in_Pipe.GetDirect3DDevice()->SetFVF(VS_D3DFVF_VERTEX_DIFFUSE);
		//in_Pipe.GetDirect3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 85, (void*)&m_pSceneVertices, sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetStreamSource(0, g_VerticesScene, 0, sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetIndices(g_IndicesScene);
	}
	//in_Pipe.GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 85);
	in_Pipe.GetDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 85*3, 0, 85);
}

void RenderSceneWall(PIPED3D2 &in_Pipe, bool Set = true) {
	if(Set) {
		in_Pipe.GetDirect3DDevice()->SetFVF(VS_D3DFVF_VERTEX_DIFFUSE);
		//in_Pipe.GetDirect3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 132, (void*)&m_pSceneVertices[255], sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetStreamSource(0, g_VerticesScene, 0, sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetIndices(g_IndicesScene);
	}
	//in_Pipe.GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 255, 132);
	//in_Pipe.GetDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 255, 132*3);
	in_Pipe.GetDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 255, 0, 132*3, 0, 132);
}

void RenderSceneCeiling(PIPED3D2 &in_Pipe, bool Set = false) {
	if(Set) {
		in_Pipe.GetDirect3DDevice()->SetFVF(VS_D3DFVF_VERTEX_DIFFUSE);
		//in_Pipe.GetDirect3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 85, (void*)&m_pSceneVertices[651], sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetStreamSource(0, g_VerticesScene, 0, sizeof(VSD3DVERTEX_DIFFUSE));
		in_Pipe.GetDirect3DDevice()->SetIndices(g_IndicesScene);
	}
	//in_Pipe.GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 651, 85);
	//in_Pipe.GetDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 651, 85*3);
	in_Pipe.GetDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 651, 0, 85*3, 0, 85);
}