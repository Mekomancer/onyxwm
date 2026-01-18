// argument for functions in the keybind table
typedef union {
	int i;
	unsigned int ui;
	float f;
	const void *v;
} arg_t;

// keybinding in the keybinding table
typedef struct {
	uint16_t mod; // moddifer key eg. MOD_MASK_SUPER
	xcb_keysym_t keysym; // key pressed
	void (*func)(arg_t); // keybinding function
	arg_t arg; // argument for function
} keybinding_t;



#define MOD MOD_MASK_SUPER

// List of applications to autostart
// List arguments and then end with a null
static const char *const autostart[] = {
	"st", NULL,
	"picom", NULL,
	"xwallpaper","--zoom", "/home/void/.config/wallpaper", NULL,
	"xbanish", NULL,
	NULL /* terminate */
};

// keybinding table, intended to modified
// modifier key, key, function, argument
static const keybinding_t keys[] = {
	{MOD,        XK_Escape,        exitWM, {0}}, 
}
