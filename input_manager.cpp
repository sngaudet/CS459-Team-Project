#include "main.h"

int mouseX, mouseY;
int mouseMotionX, mouseMotionY;
bool leftPressed = false;
bool rightPressed = false;

extern float cameraRotationX;
extern float cameraRotationY;
extern float cameraPanX;
extern float cameraPanY;
extern float cameraZoomZ;

// Add a variable to track the current mode
enum CameraMode { ZOOM, PAN, ROTATE };
CameraMode currentMode = ROTATE;

// Keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1': // Toggle to Zoom mode
        currentMode = ZOOM;
        break;
    case '2': // Toggle to Pan mode
        currentMode = PAN;
        break;
    case '3': // Toggle to Rotate mode
        currentMode = ROTATE;
        break;
    case 's': // Move up or zoom in
        if (currentMode == ZOOM) {
            cameraZoomZ -= 0.5f;
        } else if (currentMode == PAN) {
            cameraPanY += 0.1f;
        } else if (currentMode == ROTATE) {
            cameraRotationX -= 1.0f;
        }
        break;
    case 'w': // Move down or zoom out
        if (currentMode == ZOOM) {
            cameraZoomZ += 0.5f;
        } else if (currentMode == PAN) {
            cameraPanY -= 0.1f;
        } else if (currentMode == ROTATE) {
            cameraRotationX += 1.0f;
        }
        break;
    case 'd': // Move left
        if (currentMode == PAN) {
            cameraPanX -= 0.1f;
        } else if (currentMode == ROTATE) {
            cameraRotationY -= 1.0f;
        }
        break;
    case 'a': // Move right
        if (currentMode == PAN) {
            cameraPanX += 0.1f;
        } else if (currentMode == ROTATE) {
            cameraRotationY += 1.0f;
        }
        break;
    default:
        break;
    }

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

    // Handle mouse scroll for zoom
    if (button == 3) {
        cameraZoomZ -= 0.5f;
    }
    else if (button == 4) {
        cameraZoomZ += 0.5f;
    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    if (leftPressed || rightPressed) {
        int dx = x - mouseX;
        int dy = y - mouseY;

        if (leftPressed) {
            cameraRotationX += dy * 0.2f;
            cameraRotationY += dx * 0.2f;
        } else if (rightPressed) {
            cameraPanX += dx * 0.01f;
            cameraPanY -= dy * 0.01f;
        }

        mouseX = x;
        mouseY = y;

        glutPostRedisplay();
    }
}