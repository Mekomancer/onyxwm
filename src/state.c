/**
 * @file state.c
 * @brief stores program wide variables
 *
 * if deciding which file to put a global is a headache just put it here
 */

#include <xcb/xcb.h>

//connection to xcb
xcb_connection_t *dpy;
//xcb screen
xcb_screen_t *scre;

