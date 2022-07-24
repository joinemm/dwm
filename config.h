/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static unsigned int borderpx    = 3;        /* border pixel of windows */
static unsigned int snap        = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;  /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;             /* 0 means no systray */
static unsigned int gappih      = 10;       /* horiz inner gap between windows */
static unsigned int gappiv      = 10;       /* vert inner gap between windows */
static unsigned int gappoh      = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov      = 10;       /* vert outer gap between windows and screen edge */
static int swallowfloating      = 0;        /* 1 means swallow floating windows by default */
static int smartgaps            = 1;        /* 1 means no outer gap when there is only one window */
static int showbar              = 1;        /* 0 means no bar */
static int topbar               = 1;        /* 0 means bottom bar */
static char *fonts[]            = {
	"monospace:size=12",
	"Twemoji:size=12",
	"Feather Icons:size=12",
};
static char normbgcolor[]		= "#222222";
static char normbordercolor[]   = "#444444";
static char normfgcolor[]       = "#bbbbbb";
static char selfgcolor[]        = "#eeeeee";
static char selbordercolor[]    = "#770000";
static char selbgcolor[]        = "#005577";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "--class=FloatingTerminal,FloatingTerminal", NULL };
static Sp scratchpads[] = {
	/* name         cmd  */
	{"spterm",      spcmd1},
};

/* staticstatus */
static const int statmonval = 0;

/* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int user_bh = 32;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class		instance	title		tags mask	iscentered	isfloating	isterminal  noswallow  monitor */
	{ "Steam",		NULL,       NULL,		0,          1,          1,          -1 },
	{ "Steam",		NULL,       "Steam",	0,          0,          0,          -1 },
	{ "Peek",		NULL,		"Peek",     0,          1,          1,          -1 },
	{ "FloatingTerminal",NULL,	NULL,		0,          1,          1,          1 },
};

/* layout(s) */
static float mfact     = 0.5;	/* factor of master area size [0.05..0.95] */
static int nmaster     = 1;		/* number of clients in master area */
static int resizehints = 1;		/* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 0			/* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* first layout is the default */
static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[]=",	tile },						/* Default: Master on left, slaves on right */
	{ "[B]",	bstack },					/* Master on top, slaves on bottom */

	{ "[@]",	spiral },					/* Fibonacci spiral */
	{ "[\\]",	dwindle },					/* Decreasing in size right and leftward */

	{ "[D]",	deck },						/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },					/* All windows on top of eachother */

	{ "[|M|]",	centeredmaster },			/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same as centeredmaster but master floats */

	{ "><>",	NULL },                     /* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/* Xresources to load at startup */
ResourcePref resources[] = {
	{ "bordercolor",	STRING,	 &normbordercolor },
	{ "selbordercolor",	STRING,	 &selbordercolor },
	{ "background",		STRING,	 &normbgcolor },
	{ "foreground",		STRING,	 &normfgcolor },
	{ "foreground",		STRING,	 &selfgcolor },
	{ "selbgcolor",		STRING,  &selbgcolor },
	{ "borderpx",		INTEGER, &borderpx },
	{ "snap",			INTEGER, &snap },
	{ "showbar",		INTEGER, &showbar },
	{ "topbar",			INTEGER, &topbar },
	{ "nmaster",		INTEGER, &nmaster },
	{ "resizehints",	INTEGER, &resizehints },
	{ "mfact",			FLOAT,	 &mfact },
	{ "gappih",			INTEGER, &gappih },
	{ "gappiv",			INTEGER, &gappiv },
	{ "gappoh",			INTEGER, &gappoh },
	{ "gappov",			INTEGER, &gappov },
	{ "swallowfloating",INTEGER, &swallowfloating },
	{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier             key				    function        argument */
	STACKKEYS(MODKEY,                           focus)
	STACKKEYS(MODKEY|ShiftMask,                 push)
	TAGKEYS(			    XK_1,		        0)
	TAGKEYS(			    XK_2,		        1)
	TAGKEYS(			    XK_3,		        2)
	TAGKEYS(			    XK_4,		        3)
	TAGKEYS(			    XK_5,		        4)
	TAGKEYS(			    XK_6,		        5)
	TAGKEYS(			    XK_7,		        6)
	TAGKEYS(			    XK_8,		        7)
	TAGKEYS(			    XK_9,		        8)
	{ MODKEY,				XK_0,			    view,			{.ui = ~0 } },
	{ MODKEY,				XK_q,			    killclient,		{0} },
	{ MODKEY|ShiftMask,		XK_q,			    quit,			{0} },
	{ MODKEY,				XK_w,			    spawn,			SHCMD("gtk-lauch $(xdg-settings get default-web-browser)") },
	{ MODKEY|ShiftMask,		XK_w,			    spawn,			SHCMD("rofi-wifi") },
	{ MODKEY,				XK_e,			    spawn,			SHCMD("rofimoji") },
	{ MODKEY,				XK_r,			    spawn,			SHCMD(TERMINAL " -e lfub") },
	{ MODKEY|ShiftMask,		XK_r,			    spawn,			SHCMD("nemo") },
	{ MODKEY,				XK_space,		    spawn,          SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,		XK_s,				spawn,          SHCMD("flameshot gui") },
	{ 0,					XK_Print,			spawn,          SHCMD("flameshot gui") },
	{ MODKEY,				XK_o,				spawn,          SHCMD("toggle-kb-layout us fi") },
	{ MODKEY,				XK_p,				spawn,          SHCMD("rofi-screencast") },
	{ MODKEY|ShiftMask,		XK_p,				spawn,          SHCMD("rofi-screencast -s") },
	{ MODKEY,				XK_c,				spawn,          SHCMD("color") },
	{ MODKEY,				XK_b,				spawn,          SHCMD("rofi-bluetooth") },
	{ MODKEY,				XK_l,				spawn,          SHCMD("betterlockscreen -l") },
	{ MODKEY,				XK_slash,			spawn,          SHCMD("playerctl play-pause") },
	{ MODKEY,				XK_minus,			spawn,          SHCMD("playerctl play-pause") },
	{ MODKEY,				XK_comma,			spawn,          SHCMD("playerctl previous") },
	{ MODKEY,				XK_period,			spawn,          SHCMD("playerctl next") },
	{ 0,                    XF86XK_AudioPlay,	spawn,			SHCMD("playerctl play-pause") },
	{ 0,					XF86XK_AudioPrev,   spawn,			SHCMD("playerctl previous") },
	{ 0,                    XF86XK_AudioNext,	spawn,			SHCMD("playerctl next") },
	{ 0,                    XF86XK_AudioMute,	spawn,			SHCMD("audio-control mute") },
	{ 0,                    XF86XK_AudioRaiseVolume,	spawn,	SHCMD("audio-control up 1%") },
	{ 0,                    XF86XK_AudioLowerVolume,	spawn,	SHCMD("audio-control down 1%") },
	{ 0,					XF86XK_MonBrightnessUp,		spawn,	SHCMD("sudo light -Ar 15; pkill -RTMIN+11 dwmblocks") },
	{ 0,					XF86XK_MonBrightnessDown,	spawn,	SHCMD("sudo light -Ur 15; pkill -RTMIN+11 dwmblocks") },
	{ 0,					XF86XK_Calculator,	spawn,	        SHCMD("rofi -show calc -modi calc -no-show-match -no-sort") },
	{ MODKEY,				XK_BackSpace,		spawn,			SHCMD("rofi-power") },
	{ MODKEY,				XK_t,			    setlayout,		{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,			    setlayout,		{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,				XK_y,			    setlayout,		{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,			    setlayout,		{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,				XK_u,			    setlayout,		{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,			    setlayout,		{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,				XK_i,			    setlayout,		{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,			    setlayout,		{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|ShiftMask,		XK_o,			    setlayout,		{.v = &layouts[8]} }, /* floating */
	{ MODKEY,				XK_m,			    incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_m,			    incnmaster,     {.i = -1 } },
	{ MODKEY,				XK_g,			    togglegaps,		{0} },
	{ MODKEY|ShiftMask,		XK_g,			    defaultgaps,	{0} },
	{ MODKEY,				XK_s,			    togglesticky,	{0} },
	{ MODKEY|ShiftMask,		XK_h,			    setmfact,		{.f = -0.05} },
	{ MODKEY|ShiftMask,		XK_l,			    setmfact,		{.f = +0.05} },
	{ MODKEY,				XK_f,			    zoom,			{0} },
	{ MODKEY|ShiftMask,		XK_f,			    togglefullscr,	{0} },
	{ MODKEY,				XK_Tab,			    view,			{0} },
	{ MODKEY,				XK_semicolon,	    shiftview,		{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,	    shifttag,		{ .i = 1 } },
	{ MODKEY,				XK_apostrophe,	    shiftview,		{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_apostrophe,	    shifttag,		{ .i = -1 } },
	{ MODKEY,				XK_Return,		    spawn,			{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,		    togglescratch,	{.ui = 0 } },
	{ MODKEY,				XK_z,			    incrgaps,		{.i = +3 } },
	{ MODKEY,				XK_x,			    incrgaps,		{.i = -3 } },
	{ MODKEY|ShiftMask,		XK_b,			    togglebar,		{0} },
	{ MODKEY,				XK_bracketleft,	    focusmon,		{.i = -1 } },
	{ MODKEY,				XK_bracketright,    focusmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_bracketleft,	    tagmon,			{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_bracketright,    tagmon,			{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_space,		    togglefloating,	{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,			MODKEY,			Button4,		incrgaps,		{.i = +1} },
	{ ClkClientWin,			MODKEY,			Button5,		incrgaps,		{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,			0,				Button4,		shiftview,		{.i = -1} },
	{ ClkTagBar,			0,				Button5,		shiftview,		{.i = 1} },
};
