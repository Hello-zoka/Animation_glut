/* Zajcev Yurij, 10-1, 12.05.2020 */

#include <GLUT/glut.h>
#include <time.h>
#include <stdlib.h>

#ifndef __ANIM_H_
#define __ANIM_H_

namespace zygl {
    class anim;

    class object {
    public:
        virtual void Draw(anim *Ani) {} // Drawing current animation

        virtual void Keyboard(anim *Ani, int Key) {} // Getting information from keyboard for current animation
    };

    class anim {
    public:
        int IsPause = 0; // Is paused or not
        int xpos = 0, zpos = 0; // Current coordinates on table
        double SyncTime;
    private:
        long StartTime, OldTime, PauseTime;

        void Timer() { // function which count current time with pauses
            long t = clock();
            if (IsPause) {
                PauseTime += t - OldTime;
            } else {
                SyncTime = (t - StartTime - PauseTime) / (double) CLOCKS_PER_SEC;
            }
            OldTime = t;
        }

    private:
        static const int MaxNumOfObjects = 1000;
        static const int Hs = 200, Ws = 200;
        int NumOfObjects;
        object *Objects[MaxNumOfObjects]; // list of objects

        anim() :
                NumOfObjects(0), StartTime(clock()), OldTime(0), PauseTime(0), IsPause(0), SyncTime(0) {
            const char *argv[] = {"ops"};
            int argc = 1;
            // Standard glut initialization functions
            glutInit(&argc, const_cast<char **>(argv));
            glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(Hs, Ws);
            glutCreateWindow("Animation");
            // Turning on simple lighting
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            // including standard glut functions
            glutDisplayFunc(Display);
            glutKeyboardFunc(Keyboard);
            glutReshapeFunc(Reshape);
        }

    public:
        static anim Instance;

        static anim &Get() {
            return Instance;
        }

        static void Run() {
            glutMainLoop();
        }

        anim &operator<<(object *Obj) { // overriding operator for adding objects
            if (NumOfObjects < MaxNumOfObjects)
                Objects[NumOfObjects++] = Obj;
            return *this;
        }

    private:
        static void Display() {
            // standard glut display function
            glClearColor(0.30, 0.50, 0.70, 1.00); // color of background
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            gluLookAt(5, 10, 12, 5, 0, 5, 0, 1.0, 0); // point of view
            Instance.Timer(); // timer
            glEnable(GL_LIGHTING); // simple lighting
            for (int i = 0; i < Instance.NumOfObjects; i++) { // drawing all objects
                glPushMatrix();
                Instance.Objects[i]->Draw(&Instance);
                glPopMatrix();
            }
            glFinish();
            glutSwapBuffers();
            glutPostRedisplay();
        }

        static void Keyboard(unsigned char Key, int X, int Y) { // getting keyboards pushes
            if (Key == 27) // esc -> exit
                exit(0);
            else if (Key == 'f') // f -> full screen
                glutFullScreen();
            else if (Key == 'p') // p -> pause
                Instance.IsPause ^= 1;
            for (int i = 0; i < Instance.NumOfObjects; i++) { // sending this information into objects
                Instance.Objects[i]->Keyboard(&Instance, Key);
            }
        }

        static void Reshape(int W, int H) { // reshaping window
            double size = 0.1, rx = size, ry = size;
            if (W > H)
                rx *= (double) W / H;
            else
                ry *= (double) H / W;
            glViewport(0, 0, W, H);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, size, 100);
            glMatrixMode(GL_MODELVIEW);
        }
    };
}
#endif /* __ANIM_H_ */