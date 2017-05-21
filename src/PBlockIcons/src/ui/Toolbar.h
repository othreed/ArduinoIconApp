//
// Created by indrek on 7.05.2017.
//

#ifndef PBLOCKICONS_TOOLBAR_H
#define PBLOCKICONS_TOOLBAR_H


#include "Button.h"
#include "DrawingGrid.h"
#include "UiConstants.h"


class Tools;


class Toolbar {
    static const uint8_t MAX_BUTTON_COUNT = 14;
    Button1<Tools, uint8_t> buttons[MAX_BUTTON_COUNT];
    uint8_t buttonCount = 0;

public:

    static const uint16_t TOOLBAR_X = DrawingGrid::GRID_X +  DrawingGrid::GRID_W + 2;
    static const uint16_t TOOLBAR_Y = DrawingGrid::GRID_Y;
    static const uint16_t TOOLBAR_W = SCREEN_WIDTH - TOOLBAR_X;
    static const uint16_t TOOLBAR_H = DrawingGrid::GRID_H;


    Toolbar() {}

    void init();
    void reset();

    Button1<Tools, uint8_t> & addButton(bool wide);

    void draw();

private:
    uint8_t getHalfButtonWidth(uint8_t buttonIndex);



};


#endif //PBLOCKICONS_TOOLBAR_H
