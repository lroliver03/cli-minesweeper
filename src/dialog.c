#include "dialog.h"

dialog_result_t doDialog(const uint8_t top, const uint8_t left, const uint8_t width, const uint8_t height, const char *title, const char *content, const dialog_form_t form) {
  control_t input;
  uint8_t cursor;

  uint8_t options;
  if (form == DIALOG_FORM_OK) 
    options = 1;
  else if (form == DIALOG_FORM_OK_CANCEL || form == DIALOG_FORM_YES_NO) 
    options = 2;

  dialog_result_t buttons[options];
  if (form == DIALOG_FORM_OK) 
    buttons[0] = DIALOG_OK;
  else if (form == DIALOG_FORM_OK_CANCEL) {
    buttons[0] = DIALOG_OK;
    buttons[1] = DIALOG_CANCEL;
  } else if (form == DIALOG_FORM_YES_NO) {
    buttons[0] = DIALOG_YES;
    buttons[1] = DIALOG_NO;
  }

  drawDialog(top, left, width, height, title, content);

  uint8_t active = 1;
  while (active) {
    drawDialogButtons(top, left, width, height, form, cursor);
    input = getInput();
    switch (input) {
      case MOVE_LEFT:
        cursor = (cursor + options - 1) % options;
        break;
      case MOVE_RIGHT:
        cursor = (cursor + 1) % options;
        break;
      case ACTION_CLICK:
        return buttons[cursor];
      case ACTION_QUIT:
        active = 0;
        break;
    }
  }

  return DIALOG_UNRESOLVED;
}

void drawDialog(const uint8_t top, const uint8_t left, const uint8_t width, const uint8_t height, const char *title, const char *content) {
  ESC_GOTO(left, top);
  putchar(CHAR_BORDER_CORNER);
  for (int j = 2; j < width; ++j)
    putchar(CHAR_BORDER_HORIZONTAL);
  putchar(CHAR_BORDER_CORNER);

  for (int i = 2; i < height; ++i) {
    ESC_GOTO(left, top + i - 1);
    putchar(CHAR_BORDER_VERTICAL);
    for (int j = 2; j < width; ++j)
      putchar(' ');
    putchar(CHAR_BORDER_VERTICAL);
  }

  ESC_GOTO(left, top + height - 1);
  putchar(CHAR_BORDER_CORNER);
  for (int j = 2; j < width; ++j)
    putchar(CHAR_BORDER_HORIZONTAL);
  putchar(CHAR_BORDER_CORNER);

  const uint8_t title_len = (title != NULL)?(strlen(title)):(0);
  const uint8_t content_len = (content != NULL)?(strlen(content)):(0);

  const uint8_t title_pos = left + (width - title_len)/2;
  ESC_GOTO(title_pos, top + 1);
  printf("%s%s%s%s", ESC_BOLD, ESC_UNDERLINE, title, ESC_RESET);

  uint8_t line = 0;
  for (int c = 0; c < content_len;) {
    ESC_GOTO(left + 2, top + line + 3);
    for (int j = 4; j < width; ++j) {
      if (c >= content_len) 
        break;
      else if (content[c+1] != ' ' && j == width - 1)
        putchar('-');
      else
        putchar(content[c++]);
    }
    ++line;
  }
}

void drawDialogButtons(const uint8_t top, const uint8_t left, const uint8_t width, const uint8_t height, const dialog_form_t form, const uint8_t cursor) {
  ESC_GOTO(left + 2, top + height - 2);
  switch (form) {
    case DIALOG_FORM_OK:
      printf("%sOK%s", ESC_REVERSE, ESC_RESET);
      break;
    case DIALOG_FORM_OK_CANCEL:
      if (cursor == 0)
        printf(ESC_REVERSE);
      printf("OK");
      if (cursor == 0)
        printf(ESC_RESET);
      
      printf(" ");

      if (cursor == 1)
        printf(ESC_REVERSE);
      printf("CANCEL");
      if (cursor == 1)
        printf(ESC_RESET);
      
      break;
    case DIALOG_FORM_YES_NO:
      if (cursor == 0)
        printf(ESC_REVERSE);
      printf("YES");
      if (cursor == 0)
        printf(ESC_RESET);
      
      printf(" ");

      if (cursor == 1)
        printf(ESC_REVERSE);
      printf("NO");
      if (cursor == 1)
        printf(ESC_RESET);
      
      break;
  }

  ESC_GOTO(left + width - 1, top + height - 1);
}
