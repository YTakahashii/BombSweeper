#include "click.h"
#include "DxLib.h"

bool Click::LeftClick()
{
	HWND ahwnd = GetActiveWindow();
	HWND hwnd = GetMainWindowHandle();
	if( ahwnd != hwnd ) return false;
	
	bool leftclick = false;
	
	if( GetMouseInput() & MOUSE_INPUT_LEFT ){
		l_mousepressed = true;
	} else {
		if( l_mousepressed == true ){
			leftclick = true;
		}
		l_mousepressed = false;
	}
	if(leftclick) return true; 
	else return false;
}

bool Click::RightClick()
{
	HWND ahwnd = GetActiveWindow();
	HWND hwnd = GetMainWindowHandle();
	if( ahwnd != hwnd ) return false;

	bool rightclick = false;
	
	if( GetMouseInput() & MOUSE_INPUT_RIGHT ){
		r_mousepressed = true;
	} else {
		if( r_mousepressed == true ){
			rightclick = true;
		}
		
		r_mousepressed = false;
	}
	if(rightclick) return true;
	else return false;
}