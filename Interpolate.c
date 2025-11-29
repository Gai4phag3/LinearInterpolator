#include <stddef.h>

double interpolate(double firstX, double firstY, double secondX, double secondY, double interpolatedX) {
    if (firstX == secondX) {
        return 0; 
    }
    return firstY + (secondY - firstY) * (interpolatedX - firstX) / (secondX - firstX);
}

int main() {
    printf("%d", interpolate(0, 0, 1, 1, 2))
    return 0;
}