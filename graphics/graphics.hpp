#pragma once

#include <utility>
#include "../structs.hpp"

class pGraphics {
    private:

    public:
    pGraphics();
    ~pGraphics();
    
    class pButon;
    class pTextBox;
    class pCheckBox;
    class pImage;
    class pSlider;

    pColor white, black, red, green, blue, yellow, cyan, purple;
    
    std::pair<int, int> getTextSize(const char* str, void* font);
    void drawRectPoints(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, std::pair<int, int> point4, pColor color);
    void drawRect(std::pair<double, double> pos, std::pair<double, double> size, pColor color);
    void drawFilledCircle(std::pair<int, int> pos, double r, pColor color);
    void drawText(std::pair<int, int> pos, void *font, const char* str, pColor color);
    void drawTriangle(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, pColor color);
    bool mouseInRegion(std::pair<int, int> mousePointer, std::pair<int, int> pos, std::pair<int, int> size);

    pColor createNewColor(int r, int g, int b, int a = 255);
};