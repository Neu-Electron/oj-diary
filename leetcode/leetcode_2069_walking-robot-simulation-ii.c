#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int L;
    long long total_steps;
    int* pos_x;
    int* pos_y;
    char** dir;
} Robot;

Robot* robotCreate(int width, int height) {
    Robot* obj = (Robot*)malloc(sizeof(Robot));
    obj->width = width;
    obj->height = height;
    obj->total_steps = 0;
    obj->L = 2 * (width + height - 2);

    if (obj->L <= 0) {
        obj->pos_x = NULL;
        obj->pos_y = NULL;
        obj->dir = NULL;
    } else {
        obj->pos_x = (int*)malloc(obj->L * sizeof(int));
        obj->pos_y = (int*)malloc(obj->L * sizeof(int));
        obj->dir = (char**)malloc(obj->L * sizeof(char*));

        int idx = 0;
        for (int x = 1; x <= width - 1; ++x) {
            obj->pos_x[idx] = x;
            obj->pos_y[idx] = 0;
            obj->dir[idx] = "East";
            ++idx;
        }
        for (int y = 1; y <= height - 1; ++y) {
            obj->pos_x[idx] = width - 1;
            obj->pos_y[idx] = y;
            obj->dir[idx] = "North";
            ++idx;
        }
        for (int x = width - 2; x >= 0; --x) {
            obj->pos_x[idx] = x;
            obj->pos_y[idx] = height - 1;
            obj->dir[idx] = "West";
            ++idx;
        }
        for (int y = height - 2; y >= 1; --y) {
            obj->pos_x[idx] = 0;
            obj->pos_y[idx] = y;
            obj->dir[idx] = "South";
            ++idx;
        }
        if (idx < obj->L) {
            obj->pos_x[idx] = 0;
            obj->pos_y[idx] = 0;
            obj->dir[idx] = "South";
            ++idx;
        }
    }
    return obj;
}

void robotStep(Robot* obj, int num) {
    if (obj->L <= 0)
        return;
    obj->total_steps += num;
}

int* robotGetPos(Robot* obj, int* retSize) {
    *retSize = 2;
    int* pos = (int*)malloc(2 * sizeof(int));

    if (obj->L <= 0 || obj->total_steps == 0) {
        pos[0] = 0;
        pos[1] = 0;
        return pos;
    }

    long long idx = (obj->total_steps - 1) % obj->L;
    pos[0] = obj->pos_x[idx];
    pos[1] = obj->pos_y[idx];
    return pos;
}

char* robotGetDir(Robot* obj) {
    if (obj->L <= 0 || obj->total_steps == 0) {
        return "East";
    }
    long long idx = (obj->total_steps - 1) % obj->L;
    return obj->dir[idx];
}

void robotFree(Robot* obj) {
    if (obj->pos_x)
        free(obj->pos_x);
    if (obj->pos_y)
        free(obj->pos_y);
    if (obj->dir)
        free(obj->dir);
    free(obj);
}