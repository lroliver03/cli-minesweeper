#pragma once

#define ESC_BOLD "\033[1m"
#define ESC_DIM "\033[2m"
#define ESC_ITALIC "\033[3m"
#define ESC_UNDERLINE "\033[4m"
#define ESC_BLINKING "\033[5m"
#define ESC_REVERSE "\033[7m"
#define ESC_HIDDEN "\033[8m"
#define ESC_STRIKETHROUGH "\033[9m"

#define ESC_UNBOLD "\033[21m" // boldn't
#define ESC_UNDIM "\033[22m" // dimn't
#define ESC_UNITALIC "\033[23m" // italicn't
#define ESC_UNUNDERLINE "\033[24m" // underlinen't
#define ESC_UNBLINKING "\033[25m" // blinkingn't
#define ESC_UNREVERSE "\033[27m" // reversen't
#define ESC_UNHIDDEN "\033[28m" // hiddenn't
#define ESC_UNSTRIKETHROUGH "\033[29m" // strikethroughn't

#ifndef ESC_RESET
#define ESC_RESET "\033[0m"
#endif
