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

	//���ʒʒm���b�Z�[�W�p(APL��GUI�ւ̒ʒm)
	void setDistResult(DistResult* distresult);	//APL��GUIL��
	DistResult* getDistResult();				//GUI��APL

private:
	DistResult m_DistResult;
};



#endif
