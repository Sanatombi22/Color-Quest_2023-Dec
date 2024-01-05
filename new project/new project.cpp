#include <GL/glut.h>
#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants
const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 20;

// Enum for snake movement direction
enum Direction { UP, DOWN, LEFT, RIGHT };

// Structure to represent a point
struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

// Enum for food colors
enum FoodColor { RED, BLUE, GREEN, OTHER };

// Structure to represent food
struct Food {
    int x, y;
    FoodColor color;

    Food() : x(0), y(0), color(RED) {}
    Food(int x, int y, FoodColor color) : x(x), y(y), color(color) {}
};

// Global variables
deque<Point> snake;
Food food;
Direction direction = RIGHT;

// Function to draw a square at given coordinates
void drawSquare(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + CELL_SIZE, y);
    glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2i(x, y + CELL_SIZE);
    glEnd();
}

// Function to draw the snake
void drawSnake() {
    glColor3f(1.0, 1.0, 1.0); // White color for the snake
    for (const auto& segment : snake) {
        drawSquare(segment.x, segment.y);
    }
}

// Function to draw the food
void drawFood() {
    if (food.color == RED) {
        glColor3f(1.0, 0.0, 0.0); // Red color for the food
    } else if (food.color == BLUE) {
        glColor3f(0.0, 0.0, 1.0); // Blue color for the food
    } else if (food.color == GREEN) {
        glColor3f(0.0, 1.0, 0.0); // Green color for the food
    } else {
        glColor3f(1.0, 0.5, 0.0); // Default color for other foods (orange)
    }
    drawSquare(food.x, food.y);
}

// Function to draw the entire scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSnake();
    drawFood();
    glutSwapBuffers();
}

// Function to update the game state
void update(int) {
    Point newHead = snake.front();

    switch (direction) {
        case UP:
            newHead.y += CELL_SIZE;
            break;
        case DOWN:
            newHead.y -= CELL_SIZE;
            break;
        case LEFT:
            newHead.x -= CELL_SIZE;
            break;
        case RIGHT:
            newHead.x += CELL_SIZE;
            break;
    }

    snake.push_front(newHead);

    // Check if the snake eats the food
    if (newHead.x == food.x && newHead.y == food.y) {
        // Generate new food
        food.x = rand() % (WIDTH / CELL_SIZE) * CELL_SIZE;
        food.y = rand() % (HEIGHT / CELL_SIZE) * CELL_SIZE;

        // Assign a random color to the food
        int colorChoice = rand() % 3; // 0: RED, 1: BLUE, 2: GREEN
        if (colorChoice == 0) {
            food.color = RED;
        } else if (colorChoice == 1) {
            food.color = BLUE;
        } else {
            food.color = GREEN;
        }
    } else {
        // Remove the tail if the snake didn't eat the food
        snake.pop_back();
    }

    // Check for collision with itself
    for (auto it = snake.begin() + 1; it != snake.end(); ++it) {
        if (newHead.x == it->x && newHead.y == it->y) {
            cout << "Game Over!" << endl;
            exit(0);
        }
    }

    // Check for collision with the walls
    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
        cout << "Game Over!" << endl;
        exit(0);
    }

    // Check if the snake eats other color food
    if (food.color == OTHER) {
        cout << "Game Over! Snake ate other color food." << endl;
        exit(0);
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

// Function to handle keyboard input
void keyboardHandler(unsigned char key, int, int) {
    switch (key) {
        case 'w':
        case 'W':
            if (direction != DOWN) {
                direction = UP;
            }
            break;
        case 's':
        case 'S':
            if (direction != UP) {
                direction = DOWN;
            }
            break;
        case 'a':
        case 'A':
            if (direction != RIGHT) {
                direction = LEFT;
            }
            break;
        case 'd':
        case 'D':
            if (direction != LEFT) {
                direction = RIGHT;
            }
            break;
    }
}

// Main function
int main(int argc, char** argv) {
    // Initialize random seed
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Primary Color Snake Game - Red, Green, Blue");

    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    // Initialize snake and food positions
    snake.push_front(Point(WIDTH / 2, HEIGHT / 2)); // Initial position of the snake

    food.x = rand() % (WIDTH / CELL_SIZE) * CELL_SIZE;
    food.y = rand() % (HEIGHT / CELL_SIZE) * CELL_SIZE;

    // Assign a random color to the food
    int colorChoice = rand() % 3; // 0: RED, 1: BLUE, 2: GREEN
    if (colorChoice == 0) {
        food.color = RED;
    } else if (colorChoice == 1) {
        food.color = BLUE;
    } else {
        food.color = GREEN;
    }

    // Set up GLUT callbacks
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(100, update, 0);

    // Set the background color
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
