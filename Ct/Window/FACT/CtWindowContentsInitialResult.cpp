#include "CtWindowContentsInitialResult.h"

CtWindowContentsInitialResult::CtWindowContentsInitialResult(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	m_Result.RESULT    = false;
	m_Result.SUM_CHECK = false;
	m_Result.SUM_CAM   = false;
	m_Result.SUM_BE    = false;
	m_Result.CAM_RESET = false;
	m_Result.WIFI_INIT = false;
	m_Result.NFC_INIT  = false;
	m_Result.ESD_CAPA  = false;
	m_Result.ESD_NODATA= false;
}

CtWindowContentsInitialResult::CtWindowContentsInitialResult(CtWindowContentsInitialResult& content) : CtWindowContents(content.getType()) {
	setResult(content.getResult());
}

CtWindowContentsInitialResult::~CtWindowContentsInitialResult() {
}

void CtWindowContentsInitialResult::setResult(CtWindowContentsInitialResult::Result* result) {
	
	if( result == NULL ){
		return;
	}
	
	m_Result.RESULT    = result->RESULT;
	m_Result.SUM_CHECK = result->SUM_CHECK;	/* parasoft-suppress BD-PB-NOTINIT */
	m_Result.SUM_CAM   = result->SUM_CAM;
	m_Result.SUM_BE    = result->SUM_BE;
	m_Result.CAM_RESET = result->CAM_RESET;
	m_Result.WIFI_INIT = result->WIFI_INIT;
	m_Result.NFC_INIT  = result->NFC_INIT;
	m_Result.ESD_CAPA  = result->ESD_CAPA;
	m_Result.ESD_NODATA= result->ESD_NODATA;

}

CtWindowContentsInitialResult::Result* CtWindowContentsInitialResult::getResult() {
	return &m_Result;
}
