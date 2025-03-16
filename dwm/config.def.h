/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showlayout         = 0;        /* 0 means no layout indicator */
static const int iconsize           = 12;       /* icon size */
static const int iconspacing        = 5;        /* space between icon and title */
static const char *fonts[]          = { "Mononoki Nerd Font Propo:style= Bold:size=10" };
static const char dmenufont[]       = { "Mononoki Nerd Font:size=10" };
static const char col_gray1[]       = "#000000";
static const char col_gray3[]       = "#085400";
static const char white[]       	= "#ffffff";
static const char col_cyan[]        = "#04a3bf";
static const char background[]      = "#b05151";
static const char color_1[]      	= "#9c0699";

static const unsigned int ulinepad	    = 0;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 	         	= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const char *colors[][3] = {
	/*               fg(text)         bg           border   */
	[SchemeNorm]   = { white, 		background,    col_gray3 },
	[SchemeSel]    = { white, 		background,    color_1	 },
	[SchemeTitle]  = { white,	    background,    col_gray1 },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "", "", "", "", "" };

static const char *tagsel[][2] = {
	{ "#ffffff", "#7d0202" }, //1
	{ "#ffffff", "#bd4906" }, //2
	{ "#ffffff", "#02356b" }, //3
	{ "#ffffff", "#025402" }, //4
	{ "#ffffff", "#630149" }, //5
};


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Librewolf", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "main",    NULL,     NULL,           0,         0,          0,           1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// MINE //

static int nightlight_on = 0;
static void togglenight(const Arg *arg) { nightlight_on ? system("sct") : system("sct 3000"); nightlight_on ^= 1; }

// MINE //

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", background, "-nf", white, "-sb", col_cyan, "-sf", white, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key                function        argument */

	TAGKEYS(                        XK_1,              0)
	TAGKEYS(                        XK_2,              1)
	TAGKEYS(                        XK_3,              2)
	TAGKEYS(                        XK_4,              3)
	TAGKEYS(                        XK_5,              4)
	{ MODKEY,                       XK_6,              view,           {.ui = ~0 } },

	{ MODKEY,                       XK_q,              spawn,          {.v = dmenucmd } },
	{ MODKEY,		                XK_Return,         spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,              togglebar,      {0} },
	{ MODKEY,                       XK_z,              focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_x,              focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_apostrophe,     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_semicolon,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,              setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,              setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_w, 	           zoom,           {0} },
	{ MODKEY,                       XK_Tab,            view,           {0} },
	{ ALT,             	            XK_F4,             killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_KP_Home,        setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_KP_Up,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_KP_Page_Up,     setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_KP_Left,        setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask,             XK_KP_Begin,       setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,          togglefloating, {0} },
	{ MODKEY|ShiftMask,       		XK_q,              quit,           {0} },

	// MINE //
	{ MODKEY, 	                    XK_n, 		       togglenight,    {0} },
	{ MODKEY,		                XK_s,		       togglesticky,   {0} },
	{ MODKEY,		                XK_a,		       focusmaster,    {0} },
	{ MODKEY,                       XK_F5,    	       spawn,          SHCMD("~/Scripts/brightness.sh 5%-") },
	{ MODKEY|ShiftMask,             XK_F5,    	       spawn,          SHCMD("~/Scripts/brightness.sh 1%-") },
	{ MODKEY,                       XK_F6,     	       spawn,          SHCMD("~/Scripts/brightness.sh 5%+") },
	{ MODKEY|ShiftMask,             XK_F6,     	       spawn,          SHCMD("~/Scripts/brightness.sh 1%+") },
    { ALT,                          XK_F10,    	       spawn,          SHCMD("~/Scripts/volume.sh toggle") },
    { ALT,                          XK_F11,    	       spawn,          SHCMD("~/Scripts/volume.sh 5%-") },
    { ALT|ShiftMask,                XK_F11,    	       spawn,          SHCMD("~/Scripts/volume.sh 1%-") },
    { ALT,                          XK_F12,    	       spawn,          SHCMD("~/Scripts/volume.sh 5%+") },
    { ALT|ShiftMask,                XK_F12,    	       spawn,          SHCMD("~/Scripts/volume.sh 1%+") },
    { ALT|ShiftMask	,               XK_bracketleft,    spawn, 	       SHCMD("poweroff") },
    { ALT|ShiftMask	,               XK_z,      	       spawn,          SHCMD("systemctl suspend") },
    { ALT|ShiftMask	, 		        XK_comma,  	       spawn, 	       SHCMD("reboot") },
    { ALT   ,		                XK_f,     	       spawn,	       SHCMD("librewolf") },
    { ALT|ShiftMask,	           	XK_f,              spawn,	       SHCMD("librewolf --private-window") },
    { ALT   ,		                XK_s,              spawn,	       SHCMD("thunar") },
    { ALT   ,		                XK_e,              spawn,	       SHCMD("emacs") },
    { MODKEY|ShiftMask,             XK_Print,	       spawn,          SHCMD("scrot") },
    { MODKEY|ShiftMask,             XK_k,              spawn,          SHCMD("xkill") },
	// MINE //
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
