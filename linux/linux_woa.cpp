#include <X11/X.h>
#include <X11/XKBlib.h>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>

#define internal static
#define local_var static


int main(){

	Display* display = XOpenDisplay(NULL);
	if(!display){
		std::cout << "error?";
		exit(1);
	}
	int screen = XDefaultScreen(display);
	Window w = XCreateSimpleWindow(display,
								RootWindow(display,screen),
								0, 0,
								960, 540,
								0 ,
								0,
								0);

	Atom wm_delete_window = XInternAtom(display,"WM_DELETE_WINDOW",False);
	XSetWMProtocols(display,w, &wm_delete_window,1);
 	XSelectInput(display, w, KeyPressMask);
 	XMapWindow(display, w);
	local_var bool running = true;
	while(running){
	XEvent event = {0};
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
			if(event.type == ClientMessage){
    	        
        if((Atom)event.xclient.data.l[0] == wm_delete_window){
					running = false;
				}  
      
      }
		
			
		}

	}

	XCloseDisplay(display);
	return 0;

}
