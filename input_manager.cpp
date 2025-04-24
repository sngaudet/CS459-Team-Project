#include "main.h"
#include <vector>

int mouseX, mouseY;
int mouseMotionX, mouseMotionY;
bool leftPressed = false;
bool rightPressed = false;

float cameraRotationX = 0.0f;
float cameraRotationY = 0.0f;
float cameraZoomZ = 5.0f;
float cameraPanX = 0.0f;
float cameraPanY = 0.0f;

// Keyboard
void keyboard(unsigned char key, int x, int y) {
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: break;
    case GLUT_KEY_RIGHT: break;
    case GLUT_KEY_UP: break;
    case GLUT_KEY_DOWN: break;
    }
    glutPostRedisplay();
}

// Mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        leftPressed = true;
        mouseX = x;
        mouseY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        leftPressed = false;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        rightPressed = true;
        mouseX = x;
        mouseY = y;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        rightPressed = false;
    }

    // MouseWeel
    if (button == 3) {
        cameraZoomZ -= 0.5f;
    }
    else if (button == 4) {
        cameraZoomZ += 0.5f;
    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    if (leftPressed) {
        int dx = x - mouseX;
        int dy = y - mouseY;

        cameraRotationX += dy * 0.2f;
        cameraRotationY += dx * 0.2f;

        mouseX = x;
        mouseY = y;

        glutPostRedisplay();
    }
    else if (rightPressed) {
        int dx = x - mouseX;
        int dy = y - mouseY;

        cameraPanX += dx * 0.01f;
        cameraPanY -= dy * 0.01f;

        mouseX = x;
        mouseY = y;

        glutPostRedisplay();
    }
}

// Camera
void transformCamera() {
    glTranslatef(cameraPanX, cameraPanY, -cameraZoomZ);
    glRotatef(cameraRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraRotationY, 0.0f, 1.0f, 0.0f);
}

void printCameraPosition(int value) {
    std::cout << "Camera Position: x=0.0, y=-1.0, z=" << cameraZoomZ << std::endl;
    std::cout << "Camera Rotation (X-axis): " << cameraRotationX << " degrees" << std::endl;
    glutTimerFunc(5000, printCameraPosition, 0);
}