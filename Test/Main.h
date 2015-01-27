#pragma once


//#define DIRECTINPUT_VERSION 0x0900
#include <dinput.h>
#pragma comment(lib, "dinput8")

LPDIRECTINPUT8			lpDI8 = NULL;
LPDIRECTINPUTDEVICE8	lpKeyboard = NULL;

bool					Taste[12];

#define	AK_BEENDEN		0
#define	AK_LINKS		1
#define	AK_HOCH			2
#define	AK_RECHTS		3
#define	AK_RUNTER		4
#define	AK_VOR			5
#define	AK_ZURUECK		6
#define	AK_ROLLLINKS	7
#define	AK_ROLLRECHTS	8
#define	AK_STOP			9
#define	AK_SLOW			10
#define	AK_STRAFE		11


#define SPEED_WALK_FWD			0.15f
#define SPEED_WALK_FWD_SLOW		0.05f
#define SPEED_WALK_SIDE			0.1f
#define SPEED_WALK_SIDE_SLOW	0.05f
#define SPEED_WALK_ROTATE		0.15f	* 0.3f



/****************************************************************************************************/
void Initialize() {
	Taste[0] = false;	Taste[1] = false;	Taste[2] = false;	Taste[3] = false;
	Taste[4] = false;	Taste[5] = false;	Taste[6] = false;	Taste[7] = false;
	Taste[8] = false;	Taste[9] = false;	Taste[10] = false;	Taste[11] = false;
}


/****************************************************************************************************/
void ProcessKeys(CAMERA2 &in_Camera) {

	// Zerbie Buch Seite 527

	MATRIX4	matRotX, matRotY, matRotZ;
	/*
	Spieler.fRotX = 0.f;
	Spieler.fRotY = 0.f;
	Spieler.fRotZ = 0.f;
	*/
	//Spieler.Kamera.ResetRotation();

	// not implemented yet
	if(Taste[AK_HOCH]) {
		in_Camera.RotateObjectX(SPEED_WALK_ROTATE);
	} else if(Taste[AK_RUNTER]) {
		in_Camera.RotateObjectX(-SPEED_WALK_ROTATE);
	}

	if(!Taste[AK_STRAFE]) {
		if(Taste[AK_LINKS]) {
			in_Camera.RotateObjectY(-SPEED_WALK_ROTATE);
		} else if(Taste[AK_RECHTS]) {
			in_Camera.RotateObjectY(SPEED_WALK_ROTATE);
		}
	}

	if(Taste[AK_ROLLLINKS]) {
		in_Camera.RotateObjectZ(SPEED_WALK_ROTATE);
	} else if(Taste[AK_ROLLRECHTS]) {
		in_Camera.RotateObjectZ(-SPEED_WALK_ROTATE);
	}

	//Spieler.Kamera.ToRotate();

	float Movement = 0;
	if(Taste[AK_VOR]) {
		Movement = SPEED_WALK_FWD;
		if(Taste[AK_SLOW]) Movement = SPEED_WALK_FWD_SLOW;
	} else if(Taste[AK_ZURUECK]) {
		Movement = -SPEED_WALK_FWD;
		if(Taste[AK_SLOW]) Movement = -SPEED_WALK_FWD_SLOW;
	}

	float XMovement = 0;
	if(Taste[AK_STRAFE]) {
		if(Taste[AK_LINKS]) {
			XMovement = -SPEED_WALK_SIDE;
			if(Taste[AK_SLOW]) XMovement = -SPEED_WALK_SIDE_SLOW;
		} else if(Taste[AK_RECHTS]) {
			XMovement = SPEED_WALK_SIDE;
			if(Taste[AK_SLOW]) XMovement = SPEED_WALK_SIDE_SLOW;
		}
	}

	in_Camera.TranslateObjectZ(Movement);
	in_Camera.TranslateObjectX(XMovement);
	//Spieler.Kamera.ToMoveDirection(Movement);
	//Spieler.Kamera.ToMoveRight(XMovement);

}



/****************************************************************************************************/
void SpielerBewegen(CAMERA2 &in_Camera) {
	ProcessKeys(in_Camera);
	//Spieler.Kamera.ViewMatrixSetzen(inDevice);
	//in_Camera.SetViewMatrix();
}



/****************************************************************************************************/
void DIGetKeys(LPDIRECTINPUTDEVICE8 Keyboard) {
    #define KEYDOWN(key) (buffer[key] & 0x80)
 
    char     buffer[256]; 
    HRESULT  hr; 
 
    hr = Keyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr) { 
         return; 
    } 
 
	if (KEYDOWN(DIK_UP))
		Taste[AK_VOR] = true;
	else
		Taste[AK_VOR] = false;

	if (KEYDOWN(DIK_DOWN))
		Taste[AK_ZURUECK] = true;
	else
		Taste[AK_ZURUECK] = false;

	if (KEYDOWN(DIK_LEFT))
		Taste[AK_LINKS] = true;
	else
		Taste[AK_LINKS] = false;

	if (KEYDOWN(DIK_RIGHT))
		Taste[AK_RECHTS] = true;
	else
		Taste[AK_RECHTS] = false;

	if (KEYDOWN(DIK_BACK))
		Taste[AK_STOP] = true;
	else
		Taste[AK_STOP] = false;

	if (KEYDOWN(DIK_ESCAPE))
		Taste[AK_BEENDEN] = true;
	else
		Taste[AK_BEENDEN] = false;

	if (KEYDOWN(DIK_LSHIFT))
		Taste[AK_SLOW] = true;
	else
		Taste[AK_SLOW] = false;

	if (KEYDOWN(DIK_LALT))
		Taste[AK_STRAFE] = true;
	else
		Taste[AK_STRAFE] = false;

	if (KEYDOWN(DIK_DELETE))
		Taste[AK_ROLLLINKS] = true;
	else
		Taste[AK_ROLLLINKS] = false;

	if (KEYDOWN(DIK_PGDN))
		Taste[AK_ROLLRECHTS] = true;
	else
		Taste[AK_ROLLRECHTS] = false;
}