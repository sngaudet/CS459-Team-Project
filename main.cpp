#include "main.h"
/*
######### CONTROLS ##########
Mouse:
    zoom:    scroll weel
    Pan:     right click drag
    Rotate:  left click drag

Keyboard: (1,2,3) to toggle mode 
    zoom:    1 [w,s]
    Pan:     2 [w,a,s,d]
    Rotate:  3 [w,a,s,d]

Paddle:
    up arrow key: move up
    down arrow key: move down
    right arrow key: move right
    left arrow key: move left
*/

float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = -5.0f;

float paddleX = 0.0f;
float paddleY = 0.0f;
float paddleZ = 8.0f;

float ballVelocityX = 0.011f;
float ballVelocityY = 0.011f;
float ballVelocityZ = 0.02f;

float cameraRotationX = 25.0f; //tilts camera to look down if positive
float cameraRotationY = -30.0f;
float cameraZoomZ = 28.0f;
float cameraPanX = 0.0f;
float cameraPanY = -5.0f; // moves camera up if negative

// Add key state tracking for paddle movement
bool keyStates[256] = { false }; // For regular keys
bool specialKeyStates[256] = { false }; // For special keys (e.g., arrow keys)

// Paddle boundary constants
const float leftWall = -10.0f;
const float rightWall = 10.0f;
const float bottomWall = -10.0f;
const float topWall = 10.0f;
const float paddleHalfWidth = 1.75f;
const float paddleHalfHeight = 1.0f;

// Function to handle key press events
void specialKeyboardDown(int key, int x, int y) {
    specialKeyStates[key] = true;
}

// Function to handle key release events
void specialKeyboardUp(int key, int x, int y) {
    specialKeyStates[key] = false;
}

// Function to update paddle position based on active key states
void updatePaddlePosition() {
    if (specialKeyStates[GLUT_KEY_LEFT]) {
        paddleX -= 0.1f; // Adjust speed as needed
    }
    if (specialKeyStates[GLUT_KEY_RIGHT]) {
        paddleX += 0.1f;
    }
    if (specialKeyStates[GLUT_KEY_UP]) {
        paddleY += 0.1f;
    }
    if (specialKeyStates[GLUT_KEY_DOWN]) {
        paddleY -= 0.1f;
    }

    // Clamp paddle position within the walls
    paddleX = std::max(leftWall + paddleHalfWidth, std::min(paddleX, rightWall - paddleHalfWidth));
    paddleY = std::max(bottomWall + paddleHalfHeight, std::min(paddleY, topWall - paddleHalfHeight));

    glutPostRedisplay();
}

// Initilizations
void initWindow(int argc, char** argv) {
    // create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("3D Pong");

    // initialize perspective
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // light properties
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLfloat lightPosition[] = { 5.0f, 5.0f, 1.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Enable color tracking for materials
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Update input handling to use standalone functions
void initInputHandlers() {
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboardDown);
    glutSpecialUpFunc(specialKeyboardUp); // Handle key release
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
}

// Drawing
void drawWalls() {
    // back wall
    int divisions = 10;
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.4f, 0.7f);
    for (int i = -10; i <= 10; i += 20 / divisions) {
        // Vertical lines
        glVertex3f(i, -10.0f, -6.0f);
        glVertex3f(i, 10.0f, -6.0f);

        // Horizontal lines
        glVertex3f(-10.0f, i, -6.0f);
        glVertex3f(10.0f, i, -6.0f);
    }
    glEnd();

    // left side wall
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = -6; i <= 10; i += 20 / divisions) {
        glVertex3f(-10.0f, -10.0f, i);
        glVertex3f(-10.0f, 10.0f, i);

        glVertex3f(-10.0f, i, -6.0f);
        glVertex3f(-10.0f,  i, 10.0f);
    }
    glEnd();

    // right side wall
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = -6; i <= 10; i += 20 / divisions) {
        glVertex3f(10.0f, -10.0f, i);
        glVertex3f(10.0f, 10.0f, i);

        glVertex3f(10.0f, i, -6.0f);
        glVertex3f(10.0f, i, 10.0f);
    }
    glEnd();

    // top wall
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    for (int i = -10; i <= 10; i += 20 / divisions) {
        glVertex3f(i, 10.0f, -6.0f);
        glVertex3f(i, 10.0f, 10.0f);
    }
    for (int i = -6; i <= 10; i += 16 / divisions) {
        glVertex3f(-10.0f, 10.0f, i);
        glVertex3f(10.0f, 10.0f, i);
    }
    glEnd();

    // bottom wall
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    for (int i = -10; i <= 10; i += 20 / divisions) {
        glVertex3f(i, -10.0f, -6.0f);
        glVertex3f(i, -10.0f, 10.0f);
    }
    for (int i = -6; i <= 10; i += 16 / divisions) {
        glVertex3f(-10.0f, -10.0f, i);
        glVertex3f(10.0f, -10.0f, i);
    }
    glEnd();
}

void drawBox()
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void drawBall() {
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
}

void drawBallShadow(float wallX, float wallY, float wallZ, float r, float g, float b) {
    glPushMatrix();

    // Determine the projection plane and align the shadow
    if (wallX != 0.0f) {
        glTranslatef(wallX, ballY, ballZ); // Project onto X plane
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Align with the X plane
    } else if (wallY != 0.0f) {
        glTranslatef(ballX, wallY, ballZ); // Project onto Y plane
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Align with the Y plane
    } else if (wallZ != 0.0f) {
        glTranslatef(ballX, ballY, wallZ); // Project onto Z plane
        // No rotation needed for Z plane
    }

    glColor3f(r, g, b); // Use custom color for the shadow
    glScalef(1.0f, 1.0f, 0.01f); // Flatten the shadow to make it appear as a 2D projection
    glutSolidSphere(0.5, 30, 30); // Render the shadow as a sphere
    glPopMatrix();
}

void drawPaddle() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(paddleX, paddleY, paddleZ);
    glScalef(3.5, 2.0, 0.7);
    glutSolidCube(1.0);
}

void drawPaddleShadow(float wallX, float wallY, float wallZ) {
    glPushMatrix();

    // Determine the projection plane and align the shadow
    if (wallX != 0.0f) {
        glTranslatef(wallX, paddleY, paddleZ); // Project onto X plane
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Align with the X plane
        glScalef(0.7f, 2.0f, 0.01f); // Scale to match paddle's height and depth
    } else if (wallY != 0.0f) {
        glTranslatef(paddleX, wallY, paddleZ); // Project onto Y plane
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Align with the Y plane
        glScalef(3.5f, 0.7f, 0.01f); // Scale to match paddle's width and depth
    } else if (wallZ != 0.0f) {
        glTranslatef(paddleX, paddleY, wallZ); // Project onto Z plane
        glScalef(3.5f, 2.0f, 0.01f); // Scale to match paddle's width and height
    }

    glColor3f(1.0f, 0.0f, 0.0f); // Use custom color for the shadow
    glBegin(GL_QUADS); // Render the shadow as a rectangle
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

void drawShadows() {
    // Draw ball shadows with custom colors
    drawBallShadow(-9.9f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Left wall (green)
    drawBallShadow(9.9f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f); // Right wall (red)
    drawBallShadow(0.0f, -9.9f, 0.0f, 0.0f, 0.0f, 1.0f); // Bottom wall (blue)
    drawBallShadow(0.0f, 9.9f, 0.0f, 1.0f, 1.0f, 0.0f); // Top wall (yellow)

    // Draw paddle shadows with custom colors
    drawPaddleShadow(-9.9f, 0.0f, 0.0f); // Left wall
    drawPaddleShadow(9.9f, 0.0f, 0.0f); // Right wall
    drawPaddleShadow(0.0f, -9.9f, 0.0f); // Bottom wall
    drawPaddleShadow(0.0f, 9.9f, 0.0f); // Top wall
}

// Transformations
void transformCamera() {
    glTranslatef(cameraPanX, cameraPanY, -cameraZoomZ);
    glRotatef(cameraRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraRotationY, 0.0f, 1.0f, 0.0f);
}

void moveBall(int value) {
    ballX += ballVelocityX;
    ballY += ballVelocityY;
    ballZ -= ballVelocityZ;

    const float ballRadius = 0.5f;

    const float leftWall = -10.0f;
    const float rightWall = 10.0f;
    const float bottomWall = -10.0f;
    const float topWall = 10.0f;
    const float backWall = -6.0f;

    // Bounce off left and right walls
    if (ballX - ballRadius <= leftWall || ballX + ballRadius >= rightWall) {
        ballVelocityX *= -1.0f;
    }

    // Bounce off top and bottom walls
    if (ballY - ballRadius <= bottomWall || ballY + ballRadius >= topWall) {
        ballVelocityY *= -1.0f;
    }

    // Bounce off the back wall
    if (ballZ - ballRadius <= backWall) {
        ballVelocityZ *= -1.0f;
    }

    const float paddleHalfWidth = 1.75f;
    const float paddleHalfHeight = 1.0f;
    const float paddleHalfDepth = 0.35f;

    // Bounce off paddle
    if (ballZ >= paddleZ - paddleHalfDepth - ballRadius &&
        ballZ <= paddleZ + paddleHalfDepth + ballRadius) {

        if (ballX >= paddleX - paddleHalfWidth && ballX <= paddleX + paddleHalfWidth &&
            ballY >= paddleY - paddleHalfHeight && ballY <= paddleY + paddleHalfHeight) {
            ballVelocityZ *= -1.0f;
        }
    }

    updatePaddlePosition(); // Update paddle position based on key states

    glutPostRedisplay();
    glutTimerFunc(16, moveBall, 0); // ~60 FPS
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply camera transformations
    transformCamera();

    drawBall();
    drawShadows();

    drawWalls(); // the grey wall is at z=-6
    drawPaddle(); // the paddle is at z=5

    glFlush();
    glutSwapBuffers();
}

void resize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    initWindow(argc, argv);
    initLighting();
    initInputHandlers(); // Initialize input handlers
    printf("Mouse:\nzoom:    scroll wheel\nPan : right click drag\nRotate : left click drag\n\nKeyboard : (1, 2, 3) to toggle mode\nzoom : 1[w, s]\nPan : 2[w, a, s, d]\nRotate : 3[w, a, s, d]\n\nPaddle :\nup arrow key : move up\ndown arrow key : move down\nright arrow key : move right\nleft arrow key : move left");

    // render
    glutDisplayFunc(display);
    glutReshapeFunc(resize);

    srand(static_cast<unsigned>(time(0))); // seed RNG
    glutTimerFunc(0, moveBall, 0);

    // TEMP, printing camera position
    //glutTimerFunc(5000, printCameraPosition, 0);

    // loop
    glutMainLoop();
    return 0;
}