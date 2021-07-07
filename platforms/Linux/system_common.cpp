#include "system_common.h"
#include "system_wrapper.h"

int mutex_init(pthread_mutex_t *mutex)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(mutex, &attr);
	
	return 0;
}
