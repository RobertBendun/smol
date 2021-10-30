#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define Message "Hello world from Assembly!"

#define exit(n) \
		asm volatile ( \
				"movq $0, %rdi\n" \
				"movq $60, %rax\n" \
				"syscall\n" \
		)

int main() {
	Display* display = XOpenDisplay(NULL);
	if (display == NULL) {
			exit(1);
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
	Window hello_window = XCreateSimpleWindow(display, parent_window,
																						x,
																						y,
																						width,
																						height,
																						border_width,
																						border_color,
																						background_color);

	long event_mask = ExposureMask | FocusChangeMask;

	// Select window events
	XSelectInput(display, hello_window, event_mask);

	// Make window visible
	XMapWindow(display, hello_window);

	// Set window title
	XStoreName(display, hello_window, "Hello, World!");

	// Get WM_DELETE_WINDOW atom
	Atom wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", True);

	// Subscribe WM_DELETE_WINDOW message
	XSetWMProtocols(display, hello_window, &wm_delete, 1);

	for (_Bool quit = 0; !quit; ) {
		// Get next event from queue
		XEvent event;
		XNextEvent(display, &event);

		switch (event.type) {
		case Expose:
			XClearWindow(display, hello_window);
			XDrawString(display, hello_window, gc, 10, 20, Message, sizeof(Message)-1);
			break;
		case ClientMessage:
			if (event.xclient.data.l[0] == wm_delete)
				quit = 1;
		}
	}

	XCloseDisplay(display);
	exit(0);
}
