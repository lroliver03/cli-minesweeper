#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ANSI_ESC/ansi.h"
#include "charset/border.h"
#include "controls.h"

typedef enum dialog_form_t {
  DIALOG_FORM_OK,
  DIALOG_FORM_OK_CANCEL,
  DIALOG_FORM_YES_NO
} dialog_form_t;

typedef enum dialog_result_t {
  DIALOG_UNRESOLVED,
  DIALOG_OK,
  DIALOG_CANCEL,
  DIALOG_YES,
  DIALOG_NO
} dialog_result_t;

dialog_result_t doDialog(const uint8_t top, const uint8_t left, const uint8_t width, const uint8_t height, const char *title, const char *content, const dialog_form_t form);

void drawDialog(const uint8_t top, const uint8_t left, const uint8_t width, const uint8_t height, const char *title, const char *content);
void drawDialogButtons(const uint8_t top, const uint8_t left, const uint8_t width, const uint8_t height, const dialog_form_t form, const uint8_t cursor);
