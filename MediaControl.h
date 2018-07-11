#pragma once
#include "GlobalDef.h"


void SaveToMediaHelper(void* pVoid);
	


class MediaControl
{

	//MediaCash part
	MediaCash*            m_pMediaCashA;	// caches A and B both used for writing; when A fills up,
	MediaCash*            m_pMediaCashB;	// B is used, while A gets dumped to disk; and vice-verse
	unsigned int                    m_uMediaCashMaxSize;
	bool                    m_bIs_A_Active;	// currently using cache A?
	bool              m_bIsStopThread;
	bool              m_bIsSwitchMedia;
	bool              m_bIsReleaseFile;
	//CFile                   m_File;

	thread				_thread;

public:
	MediaControl();
	~MediaControl();


	void Init();
	void Close();
	void CleanUp();
	void StartMC();
	void StopMC();

	void Save2Media(unsigned long long  TimeReceived, char* pBuff, unsigned int uLength);

	bool IsStopThread() { return m_bIsStopThread; }
	bool IsSwitchMedia() { return m_bIsSwitchMedia; }
	bool IsReleaseFile() { return m_bIsReleaseFile; }
	void SwitchMedia();

	void StartReleaseFile();
	void ReleaseFile();
	
	void OpenFile();
	void CloseFile();
};

