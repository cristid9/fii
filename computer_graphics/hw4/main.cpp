#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include <map>
#include <vector>

//#include "glut.h"


#define dim 300

using namespace std;

unsigned char prevKey;
unsigned button;
unsigned state;
int click_start_x = -100;
int click_start_y = -100;

class GrilaCarteziana
{
private:
    unsigned num_lines, num_columns;
    static double constexpr base_xl = -.8;
    double base_xr = .8;
    double base_yd = -.8;
    static double constexpr base_yu = .8;
    double square_y_size;
    double square_x_size;
    bool border = true;
    double r;
    tuple<double, double> pixels[1000][1000]; // hardcoding things is bad
    vector<tuple<int, int, int, int>> saved_plots;
    void save_pixels(int lines, int columns)
    {
        for (int i = 0; i <= lines; ++i)
        {
            for (int j = 0; j <= columns; ++j)
            {
                tuple<double, double> tp;
                get<0>(tp) = base_xl + i * square_y_size;
                get<1>(tp) = base_yu - j * square_x_size;
                pixels[i][j] = tp;
            }
        }
    }

public:

    bool saved_pixels = false;
    GrilaCarteziana(unsigned n_lines, unsigned n_columns)
        : num_columns(n_columns), num_lines(n_lines)
    {
    }

    void toggle_border()
    {
        border = !border;
    }

    tuple<int, int> is_valid_pixel(double x, double y)
    {
        save_pixels(num_lines, num_columns);

        tuple<int, int> retval;
        get<0>(retval) = -1;
        get<1>(retval) = -1;
        for (int i = 0; i <= num_lines; ++i)
        {
            for (int j = 0; j <= num_columns; ++j)
            {
                tuple<double, double> tp = pixels[i][j];
                double test_x = get<0>(tp);
                double test_y = get<1>(tp);


                if (pow(x - test_x, 2.0) + pow(y - test_y, 2.0) < pow(r, 2.0))
                {
                    get<0>(retval) = i;
                    get<1>(retval) = j;

                    return retval;
                }
            }
        }
        return retval;
    }

    /**
     * Draws a circle.
     * @param i line.
     * @param j column.
     */
    void fire_pixel(double i, double j)
    {
        if ((i < 0 || j < 0) || (i > num_lines || j > num_columns))
            return;

        int num_segments = 100;
        double adjustment_x = base_xl + i * square_y_size;
        double adjustment_y = base_yu - j * square_x_size;

//        cout <<"{" << i << "}{" << j << "}" << endl;
        glBegin(GL_TRIANGLE_FAN);
            for(int ii = 0; ii < num_segments; ii++)
            {
                glColor3f(0.0f, 0.0f, 0.0f);
                float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
                float x = r * cosf(theta);//calculate the x component
                float y = r * sinf(theta);//calculate the y component

                glVertex2f(x + adjustment_x, y + adjustment_y);
            }
        glEnd();
    }

    void draw_grid()
    {

        glPushMatrix();
        glLoadIdentity();
        square_y_size = 1.0 / num_lines;
        square_x_size = 1.0 / num_columns;
        base_yd = base_yu - (num_lines * min(square_x_size, square_y_size));
        base_xr = base_xl + (num_columns * min(square_y_size, square_x_size));

        square_y_size = min(square_y_size, square_x_size);
        square_x_size = min(square_y_size, square_x_size);

        r = square_x_size / 3.0;

        cout << num_lines * min(square_x_size, square_y_size) << endl;
        cout << base_xr << endl;
        cout << base_yd << endl;

        save_pixels(num_lines, num_columns);
        saved_pixels = true;
        glColor3f(.0f, .0f, .0f);
        glBegin(GL_LINES);
            for (int i = 0; i <= num_lines; ++i)
            {
                glVertex2f(base_xl, base_yu - i * square_x_size);
                glVertex2f(base_xr, base_yu - i * square_x_size);

//                cout << "( " << base_xl << ", " << base_yu + i * square_y_size << ")"
//                     << " (" << base_xr << ", " << base_yu + i * square_y_size << ") " << endl;
            }
        glEnd();

        glColor3f(.0f, .0f, .0f);
        glBegin(GL_LINES);
            for (int i = 0; i <= num_columns; ++i)
            {
                glVertex2f(base_xl + i * square_x_size, base_yu);
                glVertex2f(base_xl + i * square_x_size, base_yd);

//                cout << "( " << base_xl + i * square_y_size << ", " << base_yd << ")"
//                     << " (" << base_xl + i * square_y_size << ", " << base_yu << ") "
//                     << endl;
            }
        glEnd();

    }

    void plot_line_low(double x0, double y0, double x1, double y1)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex2f(base_xl + x0 * square_y_size, base_yu - y0 * square_x_size);
            glVertex2f(base_xl + x1 * square_y_size, base_yu - y1 * square_x_size);
        glEnd();


        double dx = x1 - x0;
        double dy = y1 - y0;
        double yi = 1;

        if (dy < 0)
        {
            yi = -1;
            dy = -dy;
        }
        double D = 2 * dy - dx;
        double y = y0;

        for (double x = x0; x <= x1; x += 1)
        {
            if (border)
            {
                fire_pixel(x, y);
                fire_pixel(x+1, y);
                fire_pixel(x, y+1);
                fire_pixel(x+1, y+1);
                // main
                fire_pixel(x, y);
                // main
                fire_pixel(x, y);
                fire_pixel(x-1, y);
                fire_pixel(x, y-1);
                fire_pixel(x-1, y-1);
            }
            else
            {
                fire_pixel(x, y);
            }
            if (D > 0)
            {
                y = y + yi;
                D = D - 2 * dx;
            }
            D = D + 2 * dy;
        }
    }


    void save_plot(int x0, int y0, int x1, int y1)
    {
        tuple<int, int, int, int> tp;
        get<0>(tp) = x0;
        get<1>(tp) = y0;
        get<2>(tp) = x1;
        get<3>(tp) = y1;
        saved_plots.push_back(tp);
    }

    void draw_saved_plots()
    {
        for (int i = 0; i < saved_plots.size(); ++i)
        {
            tuple<int, int, int, int> tp = saved_plots[i];
            int x0 = get<0>(tp);
            int y0 = get<1>(tp);
            int x1 = get<2>(tp);
            int y1 = get<3>(tp);

            plot_line(x0, y0, x1, y1);
            cout << "drawed ==> " << endl;
            cout << x0 << " " << y0 << " " << x1 << " " << y1 << endl;
            cout << "[/drawed]" << endl;
        }
    }

    void plot_line_high(double x0, double y0, double x1, double y1)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex2f(base_xl + x0 * square_y_size, base_yu - y0 * square_x_size);
            glVertex2f(base_xl + x1 * square_y_size, base_yu - y1 * square_x_size);
        glEnd();

        double dx = x1 - x0;
        double dy = y1 - y0;
        double xi = 1;
        if (dx < 0)
        {
            xi = -1;
            dx = -dx;
        }
        double D = 2 * dx - dy;
        double x = x0;

        for (double y = y0; y <= y1; y += 1)
        {
            if (border)
            {
                fire_pixel(x, y);
                fire_pixel(x+1, y);
                fire_pixel(x, y+1);
                fire_pixel(x+1, y+1);
                // main
                fire_pixel(x, y);
                // main
                fire_pixel(x, y);
                fire_pixel(x-1, y);
                fire_pixel(x, y-1);
                fire_pixel(x-1, y-1);
            }
            else
            {
                fire_pixel(x, y);
            }
            if (D > 0)
            {
                x = x + xi;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
        }
    }

    void plot_line(double x0, double y0, double x1, double y1)
    {
        if (fabs(y1 - y0) < fabs(x1 - x0))
        {
            if (x0 > x1)
            {
                plot_line_low(x1, y1, x0, y0);
            }
            else
            {
                plot_line_low(x0, y0, x1, y1);
            }
        }
        else
        {
            if (y0 > y1)
            {
                plot_line_high(x1, y1, x0, y0);
            }
            else
            {
                plot_line_high(x0, y0, x1, y1);
            }
        }
    }
};

GrilaCarteziana gc(15, 15);

void Display1()
{
    glColor3f(1.0, 0.1, 0.1);
    gc.draw_grid();

    gc.plot_line(0, 0, 15, 5);
    gc.plot_line(0, 1, 15, 6);
    gc.plot_line(2, 0, 15, 4);

    gc.toggle_border();
    gc.plot_line(0, 15, 15, 8);
    gc.draw_saved_plots();

}

void Display(void) {
    switch(prevKey) {
        case '1':
            glClear(GL_COLOR_BUFFER_BIT);
            Display1();
        default:
            break;
    }

    glFlush();
}

void Init(void) {

    glClearColor( 1, 1, 1, 1);

    glLineWidth(1);

//   glPointSize(3);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glClearColor( 1, 1, 1, 1);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}
GLdouble ox=0.0,oy=0.0,oz=0.0;

void MouseFunc(int button, int state, int x, int y)
{
    if (button == 0)
    {
        GLint viewport[4];
        GLdouble modelview[16],projection[16];
        GLfloat wx=x,wy,wz;

        glGetIntegerv(GL_VIEWPORT,viewport);
        y=viewport[3]-y;
        wy=y;
        glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
        glGetDoublev(GL_PROJECTION_MATRIX,projection);
        glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
        gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);

        cout << ox << " " << oy << endl;

        tuple<int, int> tp = gc.is_valid_pixel(ox, oy);
        int i = get<0>(tp);
        int j = get<1>(tp);


        if (i != -1)
        {
            if (click_start_x == -100 && state == 0)
            {
                click_start_x = i;
                click_start_y = j;
            }
            else if(click_start_x != -100 && state == 1)
            {
                cout << "==================================================" << endl;
                cout << click_start_x << " <==> " << click_start_y << endl;
                cout << i << " <==> " << j << endl;
                cout << "==================================================" << endl;
                gc.save_plot(click_start_x, click_start_y, i, j);
                glutPostRedisplay();

                click_start_x = -100;
                click_start_y = -100;
            }

        }
        else
        {
            cout << "nu-i" << endl;
            cout << i << " . " << j << endl;
        }

    }
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow (argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}
