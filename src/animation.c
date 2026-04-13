//
// Created by pascal on 12.04.26.
//

#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <math.h>

#include "animation.h"
#include "common.h"

static resolution_t resolution;
static int particles_amount = 0;
static particle_t particles_array[PARTICLES_COUNT] = {0};

int init_particles(SDL_Renderer* renderer)
{
	// seed the random number generator
	srand(time(nullptr));

	// Next get resolution of current display
	SDL_GetRenderOutputSize(renderer, &resolution.x, &resolution.y);
	resolution.sum = resolution.x * resolution.y;

	// Calculate the probability of which we have to spawn the particles
	const int rel_resolution = resolution.sum / (PARTICLE_SIZE_PX_AREA * PARTICLE_SIZE_PX_AREA);
	// calculate how we have to distribute the particles
	// we use int so the result gets floored
	const int probability = rel_resolution / PARTICLES_COUNT;  // we discard the remainder
	int probability_count = probability;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // white particles
	// iterate through the display along the x-axis, marking where a potential pixel block starts
	// particle == block
	for (int abs_block_y = 0; abs_block_y < resolution.y; abs_block_y+=PARTICLE_SIZE_PX_AREA)
	{
		for (int abs_block_x = 0; abs_block_x < resolution.x; abs_block_x+=PARTICLE_SIZE_PX_AREA)
		{
			// if we reached the end of the display width, jmp to the next particle by skipping the next n-1 rows of pixels
			if (! abs_block_x % resolution.x)
			{
				abs_block_x = 0;
				abs_block_y += PARTICLE_SIZE_PX_AREA-1;
			}
			if (GET_RAND(1, probability_count) > 1)  // the possibility of a block spawning is 1/probability
			{
				// we have to make the probability of a block spawning bigger with every try
				// this guarantees that eventually a block will spawn
				probability_count -= 1/probability;  // for now this is good enough, but this will be too imprecise in the future!
				continue;
			}
			probability_count = probability;  // reset probability
			// iterate through all the pixels of a particle
			printf("Block %d at (%d, %d)\n", particles_amount, abs_block_x, abs_block_y);
			// for (int rel_block_y = 0; rel_block_y < PARTICLE_SIZE_PX_LINE; rel_block_y++)
			// {
			// 	for (int rel_block_x = 0; rel_block_x < PARTICLE_SIZE_PX_LINE; rel_block_x++)
			// 	{
			// 		particles_array[particles_amount] = (particle_t){
			// 			.x = (float)abs_block_x, .y = (float)abs_block_y,
			// 			.direction = GET_RAND(0, 360) * (M_PI / 180.0f)  // get the radians
			// 			};
			// 	}
			// }
			particles_array[particles_amount] = (particle_t){
				.x = (float)abs_block_x, .y = (float)abs_block_y,
				.direction = GET_RAND(0, 360) * (M_PI / 180.0f)  // get the radians
				};
			particles_amount++;
		}
	}
	return 0;
}

int render_particle_point(SDL_Renderer* renderer, const int particle_count)
{
	for (int rel_block_y = 0; rel_block_y < PARTICLE_SIZE_PX_LINE; rel_block_y++)
	{
		for (int rel_block_x = 0; rel_block_x < PARTICLE_SIZE_PX_LINE; rel_block_x++)
		{
			const float x = particles_array[particle_count].x + (float)rel_block_x;
			const float y = particles_array[particle_count].y + (float)rel_block_y;

			// particles_array[particle_count] = (particle_t){
			// 	.x = x, // + cosf(particles_array[particle_count].direction) * PARTICLES_SPEED,
			// 	.y = y //+ sinf(particles_array[particle_count].direction) * PARTICLES_SPEED
			// };
			SDL_RenderPoint(renderer, x, y);
		}
	}
	return 0;
}

// Now this function loads every particle from the particle array, draws it and also draws a line to the mouse
int render_particles(SDL_Renderer* renderer)
{
	mouse_position_t curr_mouse_pos;
	SDL_GetMouseState(&curr_mouse_pos.x, &curr_mouse_pos.y);  // get current mouse position

	for (int i = 0; i < particles_amount; i++)
	{
		const float particle_x = particles_array[i].x;
		const float particle_y = particles_array[i].y;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		render_particle_point(renderer, i);
		SDL_SetRenderDrawColor(renderer, 79, 76, 75, 255);
		SDL_RenderLine(renderer, particle_x, particle_y, curr_mouse_pos.x, curr_mouse_pos.y);
	}
	return 0;
}

int end_particles()
{
	// nop for now
	return 0;
}