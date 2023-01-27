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

#pragma region  Funcs

// To string func
#define STR(A) #A
// To string func with expand macro
#define EXSTR(A) STR(A)

// Concat macro
#define CONCAT(A, B) A ## B
// Concat with expand macro
#define EXCONCAT(A, B) CONCAT(A, B)
// Concat with expand and to string func
#define SCONCAT(A,B) EXSTR(EXCONCAT(A,B))

#pragma endregion


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
			#define ESC   "\e"

			// Control sequence introducer. Is equivalent to ESC [
			#define CSI   ESC "["

			// Beeps
			#define BEL   ESC "G"

			// Backspaces one column (but not past the beginning of the line)
			#define BS   ESC "H"

			// Goes to the next tab stop or to the end of the line if there is no earlier tab stop
			#define HT   ESC "I"

			// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
			#define LF   ESC "J"

			// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
			#define VT   ESC "K"

			// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
			#define FF   ESC "L"

			// Gives a carriage return
			#define CR   ESC "M"

			// Activates the G1 character set
			#define SO   ESC "N"

			// Activates the G0 character set
			#define SI   ESC "O"

			// Abort escape sequences
			#define CAN   ESC "X"

			// Abort escape sequences
			#define SUB   ESC "Z"

		#pragma endregion

		#pragma region Esc-Sequences

			// ESC- but not CSI-sequences

			// Reset.
			#define RIS   ESC "c"

			// Linefeed.
			#define IND   ESC "D"

			// Newline.
			#define NEL   ESC "E"

			// Set tab stop at current column.
			#define HTS   ESC "H"

			// Reverse linefeed.
			#define RI   ESC "M"

			// DEC private identification. The kernel returns the string  ESC [ ? 6 c, claiming that it is a VT102.
			#define DECID   ESC "Z"

			// Save current state (cursor coordinates, attributes, character sets pointed at by G0,  G1).
			#define DECSC   ESC "7"

			// Restore state most recently saved by ESC 7.
			#define DECRC   ESC "8"


			// Start sequence selecting character set
			#define SSSCS   ESC "%"

			// Select default (ISO 646 / ISO 8859-1)
			#define SELDEF   SSSCS "@"

			// Select UTF-8
			#define SELUTF8   SSSCS "G"

			// Select UTF-8 (obsolete)
			#define SELUTFO   SSSCS "8"


			// DEC screen alignment test - fill screen with Es
			#define DECALN   ESC "#8"


			// Start sequence defining G0 character set (followed by one of B, 0, U, K, as below)
			#define SSDG0 ESC "("

			// Select default (ISO 8859-1 mapping)
			#define SD0 SSDG0 "B"

			// Select VT100 graphics mapping
			#define SVT0100 SSDG0 "0"

			// Select null mapping - straight to character ROM
			#define SNM0 SSDG0 "U"

			// Select user mapping - the map that is loaded by the utility mapscrn(8)
			#define SUM0 SSDG0 "K"


			// Start sequence defining G1 (followed by one of B, 0, U, K, as above).
			#define SSDG1   ESC ")"

			// Select default (ISO 8859-1 mapping)
			#define SD1   SSDG1 "B"

			// Select VT100 graphics mapping
			#define SVT1100   SSDG1 "0"

			// Select null mapping - straight to character ROM
			#define SNM1   SSDG1 "U"

			// Select user mapping - the map that is loaded by the utility mapscrn(8)
			#define SUM1   SSDG1 "K"


			// Set numeric keypad mode
			#define DECPNM   ESC ">"

			// Set application keypad mode
			#define DECPAM   ESC "="

			/*
				(Should be: Operating system command) ESC ] P
				nrrggbb: set palette, with parameter given in
				7 hexadecimal digits after the final P :-(.
				Here n is the color (0–15), and rrggbb
				indicates the red/green/blue values (0–255).
				ESC ] R: reset palette
			*/
			#define OSC(N,R,G,B)   ESC "]" "P" #N #R #G #B

			#define RSTPALETTE ESC "]" "R"

		#pragma endregion

		#pragma region Csi-Sequences

			// ECMA-48 CSI sequences

			// Insert the indicated # of blank characters.
			#define ICH(N)   CSI #N "@"

			// Move cursor up the indicated # of rows.
			#define CUU(N)   CSI #N "A"

			// Move cursor down the indicated # of rows.
			#define CUD(N)   CSI #N "B"

			// Move cursor right the indicated # of columns.
			#define CUF(N)   CSI #N "C"

			// Move cursor left the indicated # of columns.
			#define CUB(N)   CSI #N "D"

			// Move cursor down the indicated # of rows, to column 1.
			#define CNL(N)   CSI #N "E"

			// Move cursor up the indicated # of rows, to column 1.
			#define CPL(N)   CSI #N "F"

			// Move cursor to indicated column in current row.
			#define CHA(N)   CSI #N "G"

			// Move cursor to the indicated row, column (origin at 1,1).
			#define CUP(X,Y) CSI #Y ";" #X "H"

			/*
				Erase display (default: from cursor to end of display).
				1 - erase from start to cursor.
				2 - erase whole display.
				3 - erase whole display including scroll-back buffer (since Linux 3.0).
			*/
			#define ED(N)   CSI #N "J"

			/*
				Erase line (default: from cursor to end of line).
				1 - erase from start of line to cursor.
				2 - erase whole line.
			*/
			#define EL(N)   CSI #N "K"

			// Insert the indicated # of blank lines.
			#define IL(N)   CSI #N "L"

			// Delete the indicated # of lines.
			#define DL(N)   CSI #N "M"

			// Delete the indicated # of characters on current line.
			#define DCH(N)   CSI #N "P"

			// Erase the indicated # of characters on current line.
			#define ECH(N)   CSI #N "X"

			// Move cursor right the indicated # of columns.
			#define HPR(N)   CSI #N "a"

			// Answer ESC [ ? 6 c: I am a VT102.
			#define DA  CSI "c"

			// Move cursor to the indicated row, current column.
			#define VPA(N)   CSI #N "d"

			// Move cursor down the indicated # of rows.
			#define VPR(N)   CSI #N "e"

			// Move cursor to the indicated row, column.
			#define HVP(N)   CSI #N "f"

			/*
				Without parameter: clear tab stop at current position.
				3 - delete all tab stops.
			*/
			#define TBC(N)   CSI #N "g"

			/*
				h   SM        Set Mode (see DEC Private Mode sequences).
				l   RM        Reset Mode (see DEC Private Mode sequences).
				m   SGR       Set attributes (see Select Graphic Rendition).
				n   DSR       Status report (see Status Report Commands).
			*/

			// Set keyboard LEDs.

			/*
				0 - clear all LEDs
				1 - set Scroll Lock LED
				2 - set Num Lock LED
				3 - set Caps Lock LED
			*/ 
			#define DECLL(N)   CSI #N "q"

			// Set scrolling region; parameters are top and bottom row.
			#define DECSTBM(TOP,BOTTOM)   CSI #TOP ";" #BOTTOM "r"

			// Save cursor location.
			#define SCL   CSI "s"

			// Restore cursor location.
			#define RCL   CSI "u"

			// Move cursor to indicated column in current row.
			#define HPA(N)   CSI #N "`"

		#pragma endregion

		#pragma region ECMA-48 Select Graphic Rendition

			// ECMA-48 Select Graphic Rendition

			// ECMA48_SGR_Seq
			
			// reset all attributes to their defaults
			#define RST 0

			// set bold
			#define BOLD 1

			// set half-bright (simulated with color on a color display)
			#define HalfBright 2

			// set underscore (simulated with color on a color display) (the colors used to simulate dim or underline are set using ESC ] ...)
			#define UNDRSCR 4

			// set blink
			#define BLINK 5

			// set reverse video
			#define RVRS 7

			// reset selected mapping, display control flag, and toggle meta flag (ECMA-48 says primary font).
			#define PrimFont 10

			// select null mapping, set display control flag, reset toggle meta flag (ECMA-48 says first alternate font).
			#define FiAlFont 11

			// select null mapping, set display control flag, set toggle meta flag (ECMA-48 says second alternate font).  The toggle meta flag causes the high bit of a byte to be toggled before the mapping table translation is done.
			#define SeAlFont 12

			// set underline; before Linux 4.17, this value set normal intensity (as is done in many other terminals)
			#define UNDRLN 21

			// set normal intensity
			#define SetNormInt 22

			// underline off
			#define UNDRLNOFF 24

			// blink off
			#define BLINKOFF 25

			// reverse video off
			#define RVRSOFF 27


			// set black foreground
			#define BLACK_FG 30

			// set red foreground
			#define RED_FG 31

			// set green foreground
			#define GREEN_FG 32

			// set brown foreground
			#define BROWN_FG 33

			// set blue foreground
			#define BLUE_FG 34

			// set magenta foreground
			#define MAGENTA_FG 35

			// set cyan foreground
			#define CYAN_FG 36

			// set white foreground
			#define WHITE_FG 37


			// 256/24-bit foreground color follows, shoehorned into 16 basic colors (before Linux 3.16: set underscore on, set default foreground color)
			#define FGTYPE 38

			// set default foreground color (before Linux 3.16: set underscore off, set default foreground color)
			#define FGRESET 39


			// set black background
			#define BLACK_BG 40

			// set red background
			#define RED_BG 41

			// set green background
			#define GREEN_BG 42

			// set brown background
			#define BROWN_BG 43

			// set blue background
			#define BLUE_BG 44

			// set magenta background
			#define MAGENTA_BG 45

			// set cyan background
			#define CYAN_BG 46

			// set white background
			#define WHITE_BG 47


			// 256/24-bit background color follows, shoehorned into 8 basic colors
			#define BGTYPE 48

			// set default background color
			#define BGRESET 49


			// set foreground to bright 1
			#define FG_BRIGHT1 90

			// set foreground to bright 2
			#define FG_BRIGHT2 91

			// set foreground to bright 3
			#define FG_BRIGHT3 92

			// set foreground to bright 4
			#define FG_BRIGHT4 93

			// set foreground to bright 5
			#define FG_BRIGHT5 94

			// set foreground to bright 6
			#define FG_BRIGHT6 95

			// set foreground to bright 7
			#define FG_BRIGHT7 96

			// set foreground to bright 8
			#define FG_BRIGHT8 97


			// set background, same as 40..47 (bright not supported)
			// set background to bright 1
			#define BG_BRIGHT1 100

			// set foreground to bright 2
			#define BG_BRIGHT2 101

			// set foreground to bright 3
			#define BG_BRIGHT3 102

			// set foreground to bright 4
			#define BG_BRIGHT4 103

			// set foreground to bright 5
			#define BG_BRIGHT5 104

			// set foreground to bright 6
			#define BG_BRIGHT6 105

			// set foreground to bright 7
			#define BG_BRIGHT7 106

			// set foreground to bright 8
			#define BG_BRIGHT8 107

			// Build SGR Sequences Together
			#define SGR_BUILD(...) CSI #__VA_ARGS__ "m"

			// Build SGR Sequences Together With Macro expansion
			// USING: EX_SGR_BUILD(MACRO;MACRO ...)
			#define EX_SGR_BUILD(...) SGR_BUILD(__VA_ARGS__)

			// 256 color: values 0..15 are IBGR (black, red, green, ... white), 16..231 a 6x6x6 color cube, 232..255 a grayscale ramp
			#define x256COLORSEQ(TYPE,COLOR) #TYPE ";5;" #COLOR

			// 256 color: values 0..15 are IBGR (black, red, green, ... white), 16..231 a 6x6x6 color cube, 232..255 a grayscale ramp With Macro expansion
			#define EX_x256COLORSEQ(TYPE,COLOR) x256COLORSEQ(TYPE,COLOR)

			// 24-bit color, r/g/b components are in the range 0..255
			#define x256COLORRGB(TYPE,R,G,B) #TYPE ";2;" #R ";" #G ";" #B

			// 24-bit color, r/g/b components are in the range 0..255 With Macro expansion
			#define EX_x256COLORRGB(TYPE,R,G,B) x256COLORRGB(TYPE,R,G,B)

		#pragma endregion

		#pragma region ECMA-48 Mode Switches

			// ECMA-48 Mode Switches

			// 3 - DECCRM (default off): Display control chars.
			// 4 - DECIM (default off): Set insert mode.
			// 20 - LF/NL (default off): Automatically follow echo of LF, VT, or FF with CR.
			#define DECCRM(N) CSI #N "h"

		#pragma endregion

		#pragma region ECMA-48 Status Report Commands

			// ECMA-48 Status Report Commands

			// 5 - Device status report (DSR): Answer is ESC [ 0 n (Terminal OK).
			// 6 - Cursor position report (CPR): Answer is ESC [ y ; x R, where x,y is the cursor location.
			#define DSR(N) CSI #N "n"

		#pragma endregion

		#pragma region DEC Private Mode (DECSET/DECRST) sequences

			// DEC Private Mode (DECSET/DECRST) sequences

			// set is h, unset is l

			// DECCKM (default off): When set, the cursor keys send an ESC O prefix, rather than ESC [.
			#define DECCKM ?1

			// DECCOLM (default off 80 columns): 80/132 col mode switch. The driver sources note that this alone does not suffice; some user-mode utility such as resizecons(8) has to change the hardware registers on the console video card.
			#define DECCOLM ?3

			// DECSCNM (default off): Set reverse-video mode.
			#define DECSCNM ?5

			// DECOM (default off): When set, cursor addressing is relative to the upper left corner of the scrolling region.
			#define DECOM ?6

			// DECAWM (default on): Set autowrap on.  In this mode, a graphic character emitted after column 80 (or column 132 of DECCOLM is on) forces a wrap to the beginning of the following line first.
			#define DECAWM ?7

			// DECARM (default on): Set keyboard autorepeat on.
			#define DECARM ?8

			// X10 Mouse Reporting (default off): Set reporting mode to 1 (or reset to 0) — see below.
			#define X10MR1 ?9

			// DECTECM (default on): Make cursor visible.
			#define DECTECM ?25

			// X11 Mouse Reporting (default off): Set reporting mode to 2 (or reset to 0) — see below.
			#define X11MR2 ?1000

			// set dec sequence
			#define DECSET(DECSEQ) CSI #DECSEQ "h"

			// set dec sequence with macro expansion
			#define EX_DECSET(DECSEQ) DECSET(DECSEQ)

			// unset dec sequence
			#define DECRST(DECSEQ) CSI #DECSEQ "l"

			// unset dec sequence with macro expansion
			#define EX_DECRST(DECSEQ) DECRST(DECSEQ)

		#pragma endregion

		#pragma region Linux Console Private Csi Sequences

			// Linux Console Private CSI Sequences

			// Set color n as the underline color.
			#define setUnderlineColor(N) CSI "1;" #N "]"

			// Set color n as the dim color.
			#define setDimColor(N) CSI "2;" #N "]"

			// Make the current color pair the default attributes.
			#define MakeCurColorPairDefAttr CSI "8]"


			// Set screen blank timeout to n minutes.
			#define setScreenTimeoutColor(MINUTES) CSI "9;" #MINUTES "]"

			// Set bell frequency in Hz.
			#define setBellFrequencyInHz(N) CSI "10;" #N "]"

			// Set bell duration in msec.
			#define setBellDurationMilli(MILLISECONDS) CSI "11;" #MILLISECONDS "]"

			// Bring specified console to the front.
			#define bringSpecifiedConsoleToTheFont(N) CSI "12;" #N "]"

			// Unblank the screen.
			#define unblankTheScreen CSI "13]"


			// Set the VESA powerdown interval in minutes.
			#define setVesaPwrDwnInterval(MINUTES) CSI "14;" #MINUTES "]"

			// Bring the previous console to the front (since Linux 2.6.0).
			#define bringThePreviousConsoleToTheFront CSI "15]"


			// Set the cursor blink interval in milliseconds (since Linux 4.2).
			#define setCursorBlinkInterval(MILLISECONDS) CSI "16;" #MILLISECONDS "]"

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
				#define SS2 ESC "N"
				// Single shift 3. (Select G3 character set for the next character only.)
				#define SS3 ESC "O"
				// Device control string (ended by ESC \)
				#define DCS ESC "P"
				// Start of string.
				#define SOS ESC "X"
				// Privacy message (ended by ESC \)
				#define PM ESC "^"
				// String terminator
				#define ST ESC "\\"
				// Designate G2 character set
				#define DG2CS ESC "*"
				// Designate G3 character set
				#define DG3CS ESC "+"

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

				#define setIconNameAndWindowTitle(TXT) ESC "]0;" #TXT ST

				#define setIconName(TXT) ESC "]1;" #TXT ST

				#define setWindowTitle(TXT) ESC "]2;" #TXT ST

				#define setAnsiColorNumToTxt(NUM, TXT) ESC "]4;" #NUM ";" #TXT ST

				#define setDynamicTextColorToTxt(TXT) ESC "]10;" #TXT ST

				#define changeLogFileToName(NAME) ESC "]46;" #NAME ST

				#define setFontToFn(FN) ESC "]50;" #FN ST

				/*
					It recognizes the following with slightly modified meaning
					(saving more state, behaving closer to VT100/VT220):

					ESC 7  DECSC   Save cursor
					ESC 8  DECRC   Restore cursor
				*/

				// It aslo recognizes

				// Cursor to lower left corner of screen (if enabled by xterm(1)s hpLowerleftBugCompat resource)
				#define CTLLCOS ESC "F"

				// Memory lock (per HP terminals). Locks memory above the cursor.
				#define LMATC ESC "l"

				// Memory unlock (per HP terminals).
				#define MEMUNLCK ESC "m"


				// Invoke the G2 character set.
				#define LS2 ESC "n"

				// Invoke the G3 character set.
				#define LS3 ESC "o"


				// Invoke the G3 character set as GR.
				#define LS3R ESC "|"

				// Invoke the G2 character set as GR.
				#define LS2R ESC "}"

				// Invoke the G1 character set as GR.
				#define LS1R ESC "~"

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
