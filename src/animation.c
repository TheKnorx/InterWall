//
// Created by pascal on 12.04.26.
//

#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>

#include "animation.h"
#include "common.h"

static resolution_t resolution;
static particle_t particles_array[PARTICLES_COUNT];

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
	int particles_count;
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
				// we have to make the prob. of a block spawning bigger with every try
				// this guarantees that eventually a block will spawn
				probability_count -= 1/(float)probability;  // for now this is good enough, bit this will be too imprecise in the future!
				continue;
			}
			probability_count = probability;  // reset probability
			// iterate through all the pixels of a particle
			printf("Block at (%d, %d)\n", abs_block_x, abs_block_y);
			for (int rel_block_y = 0; rel_block_y < PARTICLE_SIZE_PX_LINE; rel_block_y++)
			{
				for (int rel_block_x = 0; rel_block_x < PARTICLE_SIZE_PX_LINE; rel_block_x++)
				{
					SDL_RenderPoint(renderer, (float)(abs_block_x+rel_block_x), (float)(abs_block_y+rel_block_y));
				}
			}
		}
	}
	return 0;
}

int end_particles()
{
	// nop for now
	return 0;
}