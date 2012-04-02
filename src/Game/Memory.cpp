/*=============================================================================
    MEMORY.C:   Routines to manage memory
=============================================================================*/

//#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"
#include "Debug.h"
#include "Memory.h"


/*
    Name        : memClearDword
    Description : Clears the specified number of dwords to the specified pattern
    Inputs      : dest - pointer to location to recieve pattern
                  pattern - dword to be duplicated
                  nDwords - number of dwords to duplicate
    Outputs     :
    Return      : OKAY
----------------------------------------------------------------------------*/
sdword memClearDword(void *dest, udword pattern, sdword nDwords)
{
#if defined (_USE_ASM) && defined (_MSC_VER)
    _asm
    {
        mov edi,dest
        mov ecx,nDwords
        mov eax,pattern
        rep stosd
    }
#elif defined (_USE_ASM) && defined (__GNUC__) && defined (__i386__) && !defined (_MACOSX_86)
    __asm__ (
        "rep stosl\n\t"
        :
        : "D" (dest), "c" (nDwords), "a" (pattern) );
#else
	udword *d = ( udword *)dest;
    while (nDwords--)
        *d++ = pattern;
#endif
    return(OKAY);
}

#if 0
template<typename T>
class shared_ptr : public std::shared_ptr<T>
{
private:
	const char* _name;
public:
	shared_ptr(T* instance, const char* name) :
		std::shared_ptr<T>(instance),
		_name(name)
	{
	}
};
#endif

// FIXME:
// * change length to size_t
// * remove flags
void* memAlloc(sdword length, const char* name, udword flags)
{
	return new char[length];
/*
#if MEM_ERROR_CHECKING
    if (length <= 0)
        dbgFatalf(DBG_Loc, "Attempted to allocate %d bytes of '%s'", length, name);
#endif
#if MEM_USE_NAMES
	pointer = home::make_shared<byte>(new byte[length], name);
#else
	pointer = std::make_shared<byte>(new byte[length]);
#endif
*/
}

void* memAllocAttempt(sdword length, const char* name, udword flags)
{
	return memAlloc(length, name, flags);
}

/*-----------------------------------------------------------------------------
    Name        : memFree
    Description : Frees a block of memory
    Inputs      : pointer - pointer to memory to be freed
    Outputs     :
    Return      : void
----------------------------------------------------------------------------*/
void memFree(void *pointer)
{
	delete[] (char*)pointer;
}

/*-----------------------------------------------------------------------------
    Name        : memStringDupe
    Description : Duplicate a string
    Inputs      : string - pointer to string to duplicate
    Outputs     : allocates and strcpy's the string
    Return      : newly allocated string
    Note        : Use memFree to free these strings
----------------------------------------------------------------------------*/
char *memStringDupe(const char *string)
{
    char *newString;

    newString = (char*)memAlloc(strlen(string) + 1, string, MBF_String);
    strcpy(newString, string);
    return(newString);
}

void* memRealloc(void* currentPointer, sdword newSize, const char *name, udword flags)
{
	char* newPointer = new char[newSize];
	memcpy(newPointer, (char*)currentPointer, newSize);
	return newPointer;
/*
#if MEM_USE_NAMES
	return memReallocFunction(currentPointer, newSize, name, flags);
#else
	return memReallocFunction(currentPointer, newSize, flags);
*/
}

/*-----------------------------------------------------------------------------
    Name        : memFreeMemGet
    Description : Compute size of all available memory.
    Inputs      : pool - what pool to get the stats on
    Outputs     : ..
    Return      : available memory, in bytes
----------------------------------------------------------------------------*/
#if MEM_ANALYSIS
size_t memFreeMemGet()
{
	//TODO: Implement platform wise
	/*
	E.g. for android
	MemoryInfo mi = new MemoryInfo();
	ActivityManager activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
	activityManager.getMemoryInfo(mi);
	long availableMegs = mi.availMem / 1048576L;
*/
	return 1024 * 1024;
}
#endif

/*-----------------------------------------------------------------------------
    Name        : memStrncpy
    Description : Line strncpy, but it copies the NULL terminator will always be appended.
                  If length of source > count, dest[count - 1] will be a NULL terminator.
    Inputs      : dest - where to copy to
                  source - where to copy from
                  count - max length of dest
    Outputs     :
    Return      : dest
----------------------------------------------------------------------------*/
char *memStrncpy(char *dest, const char *source, size_t count)
{
	strncpy(dest, source, count);
	// Secure 0 termination
	dest[count - 1] = '\0';
	return dest;
}

