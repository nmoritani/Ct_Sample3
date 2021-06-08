#include "CtWindowContentsSelectClipInfo.h"

CtWindowContentsSelectClipInfo::CtWindowContentsSelectClipInfo(const CtWindowID WindowID) :
	CtWindowContentsThumb(WindowID)
{
	m_ThumbType = ContentsThumbType_SelectClipInfo;
	m_TopIndex = 0;

}

CtWindowContentsSelectClipInfo::CtWindowContentsSelectClipInfo(CtWindowContentsSelectClipInfo & contents) :
	CtWindowContentsThumb(contents.getType())
{
	m_ThumbType = ContentsThumbType_SelectClipInfo;
	m_TopIndex = contents.getTopIndex();

	ClipInfoList& list = contents.getClipInfoList();

	for (int i = 0; i < list.size(); i++) {
		if (list[i] == NULL) continue;
		CtClipInfo* CopyInfo = new CtClipInfo(*list[i]);
		m_ClipInfoList.push_back(CopyInfo);
	}
}

CtWindowContentsSelectClipInfo::~CtWindowContentsSelectClipInfo()
{
	removeAllClipInfo();
}

void CtWindowContentsSelectClipInfo::addClipInfoList(CtClipInfo* pClipInfo)
{
	m_ClipInfoList.push_back(pClipInfo);
}

CtWindowContentsSelectClipInfo::ClipInfoList & CtWindowContentsSelectClipInfo::getClipInfoList()
{
	return m_ClipInfoList;
}

void CtWindowContentsSelectClipInfo::setTopIndex(unsigned long index)
{
	m_TopIndex = index;
}

unsigned long CtWindowContentsSelectClipInfo::getTopIndex()
{
	return m_TopIndex;
}

void CtWindowContentsSelectClipInfo::removeAllClipInfo()
{
	for (int i = 0; i< m_ClipInfoList.size(); i++) {
		if (m_ClipInfoList[i] != NULL) {
			delete m_ClipInfoList[i];
		}
	}
}

