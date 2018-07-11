#include "MediaControl.h"



MediaControl::MediaControl()
{
}


MediaControl::~MediaControl()
{
}

void SaveToMediaHelper(void* pVoid)
{}


void MediaControl::Init()
{
	/*	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); //auto-reset, non-signaled
		m_hThread = CreateThread(NULL, 0, SaveToMediaHelper,
			(LPVOID)this, NULL, &m_dwThreadId);

		InitializeCriticalSection(&m_CritSection); */

	m_bIsStopThread = false;
	m_bIsSwitchMedia = false;

	_thread = thread(SaveToMediaHelper, this);

	m_pMediaCashA->uCurrentSize = 0;
	m_pMediaCashB->uCurrentSize = 0;
	m_bIs_A_Active = true;


}


void MediaControl::SwitchMedia()
{

}

void MediaControl::Close()
{

}

void MediaControl::CleanUp()
{

}

void MediaControl::StartMC()
{

}

void MediaControl::StopMC()
{

}

void MediaControl::Save2Media(unsigned long long  TimeReceived, char* pBuff, unsigned int uLength)
{


}

void MediaControl::OpenFile()
{

}

void MediaControl::CloseFile()
{

}

void MediaControl::StartReleaseFile()
{

}

void MediaControl::ReleaseFile()
{

}
