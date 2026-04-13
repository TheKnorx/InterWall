#pragma once
#include "SDL3/SDL_render.h"

#define PARTICLES_COUNT 100  // amount of particles to create
#define PARTICLE_SIZE_PX_LINE 4  //  width/heigth of each particle
#define PARTICLES_SPEED 0.1	// speed at which the particles will move
#define PARTICLE_SIZE_PX_AREA (PARTICLE_SIZE_PX_LINE * PARTICLE_SIZE_PX_LINE)  // each particle is of size line*line

#define GET_RAND(MIN, MAX) (MIN + rand() % (MAX+1 - MIN))

typedef struct
{
	int x, y, sum;
} resolution_t;

typedef struct
{
	float x, y;
	float direction;  // this will be in the form of an angle based on the base-circle
} particle_t;

typedef struct
{
	float x, y;
} mouse_position_t;

int init_particles(SDL_Renderer* renderer);
int render_particles(SDL_Renderer* renderer);
int end_particles();
int render_particle_point(SDL_Renderer* renderer, int particle_count);
