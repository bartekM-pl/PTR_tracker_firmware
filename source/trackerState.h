#ifndef __TRACKERSTATE_H
#define __TRACKERSTATE_H

typedef enum {
	STARTUP = 0,
	WAIT_FOR_FIX = 1,
	OPERATION = 5
} trackerState;

#endif
