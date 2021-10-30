#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <dlfcn.h>

#define Message "Hello world from Assembly!"

#define load(lib, L, F) \
	decltype(& F) const L = (decltype(& F))dlsym(lib, #F)
extern "C" char* __cxa_demangle(const char* mangled_name, char* buf, size_t* n, int* status) {
if (status)
*status = -1;
return nullptr;
}

int main() {
	void *x11 = dlopen("libX11.so", RTLD_LAZY);
	load(x11, open_display, XOpenDisplay);
	load(x11, create_window, XCreateSimpleWindow);
	load(x11, select_input, XSelectInput);
	load(x11, map_window, XMapWindow);
	load(x11, store_name, XStoreName);
	load(x11, intern_atom, XInternAtom);
	load(x11, set_wm_protocols, XSetWMProtocols);
	load(x11, next_event, XNextEvent);
	load(x11, clear_window, XClearWindow);
	load(x11, draw_string, XDrawString);
	load(x11, close_display, XCloseDisplay);

	Display* display = open_display(NULL);
	if (display == NULL) {
		return 1;
	}

	int screen = DefaultScreen(display);

	GC gc = DefaultGC(display, screen);

	Window parent_window = DefaultRootWindow(display);

	int x = 0;
	int y = 0;

	unsigned int width = 400;
	unsigned int height = 40;

	unsigned int border_width = 1;

	unsigned int border_color = BlackPixel(display, screen);
	unsigned int background_color = WhitePixel(display, screen);

	// Create window
	Window hello_window = create_window(display, parent_window,
																						x,
																						y,
																						width,
																						height,
																						border_width,
																						border_color,
																						background_color);

	long event_mask = ExposureMask | FocusChangeMask;

	// Select window events
	select_input(display, hello_window, event_mask);

	// Make window visible
	map_window(display, hello_window);

	// Set window title
	store_name(display, hello_window, "Hello, World!");

	// Get WM_DELETE_WINDOW atom
	Atom wm_delete = intern_atom(display, "WM_DELETE_WINDOW", True);

	// Subscribe WM_DELETE_WINDOW message
	set_wm_protocols(display, hello_window, &wm_delete, 1);

	for (bool quit = 0; !quit; ) {
		// Get next event from queue
		XEvent event;
		next_event(display, &event);

		switch (event.type) {
		case Expose:
			clear_window(display, hello_window);
			draw_string(display, hello_window, gc, 10, 20, Message, sizeof(Message)-1);
			break;
		case ClientMessage:
			if (event.xclient.data.l[0] == wm_delete)
				quit = 1;
		}
	}

	close_display(display);
}
