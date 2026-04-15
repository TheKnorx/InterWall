#pragma once
#include "SDL3/SDL_render.h"

#define PARTICLES_COUNT 100  // amount of particles to create
#define PARTICLE_SIZE_PX_LINE 2  //  width/heigth of each particle
#define PARTICLE_SIZE_PX_AREA (PARTICLE_SIZE_PX_LINE * PARTICLE_SIZE_PX_LINE)  // each particle is of size line*line
#define PARTICLES_SPEED 0.6	// speed at which the particles will move
#define PARTICLES_MOUSE_DISTANCE_PX 200  // distance (int pixels) at which particles connect with the mouse
#define PARTICLE_RESPAWN_DELAY 30  // for description see struct particle_t

#define GET_RAND_INT(MIN, MAX) ( MIN + rand() % (MAX+1 - MIN) )
#define GET_RAND_FLOAT(MIN, MAX) ( MIN + ((double)rand() / RAND_MAX) * (MAX - MIN) )

typedef struct
{
	int x, y, sum;
} resolution_t;

typedef struct
{
	float x, y;
	float direction;  // this will be in the form of an angle based on the base-circle
	int respawn_delay;  // amount of frames that a particle has to wait before respawn
} particle_t;

typedef struct
{
	float x, y;
} mouse_position_t;

int init_particles(SDL_Renderer* renderer);
int render_particles(SDL_Renderer* renderer);
int end_particles();
int render_particle_point(SDL_Renderer* renderer, int particle_count);

