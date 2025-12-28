#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    double x;
    double y;
} Point;

int compare_points(const void *a, const void *b) {
    const Point *p1 = (const Point *)a;
    const Point *p2 = (const Point *)b;

    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    return 0;
}

Point *load_csv(const char *filename, int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open CSV");
        return NULL;
    }

    int capacity = 16;
    int size = 0;
    Point *points = malloc(capacity * sizeof(Point));

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char *ptr = line;
        while (isspace(*ptr)) ptr++;
        if (*ptr == '\0') continue;

        double x, y;
        if (sscanf(line, " %lf , %lf", &x, &y) == 2) {
            if (size >= capacity) {
                capacity *= 2;
                points = realloc(points, capacity * sizeof(Point));
            }
            points[size++] = (Point){x, y};
        }
    }

    fclose(fp);
    *count = size;
    return points;
}

double interHelper(double x0, double y0,
                          double x1, double y1,
                          double x) {
    if (x1 == x0) return y0;
    return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
}

double interpolate(Point *table, int n, double x) {
    if (n < 2) return 0;

    if (x <= table[0].x) {
        return interHelper(
            table[0].x, table[0].y,
            table[1].x, table[1].y,
            x
        );
    }

    if (x >= table[n - 1].x) {
        return interHelper(
            table[n - 2].x, table[n - 2].y,
            table[n - 1].x, table[n - 1].y,
            x
        );
    }

    for (int i = 0; i < n - 1; i++) {
        if (x >= table[i].x && x <= table[i + 1].x) {
            return interHelper(
                table[i].x, table[i].y,
                table[i + 1].x, table[i + 1].y,
                x
            );
        }
    }

    return 0;
}

int main(void) {
    int csv_count;
    Point *csv_points = load_csv("table.csv", &csv_count);
    if (csv_points) {
        qsort(csv_points, csv_count, sizeof(Point), compare_points);
        printf("%f\n", interpolate(csv_points, csv_count, 2.5));
        free(csv_points);
    }

    Point pts[] = {
        {0, 0},
        {1, 1},
        {2, 4},
        {4, 16}
    };
    int n = sizeof(pts) / sizeof(pts[0]);

    qsort(pts, n, sizeof(Point), compare_points);
    printf("%f\n", interpolate(pts, n, 2.5));

    return 0;
}
