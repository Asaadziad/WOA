#include <X11/X.h>
#include <X11/XKBlib.h>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>

int main(){

	Display* display = XOpenDisplay(NULL);
	if(!display){
		std::cout << "error?";
		exit(1);
	}
	int screen = XDefaultScreen(display);
	Window w = XCreateSimpleWindow(display, RootWindow(display,screen), 0, 0, 960, 540, 1 ,BlackPixel(display,screen), WhitePixel(display,screen));
	
	XEvent event;
	XSelectInput(display, w, KeyPressMask);
 	XMapWindow(display, w);
	bool running = true;
	while(running){
		if(XPending(display)){
			XNextEvent(display, &event);
			if(event.type == KeyPress){
			//TODO:: find a way to deal with key presses without hardcoding it gkdsljjkldgjslk			
			switch (event.xkey.keycode) {
				case 0x09:
				running = false;
				break;
			
			default:break;
			}	
			}
		}
	}

	XDestroyWindow(display, w);
	XCloseDisplay(display);
	return 0;

}
