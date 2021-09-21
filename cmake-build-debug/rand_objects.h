/* Zajcev Yurij, 10-1, 12.05.2020 */

#include <GLUT/glut.h>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <chrono>

#ifndef __BALL_H_
#define __BALL_H_

namespace zygl {
    class rand_objects : public object {
    private:
        double r, g, b; // color of object
        double x, y, z; // coordinates of object
        double vel; // speed of object
        int type; // type of object

        static double r0() { // random double in range [0,1]
            return rnd() / (double) RAND_MAX;
        }

        static int r1() { // random int in range [0,4]
            return rnd() % 5;
        }

    public:
        rand_objects() : r(r0()), g(r0()), b(r0()), x(r0() * 5), y(0), z(r0() * 5), vel(3.0 * r0()),
                         type(r1()) { // random initialization
        }

        void Draw(anim *Ani) { // Drawing object
            glTranslated(x, y + fabs(sin(2 * Ani->SyncTime * vel)), z); // moving to the object's place
            glRotated(fabs(20 * Ani->SyncTime * vel), 1, 1, 1); // rotating object on it's angle
            glColor3d(r, g, b); // switching color
            switch (type) { // drawing object with normal size
                case 0:
                    glutWireSphere(0.4, 30, 30);
                    break;
                case 1:
                    glutWireTorus(0.1, 0.8, 30, 30);
                    break;
                case 2:
                    glutWireCube(0.4);
                    break;
                case 3:
                    glutWireTeapot(0.5);
                    break;
                case 4:
                    glutWireCone(0.5, 1, 30, 30);
                    break;
            }
        }
    };
}
#endif __BALL_H_
