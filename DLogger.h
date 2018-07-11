#pragma once

class AdaptersMgr;

class DLogger {

	AdaptersMgr*  m_pAdaptersMgr;
public:
	static DLogger* pDLogger ;

public:
	DLogger();
	virtual ~DLogger();

	bool Init();
};





