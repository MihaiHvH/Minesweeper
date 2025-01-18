#pragma once

#include <utility>
#include <string>

struct pColor {
    int r;
    int g;
    int b;
    int a;
};

struct pScreen {
    std::string windowName = "Minesweeper";
    std::pair<int, int> size = { 640, 640 };
    std::pair<int, int> initialSize = { 640, 640 };
    std::pair<int, int> mousePointer;
    bool leftClick = false;
    bool rightClick = false;
    bool leftClickDrag = false;
};

struct pGameInfo {
    int mines = 40;
    int flags = 0;
    bool firstClick = false;
    bool picatLemnu = false;
    bool pusLaLocLemnu = false;

    std::pair<double, double> pieceSize = { 40, 40 };

    pColor digitCol[8];
    pColor goldFlag;
    pColor downRightColor;
    pColor pieceColor;
    pColor upLeftColor;
};

struct pPiece {
    std::pair<double, double> pos;
    std::string value;
    bool show = false;
    bool flag = false;
};