#include <xcb/xcb.h>      // XCB core header
#include <xcb/xcb_keysyms.h> // XCB helper for key symbol handling (optional here)
#include <xcb/xproto.h>   // X protocol types and constants (MapRequest, KeyPress, etc.)
#include <xcb/xcb_event.h> // Event helpers
#include <stdio.h>        // printf, fprintf
#include <stdlib.h>       // exit, free
#include <unistd.h>       // fork, execlp
#include <sys/types.h>    // pid_t

static xcb_connection_t * dpy;
static xcb_screen_t * scre;

// spawn program
// char **program is an array of arguments for the program ending in null
void spawn(char **program) {
	if (fork() == 0) { //fork and continue if the program is the child
		// Child process
		setsid(); // Start a new session (detach from controlling terminal)
		execvp((char*)program[0], (char**)program); // Replace process image with program
		_exit(0); //Exit once the process is over
	}
	// Parent process does nothing; child runs the program
}

//handle events, duh
static int eventHandler(void){	
	xcb_generic_event_t *ev;
	while ((ev = xcb_wait_for_event(dpy))) {
		// Use the response type (masked off the highest bit) to determine the event
		switch (ev->response_type & ~0x80) {
			// Handle new window mapping requests
			case XCB_MAP_REQUEST: {
				// Cast the generic event to a map request event
				xcb_map_request_event_t *e = (xcb_map_request_event_t *)ev;
				// Map (show) the requested window
				xcb_map_window(dpy, e->window);
				// Flush to make sure the window is displayed
				xcb_flush(dpy);
				break;
			}
			case XCB_KEY_PRESS: {                 // Handle key presses (hotkeys)
				// Emergency exit: Ctrl+Alt+Escape
				xcb_key_press_event_t *kp = (xcb_key_press_event_t *)ev; // Cast to key press event
				if ((kp->state & (XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1)) && kp->detail == 9) { // Check modifiers and Escape key
				    free(ev);                      // Free event memory
				    xcb_disconnect(dpy);          // Disconnect from X server
				    return 0;                      // Exit safely
				}
				break;
			}

			// Handle destroy notify events (not required here, but placeholder for future)
			case XCB_DESTROY_NOTIFY: {
				// Could add cleanup logic here if needed
				break;
			}
		}

		// Free the event memory after handling it
		free(ev);
	}
	return 0;
}

int main(void) {
	int ret = 0;
	int screen_number; // Will be set to the screen number we're using
	// Connect to the default display
	dpy = xcb_connect(NULL, &screen_number);
	// Check if the connection has an error
	if (xcb_connection_has_error(dpy)) {
		fprintf(stderr, "Failed to connect to X server\n");
		return 1;
	} 

	//get setup info
	const xcb_setup_t *setup = xcb_get_setup(dpy);
	// Iterator over available screens
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	// Advance the iterator to our desired screen
	for (int i = 0; i < screen_number; i++)
		xcb_screen_next(&iter);
	// Get a pointer to the screen
	scre = iter.data;
	// Get the root window of that screen
	xcb_window_t root = scre->root;



	// We must ask to receive SubstructureRedirect events on the root window.
	// Only one client can do this at a time. If this fails, another WM is running.
	uint32_t event_mask = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |
			XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY |
			XCB_EVENT_MASK_KEY_PRESS;
	// Set the event mask on the root window (checked call so we can verify success)
	xcb_void_cookie_t cookie = xcb_change_window_attributes_checked(
		dpy, root, XCB_CW_EVENT_MASK, &event_mask
	);
	// Check if the request failed (i.e., another WM is running)
	xcb_generic_error_t *err = xcb_request_check(dpy, cookie);
	if (err) {
		fprintf(stderr, "Another window manager is already running\n");
		free(err);
		xcb_disconnect(dpy);
		return 1;
	}
	// Flush requests to the X server to ensure they are sent
	xcb_flush(dpy);
	printf("onxyWM is running");



	spawn((char *[]){"st", NULL});



	// Wait for incoming events forever
	ret = eventHandler();
	//exit after event loop is complete
	xcb_disconnect(dpy);
	return ret;
}

