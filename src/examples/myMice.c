#include<stdio.h>
#include<stdbool.h>

struct _win_st
{
	short _cury, _curx; /* current cursor position */

	/* window location and size */
	short _maxy, _maxx; /* maximums of x and y, NOT window size */
	short _begy, _begx; /* screen coords of upper-left-hand corner */

	short   _flags;		/* window state flags */

	/* attribute tracking */
	unsigned _attrs;		/* current attribute for non-space character */
	unsigned  _bkgd;		/* current background char/attribute pair */

	/* option values set by user */
	bool	_notimeout;	/* no time out on function-key entry? */
	bool	_clear;		/* consider all data in the window invalid? */
	bool	_leaveok;	/* OK to not reset cursor on exit? */
	bool	_scroll;	/* OK to scroll this window? */
	bool	_idlok;		/* OK to use insert/delete line? */
	bool	_idcok;		/* OK to use insert/delete char? */
	bool	_immed;		/* window in immed mode? (not yet used) */
	bool	_sync;		/* window in sync mode? */
	bool	_use_keypad;	/* process function keys into KEY_ symbols? */
	int	_delay;		/* 0 = nodelay, <0 = blocking, >0 = delay */

	struct ldat *_line;	/* the actual line data */

	/* global screen state */
	short _regtop;	/* top line of scrolling region */
	short _regbottom; /* bottom line of scrolling region */

	/* these are used only if this is a sub-window */
	int	_parx;		/* x coordinate of this window in parent */
	int	_pary;		/* y coordinate of this window in parent */
	struct _win_st* _parent;	/* pointer to parent if a sub-window */

	/* these are used only if this is a pad */
	struct pdat
	{
	    short _pad_y,      _pad_x;
	    short _pad_top,    _pad_left;
	    short _pad_bottom, _pad_right;
	} _pad;

	short _yoffset; /* real begy is _begy + _yoffset */

    #if NCURSES_WIDECHAR
        cchar_t  _bkgrnd;	/* current background char/attribute pair */
    #if 1
        int	_color;		/* current color-pair for non-space character */
    #endif
    #endif
};

int initscr(void);
int cbreak(void);
int noecho(void);

int keypad(struct _win_st*,bool);

int main()
{
	int initscr();
	int cbreak();
	int noecho();

	// Enables keypad mode. This makes (at least for me) mouse events getting
	// reported as KEY_MOUSE, instead as of random letters.
	keypad(stdscr, TRUE);

	// Don't mask any mouse events
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

	for (;;) { 
		int c = wgetch(stdscr);
		
		if (c == 10) break; // Exit the program on new line fed
	
		char buffer[512];
		size_t max_size = sizeof(buffer);

		if (c == ERR)
			snprintf(buffer, max_size, "Nothing happened.");
		else if (c == KEY_MOUSE)
		{
			MEVENT event;
			if (getmouse(&event) == OK)
				snprintf(buffer, max_size, "X=%d, Y=%d, bstate=0x%08lx", event.x, event.y, event.bstate);
			else
				snprintf(buffer, max_size, "Got bad mouse event.");
		}
		else snprintf(buffer, max_size, "Pressed key %d (%s)", c, keyname(c));
	
		move(0, 0);
		insertln();
		addstr(buffer);
		clrtoeol();
		move(0, 0);
	}
	
	printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

	endwin();
	
	return 0;
}