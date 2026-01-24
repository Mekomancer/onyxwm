#pragma once
/** logs a message to stdout and the log file
* @sa logError
* @note uses the same argument syntax as printf
* @param fmt format string 
* @param ... format arguments 
*/
void logMessage(const char *fmt, ...); 
/** logs a message to stderr and the log file
* @sa logMessage()
* @note uses the same argument syntax as printf
* @param fmt format string 
* @param ... format arguments 
*/ 
void logError(const char *fmt, ...); 
