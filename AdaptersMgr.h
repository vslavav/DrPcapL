#pragma once
#include "GlobalDef.h"

using namespace std;

class Adapter;

typedef list<Adapter*> Adapters;

class AdaptersMgr
{
	Adapters m_adapters;

public:
	AdaptersMgr();
	virtual ~AdaptersMgr();

	bool Init();
	bool InitAdapters();
	void CloseAdapters();
	
	void StartLog();
	void StopLog();

	
};

