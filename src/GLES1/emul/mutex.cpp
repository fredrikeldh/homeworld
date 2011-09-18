
#include "mutex.h"

Mutex::Mutex()
{
	int result = pthread_mutex_init(_mutex, PTHREAD_MUTEX_RECURSIVE);
	
	if( result )
		throw result;
}

Mutex::~Mutex()
{
	int result = pthread_mutex_destroy(_mutex);
	
	if( result )
		throw result;
}

void Mutex::Lock()
{
	int result = pthread_mutex_lock(&_mutex);
	
	if( result )
		throw result;
}

bool Mutex::TryLock()
{
	int result = pthread_mutex_trylock(&_mutex);
	
	if( result == 0 || result == EBUSY )
		return result == 0;
	
	throw result;
}

void Mutex::Unlock()
{
	int result = pthread_mutex_unlock(&_mutex);
	
	if( result )
		throw result;
}

