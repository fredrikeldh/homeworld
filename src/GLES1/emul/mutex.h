
#ifndef _HW_GLES1_MUTEX_H_
#define _HW_GLES1_MUTEX_H_

#include "include.h"
#include <pthread.h>

class Mutex
{
public:
	Mutex();
	void Lock();
	bool TryLock();
	void Unlock();
	bool IsLocked();
private:
	pthread_mutex_t* _mutex;
};

#endif //_HW_GLES1_MUTEX_H_

