/**
 * @file actions.h
 * @see actions.c
 */

#ifndef ACTIONS_H
#define ACTIONS_H

#include "types.h"

/**
 * @brief Wrapper for exitWM()
 * @see exitWM()
 *
 * @param arg Unused
 */
void quit(const arg_t *arg);

/**
 * @brief Wrapper for spawn()
 *
 * @param arg Argument list for program starting with name and ending in NULL
 */
void spawnAct(const arg_t *arg);

#endif

/* vim:set ft=c:set syn=c.doxygen: */
