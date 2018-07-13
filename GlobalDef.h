#ifndef _GlobalDef
#define _GlobalDef

#include <string>
#include <list>
#include <map>
#include <thread>
#include <mutex>
#include <cstring>
#include <condition_variable>

using namespace std;

//MediaControl

// chunk of data received
typedef struct _MediaChunk
{
	unsigned long long  TimeReceived;
	char* pBuff;
	unsigned int  uLength;

} MediaChunk;

// list of chunks of data
typedef list<MediaChunk*> ListChunk;

// media cache (containing a list of data chunks)
typedef struct
{
	ListChunk listChunk;
	unsigned int        uCurrentSize;

} MediaCash;

#endif
