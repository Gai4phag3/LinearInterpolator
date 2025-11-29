#include <stdio.h>

double interpolate(double firstX, double firstY, double secondX, double secondY, double interpolatedX) {
    if (firstX == secondX) {
        return 0; 
    }
    return firstY + (secondY - firstY) * (interpolatedX - firstX) / (secondX - firstX);
}

int main() {
    printf("%f", interpolate(0, 0, 1, 1, 0.5));
    return 0;
}