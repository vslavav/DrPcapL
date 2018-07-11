

#include "Adapter.h"
#include <iostream>
#include <sys/time.h>
#include "MediaControl.h"


Adapter::Adapter() {
	// TODO Auto-generated constructor stub

}

Adapter::~Adapter() {
	// TODO Auto-generated destructor stub
}

bool Adapter::Init(pcap_if_t* device_if, string sProto)
{
	

	char errbuf[PCAP_ERRBUF_SIZE];


	//m_bIsCloseAdapter = false;


	/* Open the adapter */
	if ((m_adhandle = pcap_open_live(device_if->name,	// name of the device
		65536,			// portion of the packet to capture. 
						// 65536 grants that the whole packet will be captured on all the MACs.
		1,				// promiscuous mode (nonzero means promiscuous)
		1000,			// read timeout
		errbuf			// error buffer
	)) == NULL)
	{

		// pcap_freealldevs(alldevs);
		return false;
	}

	/* Check the link layer. We support only Ethernet for simplicity. */
	if (pcap_datalink( m_adhandle ) != DLT_EN10MB)
	{
		// fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* Free the device list */
		// pcap_freealldevs(alldevs);
		return false;
	}


	return true;

}

void Adapter::Close()
{
	pcap_close( m_adhandle );
}

void Adapter::StartLog()
{
	_thread = thread(thread_helper, this);
}

void  Adapter::StopLog()
{
	pcap_breakloop(m_adhandle);
}

void Adapter::Capture()
{

	pcap_loop(m_adhandle, 0, packet_handler, (u_char *)this);

	return;   // No Complaint

}

void thread_helper(void* pVoid)
{
	Adapter* pAdapter = (Adapter*)pVoid;
	pAdapter->Capture();
}

#define EPOCH_DIFF 11644473600LL

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	Adapter* pAdapter = (Adapter*)param;
	//https://www.winpcap.org/docs/docs_412/html/group__wpcap__tut6.html
	
	pAdapter->Save2Media();
	
	struct timeval tv;
	unsigned long long llTime = EPOCH_DIFF;
	gettimeofday(&tv, NULL);
	llTime += tv.tv_sec;
	llTime *= 10000000LL;
	llTime += tv.tv_usec * 10;
	

	pAdapter->GetMediaControl()->Save2Media(llTime, (char*)pkt_data, header->len);

}

void Adapter::Save2Media()
{
	cout << "Save2Media" << "\n";
}
