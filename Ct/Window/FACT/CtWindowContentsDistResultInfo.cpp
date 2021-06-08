#include "CtWindowContentsDistResultInfo.h"

CtWindowContentsDistResultInfo::CtWindowContentsDistResultInfo(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	m_DistResult.RESULT    = false;
	memset(m_DistResult.dist_name, 0, sizeof(m_DistResult.dist_name));
}



CtWindowContentsDistResultInfo::CtWindowContentsDistResultInfo(CtWindowContentsDistResultInfo& content) : CtWindowContents(content.getType()) {
	setDistResult(content.getDistResult());
}



CtWindowContentsDistResultInfo::~CtWindowContentsDistResultInfo() {
}

void CtWindowContentsDistResultInfo::setDistResult(DistResult * distresult)
{
	if(NULL == distresult)
	{
		return;
	}
	
	memcpy(m_DistResult.dist_name, distresult->dist_name, sizeof(m_DistResult.dist_name));
	m_DistResult.dist_name[sizeof(m_DistResult.dist_name) - 1] = NULL;

	m_DistResult.RESULT    = distresult->RESULT;

}

CtWindowContentsDistResultInfo::DistResult* CtWindowContentsDistResultInfo::getDistResult()
{
	return &m_DistResult;
}

