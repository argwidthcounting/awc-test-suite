#include "tests.h"

int main(){
    Point x = {.x = 1.0, .y=2.0, .z=3.0};
    Point y = {.x = 4.0, .y=5.0, .z=6.0};
    Point z = {.x = 7.0, .y=8.0, .z=9.0};
    Point d = sumPoints(3, x, y, z);
    printf("Sum: (%f,%f,%f) + (%f,%f,%f) + (%f,%f,%f) = (%f,%f,%f)\n", x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, d.x, d.y, d.z);
}