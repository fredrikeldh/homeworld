#include <stdlib.h>
#include <sys/unistd.h>
#include <ma.h>

void ansi_heap_init_crt0(char *start, int length);
static char sHeap[1024*1024*32];

int resource_selector();

void mosync_preinit()
{
	ansi_heap_init_crt0(sHeap, sizeof(sHeap));

	//setenv("HOME", "/", 1);
	//setenv("HW_CDROM", "/cdrom", 1);
	chdir("/home");
}
