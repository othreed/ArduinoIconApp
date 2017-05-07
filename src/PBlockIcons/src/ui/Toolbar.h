//
// Created by indrek on 7.05.2017.
//

#ifndef PBLOCKICONS_TOOLBAR_H
#define PBLOCKICONS_TOOLBAR_H


#include "Button.h"
#include "DrawingGrid.h"
#include "UiConstants.h"


class Toolbar {
    static const uint8_t MAX_BUTTON_COUNT = 7;
    ButtonBase * buttons[MAX_BUTTON_COUNT];
    uint8_t buttonCount = 0;

public:

    static const uint16_t TOOLBAR_X = DrawingGrid::GRID_X +  DrawingGrid::GRID_W + 3;
    static const uint16_t TOOLBAR_Y = DrawingGrid::GRID_Y;
    static const uint16_t TOOLBAR_W = SCREEN_WIDTH - TOOLBAR_X;
    static const uint16_t TOOLBAR_H = DrawingGrid::GRID_H;
    static const uint16_t TOOLBAR_BUTTON_H = 40;

    void init();
    void addButton(ButtonBase & button, const char * label);
    void addButton(ButtonBase & button, Icon * icon);
    void setActive(bool active);
    void draw(bool redrawAll);



};


#endif //PBLOCKICONS_TOOLBAR_H