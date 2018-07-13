#include "MediaControl.h"



MediaControl::MediaControl():m_bIsStarted{false}
{
}


MediaControl::~MediaControl()
{
}

void SaveToMediaHelper(void* pVoid)
{
	MediaControl* pMC = (MediaControl*)pVoid;
	while (false == pMC->IsStopThread())
	{
		unique_lock<mutex> ul(pMC->GetMutex4CondVar());
		pMC->GetCondVar().wait(ul);

		// process the action based on class flags

		// stop thread if so told
		if (true == pMC->IsStopThread())
		{
			break;
		}

		// switch to next media if so told 
		if (pMC->IsSwitchMedia())
		{
			pMC->SwitchMedia();
		}
		else
        if (pMC->IsReleaseFile())
            {
                pMC->ReleaseFile();
            }
        // flush cache to disk, and switch files if current one full
            else
            {
                pMC->SaveCashMedia2File(); //Flush
                pMC->CheckCondition();
            }
	}

	
}


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
	if (m_bIsStarted)
	{
		return;
	}

//	GetNewMediaFile();
//	OpenFile();

	m_bIsStarted = true;
}

void MediaControl::StopMC()
{
	if (!m_bIsStarted)
	{
		return;
	}

	m_bIsStarted = false;

	m_bIs_A_Active = !m_bIs_A_Active; //save last active cash
	//SetEvent(m_hEvent);
}

void MediaControl::Save2Media(unsigned long long  TimeReceived, char* pBuff, unsigned int uLength)
{

	lock_guard<mutex> lock(_mutex);
	if (false == m_bIsStarted)
	{
		
		return;
	}

	MediaChunk*  pMediaChunk = new MediaChunk;
	pMediaChunk->TimeReceived = TimeReceived;
	pMediaChunk->pBuff = new char[uLength];
	memcpy(pMediaChunk->pBuff, pBuff, uLength);
	pMediaChunk->uLength = uLength;

	// figure out which media cache is active
	MediaCash* pActiveMediaCash = m_pMediaCashB;
	MediaCash* pNotActiveMediaCash = m_pMediaCashA;
	if (m_bIs_A_Active)
	{
		pActiveMediaCash = m_pMediaCashA;
		pNotActiveMediaCash = m_pMediaCashB;
	}

	if (pNotActiveMediaCash->uCurrentSize == 0)
	{
		// if active cache will become full with the addition of this chunk of data,
		// make the other cache active, and signal the Media Control thread to save
		// this almost-full (now inactive) cache to disk
		if (pActiveMediaCash->uCurrentSize + uLength > m_uMediaCashMaxSize)
		{
			m_bIs_A_Active = !m_bIs_A_Active; //swap active cash
			if (m_bIs_A_Active)
			{
				pActiveMediaCash = m_pMediaCashA;
			}
			else
			{
				pActiveMediaCash = m_pMediaCashB;
			}

			//SetEvent(m_hEvent);// will result in call to SaveCashMedia2File()
			_condVar.notify_one();
		}
	}

	pActiveMediaCash->listChunk.push_back(pMediaChunk);
	pActiveMediaCash->uCurrentSize += uLength;

}

void MediaControl::OpenFile()
{

}

void MediaControl::CloseFile()
{

}

void MediaControl::CheckCondition()
{

}

void MediaControl::StartReleaseFile()
{

}

void MediaControl::ReleaseFile()
{

}

void MediaControl::SaveCashMedia2File()
{

}

void MediaControl::StartSwitchMedia()
{

}
