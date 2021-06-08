#ifndef __CtWindowContentsDialogParamSet_H__
#define __CtWindowContentsDialogParamSet_H__

#include "CtWindowContents.h"

class CtWindowContentsDialogParamSet : public CtWindowContents {
public :
	
	CtWindowContentsDialogParamSet(const CtWindowID WindowID);
	CtWindowContentsDialogParamSet(const CtWindowID WindowID, int id, int value);
	virtual ~CtWindowContentsDialogParamSet();

	void setDate(int id, int val);
	int getParamId();
	int getValue();

private:
	int m_ParamId;
	int m_Value;

};

#endif
