#include <stdlib.h>
#include <sys/unistd.h>
#include <mastdlib.h>
#include <ma.h>

void ansi_heap_init_crt0(char *start, int length);
static char sHeap[1024*1024*32];

extern int resource_selector();

extern int main (int argc, const char* argv[]);

#define WRITE_LOG(str) maWriteLog(str, sizeof(str)-1)

int MAMain()
{
	ansi_heap_init_crt0(sHeap, sizeof(sHeap));

	// switch stdout from console to maWriteLog.
	WRITE_LOG("open_maWriteLog\n");
	int wlfd = open_maWriteLog();
	dup2(wlfd, 1);
	dup2(wlfd, 2);
	close(wlfd);

	//setenv("HOME", "/", 1);
	//setenv("HW_CDROM", "/cdrom", 1);
	chdir("/home");
	static const char* argv[] = { "homeworld", "/noSound", NULL };
	return main(2, argv);
}
