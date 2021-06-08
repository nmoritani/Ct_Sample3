#ifndef __CtWindowContentsInitialResult_H__
#define __CtWindowContentsInitialResult_H__

#include "CtWindowContents.h"

class CtWindowContentsInitialResult : public CtWindowContents {
public :
	
	typedef struct {
		bool RESULT;
		bool SUM_CHECK;
		bool SUM_CAM;
		bool SUM_BE;
		bool CAM_RESET;
		bool WIFI_INIT;
		bool NFC_INIT;
		bool ESD_CAPA;
		bool ESD_NODATA;
	} Result;
	
	CtWindowContentsInitialResult(const CtWindowID WindowID);
	CtWindowContentsInitialResult(CtWindowContentsInitialResult& message);
	virtual ~CtWindowContentsInitialResult();

	void setResult(Result* result);
	Result* getResult();

private:
	Result m_Result;
};

#endif
