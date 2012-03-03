/*=============================================================================
    MEMORY.H:  Definitions for Homeworld memory management module.

    Created June 1997 by Luke Moloney
=============================================================================*/

#ifndef ___MEMORY_H
#define ___MEMORY_H

#include "LinkedList.h"
#include "Task.h"

/*=============================================================================
    Switches:
=============================================================================*/
#define MEM_SMALL_BLOCK_HEAP    1               //enable small block heap allocations
#define MEM_VOLATILE_CLEARING   1               //the clear dwords are volatile and unreliable

#ifdef HW_BUILD_FOR_DEBUGGING

#define MEM_MODULE_TEST         0               //test the module
#define MEM_ERROR_CHECKING      1               //basic error checking
#define MEM_CLEAR_MEM           1               //clear newly allocated blocks to all clear code
#define MEM_CLEAR_MEM_ON_FREE   1               //clear newly freed blocks to all clear code
#define MEM_VERBOSE_LEVEL       1               //control verbose printing
#define MEM_USE_NAMES           1               //use names in allocated blocks
#define MEM_DEFRAGMENT_FREE     1               //attempt to join with adjacent free block(s) when freeing
#define MEM_ANALYSIS            1               //enable memory analysis functions
#define MEM_STATISTICS          1               //track memory usage stats
#define MEM_ANALYSIS_KEY        QKEY            //create a memory analysis on demand
#define MEM_DETECT_VOLATILE     1               //automatically detect what memory blocks are volatile
#define MEM_FILE_NV             0               //log non-volatile allocs to a file
#define MEM_DEBUG_NV            0               //log non-volatile allocs to debug window
#define MEM_SMALLBLOCK_STATS    1               //log usage stats on small memory blocks
#define MEM_LOG_MOSTVOLATILE    1               //keep track of the most volatile types of memory
#define MEM_ANALYSIS_AUTOCREATE 1               //automatically create memory analysis if there's an allocation failure
#define MEM_VOLATILE_CLEARING   1               //the clear dwords are volatile and unreliable
#define MEM_ANAL_CHECKING       1               //extra hard-core debuggery action

#else

#define MEM_MODULE_TEST         0               //don't test the module
#define MEM_ERROR_CHECKING      0               //no error ckecking in retail
#define MEM_CLEAR_MEM           0               //don't clear any blocks to zeros
#define MEM_CLEAR_MEM_ON_FREE   0               //clear newly freed blocks to all clear code
#define MEM_VERBOSE_LEVEL       0               //don't print any verbose strings in retail
#define MEM_USE_NAMES           0               //no names please ma'am
#define MEM_DEFRAGMENT_FREE     1               //attempt to join with adjacent free block(s) when freeing
#define MEM_ANALYSIS            0               //disable memory analysis functions
#define MEM_STATISTICS          0               //track memory usage stats
#define MEM_ANALYSIS_KEY        0               //create a memory analysis on demand
#define MEM_DETECT_VOLATILE     0               //automatically detect what memory blocks are volatile
#define MEM_FILE_NV             0               //log non-volatil allocs to a file
#define MEM_DEBUG_NV            0               //log non-volatil allocs to debug window
#define MEM_SMALLBLOCK_STATS    0               //log usage stats on small memory blocks
#define MEM_LOG_MOSTVOLATILE    0               //keep track of the most volatile types of memory
#define MEM_ANALYSIS_AUTOCREATE 0               //automatically create memory analysis if there's an allocation failure
#define MEM_ANAL_CHECKING       0               //extra hard-core debuggery action

#endif

/*=============================================================================
    Definitions:
=============================================================================*/
//memory block flags
#define MBF_AllocatedNext       1               //memory following block allocated
#define MBF_AllocatedPrev       2               //preceeding memory block allocated
//#define MBF_Purgable            4             //will be purged on next call to memPurge()
#define MBF_SmallBlockHeap      4               //allocated from a small block heap
#define Flammable               MBF_SmallBlockHeap//another way of saying very volatile
#define Pyrophoric              MBF_SmallBlockHeap//another way of saying very volatile
#define MBF_Volatile            0               //expect this block to be freed soon
#define Volatile                MBF_Volatile
#define MBF_NonVolatile         8
#define MBF_String              16
#define NonVolatile             MBF_NonVolatile
#define MBF_ExtendedPoolOnly    32
#define ExtendedPool            MBF_ExtendedPoolOnly
#define MBF_VerifyMask          0xffffffc0      //remaining bits used for verification mask
#define MBF_ParameterMask       (MBF_NonVolatile | MBF_SmallBlockHeap | MBF_String) //which parameter flags to store in the cookie flags

//verification value
#define MBF_VerifyValue         (0xfa7babe5 & MBF_VerifyMask)

//max length for cookie name strings
#ifdef _X86_64
 #if MEM_DETECT_VOLATILE
  #define MEM_NameLength          48
 #else
  #define MEM_NameLength          52
 #endif
 #if MEM_LOG_MOSTVOLATILE
  #define MBH_NameLength          20
 #else
  #define MBH_NameLength          16
 #endif
#else
 #if MEM_DETECT_VOLATILE
  #define MEM_NameLength          16
 #else
  #define MEM_NameLength          20
 #endif
 #if MEM_LOG_MOSTVOLATILE
  #define MBH_NameLength          4
 #else
  #define MBH_NameLength          8
 #endif
#endif

//allocation block granularity.
#define MEM_BlockSize           ((sdword)sizeof(memcookie))
#define MEM_BlocksPerCookie     1

//default memory heap size
#define MEM_HeapSizeDefault     (18 * 1024 * 1024)
#define MEM_HeapDefaultScalar   0.40f
#define MEM_HeapDefaultMax      (64 * 1024 * 1024)

//default name strings
#define MEM_NameHeap            "HeapLow(free)"
#define MEM_NameHeapFirst       "HeapLowFirst(Free)"
#define MEM_HeapFree            "(free)"
#define MEM_NameHeapLast        "HeapHighFirst(free)"

//memory clearing settings
#define MEM_ClearSetting        0x4e7a110c
#define MEM_FreeSetting         0xf4eeda7a

//memory statistics
#define MEM_AllocsPerStatPrint  100
#define MEM_StatsKey            QKEY

//small block allocation defines
//the smallest small allocation block must be smaller than the smallest allocation
#define MSB_SizeMin             MEM_BlockSize
#define MSB_SizeMax             2048
#define MSB_NumberSizes         ((MSB_SizeMax - MSB_SizeMin) / MEM_BlockSize)
#define MEM_OptCounterFreqSmall 2048
#define MEM_OptCounterFreqBig   8192
#define MEM_GrowFactor          96 / 256        //grow by 37.5% when a SBH pool runs out

//for printing memory statistics
#define MEM_TaskStatsPeriod     1.0             //once per second

#define MEM_VolatileLong        5.0f            //any block that is freed after this amount of time is non-volatile
#define MEM_VolatileShort       1.0f

#define MEM_HeapValidation      0xbad600f       //bad guy validation

//byte offsets for finding a heap from the linked list
#define MBH_AllocatedLinkOffset 0
//#define MBH_FreeLinkOffset      (4 + sizeof(LinkedList))

//definitions for cookie volatility logging
#define MEM_NumberVolatileStats 768

//definitions for tracking the most commonly allocated cookie names
#define MS_NumberCookieNames    64
#define MS_OutputStringLength   128
#define MS_NameStringLength     64

//definitions for growing the memory heaps
#define MGH_NumberGrowthHeaps   16              //maximum number of extra heaps we can grow to
#define MGH_MinGrowthSize       (4 * 1024 * 1024 - sizeof(memcookie) * 2)//grow in 4MB increments.  That's 64MB extra heap size.  Should be sufficient.

/*=============================================================================
    Type definitions:
=============================================================================*/
//structure for a memory block cookie
typedef struct
{
    udword flags;                               //validation and information
#if MEM_USE_NAMES
    char name[MEM_NameLength];                  //name of memory block
#else
    ubyte pad[MEM_NameLength];                  //round structure up to 16 bytes
#endif
    sdword blocksNext;                          //number of blocks to next cookie
    sdword blocksPrevious;                      //number of blocks to previous cookie
                                                //only valid when freeing memory
#if MEM_DETECT_VOLATILE
    real32 timeAllocated;                       //when was this block allocated?
#endif
}
memcookie;

typedef void *(*memgrowcallback)(sdword heapSize);//callback for growing memory
typedef void (memgrowthfreecallback)(void *heap);//callback for freeing growth heaps

/*=============================================================================
    Data:
=============================================================================*/
//memory statistics
#if MEM_STATISTICS
extern sdword memNumberWalks;
extern sdword memNumberAllocs;
extern char memStatString[256];
extern bool memStatsLogging;
extern taskhandle memStatsTaskHandle;
DECLARE_TASK(memStatsTaskFunction);
extern memcookiename memStatsCookieNames[MS_NumberCookieNames];
#endif

/*=============================================================================
    Macros:
=============================================================================*/
//name-specific stuff
void* memAlloc(sdword l, const char* name, udword flags);
void* memAllocAttempt(sdword l, const char* name, udword flags);
void* memRealloc(void* currentPointer, sdword newSize, const char *name, udword flags);

//block size macros
#define memRoundUp(n)   (((n) + (MEM_BlockSize - 1)) & (~(MEM_BlockSize - 1)))
#define memRoundDown(n) ((n) & (~(MEM_BlockSize - 1)))
#define memBlocksCompute(s, e)  ((memRoundDown((udword)(e)) - memRoundUp((udword)(s))) / MEM_BlockSize)
#define memBlocksToBytes(b)     ((b) * MEM_BlockSize)
#define memBytesToBlocks(b)     ((b) / MEM_BlockSize)

#define memCookieVerify(c)
#define mbhCookieVerify(c)

//if module not started properly, generate an error
#if MEM_ERROR_CHECKING
#define memInitCheck()\
    if (memModuleInit == FALSE)\
    {\
        dbgFatal(DBG_Loc, "Called before memory module started or after closed.");\
    }
#else
#define memInitCheck()
#endif

//small block allocation
#define msbSizeBytes(length)    (pool->firstSize[((length) / MEM_BlockSize) - 1])
#define msbSizeBlocks(length)   (pool->firstSize[length - 1])
#define msbSizeIndex(length)    (((length) / MEM_BlockSize) - 1)
#define mslSizeBytes(length)    (pool->lastSize[((length) / MEM_BlockSize) - 1])
#define mslSizeBlocks(length)   (pool->lastSize[length - 1])
#define mslSizeIndex(length)    (((length) / MEM_BlockSize) - 1)

/*=============================================================================
    Functions:
=============================================================================*/

//startup/shutdown/reset memory module
sdword memStartup(void *heapStart, sdword heapSize, memgrowcallback grow);
sdword memReset(void);
sdword memClose(memgrowthfreecallback free);

//allocate/free memory blocks
void memFree(void *pointer);
char *memStringDupe(const char *string);

//utility functions (many stubbed out in retail builds)
#if MEM_ANALYSIS
void memAnalysisCreate(void);
#endif
sdword memClearDword(void *dest, udword pattern, sdword nDwords);
char *memStrncpy(char *dest, const char *source, size_t count);

#if MEM_ANALYSIS
size_t memFreeMemGet();
#endif

const memsize * check_mem(const memsize * data);

#endif
