/*
 * DLogger.cpp
 *
 *  Created on: 9 Oct 2017
 *      Author: pi
 */

#include "DLogger.h"
#include "AdaptersMgr.h"

#include <cstddef>

DLogger* DLogger::pDLogger;

DLogger::DLogger() : m_pAdaptersMgr{ NULL }
{
	pDLogger = this;
	Init();

}

DLogger::~DLogger() {

	pDLogger = NULL;
}

bool DLogger::Init()
{
	m_pAdaptersMgr = new AdaptersMgr();
	m_pAdaptersMgr->Init();

	return true;
}


