//
// Created by indrek on 25.03.2017.
//

#ifndef PBLOCKMAIN_PBLOCKSUSER_INTERFACE_H
#define PBLOCKMAIN_PBLOCKSUSER_INTERFACE_H


#include "TouchHandler.h"
#include "src/screen/TFT.h"
#include "CalibrationView.h"
#include "DrawingGrid.h"
#include "ColorPickerView.h"
#include "ExampleView.h"
#include "Tools.h"
#include "src/icons/Icon.h"
#include "src/storage/IconMem.h"


class PBlocksUserInterface {

    static const uint8_t UNDO_BUFFER_DEPTH = 10;
    IconStorageData undoBuffer[UNDO_BUFFER_DEPTH];
    uint8_t undoStart = 0;
    uint8_t undoEnd = 0;
    uint8_t undoIndex = 0;


public:
    TFT tft;
    TouchHandler touchHandler;
    CalibrationView calibration;
    DrawingGrid drawingGrid;
    ColorPickerView pickerView;
    ExampleView exampleView;
    Tools tools;
    IconBufferMem activeIcon;
    IconMem iconStorage;



    PBlocksUserInterface();
    void init();

    void draw();
    void iconReloaded();
    void iconPixelsUpdated();
    void iconBorderUpdated();
    void iconColorUpdated();


    void saveToUndoBuffer();
    void undo();
    void redo();
    void loadFromUndoBuffer();

    bool isUndoAvailable();
    bool isRedoAvailable();

    void setActiveIcon(IconStorageData & data);
    void loadActiveIcon(IconStorageData & data);
    void showDrawingGrid();
    void showColorPicker(ColorPickerButton * button);
    void run();


private:
    void refreshUpdatedIcon(bool pixels, bool border, bool colors);


};


extern PBlocksUserInterface * UI;

#endif //PBLOCKMAIN_PBLOCKSUSER_INTERFACE_H
