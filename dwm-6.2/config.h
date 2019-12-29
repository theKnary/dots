/* See LICENSE file for copyright and license deta*/

//includes
#include <X11/XF86keysym.h> // for mediakey codes

/** appearance **/
static const unsigned int snap      = 8;        /* snap pixel */
/* gaps */
static const unsigned int gappx		= 8;		/* gap pixel between windows */
static const int onegap				= 0;		/* 1: diff gappx if one client
													0: no gap if one client */
static const unsigned int onegappx = 100;		/* single window gap px */
/* window border */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int borderalpha		= 0xcc;		/* border alpha for windows */
/* bar */
static const int showtitle			= 0;		/* 0: disable title */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int baralpha			= 0xcc;		/* bar alpha */
static const float titlepos			= 0.25;		/* title position (decimal), */
static const float statuspos		= 0.50;		/* title position (decimal), */
/* dmenu */
static const char dmenulines[]		= "5";		/* number of lines in dmenu */
static const char dmenuwidth[]		= "600";		/* width of dmenu */
/* fonts */
static const char *fonts[]          = { "noto serif:size=8" };
static const char dmenufont[]       = "noto serif:size=12";
/* colours */
static const char col_red[]			= "#a14042"; // foreground
static const char col_dark[]		= "#141414"; // background
static const char col_dim[]			= "#aaaaaa"; // dim text
static const char col_li_dim[]		= "#555555"; // light variant
static const char col_hi[]			= "#f1f1f1"; // bright text

static const char col_blue[]		= "#064575"; // blue
static const char col_green[]		= "#5d9451"; // green

/* themes */
static const char *themes[][5][3]      = {
	[ThemeDefault] =	{
		/*				fg			bg			border */
		// main
		[SchemeNorm] = { col_dim, col_dark, col_li_dim },	// unselected
		[SchemeSel]  = { col_hi, col_red,  col_red },	// selected
		// misc.
		[SchemeTitle] = { col_hi, col_dark, col_red },	// title
		[SchemeStat] = { col_dim, col_dark, col_red },	// status
		[SchemeLts] = { col_dim, col_dark, col_dark },	// layout symbol
	},

	/* fg, bg */
	// red, light
	{
		[SchemeNorm] = { col_li_dim, col_hi, col_li_dim },
		[SchemeSel]  = { col_dark, col_red,  col_red },
		[SchemeTitle] = { col_dark, col_hi, col_red },
		[SchemeStat] = { col_dark, col_hi, col_red },
		[SchemeLts] = { col_li_dim, col_hi, col_hi },
	},
	//// blue, dark
	//{
	//	[SchemeNorm] = { col_dim, col_dark, col_li_dim },
	//	[SchemeSel]  = { col_hi, col_blue,  col_blue },
	//	[SchemeTitle] = { col_hi, col_dark, col_blue },
	//	[SchemeStat] = { col_dim, col_dark, col_blue },
	//	[SchemeLts] = { col_dim, col_dark, col_dark },
	//},
	//// blue, light
	//{
	//	[SchemeNorm] = { col_li_dim, col_hi, col_li_dim },
	//	[SchemeSel]  = { col_dark, col_blue,  col_blue },
	//	[SchemeTitle] = { col_dark, col_hi, col_blue },
	//	[SchemeStat] = { col_dark, col_hi, col_blue },
	//	[SchemeLts] = { col_li_dim, col_hi, col_hi },
	//},
	//// green, dark
	//{
	//	[SchemeNorm] = { col_dim, col_dark, col_li_dim },
	//	[SchemeSel]  = { col_hi, col_green,  col_green },
	//	[SchemeTitle] = { col_hi, col_dark, col_green },
	//	[SchemeStat] = { col_dim, col_dark, col_green },
	//	[SchemeLts] = { col_dim, col_dark, col_dark },
	//},
	//// green, light
	//{
	//	[SchemeNorm] = { col_li_dim, col_hi, col_li_dim },
	//	[SchemeSel]  = { col_dark, col_green,  col_green },
	//	[SchemeTitle] = { col_dark, col_hi, col_green },
	//	[SchemeStat] = { col_dark, col_hi, col_green },
	//	[SchemeLts] = { col_li_dim, col_hi, col_hi },
	//},
};

/* alphas */
static const unsigned alphas[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel] = { OPAQUE, baralpha, OPAQUE },
	[SchemeTitle] = { OPAQUE, baralpha, borderalpha },
	[SchemeStat] = { OPAQUE, baralpha, borderalpha },
	[SchemeLts] = { OPAQUE, baralpha, borderalpha },
};

static char const *colors[LENGTH(themes[0])][LENGTH(themes[0][0])];

/* tagging */
static const char *tags[] = { ">_", "{}", "I", "www", "♪", "#", "ssh", "gui", "bg" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Arduino",     NULL,       NULL,       0,            1,           -1 },
	{ "Conky",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
// changed to 0 because st has gap when = 1
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " [] ",      tile },    /* first entry is default */
	{ " <> ",      NULL },    /* no layout function means floating behavior */
	{ " -_ ",      monocle },
	{ "|||",       col },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
// dmenu
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", dmenulines, "-w", dmenuwidth, "-x", "520", "-y", "300", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dark, "-nf", col_dim, "-sb", col_hi, "-sf", col_dark, NULL };

// terminal
// dark term
static char *term_da_cmd[]  = { "st", "-g", "+500+250", NULL };
// light term
static char *term_li_cmd[]  = { "st", "-g", "+500+250", "-p", NULL };
static char *termcmd[] = {"st", "-g", "+500+250", NULL, NULL};

// scratchpad
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x40", NULL };
// browser
static const char *browser[] = { "tsurf", NULL };
// lock screen
static const char *slock[] = { "slock", NULL };
// power commands
static const char *poweroff[] = { "poweroff", NULL };
static const char *hibernate[] = { "slock", "systemctl", "hibernate", NULL };
// Multimedia keys
static const char *volup[] = { "volup", NULL };
static const char *voldown[] = { "voldown", NULL };
static const char *volmute[] = { "volmute", NULL };
static const char *micmute[] = { "micmute", NULL };
static const char *briup[] = { "xbacklight", "-inc", "10", NULL };
static const char *bridown[] = { "xbacklight", "-dec", "10", NULL };

// keys
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,							XF86XK_AudioRaiseVolume, spawn, {.v = volup } },
	{ 0,							XF86XK_AudioLowerVolume, spawn, {.v = voldown } },
	{ 0,							XF86XK_AudioMute, spawn, {.v = volmute } },
	{ 0,							XF86XK_AudioMicMute, spawn, {.v = micmute } },
	{ 0,							XF86XK_MonBrightnessUp, spawn, {.v = briup } },
	{ 0,							XF86XK_MonBrightnessDown, spawn, {.v = bridown } },
	{ 0,							XF86XK_Launch1,	   spawn,		   {.v = slock } },
	{ MODKEY,						XK_b,      spawn,          {.v = browser } },
	{ MODKEY,						XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,						XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ControlMask,           XK_g,      togglegaps,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,		    XK_k,      incgappx,       {.i = +2 } },
	{ MODKEY|ControlMask,           XK_j,      incgappx,	   {.i = -2 } },
	{ MODKEY|ControlMask,           XK_equal,  incgappx,	   {.i = 0 } },
	{ MODKEY|ControlMask,           XK_s,	   cyclethemes,		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask,             XK_p,      spawn, {.v = poweroff } },
	{ MODKEY|ControlMask|ShiftMask,             XK_h,      spawn, {.v = hibernate } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
