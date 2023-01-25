// Console Control Sequences

// console_codes(4) — Linux manual page\
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

#include<iostream>

#pragma once

namespace ccs
{
	#pragma region Name

	// console_codes - Linux console escape and control sequences

	#pragma endregion

	#pragma region Description

		/*
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

			// Beeps
			constexpr const char* const BEL = "\eG";

			// Backspaces one column (but not past the beginning of the line)
			constexpr const char* const BS =  "\eH";

			// Goes to the next tab stop or to the end of the line if there is no earlier tab stop
			constexpr const char* const HT =  "\eI";

			// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
			constexpr const char* const LF =  "\eJ";

			// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
			constexpr const char* const VT =  "\eK";

			// All give a linefeed, and if LF/NL (new-line mode) is set also a carriage return
			constexpr const char* const FF =  "\eL";

			// Gives a carriage return
			constexpr const char* const CR =  "\eM";

			// Activates the G1 character set
			constexpr const char* const SO =  "\eN";

			// Activates the G0 character set
			constexpr const char* const SI =  "\eO";

			// Abort escape sequences
			constexpr const char* const CAN = "\eX";

			// Abort escape sequences
			constexpr const char* const SUB = "\eZ";

			// Starts an escape sequence
			constexpr const char* const ESC = "\e";

			// Control sequence introducer. Is equivalent to ESC [
			constexpr const char* const CSI = "\e[";

			#pragma endregion

			#pragma region ESC-Sequences

			// ESC- but not CSI-sequences

			// Reset.
			constexpr char* const RIS = (std::string(ESC) + 'c').c_str();

			// Linefeed.
			const char* const IND = (std::string(ESC) + 'D').c_str();

			// Newline.
			const char* const NEL = (std::string(ESC) + 'E').c_str();

			// Set tab stop at current column.
			const char* const HTS = (std::string(ESC) + 'H').c_str();

			// Reverse linefeed.
			const char* const RI = (std::string(ESC) + 'M').c_str();

			// DEC private identification. The kernel returns the string  ESC [ ? 6 c, claiming that it is a VT102.
			const char* const DECID = (std::string(ESC) + 'Z').c_str();

			// Save current state (cursor coordinates, attributes, character sets pointed at by G0,  G1).
			const char* const DECSC = (std::string(ESC) + '7').c_str();
			
			// Restore state most recently saved by ESC 7.
			const char* const DECRC = (std::string(ESC) + '8').c_str();


			// Start sequence selecting character set
			const char* const SSSCS = (std::string(ESC) + '%').c_str();

			// Select default (ISO 646 / ISO 8859-1)
			const char* const SELDEF = (std::string(SSSCS) + '@').c_str();

			// Select UTF-8
			const char* const SELUTF8 = (std::string(SSSCS) + 'G').c_str();

			// Select UTF-8 (obsolete)
			const char* const SELUTFO = (std::string(SSSCS) + '8').c_str();


			// DEC screen alignment test - fill screen with E's
			const char* const DECALN = (std::string(ESC) + "#8").c_str();


			// Start sequence defining G0 character set (followed by one of B, 0, U, K, as below)
			const char* const SSDG0 = (std::string(ESC) + '(').c_str();

			// Select default (ISO 8859-1 mapping)
			const char* const SD0 = (std::string(SSDG0) + 'B').c_str();

			// Select VT100 graphics mapping
			const char* const SVT0100 = (std::string(SSDG0) + '0').c_str();

			// Select null mapping - straight to character ROM
			const char* const SNM0 = (std::string(SSDG0) + 'U').c_str();

			// Select user mapping - the map that is loaded by the utility mapscrn(8)
			const char* const SUM0 = (std::string(SSDG0) + 'K').c_str();


			// Start sequence defining G1 (followed by one of B, 0, U, K, as above).
			const char* const SSDG1 = (std::string(ESC) + ')').c_str();

			// Select default (ISO 8859-1 mapping)
			const char* const SD1 = (std::string(SSDG1) + 'B').c_str();

			// Select VT100 graphics mapping
			const char* const SVT1100 = (std::string(SSDG1) + '0').c_str();

			// Select null mapping - straight to character ROM
			const char* const SNM1 = (std::string(SSDG1) + 'U').c_str();

			// Select user mapping - the map that is loaded by the utility mapscrn(8)
			const char* const SUM1 = (std::string(SSDG1) + 'K').c_str();


			// Set numeric keypad mode
			const char* const DECPNM = (std::string(ESC) + '>').c_str();

			// Set application keypad mode
			const char* const DECPAM = (std::string(ESC) + '=').c_str();
			

			/*
				(Should be: Operating system command) ESC ] P
                nrrggbb: set palette, with parameter given in
                7 hexadecimal digits after the final P :-(.
                Here n is the color (0–15), and rrggbb
                indicates the red/green/blue values (0–255).
                ESC ] R: reset palette
			*/
			const char* const OSC = (std::string(ESC) + ']').c_str();
			
			#pragma endregion

			#pragma region CSI-Sequences

			// ECMA-48 CSI sequences

			// Insert the indicated # of blank characters.
			const char* const ICH = (std::string(CSI) + '@').c_str();

			// Move cursor up the indicated # of rows.
			const char* const CUU = (std::string(CSI) + 'A').c_str();

			// Move cursor down the indicated # of rows.
			const char* const CUD = (std::string(CSI) + 'B').c_str();

			// Move cursor right the indicated # of columns.
			const char* const CUF = (std::string(CSI) + 'C').c_str();

			// Move cursor left the indicated # of columns.
			const char* const CUB = (std::string(CSI) + 'D').c_str();

			// Move cursor down the indicated # of rows, to column 1.
			const char* const CNL = (std::string(CSI) + 'E').c_str();

			// Move cursor up the indicated # of rows, to column 1.
			const char* const CPL = (std::string(CSI) + 'F').c_str();

			// Move cursor to indicated column in current row.
			const char* const CHA = (std::string(CSI) + 'G').c_str();

			// Move cursor to the indicated row, column (origin at 1,1).
			const char* const CUP = (std::string(CSI) + 'H').c_str();


			//Erase display (default: from cursor to end of display).
			const char* const ED = (std::string(CSI) + "J").c_str();

			// erase from start to cursor.
			const char* const ED1 = (std::string(CSI) + "1J").c_str();

			// erase whole display.
			const char* const ED2 = (std::string(CSI) + "2J").c_str();

			// erase whole display including scroll-back buffer (since Linux 3.0).
			const char* const ED3 = (std::string(CSI) + "3J").c_str();

			
			// Erase line (default: from cursor to end of line).
			const char* const EL = (std::string(CSI) + "K").c_str();

			// erase from start of line to cursor.
			const char* const EL1 = (std::string(CSI) + "1K").c_str();

			// erase whole line.
			const char* const EL2 = (std::string(CSI) + "2K").c_str();



			// Insert the indicated # of blank lines.
			const char* const IL = (std::string(CSI) + 'L').c_str();

			// Delete the indicated # of lines.
			const char* const DL = (std::string(CSI) + 'M').c_str();

			// Delete the indicated # of characters on current line.
			const char* const DCH = (std::string(CSI) + 'P').c_str();

			// Erase the indicated # of characters on current line.
			const char* const ECH = (std::string(CSI) + 'X').c_str();

			// Move cursor right the indicated # of columns.
			const char* const HPR = (std::string(CSI) + 'a').c_str();

			// Answer ESC [ ? 6 c: "I am a VT102".
			const char* const DA = (std::string(CSI) + 'c').c_str();

			// Move cursor to the indicated row, current column.
			const char* const VPA = (std::string(CSI) + 'd').c_str();

			// Move cursor down the indicated # of rows.
			const char* const VPR = (std::string(CSI) + 'E').c_str();

			// Move cursor to the indicated row, column.
			const char* const HVP = (std::string(CSI) + 'f').c_str();


			// Without parameter: clear tab stop at current position.
			const char* const TBC = (std::string(CSI) + 'g').c_str();

			// delete all tab stops.
			const char* const TBC3 = (std::string(CSI) + "3g").c_str();


			/*
				h   SM        Set Mode (see DEC Private Mode sequences).
				l   RM        Reset Mode (see DEC Private Mode sequences).
				m   SGR       Set attributes (see Select Graphic Rendition).
				n   DSR       Status report (see Status Report Commands).
			*/

			// Set keyboard LEDs.

			// clear all LEDs
			const char* const DECLL0 = (std::string(CSI) + "0q").c_str();

			// set Scroll Lock LED
			const char* const DECLL1 = (std::string(CSI) + "1q").c_str();

			// set Num Lock LED
			const char* const DECLL2 = (std::string(CSI) + "2q").c_str();

			// set Caps Lock LED
			const char* const DECLL3 = (std::string(CSI) + "3q").c_str();


			// Set scrolling region; parameters are top and bottom row.
			const char* const DECSTBM = (std::string(CSI) + 'r').c_str();

			// Save cursor location.
			const char* const SCL = (std::string(CSI) + 's').c_str();

			// Restore cursor location.
			const char* const RCL = (std::string(CSI) + 'u').c_str();

			// Move cursor to indicated column in current row.
			const char* const HPA = (std::string(CSI) + '`').c_str();


			#pragma endregion

			#pragma region ECMA-48 Select Graphic Rendition

			// ECMA-48 Select Graphic Rendition

			enum ECMA48_SGR_Seq : uint8_t
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

				// reset selected mapping, display control flag, and toggle meta flag (ECMA-48 says "primary font").
				PrimFont = 10,

				// select null mapping, set display control flag, reset toggle meta flag (ECMA-48 says "first alternate font").
				FiAlFont = 11,

				// select null mapping, set display control flag, set toggle meta flag (ECMA-48 says "second alternate font").  The toggle meta flag causes the high bit of a byte to be toggled before the mapping table translation is done.
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
				x256FGCOLOR = 38,

				// set default foreground color (before Linux 3.16: set underscore off, set default foreground color)
				x256FGRESET = 39,


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
				x256BGCOLOR = 48,

				// set default background color
				x256BGRESET = 49,


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

			// 256 color: values 0..15 are IBGR (black, red, green, ... white), 16..231 a 6x6x6 color cube, 232..255 a grayscale ramp
			constexpr char* const x256COLORSEQ = ";5;";

			// 24-bit color, r/g/b components are in the range 0..255
			constexpr char* const x256COLORRGB = ";2;";

			#pragma endregion

			#pragma region ECMA-48 Mode Switches

			// ECMA-48 Mode Switches

			// DECCRM (default off): Display control chars.
			const char* const DECCRM = (std::string(CSI) + "3h").c_str();

			// DECIM (default off): Set insert mode.
			const char* const DECIM = (std::string(CSI) + "4h").c_str();

			// LF/NL (default off): Automatically follow echo of LF, VT, or FF with CR.
			const char* const LF_NL = (std::string(CSI) + "20h").c_str();

			#pragma endregion

			#pragma region ECMA-48 Status Report Commands

			// ECMA-48 Status Report Commands

			// Device status report (DSR): Answer is ESC [ 0 n (Terminal OK).
			const char* const DSR = (std::string(CSI) + "5n").c_str();

			// Cursor position report (CPR): Answer is ESC [ y ; x R, where x,y is the cursor location.
			const char* const CPR = (std::string(CSI) + "6n").c_str();

			#pragma endregion

			#pragma region DEC Private Mode (DECSET/DECRST) sequences

			// DEC Private Mode (DECSET/DECRST) sequences

			// set is h, unset is l

			// DECCKM (default off): When set, the cursor keys send an ESC O prefix, rather than ESC [.
			const char* const DECCKM = (std::string(CSI) + "?1").c_str();

			// DECCOLM (default off = 80 columns): 80/132 col mode switch. The driver sources note that this alone does not suffice; some user-mode utility such as resizecons(8) has to change the hardware registers on the console video card.
			const char* const DECCOLM = (std::string(CSI) + "?3").c_str();

			// DECSCNM (default off): Set reverse-video mode.
			const char* const DECSCNM = (std::string(CSI) + "?5").c_str();

			// DECOM (default off): When set, cursor addressing is relative to the upper left corner of the scrolling region.
			const char* const DECOM = (std::string(CSI) + "?6").c_str();

			// DECAWM (default on): Set autowrap on.  In this mode, a graphic character emitted after column 80 (or column 132 of DECCOLM is on) forces a wrap to the beginning of the following line first.
			const char* const DECAWM = (std::string(CSI) + "?7").c_str();

			// DECARM (default on): Set keyboard autorepeat on.
			const char* const DECARM = (std::string(CSI) + "?8").c_str();

			// X10 Mouse Reporting (default off): Set reporting mode to 1 (or reset to 0)—see below.
			const char* const X10MR1 = (std::string(CSI) + "?9").c_str();

			// DECTECM (default on): Make cursor visible.
			const char* const DECTECM = (std::string(CSI) + "?25").c_str();

			// X11 Mouse Reporting (default off): Set reporting mode to 2 (or reset to 0)—see below.
			const char* const X10MR2 = (std::string(CSI) + "?1000").c_str();


			#pragma endregion

			#pragma region Linux Console Private CSI Sequences

			// Linux Console Private CSI Sequences

			// Set color n as the underline color.
			constexpr const char* const setUnderlineColor(const int const n)
			{
				return (std::string(CSI) + "1;" + static_cast<char>(n)+']').c_str();
			}
			
			// Set color n as the dim color.
			constexpr const char* const setDimColor(const int const n)
			{
				return (std::string(CSI) + "2;" + static_cast<char>(n)+']').c_str();
			}
			
			// Make the current color pair the default attributes.
			const char* const MakeCurColorPairDefAttr = (std::string(CSI) + "8]").c_str();
			
			
			// Set screen blank timeout to n minutes.
			constexpr const char* const setScreenTimeoutColor(const int const munutes)
			{
				return (std::string(CSI) + "9;" + static_cast<char>(munutes)+']').c_str();
			}
			
			// Set bell frequency in Hz.
			constexpr const char* const setBellFrequencyInHz(const int const n)
			{
				return (std::string(CSI) + "10;" + static_cast<char>(n)+']').c_str();
			}
			
			// Set bell duration in msec.
			constexpr const char* const setBellDurationMilli(const int const milliseconds)
			{
				return (std::string(CSI) + "11;" + static_cast<char>(milliseconds)+']').c_str();
			}
			
			// Bring specified console to the front.
			constexpr const char* const bringSpecifiedConsoleToTheFont(const int const n)
			{
				return (std::string(CSI) + "12;" + static_cast<char>(n)+']').c_str();
			}
			
			// Unblank the screen.
			const char* const unblankTheScreen = (std::string(CSI) + "13]").c_str();
			
			
			// Set the VESA powerdown interval in minutes.
			constexpr const char* const setVesaPwrDwnInterval(const int const munutes)
			{
				return (std::string(CSI) + "14;" + static_cast<char>(munutes)+']').c_str();
			}
			
			// Bring the previous console to the front (since Linux 2.6.0).
			const char* const bringThePreviousConsoleToTheFront = (std::string(CSI) + "15]").c_str();
			
			
			// Set the cursor blink interval in milliseconds (since Linux 4.2).
			constexpr const char* const setCursorBlinkInterval(const int const milliseconds)
			{
				return (std::string(CSI) + "16;" + static_cast<char>(milliseconds)+']').c_str();
			}

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
			want if the screen is all garbled.  The oft-advised "echo ^V^O"
			will make only G0 current, but there is no guarantee that G0
			points at table a).  In some distributions there is a program
			reset(1) that just does "echo ^[c".  If your terminfo entry for
			the console is correct (and has an entry rs1=\Ec), then "tput
			reset" will also work.

			The user-defined mapping table can be set using mapscrn(8).  The
			result of the mapping is that if a symbol c is printed, the
			symbol s = map[c] is sent to the video memory.  The bitmap that
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
			example, '!' is 1.  The screen coordinate system is 1-based.

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
				console, as being "VT100-compatible".  Here we discuss
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

			#pragma region Escape sequences

			/* 	Escape sequences
				VT100 console sequences not implemented on the Linux console:
			*/

			#ifndef __linux__

			// Single shift 2. (Select G2 character set for the next character only.)
			const char* const SS2 = (std::string(ESC) + 'N').c_str();
			// Single shift 3. (Select G3 character set for the next character only.)
			const char* const SS3 = (std::string(ESC) + 'O').c_str();
			// Device control string (ended by ESC \)
			const char* const DCS = (std::string(ESC) + 'P').c_str();
			// Start of string.
			const char* const SOS = (std::string(ESC) + 'X').c_str();
			// Privacy message (ended by ESC \)
			const char* const PM = (std::string(ESC) + '^').c_str();
			// String terminator
			const char* const ST = (std::string(ESC) + '\\').c_str();
			// Designate G2 character set
			const char* const DG2CS = (std::string(ESC) + '*').c_str();
			// Designate G3 character set
			const char* const DG3CS = (std::string(ESC) + '+').c_str();

			#endif

			/*
				The program xterm(1) (in VT100 mode) recognizes ESC c, ESC # 8,
				ESC >, ESC =, ESC D, ESC E, ESC H, ESC M, ESC N, ESC O, ESC P ...
				ESC \, ESC Z (it answers ESC [ ? 1 ; 2 c, "I am a VT100 with
				advanced video option") and ESC ^ ... ESC \ with the same
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

			constexpr const char* const setIconNameAndWindowTitle(const int const txt)
			{
				return (std::string(ESC) + "]0;" + static_cast<char>(txt) + "ST").c_str();
			}

			constexpr const char* const setIconName(const int const txt)
			{
				return (std::string(ESC) + "]1;" + static_cast<char>(txt) + "ST").c_str();
			}

			constexpr const char* const setWindowTitle(const int const txt)
			{
				return (std::string(ESC) + "]2;" + static_cast<char>(txt) + "ST").c_str();
			}

			constexpr const char* const setAnsiColorNumToTxt(const unsigned const num,const int const txt)
			{
				return (std::string(ESC) + "]4;" + static_cast<char>(num) + ';' + static_cast<char>(txt) + "ST").c_str();
			}

			constexpr const char* const setDynamicTextColorToTxt(const int const txt)
			{
				return (std::string(ESC) + "]10;"+ static_cast<char>(txt) + "ST").c_str();
			}

			constexpr const char* const changeLogFileToName(const int const name)
			{
				return (std::string(ESC) + "]46;"+ static_cast<char>(name) + "ST").c_str();
			}

			constexpr const char* const setFontToFn(const int const fn)
			{
				return (std::string(ESC) + "]50;"+ static_cast<char>(fn) + "ST").c_str();
			}

			/*
				It recognizes the following with slightly modified meaning
				(saving more state, behaving closer to VT100/VT220):

				ESC 7  DECSC   Save cursor
				ESC 8  DECRC   Restore cursor
			*/

			//	It aslo recognizes

			// Cursor to lower left corner of screen (if enabled by xterm(1)'s hpLowerleftBugCompat resource)
			const char* const CTLLCOS = (std::string(ESC) + 'F').c_str();

			// Memory lock (per HP terminals). Locks memory above the cursor.
			const char* const LMATC = (std::string(ESC) + 'l').c_str();

			// Memory unlock (per HP terminals).
			const char* const MEMUNLCK = (std::string(ESC) + 'm').c_str();

			// Invoke the G2 character set.
			const char* const LS2 = (std::string(ESC) + 'n').c_str();

			// Invoke the G3 character set.
			const char* const LS3 = (std::string(ESC) + 'o').c_str();


			// Invoke the G3 character set as GR.
			const char* const LS3R = (std::string(ESC) + '|').c_str();

			// Invoke the G2 character set as GR.
			const char* const LS2R = (std::string(ESC) + '}').c_str();

			// Invoke the G1 character set as GR.
			const char* const LS1R = (std::string(ESC) + '~').c_str();
			
			/*
				It also recognizes ESC % and provides a more complete UTF-8
				implementation than Linux console.
			*/

			#pragma endregion

			#pragma region CSI Sequences

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
			sequences.  For discussion of xterm(1)'s own private-mode
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
		sequences.  These "C1 controls" use codes between 128 and 159 to
		replace ESC [, ESC ] and similar two-byte control sequence
		initiators.  There are fragments of that in modern kernels
		(either overlooked or broken by changes to support UTF-8), but
		the implementation is incomplete and should be regarded as
		unreliable.

		Linux "private mode" sequences do not follow the rules in ECMA-48
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