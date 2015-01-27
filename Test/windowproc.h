/*******************************************************************
 *					     :: v-scope engine ::
 *							  TESTLAUF
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *   name: windowproc.h
 *   desc: Windowproc/Main
 * 
 ******************************************************************/

/* 
 * name:	WindowProc
 * desc:	Window Procedure des Hauptfensters
 * return:	LRESULT
 */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_KEYDOWN:
			switch(wParam) {
				case VK_ESCAPE:
					g_bRunning=FALSE;
					break;
			}
		case WM_CLOSE:
			return 0L;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0L;
		case WM_SYSCOMMAND:
            if((wParam&0xFFF0)==SC_SCREENSAVE || (wParam&0xFFF0)==SC_MONITORPOWER)
            return 0L;
	}
	return (DefWindowProc(hWnd,msg,wParam,lParam));
}