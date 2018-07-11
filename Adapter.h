#pragma once

#include "GlobalDef.h"
#include "pcap.h"

class MediaControl;

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void thread_helper(void* pVoid);

class Adapter
{

	pcap_t*       m_adhandle;

	thread      _thread;

	MediaControl* m_pMediaControl;

public:
	Adapter();
	virtual ~Adapter();

	bool Init(pcap_if_t* device_if, string sProto);

	void SetMediaControl(MediaControl* pMediaControl) { m_pMediaControl = pMediaControl; }
	MediaControl* GetMediaControl() { return m_pMediaControl; }
	
	void Close();
	void StartLog();
	void StopLog();
	void Capture();

	void Save2Media();
};


