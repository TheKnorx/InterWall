#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#define PARTICLES_COUNT 100  // amount of particles to create
#define PARTICLE_SIZE_PX_LINE 4  //  width/heigth of each particle
#define PARTICLE_SIZE_PX_AREA (PARTICLE_SIZE_PX_LINE * PARTICLE_SIZE_PX_LINE)  // each particle is of size line*line

#define GET_RAND(MIN, MAX) (MIN + rand() % (MAX+1 - MIN))

typedef struct
{
	int x, y, sum;
} resolution_t;

typedef struct
{
	float x, y;

} particle_t;


int init_particles(SDL_Renderer* renderer);
