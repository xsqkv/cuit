// pseudo graphics enumeration class file 

#pragma once

class pseudoGraphics
{
    public:
    enum Single : uint8_t
    {
        SINGLE_HORISONTAL,
        SINGLE_VERTICAL,
        SINGLE_TRIPPLE_LEFT,
        SINGLE_TRIPPLE_RIGHT,
        SINGLE_TRIPPLE_UP,
        SINGLE_TRIPPLE_DOWN,
        SINGLE_LEFT_DOWN_CORNER,
        SINGLE_LEFT_UP_CORNER,
        SINGLE_RIGHT_DOWN_CORNER,
        SINGLE_RIGHT_UP_CORNER,
        SINGLE_CROSS,
        SINGLE_LEFT_UP_SMOOTH_CORNER,
        SINGLE_RIGHT_UP_SMOOTH_CORNER,
        SINGLE_RIGHT_DOWN_SMOOTH_CORNER,
        SINGLE_LEFT_DOWN_SMOOTH_CORNER,
    };
    const char* single[15] = {
        "─",
        "│",
        "┤",
        "├",
        "┴",
        "┬",
        "└",
        "┌",
        "┘",
        "┐",
        "┼",
        "╭",
        "╮",
        "╯",
        "╰",
    };

    enum SingleDoubled : uint8_t
    {
        SINGLE_DOUBLED_HORISONTAL,
        SINGLE_DOUBLED_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_LEFT_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_LEFT_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_RIGHT_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_RIGHT_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_UP_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_UP_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_DOWN_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_DOWN_VERTICAL,
        SINGLE_DOUBLED_LEFT_DOWN_CORNER_HORISONTAL,
        SINGLE_DOUBLED_LEFT_DOWN_CORNER_VERTICAL,
        SINGLE_DOUBLED_LEFT_UP_CORNER_HORISONTAL,
        SINGLE_DOUBLED_LEFT_UP_CORNER_VERTICAL,
        SINGLE_DOUBLED_RIGHT_DOWN_CORNER_HORISONTAL,
        SINGLE_DOUBLED_RIGHT_DOWN_CORNER_VERTICAL,
        SINGLE_DOUBLED_RIGHT_UP_CORNER_HORISONTAL,
        SINGLE_DOUBLED_RIGHT_UP_CORNER_VERTICAL,
        SINGLE_DOUBLED_CROSS_HORISONTAL,
        SINGLE_DOUBLED_CROSS_VERTICAL,
    };
    const char* singleDoubled[20] = {
        "═",
        "║",
        "╡",
        "╢",
        "╞",
        "╟",
        "╧",
        "╨",
        "╤",
        "╥",
        "╘",
        "╙",
        "╒",
        "╓",
        "╛",
        "╜",
        "╕",
        "╖",
        "╪",
        "╫",
    };

    enum Doubled : uint8_t
    {
        DOUBLED_HORISONTAL,
        DOUBLED_VERTICAL,
        DOUBLED_TRIPPLE_LEFT,
        DOUBLED_TRIPPLE_RIGHT,
        DOUBLED_TRIPPLE_UP,
        DOUBLED_TRIPPLE_DOWN,
        DOUBLED_LEFT_DOWN_CORNER,
        DOUBLED_LEFT_UP_CORNER,
        DOUBLED_RIGHT_DOWN_CORNER,
        DOUBLED_RIGHT_UP_CORNER,
        DOUBLED_CROSS,
    };
    const char* doubled[11] = {
        "═",
        "║",
        "╣",
        "╠",
        "╩",
        "╦",
        "╚",
        "╔",
        "╝",
        "╗",
        "╬",
    };

    enum Bold : uint8_t
    {
        BOLD_HORISONTAL,
        BOLD_VERTICAL,
        BOLD_TRIPPLE_LEFT,
        BOLD_TRIPPLE_RIGHT,
        BOLD_TRIPPLE_UP,
        BOLD_TRIPPLE_DOWN,
        BOLD_LEFT_DOWN_CORNER,
        BOLD_LEFT_UP_CORNER,
        BOLD_RIGHT_DOWN_CORNER,
        BOLD_RIGHT_UP_CORNER,
        BOLD_CROSS,
    };
    const char* bold[11] = {
        "━",
        "┃",
        "┫",
        "┣",
        "┻",
        "┳",
        "┗",
        "┏",
        "┛",
        "┓",
        "╋",
    };

    enum SlimBolded : uint8_t
    {
        RIGHT_SLIM_BOLDED_LINE,
        DOWN_SLIM_BOLDED_LINE,
        LEFT_SLIM_BOLDED_LINE,
        UP_SLIM_BOLDED_LINE,
        SAMPLE,
    };
    const char* slimBolded[50] = {
        "╼",
        "╽",
        "╾",
        "╿",
        "┍",
        "┎",
        "┑",
        "┒",
        "┕",
        "┖",
        "┙",
        "┚",
        "┝",
        "┞",
        "┟",
        "┠",
        "┡",
        "┢",
        "┥",
        "┦",
        "┧",
        "┨",
        "┩",
        "┪",
        "┭",
        "┮",
        "┯",
        "┰",
        "┱",
        "┲",
        "┵",
        "┶",
        "┷",
        "┸",
        "┹",
        "┺",
        "┽",
        "┾",
        "┿",
        "╀",
        "╁",
        "╂",
        "╃",
        "╄",
        "╅",
        "╆",
        "╇",
        "╈",
        "╉",
        "╊",
    };

    enum PiecesLines : uint8_t
    {
        LEFT_PIECE_INE,
        UP_PIECE_LINE,
        RIGHT_PIECE_LINE,
        DOWN_PIECE_LINE,
    };
    const char* piecesLines[4] = {
        "╴",
        "╵",
        "╶",
        "╷",
    };

    enum BoldPieces : uint8_t
    {
        LEFT_PIECE_BOLD_LINE,
        UP_PIECE_BOLD_LINE,
        RIGHT_PIECE_BOLD_LINE,
        DOWN_PIECE_BOLD_LINE,
    };
    const char* boldPieces[4] = {
        "╸",
        "╹",
        "╺",
        "╻",
    };

    enum DottedLines : uint8_t
    {
        HORISONTAL_LOW_DOTTED_LINE,
        VERTICAL_LOW_DOTTED_LINE,
        HORISONTAL_MED_DOTTED_LINE,
        VERTICAL_MED_DOTTED_LINE,
        HORISONTAL_HIGH_DOTTED_LINE,
        VERTICAL_HIGH_DOTTED_LINE,
    };
    const char* dottedLines[6] = {
        "╌",
        "╎",
        "┄",
        "┆",
        "┈",
        "┊",
    };

    enum BoldDottedLines : uint8_t
    {
        HORISONTAL_LOW_BOLD_DOTTED_LINE,
        VERTICAL_LOW_BOLD_DOTTED_LINE,
        HORISONTAL_MED_BOLD_DOTTED_LINE,
        VERTICAL_MED_BOLD_DOTTED_LINE,
        HORISONTAL_HIGH_BOLD_DOTTED_LINE,
        VERTICAL_HIGH_BOLD_DOTTED_LINE,
    };
    const char* boldDottedLines[6] = {
        "╍",
        "╏",
        "┅",
        "┇",
        "┉",
        "┉",
    };

    enum DiagonaleLines : uint8_t
    {
        DIAGONALE_LINE,
        BACK_DIAGONALE_LINE,
        DOUBLE_DIAGONALE_LINE,
    };
    const char* diagonaleLines[3] = {
        "╱",
        "╲",
        "╳",
    };

    enum Blocks : uint8_t
    {
        LOW_LIGHT_BLOCK,
        MID_LIGHT_BLOCK,
        HIGH_LIGHT_BLOCK,
        LIGHT_BLOCK,
        DOWN_HALF_BLOCK,
        UP_HALF_BLOCK,
        LEFT_HALF_BLOCK,
        RIGHT_HALF_BLOCK,
        SQUARE,
        LOW_RECTANGLE
    };
    const char* blocks[10] = {
        "░",
        "▒",
        "▓",
        "█",
        "▄",
        "▀",
        "▌",
        "▐",
        "■",
        "▬"
    };

    enum Etc : uint8_t
    {
        SMILE,
        FILLED_SMILE,
        HEART,
        CLUB,
        DIAMOND,
        SPADE,
        SMALL_FILLED_CIRCLE,
        SQUARED_CIRCLE,
        CIRCLE,
        FILLED_SQUARED_CIRCLE,
        MALE,
        FEMALE,
        EIGHT_NOTE,
        TWO_EIGHT_NOTE,
        SUN,
        RIGHT_ARROW,
        LEFT_ARROW,
        UP_ARROW,
        DOWN_ARROW,
        DOUBLE_SCREAMER,
        PILCROW,
        PARAGRAPH,
        SMALL_ARROW_UP,
        SMALL_ARROW_DOWN,
        SMALL_ARROW_RIGHT,
        SMALL_ARROW_LEFT,
        UP_DOWN_ARROW_LINE,
        UP_DOWN_ARROW,
        LEFT_RIGHT_ARROW,
        THREE_DOTS,
        CHRIST,
        DOUBLE_CHRIST,
        HORISONTAL_LINE,
        LONG_HORISONTAL_LINE,
        TM,
        LINED_CIRCLE,
        TWO_VERTICAL_LINES,
        C,
        TOP_RIGHT_CORNER,
        R,
        CELSIUS,
        PLUS_MINUS,
        FILLED_CIRCLE,
        BIG_FILLED_CIRCLE,
        BIG_BORDERED_FILLED_CIRCLE,
        WIDE_DIAMOND,
    };
    const char* etc[46] = {
        "☺",
        "☻",
        "♥",
        "♣",
        "♦",
        "♠",
        "•",
        "◘",
        "○",
        "◙",
        "♂",
        "♀",
        "♪",
        "♫",
        "☼",
        "►",
        "◄",
        "▲",
        "▼",
        "‼",
        "¶",
        "§",
        "↑",
        "↓",
        "→",
        "←",
        "↨",
        "↕",
        "↔",
        "…",
        "†",
        "‡",
        "–",
        "—",
        "™",
        "¤",
        "¦",
        "©",
        "¬",
        "®",
        "°",
        "±",
        "·",
        "●",
        "◉",
        "◆",
    };
};
