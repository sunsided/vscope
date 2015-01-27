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

	Dateiname:		blit2d.cpp
	Beschreibung:	2D-Blitten mit DirectX
	Revision:		2
	Erstellt:		MMT, 10. Juli 2002 00:24

	Changelog:
	[2]		20. Juli 2002 06:31 MMT
			SurfFormatToString
	[1]		10. Juli 2002 00:24
			Erstellt

===========================================================================*/

#include "blit2d.h"
#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"
#include "..\vertices\vertices.inl.h"

#pragma intrinsic(memset)

bool VSFASTCALL CreateMaterial(D3DMATERIAL9* out_Material, float in_ambientR, float in_ambientG, float in_ambientB, float in_emissiveR,  float in_emissiveG, float in_emissiveB) {
	//ZeroMemory(out_Material, sizeof(out_Material));
	memset(out_Material, 0, sizeof(out_Material));
	out_Material->Ambient.r  = in_ambientR;
	out_Material->Ambient.g  = in_ambientG;
	out_Material->Ambient.b  = in_ambientB;
	out_Material->Emissive.r = in_emissiveR;
	out_Material->Emissive.g = in_emissiveG;
	out_Material->Emissive.b = in_emissiveB;
	return TRUE;
}

void VSFASTCALL BlitRect(LPDIRECT3DDEVICE9 in_Device, LPDIRECT3DTEXTURE9 in_SourceTexture, float left, float top, float right, float bottom, D3DCOLOR in_Color, BOOL in_UseTextureAlpha, float in_zDist) {
	float rhw=1.0f/(in_zDist*990.0f+10.0f);

	VSD3DTLVERTEX verts[4];
	verts[0]=VSD3DTLVERTEX(D3DXVECTOR3(left,  top,	in_zDist), rhw, in_Color, 0.0f, 0.0f); 
	verts[1]=VSD3DTLVERTEX(D3DXVECTOR3(right, top,    in_zDist), rhw, in_Color, 1.0f, 0.0f);
	verts[2]=VSD3DTLVERTEX(D3DXVECTOR3(right, bottom, in_zDist), rhw, in_Color, 1.0f, 1.0f); 
	verts[3]=VSD3DTLVERTEX(D3DXVECTOR3(left,  bottom, in_zDist), rhw, in_Color, 0.0f, 1.0f);

	in_Device->SetTexture(0, in_SourceTexture);
	//in_Device->SetVertexShader(VS_D3DFVF_TLVERTEX);
	//in_Device->SetVertexShader(NULL);
	in_Device->SetFVF(VS_D3DFVF_TLVERTEX);

	if(in_UseTextureAlpha) {
		in_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		in_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 
		in_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		in_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}

	in_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, verts, sizeof(VSD3DTLVERTEX));

	if(in_UseTextureAlpha) {
		in_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}


char* VSFASTCALL SurfFormatToString(D3DFORMAT srcformat) {
	switch(srcformat) {
		case D3DFMT_UNKNOWN:      return("D3DFMT_UNKNOWN");      
	                             
		case D3DFMT_R8G8B8:       return("D3DFMT_R8G8B8");       
		case D3DFMT_A8R8G8B8:     return("D3DFMT_A8R8G8B8");     
		case D3DFMT_X8R8G8B8:     return("D3DFMT_X8R8G8B8");     
		case D3DFMT_R5G6B5:       return("D3DFMT_R5G6B5");       
		case D3DFMT_X1R5G5B5:     return("D3DFMT_X1R5G5B5");     
		case D3DFMT_A1R5G5B5:     return("D3DFMT_A1R5G5B5");     
		case D3DFMT_A4R4G4B4:     return("D3DFMT_A4R4G4B4");     
		case D3DFMT_R3G3B2:       return("D3DFMT_R3G3B2");       
		case D3DFMT_A8:           return("D3DFMT_A8");           
		case D3DFMT_A8R3G3B2:     return("D3DFMT_A8R3G3B2");     
		case D3DFMT_X4R4G4B4:     return("D3DFMT_X4R4G4B4");     
	                             
		case D3DFMT_A8P8:         return("D3DFMT_A8P8");         
		case D3DFMT_P8:           return("D3DFMT_P8");           
	                             
		case D3DFMT_L8:           return("D3DFMT_L8");           
		case D3DFMT_A8L8:         return("D3DFMT_A8L8");         
		case D3DFMT_A4L4:         return("D3DFMT_A4L4");         
	                             
		case D3DFMT_V8U8:         return("D3DFMT_V8U8");         
		case D3DFMT_L6V5U5:       return("D3DFMT_L6V5U5");       
		case D3DFMT_X8L8V8U8:     return("D3DFMT_X8L8V8U8");     
		case D3DFMT_Q8W8V8U8:     return("D3DFMT_Q8W8V8U8");     
		case D3DFMT_V16U16:       return("D3DFMT_V16U16");       
		//case D3DFMT_W11V11U10:    return("D3DFMT_W11V11U10");    
	                                                                 
		case D3DFMT_UYVY:         return("D3DFMT_UYVY");         
		case D3DFMT_YUY2:         return("D3DFMT_YUY2");         
		case D3DFMT_DXT1:         return("D3DFMT_DXT1");         
		case D3DFMT_DXT2:         return("D3DFMT_DXT2");         
		case D3DFMT_DXT3:         return("D3DFMT_DXT3");         
		case D3DFMT_DXT4:         return("D3DFMT_DXT4");         
		case D3DFMT_DXT5:         return("D3DFMT_DXT5");         

		case D3DFMT_D16_LOCKABLE: return("D3DFMT_D16_LOCKABLE"); 
		case D3DFMT_D32:          return("D3DFMT_D32");          
		case D3DFMT_D15S1:        return("D3DFMT_D15S1");        
		case D3DFMT_D24S8:        return("D3DFMT_D24S8");        
		case D3DFMT_D16:          return("D3DFMT_D16");          
		case D3DFMT_D24X8:        return("D3DFMT_D24X8");        
		case D3DFMT_D24X4S4:      return("D3DFMT_D24X4S4");      

		case D3DFMT_VERTEXDATA:   return("D3DFMT_VERTEXDATA"); 
		case D3DFMT_INDEX16:      return("D3DFMT_INDEX16"); 
		case D3DFMT_INDEX32:      return("D3DFMT_INDEX32"); 
		default:                  return("**UNKNOWN**"); 
	};
	return("");
}