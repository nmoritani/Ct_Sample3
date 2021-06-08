
#if !defined(__CtMemory_H__)
#define __CtMemory_H__

#include <stdio.h>

class CtMemory
{
public:
	static void* get(size_t size);
	static void free(void* ptr);
};

#endif // !defined(__CtMemory_H__)
