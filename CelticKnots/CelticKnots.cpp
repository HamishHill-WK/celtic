#include <GLFW/glfw3.h>
#include <cmath>

void drawQuadraticBezierCurve()
{
    GLfloat controlPoints[3][2] = {
        { -0.6f, -0.5f }, // Control Point P0
        { 0.0f, 0.6f },   // Control Point P1
        { 0.6f, -0.5f }   // Control Point P2
    };

    GLint numSegments = 100; // Number of line segments to approximate the curve

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= numSegments; i++)
    {
        GLfloat t = static_cast<GLfloat>(i) / numSegments;
        GLfloat u = 1.0f - t;

        GLfloat x = u * u * controlPoints[0][0] + 2.0f * u * t * controlPoints[1][0] + t * t * controlPoints[2][0];
        GLfloat y = u * u * controlPoints[0][1] + 2.0f * u * t * controlPoints[1][1] + t * t * controlPoints[2][1];

        glVertex2f(x, y);
    }

    glEnd();
}

void display(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f); // Set line color to white

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawQuadraticBezierCurve();

    glfwSwapBuffers(window);
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Quadratic Bezier Curve", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, 800, 600);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

        display(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
