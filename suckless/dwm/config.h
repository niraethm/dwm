/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const char *fonts[]          = { "undefined-medium:size=14" };
static const char dmenufont[]       = "undefined-medium:size=14";
static unsigned int baralpha		= 0xd0;
static unsigned int borderalpha		= OPAQUE;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#282a36";
static const char col_green[]		= "#50fa7b";
static const char col_pink[]		= "#ff79c6";
static const char col_purple[]		= "#bd93f9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_pink, col_gray1, col_gray2 },
	[SchemeSel]  = { col_purple, col_gray1,  col_purple},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,        0,            1,           -1 },
	{ NULL,      NULL,     "Event Tester", 0,            0,           -1 },
	
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_purple, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *scrotcmd[] = { "/bin/sh", "-c", "scrot -f '/tmp/clipboard.png' -o -s -e 'xclip -selection clipboard -t image/png -i $f'", NULL};
static const char *volupcmd[] = { "wpctl", "set-volume", "@DEFAULT_SINK@", "5%+", NULL };
static const char *voldowncmd[] = { "wpctl", "set-volume", "@DEFAULT_SINK@","5%-", NULL };
static const char *volmutecmd[] = { "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key         function            argument */
	{ MODKEY,                       XK_d,       spawn,              {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,  spawn,              {.v = termcmd } },
    { 0,                            XK_Print,   spawn,              {.v = scrotcmd } },
    { MODKEY,                       XK_F8,      spawn,              {.v = volmutecmd } },
    { MODKEY,                       XK_F9,      spawn,              {.v = voldowncmd } },
    { MODKEY,                       XK_F10,     spawn,              {.v = volupcmd } },
	{ MODKEY,                       XK_b,       togglebar,          {0} },
	{ MODKEY,                       XK_j,       focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,         {.i = -1 } },
	{ MODKEY,                       XK_u,       incnmaster,         {.i = +1 } },
	{ MODKEY,                       XK_i,       incnmaster,         {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,           {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,           {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,  zoom,               {0} },
	{ MODKEY,                       XK_Tab,     view,               {0} },
	{ MODKEY,                       XK_q,       killclient,         {0} },
	{ MODKEY,                       XK_t,       setlayout,          {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,       setlayout,          {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,       setlayout,          {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,   setlayout,          {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating,     {0} },
	{ MODKEY,                       XK_0,       view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,                {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,           {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,             {.i = +1 } },
	{ MODKEY,                       XK_minus,   setgaps,            {.i = -1 } },
	{ MODKEY,                       XK_equal,   setgaps,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,   setgaps,            {.i = 0  } },
    { MODKEY|ShiftMask,             XK_f,       togglefullscr,      {0} },
	TAGKEYS(                        XK_1,                           0)
	TAGKEYS(                        XK_2,                           1)
	TAGKEYS(                        XK_3,                           2)
	TAGKEYS(                        XK_4,                           3)
	TAGKEYS(                        XK_5,                           4)
	TAGKEYS(                        XK_6,                           5)
	TAGKEYS(                        XK_7,                           6)
	TAGKEYS(                        XK_8,                           7)
	TAGKEYS(                        XK_9,                           8)
	{ MODKEY|ShiftMask,             XK_q,	    quit,		        {0} },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
    { 0,                            XF86XK_AudioMute, spawn,        {.v = volmutecmd } },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};