#include "main.hpp"

pInterface interface;

void Render();

void Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);

    interface.drawPieces();
    interface.pRender = Render;

    glutSwapBuffers();
}

void Resize(GLint newWidth, GLint newHeight) {
    if (newWidth >= 8 && newHeight >= 8) {
        for (auto &i : interface.pieces) {
            i.pos.first /= interface.gameInfo.pieceSize.first;
            i.pos.second /= interface.gameInfo.pieceSize.second;
        }

        interface.gameInfo.pieceSize.first = newWidth / 16.f;
        interface.gameInfo.pieceSize.second = newHeight / 16.f;
        interface.screen.size = { newWidth, newHeight };

        for (auto &i : interface.pieces) {
            i.pos.first *= interface.gameInfo.pieceSize.first;
            i.pos.second *= interface.gameInfo.pieceSize.second;
        }

        glViewport( 0, 0, newWidth, newHeight );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( 0, GLdouble (newWidth), GLdouble (newHeight), 0);
        Render();
        glutPostRedisplay();
    }
}

void ProcessSpecialInput(int key, int x, int y) {

}

void ProcessInput(unsigned char key, int x, int y) {
    if (key == 'F') {
        for (int i = interface.pieces.size() - 1; i >= 0; --i)
            printf("%s, %d, %d\n", interface.pieces.at(i).value.c_str(), interface.pieces.at(i).pos.first, interface.pieces.at(i).pos.second);
    }
}

void HandleMouseKeys(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON: {
            interface.screen.leftClick = state;

            if (state != GLUT_DOWN)
                break;

            interface.handleClick();

            break;
        }
        case GLUT_RIGHT_BUTTON: {
            interface.screen.rightClick = state;

            if (state != GLUT_DOWN)
                break;
            
            interface.handleClick(true);

            break;
        }
    }
    Render();
}

void HandleMouseMovement(int x, int y) {
    interface.screen.mousePointer = { x, y };
}

void HandleMouseDrag(int x, int y) {
    interface.screen.mousePointer = { x, y };
    if (interface.screen.leftClick != interface.screen.leftClickDrag)
        interface.screen.leftClickDrag = interface.screen.leftClick;
}

void HandleIdle() {

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(interface.screen.initialSize.first, interface.screen.initialSize.second);
    glutCreateWindow (interface.screen.windowName.c_str());

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( 0, interface.screen.initialSize.first, interface.screen.initialSize.second, 0);
    glClearColor(interface.gameInfo.pieceColor.r / 255.f, interface.gameInfo.pieceColor.g / 255.f, interface.gameInfo.pieceColor.b / 255.f, 1.0);

    glutDisplayFunc(Render);
    glutKeyboardFunc(ProcessInput);
    glutSpecialFunc(ProcessSpecialInput);
    glutReshapeFunc(Resize);
    glutMouseFunc(HandleMouseKeys);
    glutPassiveMotionFunc(HandleMouseMovement);
    glutMotionFunc(HandleMouseDrag);
    glutIdleFunc(HandleIdle);

    glutMainLoop();

    return 0;
}