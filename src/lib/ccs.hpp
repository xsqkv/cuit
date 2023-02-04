#include<iostream>
#include<string.h>

//	Console Control Sequences

//	console_codes(4) — Linux manual page\
	https://man7.org/linux/man-pages/man4/console_codes.4.html

/*
	Copyright for console_codes.4:

	Copyright (c) 1996 Andries Brouwer <aeb@cwi.nl>, Mon Oct 31 22:13:04 1996
	License for console_codes.4:

	This is free documentation; you can redistribute it and/or
	modify it under the terms of the GNU General Public License as
	published by the Free Software Foundation; either version 2 of
	the License, or (at your option) any later version.
*/

/*
	Writen by Artem Vanty <25.01.2023>

	License - MIT
*/

#pragma once

template <typename T, typename U>
char* multicat(T a, U b) // for single param func
{
    return strcat(a,b);
}

template <typename T, typename U, typename... Targs>
char* multicat(T a, U b, Targs... Fargs) // recursive variadic function
{
    strcat(a,b);
    return multicat(a,Fargs...); // recursive call
}

namespace ccs
{
	#pragma region Name

	// console_codes - Linux console escape and control sequences

	#pragma endregion

	#pragma region Description

		/*	Description

			The Linux console implements a large subset of the VT102 and
			ECMA-48/ISO 6429/ANSI X3.64 terminal controls, plus certain
			private-mode sequences for changing the color palette, character-
			set mapping, and so on.  In the tabular descriptions below, the
			second column gives ECMA-48 or DEC mnemonics (the latter if
			prefixed with DEC) for the given function.  Sequences without a
			mnemonic are neither ECMA-48 nor VT102.

			After all the normal output processing has been done, and a
			stream of characters arrives at the console driver for actual
			printing, the first thing that happens is a translation from the
			code used for processing to the code used for printing.

			If the console is in UTF-8 mode, then the incoming bytes are
			first assembled into 16-bit Unicode codes.  Otherwise, each byte
			is transformed according to the current mapping table (which
			translates it to a Unicode value).  See the Character Sets
			section below for discussion.

			In the normal case, the Unicode value is converted to a font
			index, and this is stored in video memory, so that the
			corresponding glyph (as found in video ROM) appears on the
			screen.  Note that the use of Unicode (and the design of the PC
			hardware) allows us to use 512 different glyphs simultaneously.

			If the current Unicode value is a control character, or we are
			currently processing an escape sequence, the value will treated
			specially.  Instead of being turned into a font index and
			rendered as a glyph, it may trigger cursor movement or other
			control functions.  See the Linux Console Controls section below
			for discussion.

			It is generally not good practice to hard-wire terminal controls
			into programs.  Linux supports a terminfo(5) database of terminal
			capabilities.  Rather than emitting console escape sequences by
			hand, you will almost always want to use a terminfo-aware screen
			library or utility such as ncurses(3), tput(1), or reset(1).
		*/

		#pragma region Linux console controls

			/*  Linux console controls

				This section describes all the control characters and escape
				sequences that invoke special functions (i.e., anything other
				than writing a glyph at the current cursor location) on the Linux
				console.
			*/

			#pragma region Control Characters

				// Control characters

				// Starts an escape sequence
				constexpr const char ESC[] = "\e";

				// Control sequence introducer. Is equivalent to ESC [
				constexpr const char CSI[] = "\e[";
				
				// Beeps
				constexpr const char BEL[] = "\eG";

				// Backspaces one column (but not past the beginning of the line)
				constexpr const char BS[] = "\eH";

				// Goes to the next tab stop or to the end of the line if there is no earlier tab stop
				constexpr const char HT[] = "\eI";

				// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
				constexpr const char LF[] = "\eJ";

				// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
				constexpr const char VT[] = "\eK";

				// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
				constexpr const char FF[] = "\eL";

				// Gives a carriage return
				constexpr const char CR[] = "\eM";

				// Activates the G1 character set
				constexpr const char SO[] = "\eN";

				// Activates the G0 character set
				constexpr const char SI[] = "\eO";

				// Abort escape sequences
				constexpr const char CAN[] = "\eX";

				// Abort escape sequences
				constexpr const char SUB[] = "\eZ";

			#pragma endregion

			#pragma region Esc-Sequences

				// ESC- but not CSI-sequences

				// Reset.
				constexpr const char RIS[] = "\ec";

				// Linefeed.
				constexpr const char IND[] = "\eD";

				// Newline.
				constexpr const char NEL[] = "\eE";

				// Set tab stop at current column.
				constexpr const char HTS[] = "\eH";

				// Reverse linefeed.
				constexpr const char RI[] = "\eM";

				// DEC private identification. The kernel returns the string  ESC [ ? 6 c, claiming that it is a VT102.
				constexpr const char DECID[] = "\eZ";

				// Save current state (cursor coordinates, attributes, character sets pointed at by G0,  G1).
				constexpr const char DECSC[] = "\e7";

				// Restore state most recently saved by ESC 7.
				constexpr const char DECRC[] = "\e8";


				// Start sequence selecting character set
				constexpr const char SSSCS[] = "\e[%";

				// Select default (ISO 646 / ISO 8859-1)
				constexpr const char SELDEF[] = "\e[%@";

				// Select UTF-8
				constexpr const char SELUTF8[] = "\e[%G";

				// Select UTF-8 (obsolete)
				constexpr const char SELUTFO[] = "\e[%8";


				// DEC screen alignment test - fill screen with Es
				constexpr const char DECALN[] = "\e#8";


				// Start sequence defining G0 character set (followed by one of B, 0, U, K, as below)
				constexpr const char SSDG0[] = "\e(";

				// Select default (ISO 8859-1 mapping)
				constexpr const char SD0[] = "\e(B";

				// Select VT100 graphics mapping
				constexpr const char SVT0100[] = "\e(0";

				// Select null mapping - straight to character ROM
				constexpr const char SNM0[] = "\e(U";

				// Select user mapping - the map that is loaded by the utility mapscrn(8)
				constexpr const char SUM0[] = "\e(K";


				// Start sequence defining G1 (followed by one of B, 0, U, K, as above).
				constexpr const char SSDG1[] =  "\e)";

				// Select default (ISO 8859-1 mapping)
				constexpr const char SD1[] = "\e)B";

				// Select VT100 graphics mapping
				constexpr const char SVT1100[] = "\e)0";

				// Select null mapping - straight to character ROM
				constexpr const char SNM1[] = "\e)U";

				// Select user mapping - the map that is loaded by the utility mapscrn(8)
				constexpr const char SUM1[] = "\e)K";


				// Set numeric keypad mode
				constexpr const char DECPNM[] =  "\e>";

				// Set application keypad mode
				constexpr const char DECPAM[] =  "\e=";

				char OSC_OUT[16];

				/*
					(Should be: Operating system command) ESC ] P
					nrrggbb: set palette, with parameter given in
					7 hexadecimal digits after the final P :-(.
					Here n is the color (0–15), and rrggbb
					indicates the red/green/blue values (0–255).
					ESC ] R: reset palette
				*/
				char* OSC(const char * palette)
				{
					return multicat(OSC_OUT,"\e]P", palette, "P");
				}

				constexpr const char RSTPALETTE[] = "\e]R";

			#pragma endregion

			#pragma region Csi-Sequences

				// ECMA-48 CSI sequences

				char ICH_OUT[8];

				// Insert the indicated # of blank characters.
				char* ICH(const char * n) { return multicat(ICH_OUT,"\e[", n, "@"); }

				char CUU_OUT[8];

				// Move cursor up the indicated # of rows.
				char* CUU(const char * n) { return multicat(CUU_OUT,"\e[", n, "A"); }

				char CUD_OUT[8];

				// Move cursor down the indicated # of rows.
				char* CUD(const char * n) { return multicat(CUD_OUT,"\e[", n, "B"); }

				char CUF_OUT[8];

				// Move cursor right the indicated # of columns.
				char* CUF(const char * n) { return multicat(CUD_OUT,"\e[", n, "C"); }

				char CUB_OUT[8];

				// Move cursor left the indicated # of columns.
				char* CUB(const char * n) { return multicat(CUB_OUT,"\e[", n, "D"); }

				char CNL_OUT[8];

				// Move cursor down the indicated # of rows, to column 1.
				char* CNL(const char * n) { return multicat(CNL_OUT,"\e[", n, "E"); }

				char CPL_OUT[8];

				// Move cursor up the indicated # of rows, to column 1.
				char* CPL(const char * n) { return multicat(CPL_OUT,"\e[", n, "F"); }

				char CHA_OUT[8];

				// Move cursor to indicated column in current row.
				char* CHA(const char * n) { return multicat(CHA_OUT,"\e[", n, "G"); }

				char CUP_OUT[8];

				// Move cursor to the indicated row, column (origin at 1,1).
				char* CUP(const char * x, const char * y) { return multicat(CUP_OUT,"\e[", y, ";", x, "H"); }

				char ED_OUT[8];

				// Erase display (default: from cursor to end of display).
				char* ED() { return multicat(ED_OUT,"\e[J"); }

				/*	1 - erase from start to cursor.
					2 - erase whole display.
					3 - erase whole display including scroll-back buffer (since Linux 3.0).	*/
				char* ED(const char * n) { return multicat(ED_OUT,"\e[", n, "J"); }

				char EL_OUT[8];

				// Erase line (default: from cursor to end of line).
				char* EL() { return multicat(EL_OUT,"\e[K"); } 

				/*1 - erase from start of line to cursor.
				  2 - erase whole line.*/
				char* EL(const char * n) { return multicat(EL_OUT,"\e[", n, "K"); }

				char IL_OUT[8];

				// Insert the indicated # of blank lines.
				char* IL(const char * n) { return multicat(IL_OUT,"\e[", n, "L"); }

				char DL_OUT[8];

				// Delete the indicated # of lines.
				char* DL(const char * n) { return multicat(DL_OUT,"\e[", n, "M"); }

				char DCH_OUT[8];

				// Delete the indicated # of characters on current line.
				char* DCH(const char * n) { return multicat(DCH_OUT,"\e[", n, "P"); }

				char ECH_OUT[8];

				// Erase the indicated # of characters on current line.
				char* ECH(const char * n) { return multicat(ECH_OUT,"\e[", n, "X"); }

				char HPR_OUT[8];

				// Move cursor right the indicated # of columns.
				char* HPR(const char * n) { return multicat(HPR_OUT,"\e[", n, "a"); }

				// Answer ESC [ ? 6 c: I am a VT102.
				constexpr const char DA[] = "\e[c";

				char VPA_OUT[8];

				// Move cursor to the indicated row, current column.
				char* VPA(const char * n) { return multicat(VPA_OUT,"\e[", n, "d"); }

				char VPR_OUT[8];

				// Move cursor down the indicated # of rows.
				char* VPR(const char * n) { return multicat(VPR_OUT,"\e[", n, "e"); }

				char HVP_OUT[8];

				// Move cursor to the indicated row, column.
				char* HVP(const char * n) { return multicat(HVP_OUT,"\e[", n, "f"); }

				char TBC_OUT[8];
				
				// Without parameter: clear tab stop at current position.
				char* TBC() { return multicat(TBC_OUT,"\e[g"); }

				// 3 - Delete all tab stops.
				char* TBC(const char * n) { return multicat(TBC_OUT,"\e[", n, "g"); }

				/*
					h   SM        Set Mode (see DEC Private Mode sequences).
					l   RM        Reset Mode (see DEC Private Mode sequences).
					m   SGR       Set attributes (see Select Graphic Rendition) {.
					n   DSR       Status report (see Status Report Commands).
				*/

				char DECLL_OUT[8];

				// Set keyboard LEDs.

				/*
					0 - clear all LEDs
					1 - set Scroll Lock LED
					2 - set Num Lock LED
					3 - set Caps Lock LED
				*/ 
				char* DECLL(const char * n) { return multicat(DECLL_OUT,"\e[", n, "q"); }

				char DECSTBM_OUT[16];

				// Set scrolling region; parameters are top and bottom row.
				char* DECSTBM(const char * top, const char * bottom) { return multicat(DECSTBM_OUT,"\e[", top, ";", bottom, "r"); }

				// Save cursor location.
				constexpr const char SCL[] = "\e[s";

				// Restore cursor location.
				constexpr const char RCL[] = "\e[u";

				char HPA_OUT[16];

				// Move cursor to indicated column in current row.
				char* HPA(const char * n) { return multicat(HPA_OUT,"\e[", n, "`"); }

			#pragma endregion

			#pragma region ECMA-48 Select Graphic Rendition

				// ECMA-48 Select Graphic Rendition

				// ECMA48_SGR_Seq
				enum ecma48_sgr_seq : uint8_t
				{
					// reset all attributes to their defaults
					RST = 0,

					// set bold
					BOLD = 1,

					// set half-bright (simulated with color on a color display)
					HalfBright = 2,

					// set underscore (simulated with color on a color display) (the colors used to simulate dim or underline are set using ESC ] ...)
					UNDRSCR = 4,

					// set blink
					BLINK = 5,

					// set reverse video
					RVRS = 7,

					// reset selected mapping, display control flag, and toggle meta flag (ECMA-48 says primary font).
					PrimFont = 10,

					// select null mapping, set display control flag, reset toggle meta flag (ECMA-48 says first alternate font).
					FiAlFont = 11,

					// select null mapping, set display control flag, set toggle meta flag (ECMA-48 says second alternate font).  The toggle meta flag causes the high bit of a byte to be toggled before the mapping table translation is done.
					SeAlFont = 12,

					// set underline; before Linux 4.17, this value set normal intensity (as is done in many other terminals)
					UNDRLN = 21,

					// set normal intensity
					SetNormInt = 22,

					// underline off
					UNDRLNOFF = 24,

					// blink off
					BLINKOFF = 25,

					// reverse video off
					RVRSOFF = 27,


					// set black foreground
					BLACK_FG = 30,

					// set red foreground
					RED_FG = 31,

					// set green foreground
					GREEN_FG = 32,

					// set brown foreground
					BROWN_FG = 33,

					// set blue foreground
					BLUE_FG = 34,

					// set magenta foreground
					MAGENTA_FG = 35,

					// set cyan foreground
					CYAN_FG = 36,

					// set white foreground
					WHITE_FG = 37,


					// 256/24-bit foreground color follows, shoehorned into 16 basic colors (before Linux 3.16: set underscore on, set default foreground color)
					FGTYPE = 38,

					// set default foreground color (before Linux 3.16: set underscore off, set default foreground color)
					FGRESET = 39,


					// set black background
					BLACK_BG = 40,

					// set red background
					RED_BG = 41,

					// set green background
					GREEN_BG = 42,

					// set brown background
					BROWN_BG = 43,

					// set blue background
					BLUE_BG = 44,

					// set magenta background
					MAGENTA_BG = 45,

					// set cyan background
					CYAN_BG = 46,

					// set white background
					WHITE_BG = 47,


					// 256/24-bit background color follows, shoehorned into 8 basic colors
					BGTYPE = 48,

					// set default background color
					BGRESET = 49,


					// set foreground to bright 1
					FG_BRIGHT1 = 90,

					// set foreground to bright 2
					FG_BRIGHT2 = 91,

					// set foreground to bright 3
					FG_BRIGHT3 = 92,

					// set foreground to bright 4
					FG_BRIGHT4 = 93,

					// set foreground to bright 5
					FG_BRIGHT5 = 94,

					// set foreground to bright 6
					FG_BRIGHT6 = 95,

					// set foreground to bright 7
					FG_BRIGHT7 = 96,

					// set foreground to bright 8
					FG_BRIGHT8 = 97,


					// set background, same as 40..47 (bright not supported)
					// set background to bright 1
					BG_BRIGHT1 = 100,

					// set foreground to bright 2
					BG_BRIGHT2 = 101,

					// set foreground to bright 3
					BG_BRIGHT3 = 102,

					// set foreground to bright 4
					BG_BRIGHT4 = 103,

					// set foreground to bright 5
					BG_BRIGHT5 = 104,

					// set foreground to bright 6
					BG_BRIGHT6 = 105,

					// set foreground to bright 7
					BG_BRIGHT7 = 106,

					// set foreground to bright 8
					BG_BRIGHT8 = 107,
				};
				
				char SCR_BUILD_OUT[256];

				// Build SGR Sequences Together
				template<class... Ts>
				char* SGR_BUILD(Ts... ts) {
					return multicat(SCR_BUILD_OUT,"\e[",ts...,"m");
				}

				char x256COLORSEQ_OUT[8];

				// 256 color: values 0..15 are IBGR (black, red, green, ... white), 16..231 a 6x6x6 color cube, 232..255 a grayscale ramp
				char* x256COLORSEQ(const char* type,const char * color) { return multicat(x256COLORSEQ_OUT,";5;", color); }

				char x256COLORRGB_OUT[16];
				// 24-bit color, r/g/b components are in the range 0..255
				char* x256COLORRGB(const char* type,const char * r,const char * g,const char * b) {
					return multicat(x256COLORRGB_OUT, type, ";2;", r, ";", g, ";", b);
				}

			#pragma endregion

			#pragma region ECMA-48 Mode Switches

				char DECCRM_OUT[8];

				// ECMA-48 Mode Switches

				// 3 - DECCRM (default off): Display control chars.
				// 4 - DECIM (default off): Set insert mode.
				// 20 - LF/NL (default off): Automatically follow echo of LF, VT, or FF with CR.
				char* DECCRM(const char * n) { return multicat(DECCRM_OUT,"\e[", n, "h"); }

			#pragma endregion

			#pragma region ECMA-48 Status Report Commands

				char DSR_OUT[8];

				// ECMA-48 Status Report Commands

				// 5 - Device status report (DSR): Answer is ESC [ 0 n (Terminal OK).
				// 6 - Cursor position report (CPR): Answer is ESC [ y ; x R, where x,y is the cursor location.
				char* DSR(const char * n) { return multicat(DSR_OUT,"\e[", n, "n"); }

			#pragma endregion

			#pragma region DEC Private Mode (DECSET/DECRST) sequences

				// DEC Private Mode (DECSET/DECRST) sequences

				// set is h, unset is l

				// DECCKM (default off): When set, the cursor keys send an ESC O prefix, rather than ESC [.
				constexpr const char DECCKM[] = "\e[?1";

				// DECCOLM (default off 80 columns): 80/132 col mode switch. The driver sources note that this alone does not suffice; some user-mode utility such as resizecons(8) has to change the hardware registers on the console video card.
				constexpr const char DECCOLM[] = "\e[?3";

				// DECSCNM (default off): Set reverse-video mode.
				constexpr const char DECSCNM[] = "\e[?5";

				// DECOM (default off): When set, cursor addressing is relative to the upper left corner of the scrolling region.
				constexpr const char DECOM[] = "\e[?6";

				// DECAWM (default on): Set autowrap on.  In this mode, a graphic character emitted after column 80 (or column 132 of DECCOLM is on) forces a wrap to the beginning of the following line first.
				constexpr const char DECAWM[] = "\e[?7";

				// DECARM (default on): Set keyboard autorepeat on.
				constexpr const char DECARM[] = "\e[?8";

				// X10 Mouse Reporting (default off): Set reporting mode to 1 (or reset to 0) — see below.
				constexpr const char X10MR1[] = "\e[?9";

				// DECTECM (default on): Make cursor visible.
				constexpr const char DECTECM[] = "\e[?25";

				// X11 Mouse Reporting (default off): Set reporting mode to 2 (or reset to 0) — see below.
				constexpr const char X11MR2[] = "\e[?1000";

				char DECSET_OUT[16];

				// set dec sequence
				char* DECSET(const char* decseq) { return multicat(DECSET_OUT,"\e[", decseq, "h"); }

				char DECRST_OUT[16];

				// unset dec sequence
				char* DECRST(const char* decseq) { return multicat(DECRST_OUT,"\e[", decseq, "l"); }

			#pragma endregion

			#pragma region Linux Console Private Csi Sequences

				// Linux Console Private CSI Sequences

				char setUnderlineColor_OUT[8];

				// Set color n as the underline color.
				char* setUnderlineColor(const char * n) { return multicat(setUnderlineColor_OUT,"\e[1;", n, "]"); }

				char setDimColor_OUT[8];

				// Set color n as the dim color.
				char* setDimColor(const char * n) { return multicat(setDimColor_OUT,"\e[2;", n, "]"); }

				// Make the current color pair the default attributes.
				constexpr const char MakeCurColorPairDefAttr[] = "\e[8]";


				char setScreenTimeoutColor_OUT[16];

				// Set screen blank timeout to n minutes.
				char* setScreenTimeoutColor(const char * minutes) { return multicat(setScreenTimeoutColor_OUT,"\e[9;", minutes, "]"); }

				char setBellFrequencyInHz_OUT[16];

				// Set bell frequency in Hz.
				char* setBellFrequencyInHz(const char * n) { return multicat(setBellFrequencyInHz_OUT,"\e[10;", n, "]"); }

				char setBellDurationMilli_OUT[16];

				// Set bell duration in msec.
				char* setBellDurationMilli(const char * milliseconds) { return multicat(setBellDurationMilli_OUT,"\e[11;", milliseconds, "]"); }

				char bringSpecifiedConsoleToTheFont_OUT[16];

				// Bring specified console to the front.
				char* bringSpecifiedConsoleToTheFont(const char * n) { return multicat(bringSpecifiedConsoleToTheFont_OUT,"\e[12;", n, "]"); }

				// Unblank the screen.
				constexpr const char unblankTheScreen[] = "\e[13]";

				char setVesaPwrDwnInterval_OUT[16];

				// Set the VESA powerdown interval in minutes.
				char* setVesaPwrDwnInterval(const char * minutes) { return multicat(setVesaPwrDwnInterval_OUT,"\e[14;", minutes, "]"); }

				// Bring the previous console to the front (since Linux 2.6.0).
				constexpr const char bringThePreviousConsoleToTheFront[] = "\e[15]";


				char setCursorBlinkInterval_OUT[16];

				// Set the cursor blink interval in milliseconds (since Linux 4.2).
				char* setCursorBlinkInterval(const char * milliseconds) { return multicat(setCursorBlinkInterval_OUT,"\e[16;", milliseconds, "]"); }

			#pragma endregion

		#pragma endregion

		#pragma region Character sets

			/* 	Character sets

				The kernel knows about 4 translations of bytes into console-
				screen symbols.  The four tables are: a) Latin1 -> PC, b) VT100
				graphics -> PC, c) PC -> PC, d) user-defined.

				There are two character sets, called G0 and G1, and one of them
				is the current character set.  (Initially G0.)  Typing ^N causes
				G1 to become current, ^O causes G0 to become current.

				These variables G0 and G1 point at a translation table, and can
				be changed by the user.  Initially they point at tables a) and
				b), respectively.  The sequences ESC ( B and ESC ( 0 and ESC ( U
				and ESC ( K cause G0 to point at translation table a), b), c),
				and d), respectively.  The sequences ESC ) B and ESC ) 0 and ESC
				) U and ESC ) K cause G1 to point at translation table a), b),
				c), and d), respectively.

				The sequence ESC c causes a terminal reset, which is what you
				want if the screen is all garbled.  The oft-advised echo ^V^O
				will make only G0 current, but there is no guarantee that G0
				points at table a).  In some distributions there is a program
				reset(1) that just does echo ^[c.  If your terminfo entry for
				the console is correct (and has an entry rs1=\Ec), then tput
				reset will also work.

				The user-defined mapping table can be set using mapscrn(8).  The
				result of the mapping is that if a symbol c is printed, the
				symbol s map[c] is sent to the video memory.  The bitmap that
				corresponds to s is found in the character ROM, and can be
				changed using setfont(8).
			*/

		#pragma endregion

		#pragma region Mouse tracking

			/*	Mouse tracking

				The mouse tracking facility is intended to return
				xterm(1)-compatible mouse status reports.  Because the console
				driver has no way to know the device or type of the mouse, these
				reports are returned in the console input stream only when the
				virtual terminal driver receives a mouse update ioctl.  These
				ioctls must be generated by a mouse-aware user-mode application
				such as the gpm(8) daemon.

				The mouse tracking escape sequences generated by xterm(1) encode
				numeric parameters in a single character as value+040.  For
				example, ! is 1.  The screen coordinate system is 1-based.

				The X10 compatibility mode sends an escape sequence on button
				press encoding the location and the mouse button pressed.  It is
				enabled by sending ESC [ ? 9 h and disabled with ESC [ ? 9 l.  On
				button press, xterm(1) sends ESC [ M bxy (6 characters).  Here b
				is button-1, and x and y are the x and y coordinates of the mouse
				when the button was pressed.  This is the same code the kernel
				also produces.

				Normal tracking mode (not implemented in Linux 2.0.24) sends an
				escape sequence on both button press and release.  Modifier
				information is also sent.  It is enabled by sending ESC [ ? 1000
				h and disabled with ESC [ ? 1000 l.  On button press or release,
				xterm(1) sends ESC [ M bxy.  The low two bits of b encode button
				information: 0=MB1 pressed, 1=MB2 pressed, 2=MB3 pressed,
				3=release.  The upper bits encode what modifiers were down when
				the button was pressed and are added together: 4=Shift, 8=Meta,
				16=Control.  Again x and y are the x and y coordinates of the
				mouse event.  The upper left corner is (1,1).
			*/

		#pragma endregion

		#pragma region Comparisons with other terminals

			/* 	Comparisons with other terminals

				Many different terminal types are described, like the Linux
				console, as being VT100-compatible.  Here we discuss
				differences between the Linux console and the two most important
				others, the DEC VT102 and xterm(1).
			*/

			#pragma region Control-character handling

				/*	Control-character handling

					The VT102 also recognized the following control characters:

					NUL (0x00) was ignored;

					ENQ (0x05) triggered an answerback message;

					DC1 (0x11, ^Q, XON) resumed transmission;

					DC3 (0x13, ^S, XOFF) caused VT100 to ignore (and stop
					transmitting) all codes except XOFF and XON.

					VT100-like DC1/DC3 processing may be enabled by the terminal
					driver.

					The xterm(1) program (in VT100 mode) recognizes the control
					characters BEL, BS, HT, LF, VT, FF, CR, SO, SI, ESC.
				*/

			#pragma endregion

			#pragma region Escape Sequences

				/* 	Escape sequences

					VT100 console sequences not implemented on the Linux console:
				*/

				#ifndef __linux__

					// Single shift 2. (Select G2 character set for the next character only.)
					constexpr const char SS2[] = "\eN";
					// Single shift 3. (Select G3 character set for the next character only.)
					constexpr const char SS3[] = "\eO";
					// Device control string (ended by ESC \)
					constexpr const char DCS[] = "\eP";
					// Start of string.
					constexpr const char SOS[] = "\eX";
					// Privacy message (ended by ESC \)
					constexpr const char PM[] = "\e^";
					// String terminator
					constexpr const char ST[] = "\e\\";
					// Designate G2 character set
					constexpr const char DG2CS[] = "\e*";
					// Designate G3 character set
					constexpr const char DG3CS[] = "\e+";

					/*
						The program xterm(1) (in VT100 mode) recognizes ESC c, ESC # 8,
						ESC >, ESC, ESC D, ESC E, ESC H, ESC M, ESC N, ESC O, ESC P ...
						ESC \, ESC Z (it answers ESC [ ? 1 ; 2 c, I am a VT100 with
						advanced video option) and ESC ^ ... ESC \ with the same
						meanings as indicated above.  It accepts ESC (, ESC ), ESC *,
						ESC + followed by 0, A, B for the DEC special character and line
						drawing set, UK, and US-ASCII, respectively.

						The user can configure xterm(1) to respond to VT220-specific
						control sequences, and it will identify itself as a VT52, VT100,
						and up depending on the way it is configured and initialized.

						It accepts ESC ] (OSC) for the setting of certain resources.  In
						addition to the ECMA-48 string terminator (ST), xterm(1) accepts
						a BEL to terminate an OSC string.  These are a few of the OSC
						control sequences recognized by xterm(1):
					*/

					char* setIconNameAndWindowTitle(char* txt) { return multicat("\e]0;", txt, ST); }

					char* setIconName(char* txt) { return multicat("\e]1;", txt, ST); }

					char* setWindowTitle(char* txt) { return multicat("\e]2;",txt,ST); }

					char* setAnsiColorNumToTxt(const char * num, char* txt) { return multicat("\e]4;",num,";",txt, ST); }

					char* setDynamicTextColorToTxt(char* txt) { return multicat("\e]10;", txt, ST); }

					char* changeLogFileToName(char* name) { return multicat("\e]46;", name, ST); }

					char* setFontToFn(char* fn) { return multicat("\e]50;", fn, ST); }

					/*
						It recognizes the following with slightly modified meaning
						(saving more state, behaving closer to VT100/VT220):

						ESC 7  DECSC   Save cursor
						ESC 8  DECRC   Restore cursor
					*/

					// It aslo recognizes

					// Cursor to lower left corner of screen (if enabled by xterm(1)s hpLowerleftBugCompat resource)
					constexpr const char CTLLCOS[] = "\eF";

					// Memory lock (per HP terminals). Locks memory above the cursor.
					constexpr const char LMATC[] = "\el";

					// Memory unlock (per HP terminals).
					constexpr const char MEMUNLCK[] = "\em";


					// Invoke the G2 character set.
					constexpr const char LS2[] = "\en";

					// Invoke the G3 character set.
					constexpr const char LS3[] = "\eo";


					// Invoke the G3 character set as GR.
					constexpr const char LS3R[] = "\e|";

					// Invoke the G2 character set as GR.
					constexpr const char LS2R[] = "\e}";

					// Invoke the G1 character set as GR.
					constexpr const char LS1R[] = "\e~";

				#endif

				/*
					It also recognizes ESC % and provides a more complete UTF-8
					implementation than Linux console.
				*/

			#pragma endregion

			#pragma region csi Sequences

			/* 	CSI Sequences

				Old versions of xterm(1), for example, from X11R5, interpret the
				blink SGR as a bold SGR.  Later versions which implemented ANSI
				colors, for example, XFree86 3.1.2A in 1995, improved this by
				allowing the blink attribute to be displayed as a color.  Modern
				versions of xterm implement blink SGR as blinking text and still
				allow colored text as an alternate rendering of SGRs.  Stock
				X11R6 versions did not recognize the color-setting SGRs until the
				X11R6.8 release, which incorporated XFree86 xterm.  All ECMA-48
				CSI sequences recognized by Linux are also recognized by xterm,
				however xterm(1) implements several ECMA-48 and DEC control
				sequences not recognized by Linux.

				The xterm(1) program recognizes all of the DEC Private Mode
				sequences listed above, but none of the Linux private-mode
				sequences.  For discussion of xterm(1)s own private-mode
				sequences, refer to the Xterm Control Sequences document by
				Edward Moy, Stephen Gildea, and Thomas E. Dickey available with
				the X distribution.  That document, though terse, is much longer
				than this manual page.  For a chronological overview,

				⟨http://invisible-island.net/xterm/xterm.log.html⟩

				details changes to xterm.

				The vttest program

				⟨http://invisible-island.net/vttest/⟩

				demonstrates many of these control sequences.  The xterm(1)
				source distribution also contains sample scripts which exercise
				other features.
			*/

			#pragma endregion

		#pragma endregion

	#pragma endregion

	#pragma region Notes

		/*	NOTES

			ESC 8 (DECRC) is not able to restore the character set changed
			with ESC %.
		*/

	#pragma endregion

	#pragma region Bugs

		/*	BUGS

			In 2.0.23, CSI is broken, and NUL is not ignored inside escape
			sequences.

			Some older kernel versions (after 2.0) interpret 8-bit control
			sequences.  These C1 controls use codes between 128 and 159 to
			replace ESC [, ESC ] and similar two-byte control sequence
			initiators.  There are fragments of that in modern kernels
			(either overlooked or broken by changes to support UTF-8), but
			the implementation is incomplete and should be regarded as
			unreliable.

			Linux private mode sequences do not follow the rules in ECMA-48
			for private mode control sequences.  In particular, those ending
			with ] do not use a standard terminating character.  The OSC (set
			palette) sequence is a greater problem, since xterm(1) may
			interpret this as a control sequence which requires a string
			terminator (ST).  Unlike the setterm(1) sequences which will be
			ignored (since they are invalid control sequences), the palette
			sequence will make xterm(1) appear to hang (though pressing the
			return-key will fix that).  To accommodate applications which
			have been hardcoded to use Linux control sequences, set the
			xterm(1) resource brokenLinuxOSC to true.

			An older version of this document implied that Linux recognizes
			the ECMA-48 control sequence for invisible text.  It is ignored.
		*/

	#pragma endregion

	// This page is part of release 5.13 of the Linux man-pages project.
}