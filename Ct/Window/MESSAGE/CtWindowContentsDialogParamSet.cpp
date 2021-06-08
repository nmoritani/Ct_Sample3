#include "CtWindowContentsDialogParamSet.h"
#include "AplParamService.h"

CtWindowContentsDialogParamSet::CtWindowContentsDialogParamSet(const CtWindowID WindowID) : 
	CtWindowContents(WindowID)
{
	setDate(AplParamIdMax, 0);
	setClassType(CtClassType_ContentsParamSet);
}

CtWindowContentsDialogParamSet::CtWindowContentsDialogParamSet(const CtWindowID WindowID, int id, int value) :
	CtWindowContents(WindowID)
{
	setDate(id, value);
	setClassType(CtClassType_ContentsParamSet);
}

CtWindowContentsDialogParamSet::~CtWindowContentsDialogParamSet() {
}

void CtWindowContentsDialogParamSet::setDate(int id, int val)
{
	m_ParamId = id;
	m_Value   = val;
}
int CtWindowContentsDialogParamSet::getParamId() {
	return m_ParamId;
}
int CtWindowContentsDialogParamSet::getValue() {
	return m_Value;
}
