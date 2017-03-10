#pragma once

enum class KeyState {
    PRESSED,
    RELEASED,
    TAPPED,
    NOTACTIVE
};

#define SCANCODE_MASK (1<<30)
#define SCANCODE_TO_KEYCODE(X) (X | SCANCODE_MASK) 
#define BUTTON(X) (1 << ((X)-1))

typedef unsigned int KeyID;

namespace Key {
    enum {
        UNKNOWN = 0,

        RETURN = '\r',
        ESCAPE = '\033',
        BACKSPACE = '\b',
        TAB = '\t',
        SPACE = ' ',
        EXCLAIM = '!',
        QUOTEDBL = '"',
        HASH = '#',
        PERCENT = '%',
        DOLLAR = '$',
        AMPERSAND = '&',
        QUOTE = '\'',
        LEFTPAREN = '(',
        RIGHTPAREN = ')',
        ASTERISK = '*',
        PLUS = '+',
        COMMA = ',',
        MINUS = '-',
        PERIOD = '.',
        FORWARDSLASH = '/',
        NUM0 = '0',
        NUM1 = '1',
        NUM2 = '2',
        NUM3 = '3',
        NUM4 = '4',
        NUM5 = '5',
        NUM6 = '6',
        NUM7 = '7',
        NUM8 = '8',
        NUM9 = '9',
        COLON = ':',
        SEMICOLON = ';',
        LESS = '<',
        EQUALS = '=',
        GREATER = '>',
        QUESTION = '?',
        AT = '@',
        LEFTBRACKET = '[',
        BACKSLASH = '\\',
        RIGHTBRACKET = ']',
        CARET = '^',
        UNDERSCORE = '_',
        BACKQUOTE = '`',
        /*
        * Only defines lowercase
        * Use modifiers to defer
        */
        a = 'a',
        b = 'b',
        c = 'c',
        d = 'd',
        e = 'e',
        f = 'f',
        g = 'g',
        h = 'h',
        i = 'i',
        j = 'j',
        k = 'k',
        l = 'l',
        m = 'm',
        n = 'n',
        o = 'o',
        p = 'p',
        q = 'q',
        r = 'r',
        s = 's',
        t = 't',
        u = 'u',
        v = 'v',
        w = 'w',
        x = 'x',
        y = 'y',
        z = 'z',

        F1 = SCANCODE_TO_KEYCODE(58),
        F2 = SCANCODE_TO_KEYCODE(59),
        F3 = SCANCODE_TO_KEYCODE(60),
        F4 = SCANCODE_TO_KEYCODE(61),
        F5 = SCANCODE_TO_KEYCODE(62),
        F6 = SCANCODE_TO_KEYCODE(63),
        F7 = SCANCODE_TO_KEYCODE(64),
        F8 = SCANCODE_TO_KEYCODE(65),
        F9 = SCANCODE_TO_KEYCODE(66),
        F10 = SCANCODE_TO_KEYCODE(67),
        F11 = SCANCODE_TO_KEYCODE(68),
        F12 = SCANCODE_TO_KEYCODE(69),

        PRINTSCREEN = SCANCODE_TO_KEYCODE(70),
        SCROLLLOCK = SCANCODE_TO_KEYCODE(71),
        PAUSE = SCANCODE_TO_KEYCODE(72),
        INSERT = SCANCODE_TO_KEYCODE(73),/**< insert on PC, help on some Mac keyboards
                                         (but does send code 73, not 117) */
        HOME = SCANCODE_TO_KEYCODE(74),
        PAGEUP = SCANCODE_TO_KEYCODE(75),
        DELETE = '\177',
        END = SCANCODE_TO_KEYCODE(77),
        PAGEDOWN = SCANCODE_TO_KEYCODE(78),
        RIGHT = SCANCODE_TO_KEYCODE(79),
        LEFT = SCANCODE_TO_KEYCODE(80),
        DOWN = SCANCODE_TO_KEYCODE(81),
        UP = SCANCODE_TO_KEYCODE(82),

        NUMLOCKCLEAR = SCANCODE_TO_KEYCODE(83),
        KP_DIVIDE = SCANCODE_TO_KEYCODE(84),
        KP_MULTIPLY = SCANCODE_TO_KEYCODE(85),
        KP_MINUS = SCANCODE_TO_KEYCODE(86),
        KP_PLUS = SCANCODE_TO_KEYCODE(87),
        KP_ENTER = SCANCODE_TO_KEYCODE(88),
        KP_1 = SCANCODE_TO_KEYCODE(89),
        KP_2 = SCANCODE_TO_KEYCODE(90),
        KP_3 = SCANCODE_TO_KEYCODE(91),
        KP_4 = SCANCODE_TO_KEYCODE(92),
        KP_5 = SCANCODE_TO_KEYCODE(93),
        KP_6 = SCANCODE_TO_KEYCODE(94),
        KP_7 = SCANCODE_TO_KEYCODE(95),
        KP_8 = SCANCODE_TO_KEYCODE(96),
        KP_9 = SCANCODE_TO_KEYCODE(97),
        KP_0 = SCANCODE_TO_KEYCODE(98),
        KP_PERIOD = SCANCODE_TO_KEYCODE(99),

        APPLICATION = SCANCODE_TO_KEYCODE(101), /**< windows contextual menu, compose */

        /* Anything past here is nearly unecessary but I'll leave it in just in case. */
        POWER = SCANCODE_TO_KEYCODE(102),/**< The USB document says this is a status flag,
                                         *   not a physical key - but some Mac keyboards
                                         *   do have a power key. */

        KP_EQUALS = SCANCODE_TO_KEYCODE(103),
        F13 = SCANCODE_TO_KEYCODE(104),
        F14 = SCANCODE_TO_KEYCODE(105),
        F15 = SCANCODE_TO_KEYCODE(106),
        F16 = SCANCODE_TO_KEYCODE(107),
        F17 = SCANCODE_TO_KEYCODE(108),
        F18 = SCANCODE_TO_KEYCODE(109),
        F19 = SCANCODE_TO_KEYCODE(110),
        F20 = SCANCODE_TO_KEYCODE(111),
        F21 = SCANCODE_TO_KEYCODE(112),
        F22 = SCANCODE_TO_KEYCODE(113),
        F23 = SCANCODE_TO_KEYCODE(114),
        F24 = SCANCODE_TO_KEYCODE(115),
        EXECUTE = SCANCODE_TO_KEYCODE(116),
        HELP = SCANCODE_TO_KEYCODE(117),
        MENU = SCANCODE_TO_KEYCODE(118),
        SELECT = SCANCODE_TO_KEYCODE(119),
        STOP = SCANCODE_TO_KEYCODE(120),
        AGAIN = SCANCODE_TO_KEYCODE(121),
        UNDO = SCANCODE_TO_KEYCODE(122),
        CUT = SCANCODE_TO_KEYCODE(123),
        COPY = SCANCODE_TO_KEYCODE(124),
        PASTE = SCANCODE_TO_KEYCODE(125),
        FIND = SCANCODE_TO_KEYCODE(126),
        MUTE = SCANCODE_TO_KEYCODE(127),
        VOLUMEUP = SCANCODE_TO_KEYCODE(128),
        VOLUMEDOWN = SCANCODE_TO_KEYCODE(129),
        KP_COMMA = SCANCODE_TO_KEYCODE(133),
        KP_EQUALSAS400 = SCANCODE_TO_KEYCODE(134),

        ALTERASE = SCANCODE_TO_KEYCODE(153),
        SYSREQ = SCANCODE_TO_KEYCODE(154),
        CANCEL = SCANCODE_TO_KEYCODE(155),
        CLEAR = SCANCODE_TO_KEYCODE(156),
        PRIOR = SCANCODE_TO_KEYCODE(157),
        RETURN2 = SCANCODE_TO_KEYCODE(158),
        SEPARATOR = SCANCODE_TO_KEYCODE(159),
        OUT = SCANCODE_TO_KEYCODE(160),
        OPER = SCANCODE_TO_KEYCODE(161),
        CLEARAGAIN = SCANCODE_TO_KEYCODE(162),
        CRSEL = SCANCODE_TO_KEYCODE(163),
        EXSEL = SCANCODE_TO_KEYCODE(164),

        KP_00 = SCANCODE_TO_KEYCODE(176),
        KP_000 = SCANCODE_TO_KEYCODE(177),
        THOUSANDSSEPARATOR = SCANCODE_TO_KEYCODE(178),
        DECIMALSEPARATOR = SCANCODE_TO_KEYCODE(179),
        CURRENCYUNIT = SCANCODE_TO_KEYCODE(180),
        CURRENCYSUBUNIT = SCANCODE_TO_KEYCODE(181),
        KP_LEFTPAREN = SCANCODE_TO_KEYCODE(182),
        KP_RIGHTPAREN = SCANCODE_TO_KEYCODE(183),
        KP_LEFTBRACE = SCANCODE_TO_KEYCODE(184),
        KP_RIGHTBRACE = SCANCODE_TO_KEYCODE(185),
        KP_TAB = SCANCODE_TO_KEYCODE(186),
        KP_BACKSPACE = SCANCODE_TO_KEYCODE(187),
        KP_A = SCANCODE_TO_KEYCODE(188),
        KP_B = SCANCODE_TO_KEYCODE(189),
        KP_C = SCANCODE_TO_KEYCODE(190),
        KP_D = SCANCODE_TO_KEYCODE(191),
        KP_E = SCANCODE_TO_KEYCODE(192),
        KP_F = SCANCODE_TO_KEYCODE(193),
        KP_XOR = SCANCODE_TO_KEYCODE(194),
        KP_POWER = SCANCODE_TO_KEYCODE(195),
        KP_PERCENT = SCANCODE_TO_KEYCODE(196),
        KP_LESS = SCANCODE_TO_KEYCODE(197),
        KP_GREATER = SCANCODE_TO_KEYCODE(198),
        KP_AMPERSAND = SCANCODE_TO_KEYCODE(199),
        KP_DBLAMPERSAND = SCANCODE_TO_KEYCODE(200),
        KP_VERTICALBAR = SCANCODE_TO_KEYCODE(201),
        KP_DBLVERTICALBAR = SCANCODE_TO_KEYCODE(202),
        KP_COLON = SCANCODE_TO_KEYCODE(203),
        KP_HASH = SCANCODE_TO_KEYCODE(204),
        KP_SPACE = SCANCODE_TO_KEYCODE(205),
        KP_AT = SCANCODE_TO_KEYCODE(206),
        KP_EXCLAM = SCANCODE_TO_KEYCODE(207),
        KP_MEMSTORE = SCANCODE_TO_KEYCODE(208),
        KP_MEMRECALL = SCANCODE_TO_KEYCODE(209),
        KP_MEMCLEAR = SCANCODE_TO_KEYCODE(210),
        KP_MEMADD = SCANCODE_TO_KEYCODE(211),
        KP_MEMSUBTRACT = SCANCODE_TO_KEYCODE(212),
        KP_MEMMULTIPLY = SCANCODE_TO_KEYCODE(213),
        KP_MEMDIVIDE = SCANCODE_TO_KEYCODE(214),
        KP_PLUSMINUS = SCANCODE_TO_KEYCODE(215),
        KP_CLEAR = SCANCODE_TO_KEYCODE(216),
        KP_CLEARENTRY = SCANCODE_TO_KEYCODE(217),
        KP_BINARY = SCANCODE_TO_KEYCODE(218),
        KP_OCTAL = SCANCODE_TO_KEYCODE(219),
        KP_DECIMAL = SCANCODE_TO_KEYCODE(220),
        KP_HEXADECIMAL = SCANCODE_TO_KEYCODE(221),

        MODE = SCANCODE_TO_KEYCODE(257),/**< I'm not sure if this is really not covered
                                        *   by any of the above, but since there's a
                                        *   special KMOD_MODE for it I'm adding it here
                                        */


        /* These values are mapped from usage page 0x0C (USB consumer page) */
        AUDIONEXT = SCANCODE_TO_KEYCODE(258),
        AUDIOPREV = SCANCODE_TO_KEYCODE(259),
        AUDIOSTOP = SCANCODE_TO_KEYCODE(260),
        AUDIOPLAY = SCANCODE_TO_KEYCODE(261),
        AUDIOMUTE = SCANCODE_TO_KEYCODE(262),
        MEDIASELECT = SCANCODE_TO_KEYCODE(263),
        WWW = SCANCODE_TO_KEYCODE(264),
        MAIL = SCANCODE_TO_KEYCODE(265),
        CALCULATOR = SCANCODE_TO_KEYCODE(266),
        COMPUTER = SCANCODE_TO_KEYCODE(267),
        AC_SEARCH = SCANCODE_TO_KEYCODE(268),
        AC_HOME = SCANCODE_TO_KEYCODE(269),
        AC_BACK = SCANCODE_TO_KEYCODE(270),
        AC_FORWARD = SCANCODE_TO_KEYCODE(271),
        AC_STOP = SCANCODE_TO_KEYCODE(272),
        AC_REFRESH = SCANCODE_TO_KEYCODE(273),
        AC_BOOKMARKS = SCANCODE_TO_KEYCODE(274),

        /* These are values that Christian Walther added (for mac keyboard?) */
        BRIGHTNESSDOWN = SCANCODE_TO_KEYCODE(275),
        BRIGHTNESSUP = SCANCODE_TO_KEYCODE(276),
        DISPLAYSWITCH = SCANCODE_TO_KEYCODE(277),

        KBDILLUMTOGGLE = SCANCODE_TO_KEYCODE(278),
        KBDILLUMDOWN = SCANCODE_TO_KEYCODE(279),
        KBDILLUMUP = SCANCODE_TO_KEYCODE(280),
        EJECT = SCANCODE_TO_KEYCODE(281),
        SLEEP = SCANCODE_TO_KEYCODE(282)
    };

    namespace Modifier {
        enum {
            CAPSLOCK = SCANCODE_TO_KEYCODE(57),

            LCTRL = SCANCODE_TO_KEYCODE(224),
            RCTRL = SCANCODE_TO_KEYCODE(228),
            LSHIFT = SCANCODE_TO_KEYCODE(225),
            RSHIFT = SCANCODE_TO_KEYCODE(229),
            LALT = SCANCODE_TO_KEYCODE(226), /**< alt, option */
            RALT = SCANCODE_TO_KEYCODE(230), /**< alt gr, option */
            LGUI = SCANCODE_TO_KEYCODE(227), /**< windows, command (apple), meta */
            RGUI = SCANCODE_TO_KEYCODE(231) /**< windows, command (apple), meta */
        };
    }
}