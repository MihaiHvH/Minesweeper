#include "../main.hpp"
#include "graphics.hpp"

#ifndef M_PI
    #define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
#endif

pGraphics::pGraphics() {
    black =  createNewColor(0, 0, 0);
    white =  createNewColor(255, 255,255);
    red =    createNewColor(255, 0, 0);
    green =  createNewColor(0, 255, 0);
    blue =   createNewColor(0, 0, 255);
    yellow = createNewColor(255, 255, 0);
    cyan =   createNewColor(0, 255, 255);
    purple = createNewColor(255, 0, 255);
}

pGraphics::~pGraphics() {

}

pColor pGraphics::createNewColor(int r, int g, int b, int a) {
    pColor color{};
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

bool pGraphics::mouseInRegion(std::pair<int, int> mousePointer, std::pair<int, int> pos, std::pair<int, int> size) {
    if (mousePointer.first >= pos.first &&
        mousePointer.first <= pos.first + size.first &&
        mousePointer.second >= pos.second &&
        mousePointer.second <= pos.second + size.second)
        return true;
    return false;
}

void pGraphics::drawRectPoints(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, std::pair<int, int> point4, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    glVertex2i(point1.first, point1.second);
    glVertex2i(point2.first, point2.second);
    glVertex2i(point3.first, point3.second);
    glVertex2i(point4.first, point4.second);
    glEnd();
}

void pGraphics::drawRect(std::pair<double, double> pos, std::pair<double, double> size, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    glVertex2f(pos.first, pos.second); //corner down
    glVertex2f(pos.first + size.first, pos.second); //right down corner
    glVertex2f(pos.first + size.first, pos.second + size.second); //right up corner
    glVertex2f(pos.first, pos.second + size.second); //corner up
    glEnd();
}

void pGraphics::drawFilledCircle(std::pair<int, int> pos, double r, pColor color) {
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_POLYGON);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    for (double i = 0; i <= 360;) {
        double angle = 2 * M_PI * i / 360;
        double x = cos(angle) * r;
        double y = sin(angle) * r;
        glVertex2d(pos.first + x, pos.second + y);
        i += 0.25;
    }
    glEnd();
}

void pGraphics::drawTriangle(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_TRIANGLES);
    glVertex2i(point1.first, point1.second);
    glVertex2i(point2.first, point2.second);
    glVertex2i(point3.first, point3.second);
    glEnd();
}

std::pair<int, int> pGraphics::getTextSize(const char* str, void* font) {
    const unsigned char* s = reinterpret_cast<unsigned const char*>(str);

    int wMax = -1;

    for (int i = 0; i < strlen(str); ++i) {
        if (wMax == -1)
            wMax = glutBitmapWidth(font, str[i]);
        if (wMax < glutBitmapWidth(font, str[i]))
            wMax = glutBitmapWidth(font, str[i]);
    }

    return { glutBitmapLength(font, s), wMax };
}

void pGraphics::drawText(std::pair<int, int> pos, void *font, const char *str, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glRasterPos2i(pos.first, pos.second);
    
    for (size_t i = 0; i < strlen(str); ++i)
        glutBitmapCharacter(font, str[i]);
}