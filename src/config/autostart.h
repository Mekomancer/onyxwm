// List of applications to autostart
// List arguments and then end with a null
// increase the number if arguments go over 4
static char *autostart_list[][4] = {
	{"st", NULL},
	{"picom", NULL},
	{"xwallpaper","--zoom", "/home/void/.config/wallpaper", NULL},
	{"xbanish", NULL},
	{NULL} // end list
};

