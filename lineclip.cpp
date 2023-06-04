#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

float xmin, ymin, xmax, ymax, x_1, y_1, x_2, y_2;

void display()
{

    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x_1, y_1);
    glVertex2i(x_2, y_2);
    glEnd();

    glFlush();
}

int outcode(float x, float y)
{
    int c = 0;

    if (y > ymax)
    {
        c = 8;
    }
    else if (y < ymin)
    {
        c = 4;
    }
    if (x > xmax)
    {
        c |= 2;
    }
    else if (x < xmin)
    {
        c |= 1;
    }

    return c;
}

void lineclip(unsigned char key, int x, int y)
{
    bool accept = false;
    bool done = false;

    int outcode0 = outcode(x_1, y_1);
    int outcode1 = outcode(x_2, y_2);

    int outcodeout, xx = 0, yy = 0;

    while (!done)
    {
        if (outcode0 == 0 && outcode1 == 0)
        {
            accept = true;
            done = true;
        }
        else if (outcode0 & outcode1 != 0)
        {
            done = true;
        }
        else
        {
            if (outcode0 != 0)
            {
                outcodeout = outcode0;
            }
            else
            {
                outcodeout = outcode1;
            }

            if ((outcodeout & 8) == 8)
            {
                xx = x_1 + (x_2 - x_1) * (ymax - y_1) / (y_2 - y_1);
                yy = ymax;
            }
            else if ((outcodeout & 4) == 4)
            {
                xx = x_1 + (x_2 - x_1) * (ymin - y_1) / (y_2 - y_1);
                yy = ymin;
            }
            else if ((outcodeout & 2) == 2)
            {
                yy = y_1 + (y_2 - y_1) * (xmax - x_1) / (x_2 - x_1);
                xx = xmax;
            }
            else if ((outcodeout & 1) == 1)
            {
                yy = y_1 + (y_2 - y_1) * (xmin - x_1) / (x_2 - x_1);
                xx = xmin;
            }

            if (outcodeout == outcode0)
            {
                x_1 = xx;
                y_1 = yy;
                outcode0 = outcode(x_1, y_1);
            }
            else if (outcodeout == outcode1)
            {
                x_2 = xx;
                y_2 = yy;
                outcode1 = outcode(x_2, y_2);
            }
        }
    }

    cout << "(" << x_1 << "," << y_1 << ") and (" << x_2 << "," << y_2 << ")" << endl;

    glClear(GL_COLOR_BUFFER_BIT);
    display();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-480, 480, -480, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    cout << "Enter xmin, ymin : ";
    cin >> xmin >> ymin;

    cout << "Enter xmax, ymax : ";
    cin >> xmax >> ymax;

    cout << "Enter x_1, y_1 : ";
    cin >> x_1 >> y_1;

    cout << "Enter x_2, y_2 : ";
    cin >> x_2 >> y_2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line-Clipping");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(lineclip);
    glutMainLoop();

    return 0;
}