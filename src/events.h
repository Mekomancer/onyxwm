/**
 * @file events.h
 * @see events.c
 */
#ifndef EVENTS_H
#define EVENTS_H

#include <xcb/xcb.h>

/**
 * @brief Calls the corresponding handler in event_handlers
 *
 * @param ev The generic event to be handled
 */
void handleEvent(xcb_generic_event_t *ev);

#endif

/* vim:set ft=c:set syn=c.doxygen: */
