
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "Types.h"
#include "File.h"
#include "CommandWrap.h"

#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

static const std::string TITAN_LOG_FILE_NAME(u8"titanlog.txt");

//bool titanLogEnable = TRUE;

static TitanLog* LOG = NULL;

class TitanLog : public LogFile
{
public:
	void Debug(char *format, ...)
	{
		//TODO: switch to UTF8
#define DATA_SIZE 200 // space passed data is allowed to take up
#define TIME_SIZE 9   // space required by time string at front of each line
		char buffer[DATA_SIZE + TIME_SIZE + 2]; // +1 for the carriage-return and null terminator
		va_list argList;
		int aNumChars;
#ifdef _WIN32
		SYSTEMTIME systime;

		GetSystemTime(&systime);
		snprintf(buffer, TIME_SIZE, "%02d:%02d:%02d ", systime.wHour, systime.wMinute, systime.wSecond);
#else
		struct timeval tv;
		long tv_hour, tv_minute, tv_second;

		gettimeofday(&tv, 0);
		tv_hour   = (tv.tv_sec % 86400) / 3600;
		tv_minute = (tv.tv_sec %  3600) /   60;
		tv_second = (tv.tv_sec %    60);
		snprintf(buffer, TIME_SIZE, "%02ld:%02ld:%02ld ", tv_hour, tv_minute, tv_second);
#endif

		va_start(argList, format);                            //get first arg
		aNumChars = vsnprintf(buffer + TIME_SIZE, DATA_SIZE, format, argList); //prepare output string
		va_end(argList);

		if (aNumChars >= 0)
			memcpy((void*)(buffer + TIME_SIZE + aNumChars), "\n\0", 2);
		
		Log(buffer);
	}
	
	TitanLog() :
		LogFile(TITAN_LOG_FILE_NAME.c_str())
	{
		Clear();
		time_t now = time(NULL);
		char datestring[16];
		strftime(datestring, 16, "%a %b %d %Y", gmtime(&now));
		Debug("Todays date is: %s", datestring);
	}
};

void titanDebug(char *format, ...)
{
	if( !LOG )
		return;
	
	LOG->Debug(format, ...);
}

void titanLogFileOpen()
{
	if( LOG && logEnable )
		return;
	
	LOG = new TitanLog();
}

void titanLogFileClose(void)
{
	//NO Op
}

