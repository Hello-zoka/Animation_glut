/* Zajcev Yurij, 10-1, 12.05.2020 */
#include <iostream>
#include "ANIM.h"
#include "cmake-build-debug/bounce_ball.h"
#include "cmake-build-debug/rand_objects.h"
#include "ANIM.cpp"

int main() {
    std::cout
            << "Hello!\nThis if very useful glut implementation of drawing objects, which can be used in many different tasks.\n"
               "For example, you can find there two projects:\n"
               "1) Table with the recoloring rand_objects(press wasd-buttons to move)\n"
               "2) A lot of random glut-objects\n"
               "You can press 'f'-button for full-screen mod, 'p'-button to pause, esc - to exit\n"
               "Type 1 or 2 to select project, please: ";
    int val;
    std::cin >> val;
    zygl::anim &My = zygl::anim::Get();

    if (val == 1) {
        My << new zygl::bounce_ball();
    } else {
        for (int i = 0; i < 100; i++) {
            My << new zygl::rand_objects();
        }
    }
    My.Run();
    return 0;
}