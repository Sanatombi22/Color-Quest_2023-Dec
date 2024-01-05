#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

bool tertiaryGameStarted = false;
float tertiaryPrimaryR, tertiaryPrimaryG, tertiaryPrimaryB;
float tertiarySecondaryR, tertiarySecondaryG, tertiarySecondaryB;

void generateRandomColor(float& r, float& g, float& b) {
    r = static_cast<float>(rand()) / RAND_MAX;
    g = static_cast<float>(rand()) / RAND_MAX;
    b = static_cast<float>(rand()) / RAND_MAX;
}
void colorMatchingGame(float primaryR, float primaryG, float primaryB, float secondaryR, float secondaryG, float secondaryB);
void colorMatchingGame(float primaryR, float primaryG, float primaryB, float secondaryR, float secondaryG, float secondaryB);
enum GameState {
    MAIN_MENU,
    LEVEL_SELECTION,
    LEVEL_ONE,
    LEVEL_TWO,
    LEVEL_THREE
};

GameState currentState = MAIN_MENU;

void exitGame() {
    glutLeaveMainLoop();
}

void handleMouse(int button, int state, int x, int y) {
    if (currentState == MAIN_MENU && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x >= 360 && x <= 460 && y >= 290 && y <= 360) {
            currentState = LEVEL_SELECTION;
        }
    } else if (currentState == LEVEL_SELECTION && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x >= 110 && x <= 200 && y >= 110 && y <= 200) {
            currentState = LEVEL_ONE;
        } else if (x >= 250 && x <= 340 && y >= 110 && y <= 200) {
            currentState = LEVEL_TWO;
        } else if (x >= 390 && x <= 480 && y >= 110 && y <= 200) {
            currentState = LEVEL_THREE;
        }
    }
}


void drawExitButton() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(10, 20);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Exit");
}

void drawPlayGameButton() {
    glColor3ub(0, 26, 75);
    glBegin(GL_QUADS);
    glVertex2i(360, 290);
    glVertex2i(460, 290);
    glVertex2i(460, 340);
    glVertex2i(360, 340);
    glEnd();
    glColor3ub(244, 178, 162);
    glRasterPos2i(365, 315);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Play Game");
}

void drawLevelSelection() {
    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 800, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex2i(800, 800);
    glVertex2i(0, 0);
    glVertex2i(0, 800);
    glVertex2i(800, 0);
    glEnd();

    // Level selection box
    glBegin(GL_QUADS);
    glColor3f(0.8863f, 0.3843f, 0.0980f); // Color #E26219
    glVertex2d(100, 100);
    glVertex2d(700, 100);
    glVertex2d(700, 700);
    glVertex2d(100, 700);
    glEnd();

    // Level 1 button
    glBegin(GL_POLYGON);
    glColor3f(0.1137f, 0.6157f, 0.9020f);
    glVertex2f(110, 110);
    glVertex2f(200, 110);
    glVertex2f(200, 200);
    glVertex2f(110, 200);
    glEnd();

    // Level 1 text
    glColor3ub(50, 89, 84);
    glRasterPos2i(121, 155);
    const char* levelText1 = "Level 1";
    int levelTextLength1 = strlen(levelText1);

    for (int i = 0; i < levelTextLength1; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelText1[i]);
    }

    // Level 2 button
    glBegin(GL_POLYGON);
    glColor3f(0.9020f, 0.1137f, 0.6157f);
    glVertex2f(210, 110);
    glVertex2f(300, 110);
    glVertex2f(300, 200);
    glVertex2f(210, 200);
    glEnd();

    // Level 2 text
    glColor3ub(84, 50, 89);
    glRasterPos2i(221, 155);
    const char* levelText2 = "Level 2";
    int levelTextLength2 = strlen(levelText2);

    for (int i = 0; i < levelTextLength2; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelText2[i]);
    }

    // Level 3 button
    glBegin(GL_POLYGON);
    glColor3f(0.6157f, 0.9020f, 0.1137f);
    glVertex2f(310, 110);
    glVertex2f(400, 110);
    glVertex2f(400, 200);
    glVertex2f(310, 200);
    glEnd();

    // Level 3 text
    glColor3ub(89, 84, 50);
    glRasterPos2i(321, 155);
    const char* levelText3 = "Level 3";
    int levelTextLength3 = strlen(levelText3);

    for (int i = 0; i < levelTextLength3; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelText3[i]);
    }

    glFlush();
}

void drawLevelOne() {

}

void drawLevelTwo() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Level Two elements here
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 800);

    // Background
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex2i(800, 800);
    glVertex2i(0, 800);
    glVertex2i(0, 0);
    glVertex2i(800, 0);
    glEnd();

    // Example: Draw a yellow circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glVertex2f(400, 400); // Center of the circle
    for (int i = 0; i <= 360; i++) {
        glVertex2f(400 + 50 * cosf((GLfloat)i * 3.14159f / 180.0f),
                   400 + 50 * sinf((GLfloat)i * 3.14159f / 180.0f));
    }
    glEnd();

    // Example: Draw a purple triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.0f, 0.5f); // Purple color
    glVertex2f(200, 200);
    glVertex2f(300, 200);
    glVertex2f(250, 300);
    glEnd();

    // Example: Draw a cyan line
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan color
    glVertex2f(500, 200);
    glVertex2f(600, 300);
    glEnd();

    glFlush();
}

void drawLevelThree() {
}



void display() {
    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 800, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentState) {
        case MAIN_MENU:
            drawExitButton();
            drawPlayGameButton();
            break;
        case LEVEL_SELECTION:
            drawLevelSelection();
            break;
        case LEVEL_ONE:
            drawLevelOne();
            break;
        case LEVEL_TWO:
            drawLevelTwo();
            break;
        case LEVEL_THREE:
            drawLevelThree();
            break;
    }


    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ASCII code for the ESC key
            exitGame();
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Opengl Game");

    glClearColor(1.0f, 0.89f, 0.70f, 1.0); // Background color

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(handleMouse);

    glutMainLoop();
    return 0;
}
