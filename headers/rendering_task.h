#ifndef RENDER_TASKS_HEADER
#define RENDER_TASKS_HEADER

/*
 * Overview: File contains rendering and
 * thread handling functions of the Maze game
 */

/* Rendering and Thread Handling functions */
void transmit_viewport(SDL_Instance *sdl);
int handle_thread(void *thrd_ptr);

#endif