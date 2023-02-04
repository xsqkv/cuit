#include<stdio.h>
#include<unistd.h> // sleep / pause

#include "../lib/ccs.hpp"

int main()
{
	// A clear example of the work of the Console Codes library

	//setbuf(stdout, NULL); // Set unbuffered stream (need for sleep/pause) (won't work with getchar)

	printf("fill screen with Es: ");
	getchar();
	printf(ccs::DECALN); // DEC screen alignment test - fill screen with Es
	printf("\n");

	printf("Clear Console: ");
	getchar();
	printf("%sc",ccs::ESC); // Clear Sequence
	printf("\n");

	printf("Write text Bold style: ");
	getchar();
	printf("%s1m Bold %sm",ccs::CSI, ccs::CSI); // Bold SGR Sequence
	printf("\n");

	printf("Beep: ");
	getchar();
	printf(ccs::BEL); // Beeps
	printf("\n");

	printf("Backspace one column: ");
	getchar();
	printf(ccs::BS); // Backspace one column
	printf("\n");

	printf("Goes to the next tab stop: ");
	getchar();
	printf(ccs::HT); // Goes to the next tab stop
	printf("\n");

	printf("All give a line feed: ");
	getchar();
	printf(ccs::LF); // All give a line feed
	//printf(VT); // All give a line feed
	//printf(FF); // All give a line feed
	printf("\n");

	printf("Return carriarge: ");
	getchar();
	printf(ccs::CR); // Return carriarge
	printf("\n");

	printf("Activates the G1 character set: ");
	getchar();
	printf(ccs::SO); // Activates the G1 character set
	printf("\n");

	printf("Activates the G0 character set: ");
	getchar();
	printf(ccs::SI); // Activates the G0 character set
	printf("\n");

	printf("Abort escape sequences: ");
	getchar();
	printf(ccs::CAN); // Abort escape sequences
	//printf(SUB); // Abort escape sequences
	printf("\n");

	printf("Reset (Clear): ");
	getchar();
	printf(ccs::RIS); // Reset.
	printf("\n");

	printf("Linefeed: ");
	getchar();
	printf(ccs::IND); // Linefeed.
	printf("\n");

	printf("Newline: ");
	getchar();
	printf(ccs::NEL); // Newline.
	printf("\n");

	printf("Set tab stop at current column: ");
	getchar();
	printf(ccs::HTS); // Set tab stop at current column.
	printf("\n");

	printf("Reverse linefeed: ");
	getchar();
	printf(ccs::RI); // Reverse linefeed.
	printf("\n");

	printf("DEC private identification: ");
	getchar();
	printf(ccs::DECID); // DEC private identification. The kernel returns the string  ESC [ ? 6 c, claiming that it is a VT102.
	printf("\n");

	printf("Save current state: "); // xterm drops commands out from 100 line to 287 line
	getchar();
	printf(ccs::DECSC); // Save current state (cursor coordinates, attributes, character sets pointed at by G0,  G1).
	printf("\n");

	printf("Restore state: ");
	getchar();
	printf(ccs::DECRC); // Restore state most recently saved by ESC 7.
	printf("\n");

	//printf(SSSCS); // Start sequence selecting character set

	printf("Select default: ");
	getchar();
	printf(ccs::SELDEF); // Select default (ISO 646 / ISO 8859-1)
	printf("\n");

	printf("Select UTF-8: ");
	getchar();
	printf(ccs::SELUTF8); // Select UTF-8
	printf("\n");

	printf("Select UTF-8(obsolete): ");
	getchar();
	printf(ccs::SELUTFO); // Select UTF-8 (obsolete)
	printf("\n");

	//printf(SSDG0); // Start sequence defining G0 character set (followed by one of B, 0, U, K, as below)

	printf("Select default (ISO 8859-1 G0 mapping): ");
	getchar();
	printf(ccs::SD0); // Select default (ISO 8859-1 mapping)
	printf("\n");

	printf("Select VT100 G0 graphics mapping: ");
	getchar();
	printf(ccs::SVT0100); // Select VT100 graphics mapping
	printf("\n");

	printf("Select null G0 mapping: ");
	getchar();
	printf(ccs::SNM0); // Select null mapping - straight to character ROM
	printf("\n");

	printf("Select user G0 mapping: ");
	getchar();
	printf(ccs::SUM0); // Select user mapping - the map that is loaded by the utility mapscrn(8)
	printf("\n");

	//printf(SSDG1); // Start sequence defining G1 (followed by one of B, 0, U, K, as above).

	printf("Select default (ISO 8859-1 G1 mapping): ");
	getchar();
	printf(ccs::SD1); // Select default (ISO 8859-1 mapping)
	printf("\n");

	printf("Select VT100 graphics G1 mapping: ");
	getchar();
	printf(ccs::SVT1100); // Select VT100 graphics mapping
	printf("\n");

	printf("Select null G1 mapping: ");
	getchar();
	printf(ccs::SNM1); // Select null mapping - straight to character ROM
	printf("\n");

	printf("Select user G1 mapping: ");
	getchar();
	printf(ccs::SUM1); // Select user mapping - the map that is loaded by the utility mapscrn(8)
	printf("\n");


	printf("Set numeric keypad mode: ");
	getchar();
	printf(ccs::DECPNM); // Set numeric keypad mode
	printf("\n");

	printf("Set application keypad mode: ");
	getchar();
	printf(ccs::DECPAM); // Set application keypad mode
	printf("\n");

	printf("Set pallete: ");
	getchar();
	printf(ccs::OSC("FFF7F00")); // Set pallete
	printf("\n");

	printf("Reset pallete: ");
	getchar();
	printf(ccs::RSTPALETTE); // Reset pallete
	printf("\n");

	printf("Insert the indicated # of blank characters: ");
	getchar();
	printf(ccs::ICH("0"));// Insert the indicated # of blank characters.
	printf("\n");

	printf("Move cursor up the indicated # of rows: ");
	getchar();
	printf(ccs::CUU("0"));// Move cursor up the indicated # of rows.
	printf("\n");

	printf("Move cursor down the indicated # of rows: ");
	getchar();
	printf(ccs::CUD("0"));// Move cursor down the indicated # of rows.
	printf("\n");

	printf("Move cursor right the indicated # of columns: ");
	getchar();
	printf(ccs::CUF("0"));// Move cursor right the indicated # of columns. // DUPLICATE
	printf("\n");

	printf("Move cursor left the indicated # of columns: ");
	getchar();
	printf(ccs::CUB("0"));// Move cursor left the indicated # of columns.
	printf("\n");

	printf("Move cursor down the indicated # of rows, to column 1: ");
	getchar();
	printf(ccs::CNL("0"));// Move cursor down the indicated # of rows, to column 1.
	printf("\n");

	printf("Move cursor up the indicated # of rows, to column 1: ");
	getchar();
	printf(ccs::CPL("0"));// Move cursor up the indicated # of rows, to column 1.
	printf("\n");

	printf("Move cursor to indicated column in current row: "); // DUPLICATE
	getchar();
	printf(ccs::CHA("0"));// Move cursor to indicated column in current row.
	printf("\n");

	printf("Move cursor to the indicated row, column: ");
	getchar();
	printf(ccs::CUP("10","10"));// Move cursor to the indicated row, column (origin at 1,1).
	printf("\n");

	printf("Erase display: ");
	getchar();
	printf(ccs::ED());// Erase display (default: from cursor to end of display).
	printf("\n");

	printf("erase from start to cursor: ");
	getchar();
	printf(ccs::ED("1"));// 1 - erase from start to cursor.
	printf("\n");

	printf("erase whole display: ");
	getchar();
	printf(ccs::ED("2"));// 2 - erase whole display.
	printf("\n");

	printf("erase whole display including scroll-back buffer: ");
	getchar();
	printf(ccs::ED("3"));// 3 - erase whole display including scroll-back buffer (since Linux 3.0).
	printf("\n");

	printf("Erase line: ");
	getchar();
	printf(ccs::EL());// Erase line (default: from cursor to end of line).
	printf("\n");

	printf("erase from start of line to cursor: ");
	getchar();
	printf(ccs::EL("1"));// 1 - erase from start of line to cursor.
	printf("\n");

	printf("erase whole line: ");
	getchar();
	printf(ccs::EL("2"));// 2 - erase whole line.
	printf("\n");

	printf("Insert the indicated # of blank lines: ");
	getchar();
	printf(ccs::IL("0"));// Insert the indicated # of blank lines.
	printf("\n");

	printf("Delete the indicated # of lines: ");
	getchar();
	printf(ccs::DL("0"));// Delete the indicated # of lines.
	printf("\n");

	printf("Delete the indicated # of characters on current line: ");
	getchar();
	printf(ccs::DCH("0"));// Delete the indicated # of characters on current line.
	printf("\n");

	printf("Erase the indicated # of characters on current line: ");
	getchar();
	printf(ccs::ECH("0"));// Erase the indicated # of characters on current line.
	printf("\n");

	printf("Move cursor right the indicated # of columns: ");
	getchar();
	printf(ccs::HPR("0"));// Move cursor right the indicated # of columns. // DUBLICATE
	printf("\n");

	printf("Answer I am a VT102?: ");
	getchar();
	printf(ccs::DA);// Answer ESC [ ? 6 c: I am a VT102.
	printf("\n");

	printf("Move cursor to the indicated row, current column: "); // xterm drops from here to the line 545
	getchar();
	printf(ccs::VPA("0"));// Move cursor to the indicated row, current column.
	printf("\n");

	printf("Move cursor down the indicated # of rows: ");
	getchar();
	printf(ccs::VPR("0"));// Move cursor down the indicated # of rows.
	printf("\n");

	printf("Move cursor to the indicated row, column: ");
	getchar();
	printf(ccs::HVP("0"));// Move cursor to the indicated row, column.
	printf("\n");

	printf("clear tab stop at current position: ");
	getchar();
	printf(ccs::TBC());// Without parameter: clear tab stop at current position.
	printf("\n");

	printf("delete all tab stops: ");
	getchar();
	printf(ccs::TBC("3"));// 3 - delete all tab stops.
	printf("\n");

	printf("set Scroll Lock LED: ");
	getchar();
	printf(ccs::DECLL("1"));// 1 - set Scroll Lock LED
	printf("\n");

	printf("set Num Lock LED: ");
	getchar();
	printf(ccs::DECLL("2"));// 2 - set Num Lock LED
	printf("\n");

	printf("set Caps Lock LED: ");
	getchar();
	printf(ccs::DECLL("3"));// 3 - set Caps Lock LED
	printf("\n");

	printf("clear all LEDs: ");
	getchar();
	printf(ccs::DECLL("0"));// 0 - clear all LEDs
	printf("\n");

	printf("Set scrolling region: ");
	getchar();
	printf(ccs::DECSTBM("10","20"));// Set scrolling region; parameters are top and bottom row.
	printf("\n");

	printf("Save cursor location: ");
	getchar();
	printf(ccs::SCL);// Save cursor location.
	printf("\n");

	printf("Restore cursor location: ");
	getchar();
	printf(ccs::RCL);// Restore cursor location.
	printf("\n");

	printf("Move cursor to indicated column in current row: "); // DUPLICATE
	getchar();
	printf(ccs::HPA("0"));// Move cursor to indicated column in current row.
	printf("\n");

	// RST // reset all attributes to their defaults
	// BOLD // set bold
	// HalfBright // set half-bright (simulated with color on a color display)
	// UNDRSCR // set underscore (simulated with color on a color display) (the colors used to simulate dim or underline are set using ESC ] ...)
	// BLINK // set blink
	// RVRS // set reverse video
	// PrimFont // reset selected mapping, display control flag, and toggle meta flag (ECMA-48 says primary font).
	// FiAlFont // select null mapping, set display control flag, reset toggle meta flag (ECMA-48 says first alternate font).
	// SeAlFont // select null mapping, set display control flag, set toggle meta flag (ECMA-48 says second alternate font).  The toggle meta flag causes the high bit of a byte to be toggled before the mapping table translation is done.
	// UNDRLN // set underline; before Linux 4.17, this value set normal intensity (as is done in many other terminals)
	// SetNormInt // set normal intensity
	// UNDRLNOFF // underline off
	// BLINKOFF // blink off
	// RVRSOFF // reverse video off
	// BLACK_FG // set black foreground
	// RED_FG // set red foreground
	// GREEN_FG / set green foreground
	// BROWN_FG // set brown foreground
	// BLUE_FG // set blue foreground
	// MAGENTA_FG // set magenta foreground
	// CYAN_FG // set cyan foreground
	// WHITE_FG // set white foreground
	// FGTYPE // 256/24-bit foreground color follows, shoehorned into 16 basic colors (before Linux 3.16: set underscore on, set default foreground color)
	// FGRESET // set default foreground color (before Linux 3.16: set underscore off, set default foreground color)
	// BLACK_BG // set black background
	// RED_BG // set red background
	// GREEN_BG // set green background
	// BROWN_BG // set brown background
	// BLUE_BG // set blue background
	// MAGENTA_BG // set magenta background
	// CYAN_BG // set cyan background
	// WHITE_BG // set white background
	// BGTYPE // 256/24-bit background color follows, shoehorned into 8 basic colors
	// BGRESET // set default background color

	// FG_BRIGHT1 // set foreground to bright 1
	// FG_BRIGHT2 // set foreground to bright 2
	// FG_BRIGHT3 // set foreground to bright 3
	// FG_BRIGHT4 // set foreground to bright 4
	// FG_BRIGHT5 // set foreground to bright 5
	// FG_BRIGHT6 // set foreground to bright 6
	// FG_BRIGHT7 // set foreground to bright 7
	// FG_BRIGHT8 // set foreground to bright 8

	// BG_BRIGHT1 // set background to bright 1
	// BG_BRIGHT2 // set background to bright 2
	// BG_BRIGHT3 // set background to bright 3
	// BG_BRIGHT4 // set background to bright 4
	// BG_BRIGHT5 // set background to bright 5
	// BG_BRIGHT6 // set background to bright 6
	// BG_BRIGHT7 // set background to bright 7
	// BG_BRIGHT8 // set background to bright 8

	printf("Build SGR Sequences Together: ");
	getchar();
	printf("%sTest Text",ccs::SGR_BUILD("1;2;4;5;7"));// Build SGR Sequences Together
	printf("\n");

	printf("Set font color 64 seq number: ");
	getchar();
	printf("%sTest Text",ccs::x256COLORSEQ("38","64"));// 256 color: values 0..15 are IBGR (black, red, green, ... white), 16..231 a 6x6x6 color cube, 232..255 a grayscale ramp
	printf("\n");

	printf("Set font color r:128 g:64 b:32 : ");
	getchar();
	printf("%sTest Text",ccs::x256COLORRGB("38","128","64","32"));// 24-bit color, r/g/b components are in the range 0..255
	printf("\n");

	printf("Display control chars: ");
	getchar();
	printf(ccs::DECCRM("3"));// 3 - DECCRM (default off): Display control chars.
	printf("\n");

	printf("Set insert mode: ");
	getchar();
	printf(ccs::DECCRM("4"));// 4 - DECIM (default off): Set insert mode.
	printf("\n");

	printf("Automatically follow echo of LF, VT, or FF with CR: ");
	getchar();
	printf(ccs::DECCRM("20"));// 20 - LF/NL (default off): Automatically follow echo of LF, VT, or FF with CR.
	printf("\n");

	printf("Device status report: ");
	getchar();
	printf(ccs::DSR("5"));// 5 - Device status report (DSR): Answer is ESC [ 0 n (Terminal OK).
	printf("\n");

	printf("Cursor position report: ");
	getchar();
	printf(ccs::DSR("6"));// 6 - Cursor position report (CPR): Answer is ESC [ y ; x R, where x,y is the cursor location.
	printf("\n");
	
	// DECCKM (default off): When set, the cursor keys printf an ESC O prefix, rather than ESC [. 
	// DECCOLM (default off 80 columns): 80/132 col mode switch. The driver sources note that this alone does not suffice; some user-mode utility such as resizecons(8) has to change the hardware registers on the console video card. 
	// DECSCNM (default off): Set reverse-video mode.
	// DECOM (default off): When set, cursor addressing is relative to the upper left corner of the scrolling region. 
	// DECAWM (default on): Set autowrap on.  In this mode, a graphic character emitted after column 80 (or column 132 of DECCOLM is on) forces a wrap to the beginning of the following line first. 
	// DECARM (default on): Set keyboard autorepeat on.
	// X10MR1 X10 Mouse Reporting (default off): Set reporting mode to 1 (or reset to 0) — see below.
	// DECTECM (default on): Make cursor visible.
	// X11MR2 X11 Mouse Reporting (default off): Set reporting mode to 2 (or reset to 0) — see below.

	printf("set dec sequence mouse reporting: ");
	getchar();
	printf(ccs::DECSET(ccs::X11MR2));// set dec sequence
	printf("\n");

	printf("unset dec sequence mouse reporting: ");
	getchar();
	printf(ccs::DECRST(ccs::X11MR2));// unset dec sequence
	printf("\n");

	printf("Set color n as the underline color: ");
	getchar();
	printf(ccs::setUnderlineColor("0"));// Set color n as the underline color.
	printf("\n");

	printf("Set color n as the dim color: ");
	getchar();
	printf(ccs::setDimColor("0"));// Set color n as the dim color.
	printf("\n");

	printf("Make the current color pair the default attributes: ");
	getchar();
	printf(ccs::MakeCurColorPairDefAttr);// Make the current color pair the default attributes.
	printf("\n");

	printf("Set screen blank timeout to n minutes: ");
	getchar();
	printf(ccs::setScreenTimeoutColor("0"));// Set screen blank timeout to n minutes.
	printf("\n");

	printf("Set bell frequency in Hz: ");
	getchar();
	printf(ccs::setBellFrequencyInHz("0"));// Set bell frequency in Hz.
	printf("\n");

	printf("Set bell duration in msec: ");
	getchar();
	printf(ccs::setBellDurationMilli("0"));// Set bell duration in msec.
	printf("\n");

	printf("Bring specified console to the front: ");
	getchar();
	printf(ccs::bringSpecifiedConsoleToTheFont("0"));// Bring specified console to the front.
	printf("\n");

	printf("Unblank the screen: ");
	getchar();
	printf(ccs::unblankTheScreen);// Unblank the screen.
	printf("\n");

	printf("Set the VESA powerdown interval in minutes: "); // xterm drops for the end of program
	getchar();
	printf(ccs::setVesaPwrDwnInterval("0"));// Set the VESA powerdown interval in minutes.
	printf("\n");

	printf("Bring the previous console to the front: ");
	getchar();
	printf(ccs::bringThePreviousConsoleToTheFront);// Bring the previous console to the front (since Linux 2.6.0).
	printf("\n");

	printf("Set the cursor blink interval in milliseconds: ");
	getchar();
	printf(ccs::setCursorBlinkInterval("0"));// Set the cursor blink interval in milliseconds (since Linux 4.2).
	printf("\n");

	#ifndef __linux__

		printf("Single shift 2: ");
		getchar();
		printf(ccs::SS2);// Single shift 2. (Select G2 character set for the next character only.)
		printf("\n");

		printf("Single shift 3: ");
		getchar();
		printf(ccs::SS3);// Single shift 3. (Select G3 character set for the next character only.)
		printf("\n");

		printf("Device control string: ");
		getchar();
		printf(ccs::DCS);// Device control string (ended by ESC \)
		printf("\n");

		printf("Start of string: ");
		getchar();
		printf(ccs::SOS);// Start of string.
		printf("\n");

		printf("Privacy message: ");
		getchar();
		printf(ccs::PM);// Privacy message (ended by ESC \)
		printf("\n");

		printf("String terminator: ");
		getchar();
		printf(ccs::ST);// String terminator
		printf("\n");

		printf("Designate G2 character set: ");
		getchar();
		printf(ccs::DG2CS);// Designate G2 character set
		printf("\n");

		printf("Designate G3 character set: ");
		getchar();
		printf(ccs::DG3CS);// Designate G3 character set
		printf("\n");

		printf("Set Icon Name And Window Title: ");
		getchar();
		printf(ccs::setIconNameAndWindowTitle(TXT));
		printf("\n");

		printf("Set Icon Name: ");
		getchar();
		printf(ccs::setIconName(TXT));
		printf("\n");

		printf("Set Window Title: ");
		getchar();
		printf(ccs::setWindowTitle(TXT));
		printf("\n");

		printf("Set Ansi Color Num To Txt: ");
		getchar();
		printf(ccs::setAnsiColorNumToTxt(NUM, TXT));
		printf("\n");

		printf("Set Dynamic Text Color To Txt: ");
		getchar();
		printf(ccs::setDynamicTextColorToTxt(TXT));
		printf("\n");

		printf("Change Log File To Name: ");
		getchar();
		printf(ccs::changeLogFileToName(NAME));
		printf("\n");

		printf("Set Font To Fn: ");
		getchar();
		printf(ccs::setFontToFn(FN));
		printf("\n");

		printf("Cursor to lower left corner of screen: ");
		getchar();
		printf(ccs::CTLLCOS);// Cursor to lower left corner of screen (if enabled by xterm(1)s hpLowerleftBugCompat resource)
		printf("\n");

		printf("Locks memory above the cursor: ");
		getchar();
		printf(ccs::LMATC);// Memory lock (per HP terminals). Locks memory above the cursor.
		printf("\n");

		printf("Memory unlock: ");
		getchar();
		printf(ccs::MEMUNLCK);// Memory unlock (per HP terminals).
		printf("\n");

		printf("Invoke the G2 character set: ");
		getchar();
		printf(ccs::LS2);// Invoke the G2 character set.
		printf("\n");

		printf("Invoke the G3 character set: ");
		getchar();
		printf(ccs::LS3);// Invoke the G3 character set.
		printf("\n");

		printf("Invoke the G3 character set as GR: ");
		getchar();
		printf(ccs::LS3R);// Invoke the G3 character set as GR.
		printf("\n");

		printf("Invoke the G2 character set as GR: ");
		getchar();
		printf(ccs::LS2R);// Invoke the G2 character set as GR.
		printf("\n");

		printf("Invoke the G1 character set as GR: ");
		getchar();
		printf(ccs::LS1R);// Invoke the G1 character set as GR.
		printf("\n");
	#else
		printf("VT100 console sequences not implemented on the Linux console !!!");
	#endif

	exit(0);
}