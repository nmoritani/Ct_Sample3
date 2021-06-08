#ifndef __CtWindowContentsDistResultInfo_H__
#define __CtWindowContentsDistResultInfo_H__

#include "CtWindowContents.h"

class CtWindowContentsDistResultInfo : public CtWindowContents {

public :
	typedef struct {
		bool RESULT;
		char dist_name[50];
	} DistResult;

	CtWindowContentsDistResultInfo(const CtWindowID WindowID);
	CtWindowContentsDistResultInfo(CtWindowContentsDistResultInfo& distresult);
	virtual ~CtWindowContentsDistResultInfo();

	//結果通知メッセージ用(APL⇒GUIへの通知)
	void setDistResult(DistResult* distresult);	//APL→GUIL側
	DistResult* getDistResult();				//GUI→APL

private:
	DistResult m_DistResult;
};



#endif
