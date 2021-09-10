/* Zajcev Yurij, 10-1, 19.05.2020 */
#include <GLUT/glut.h>
#include <math.h>
#include <chrono>
#include <random>
#include <stdlib.h>

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count()); // using good random

#ifndef __CHECKER_H_
#define __CHECKER_H_


namespace zygl {
    class checker : public object {
    private:
        static const int W_Size = 10, H_Size = 10;
        const double EPS = 0.03;

        static double r0() { // random double in range [0,1]
            return rnd() / (double) RAND_MAX;
        }

        double col[W_Size][H_Size][3]; // colors of cells

        void upd(int x, int y) { // changing color of x, y cell
            if (x < 0 || x >= W_Size || y < 0 || y >= H_Size)
                return;
            col[x][y][0] = r0();
            col[x][y][1] = r0();
            col[x][y][2] = r0();
        }

    public:
        checker() { // initialization colors of white/grey chess table
            for (int i = 0; i < W_Size; i++) {
                for (int j = 0; j < H_Size; j++) {
                    if ((i ^ j) & 1) {
                        col[i][j][0] = 1;
                        col[i][j][1] = 1;
                        col[i][j][2] = 1;
                    } else {
                        col[i][j][0] = 0.5;
                        col[i][j][1] = 0.5;
                        col[i][j][2] = 0.5;
                    }
                }
            }
        }

        double sphere_radius = 0.3, table_height = 2, cell_square = 1;

        void Keyboard(anim *Ani, int Key) { // moving sphere, using information about pushed buttons
            if ((Key == 'd') && Ani->xpos != H_Size - 1)
                Ani->xpos++;
            if (Key == 'a' && Ani->xpos != 0)
                Ani->xpos--;
            if (Key == 's' && Ani->zpos != W_Size - 1)
                Ani->zpos++;
            if (Key == 'w' && Ani->zpos != 0)
                Ani->zpos--;
        }

        void Draw(anim *Ani) override { // drawing table
            for (int i = 0; i < W_Size; i++) {
                for (int j = 0; j < H_Size; j++) {
                    glPushMatrix();
                    glTranslated(cell_square / 2 + j, -table_height / 2, cell_square / 2 + i); // move to current cell
                    glColor3d(col[i][j][0], col[i][j][1], col[i][j][2]); // setting color of cell
                    glScaled(cell_square, table_height, cell_square);
                    glutSolidCube(cell_square); // drawing cell
                    glPopMatrix();
                }
                glPushMatrix();
                double y_pos = fabs(sin(30 * Ani->SyncTime)); // current y-position
                if (y_pos <= EPS) // checking if sphere "touch" cell
                    upd(Ani->zpos, Ani->xpos); // making new random cell color
                glTranslated(cell_square / 2 + Ani->xpos, y_pos,
                             cell_square / 2 + Ani->zpos); // moving of sphere
                glutSolidSphere(sphere_radius, 30, 30); // drawing sphere
                glPopMatrix();
            }
        }
    };
}
#endif __CHECKER_H_