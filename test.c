#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG

obj2d *import(uint32_t count, char *path);
void printObjs(obj2d *objects, int count);
void generateArrays(int count);

void calculateForces(int count);
void calculateAccels(int count);
void calculateVelocities(int count, float dt);
void calculatePositions(int count, float dt);

obj2d *objects;
int count;
int dt = 1;
char *filePath;

float *forces;
float *accelerations;
float *velocities;
int32_t *positions; 
int32_t *masses;
int32_t *rads;


int main(int argc, char *argv[])
{
#ifndef DEBUG
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    if (argc != 3)
    {
        perror("Incorrect argument count\n");
    }
    filePath = malloc(PATH_LENGTH);
    strcpy(filePath, argv[1]);
    count = atoi(argv[2]);
#endif

#ifdef DEBUG
    filePath = malloc(PATH_LENGTH);
    strcpy(filePath, "testData.txt");
    count = 2;
#endif
    objects = import(count, filePath);
    printObjs(objects, count);

    generateArrays(count);

    while(true)
    {

    }
}

obj2d *import(uint32_t count, char *path)
{
    obj2d *objects = malloc(count * sizeof(obj2d));
    FILE *file = fopen(path, "r");
    char tmp[PATH_LENGTH];
    char *c;
    int j;

    if (file == NULL)
    {
        perror("File not found\n");
    }
    for (int i = 0; i < count; i++)
    {
        fgets(tmp, PATH_LENGTH, file);
        printf("%s\n", tmp);

        c = strtok(tmp, ",");
        strcpy(objects[i].name, c);

        c = strtok(NULL, ",");
        objects[i].r = atoi(c);

        c = strtok(NULL, ",");
        objects[i].m = atoi(c);

        c = strtok(NULL, ",");
        objects[i].x = atoi(c);

        c = strtok(NULL, ",");
        objects[i].y = atoi(c);

        c = strtok(NULL, ",");
        objects[i].ax = atof(c);

        c = strtok(NULL, ",");
        objects[i].ay = atof(c);

        c = strtok(NULL, ",");
        objects[i].vx = atof(c);

        c = strtok(NULL, ",");
        objects[i].vy = atof(c);
    }
    fclose(file);
    return objects;
}

void printObjs(obj2d *objects, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s: r: %d, m: %d, x: %d, y: %d, ax: %f, ay: %f, vx: %f, vy: %f\n", objects[i].name, objects[i].r, objects[i].m, objects[i].x, objects[i].y, objects[i].ax, objects[i].ay, objects[i].vx, objects[i].vy);
    }
}

void generateArrays(int count)
{
    forces = malloc(sizeof(float) * DIMMENSIONS * count * count);
    accelerations = malloc(sizeof(float) * DIMMENSIONS * count);
    velocities = malloc(sizeof(float) * DIMMENSIONS * count);
    positions = malloc(sizeof(int32_t) * DIMMENSIONS * count);
    masses = malloc(sizeof(int32_t) * count);
    rads = malloc(sizeof(int32_t) * count);

    for(int i = 0; i < count; i++)
    {
        accelerations[i * DIMMENSIONS] = objects[i].ax;
        accelerations[i * DIMMENSIONS + 1] = objects[i].ay;
        velocities[i * DIMMENSIONS] = objects[i].vx;
        velocities[i * DIMMENSIONS + 1] = objects[i].vy;
        positions[i * DIMMENSIONS] = objects[i].x;
        positions[i * DIMMENSIONS + 1] = objects[i].y;
        masses[i] = objects[i].m;
        rads[i] = objects[i].r;
    }
}