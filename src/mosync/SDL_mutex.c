#include <SDL_mutex.h>


SDL_sem *SDL_CreateSemaphore(Uint32 initial_value)
{
	return (SDL_sem *)1;
}

void SDL_DestroySemaphore(SDL_sem *sem)
{
	return;
}

int SDL_SemTryWait(SDL_sem *sem)
{
	return 0;
}

int SDL_SemWaitTimeout(SDL_sem *sem, Uint32 timeout)
{
	return 0;
}

int SDL_SemWait(SDL_sem *sem)
{
	return 0;
}

Uint32 SDL_SemValue(SDL_sem *sem)
{
	return 0;
}

int SDL_SemPost(SDL_sem *sem)
{
	return 0;
}

SDL_mutex * SDL_CreateMutex(void) { return (SDL_mutex*)1; }
int SDL_mutexP(SDL_mutex *mutex) { return 0; }
int SDL_mutexV(SDL_mutex *mutex) { return 0; }
void SDL_DestroyMutex(SDL_mutex *mutex) {}
