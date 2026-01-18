#include "../types.h"

// Main modkey, default is super key
#define MOD XCB_MOD_MASK_4
#define SHIFT XCB_MOD_MASK_SHIFT
#define CTRL XCB_MOD_MASK_CONTROL

// keybinding table, intended to modified
// modifier key, key, function, argument
static const keybinding_t keys[] = {
	{MOD|SHIFT, XK_Escape,        quit,        {0}}, 
};
