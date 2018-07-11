#include "AdaptersMgr.h"
#include "pcap.h"
#include "Adapter.h"
#include <iostream>



AdaptersMgr::AdaptersMgr()
{
}


AdaptersMgr::~AdaptersMgr()
{
}

bool AdaptersMgr::Init()
{
	bool bRes = true;

	bRes = InitAdapters();

	StartLog();

	return bRes;
}

bool AdaptersMgr::InitAdapters()
{
	bool bRes = true;
	
	char errbuf[PCAP_ERRBUF_SIZE];
	

	pcap_if_t* alldevs;
	pcap_if_t* d;


	pcap_findalldevs(&alldevs, errbuf);

	

	for (d = alldevs; d; d = d->next)
	{
		string sName(d->name);

		string sDescr;
		if (d->description != 0)
		{
			sDescr = d->description;
		}
		

		cout << sName << ":" << sDescr << "\n";

		if (sName.find("wlan") == string::npos)
		{
			continue;
		}

		Adapter* pAdapter = new Adapter;
		// pAdapter->Init(d, "ip and udp and tcp");
		pAdapter->Init(d, "");
		

		m_adapters.push_back(pAdapter);


	}

	pcap_freealldevs(alldevs);




	return bRes;
}

void AdaptersMgr::CloseAdapters()
{

}


void AdaptersMgr::StartLog()
{
	for (auto pAdapter : m_adapters)
	{
		pAdapter->StartLog();
	}
}

void AdaptersMgr::StopLog()
{

}
