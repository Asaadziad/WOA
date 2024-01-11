#ifndef GAME_UI_H
#define GAME_UI_H

#include "stdbool.h"

typedef struct game_ui_t* UI;

void begin();
void end();

bool uiIsInteractable(UI ui);
bool uiInteracted(UI ui);

#endif
