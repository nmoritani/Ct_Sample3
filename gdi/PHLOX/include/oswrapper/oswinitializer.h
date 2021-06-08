/*
  Copyright (c) 2012, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_INITIALIZER_H__
#define __OSW_INITIALIZER_H__

#include <oswrapper/oswplatform.h>

#ifdef __cplusplus
extern "C" {
#endif


#if	defined(_MSC_VER)

#include <windows.h>
#include <tchar.h>

#define OSW_INITIALIZER(f1, f2)														\
																					\
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)	\
	{																				\
		switch(fdwReason)															\
		{																			\
		  case DLL_PROCESS_ATTACH:													\
			{																		\
				void (*func)() = f1;												\
				if (func) func();													\
			}																		\
			break;																	\
																					\
		  case DLL_PROCESS_DETACH:													\
			{																		\
				void (*func)() = f2;												\
				if (func) func();													\
			}																		\
			break;																	\
																					\
		  case DLL_THREAD_ATTACH:													\
			break;																	\
																					\
		  case DLL_THREAD_DETACH:													\
			break;																	\
		}																			\
		return TRUE;																\
	}


#elif	defined(__GNUC__) || defined(__arm)

/*
 *  ARM C: need --translate_gcc, --translate_gld, --translate_g++
 */

#define OSW_INITIALIZER(f1, f2)			\
	static void __OSW_constructor(void)	__attribute__	((constructor));	\
	static void __OSW_destructor(void)	__attribute__	((destructor));		\
										\
	static void __OSW_constructor(void)	\
	{									\
		void (*func)() = f1;			\
		if (func) func();				\
	}									\
										\
	static void __OSW_destructor(void)	\
	{									\
		void (*func)() = f2;			\
		if (func) func();				\
	}

#else

#	error	OSW_INITIALIZER: GCC only

#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_INITIALIZER_H__ */
