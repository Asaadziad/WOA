#include <X11/X.h>
#include <iostream>
#include <X11/Xlib.h>

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
			switch (event.xkey.keycode) {
				case 9:
				running = false;
				break;
			}	
			}
		}
	}

	XDestroyWindow(display, w);
	XCloseDisplay(display);
	return 0;

}
