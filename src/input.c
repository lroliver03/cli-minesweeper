#include "input.h"

control_t getInput() {
  switch (getc(stdin)) {
    case KEY_FLAG:
    case KEY_FLAG_UPPERCASE:
      return ACTION_FLAG;
    case KEY_CLICK:
      return ACTION_CLICK;
    case KEY_QUIT:
      return ACTION_QUIT;
    case '\033':
      getc(stdin);
      switch (getc(stdin)) {
        case 'A':
          return MOVE_UP;
        case 'B':
          return MOVE_DOWN;
        case 'C':
          return MOVE_RIGHT;
        case 'D':
          return MOVE_LEFT;
      }
  }
  return ACTION_INVALID;
}
