#pragma once

#define ESC_GOUP(dy) printf("\033[%dA", dy)
#define ESC_GODOWN(dy) printf("\033[%dB", dy)
#define ESC_GORIGHT(dx) printf("\033[%dC", dx)
#define ESC_GOLEFT(dx) printf("\033[%dD", dx)

#define ESC_GONEXTLINE(n) printf("\033[%dE", n)
#define ESC_GOPREVLINE(n) printf("\033[%dF", n)

#define ESC_GOTO(x,y) printf("\033[%d;%dH", y, x)

#define ESC_ERASENEXT() printf("\033[0J")
#define ESC_ERASEPREV() printf("\033[1J")
#define ESC_ERASEALL() printf("\033[2J")
#define ESC_ERASENEXT_INLINE() printf("\033[0K")
#define ESC_ERASEPREV_INLINE() printf("\033[1K")
#define ESC_ERASELINE() printf("\033[2K")
