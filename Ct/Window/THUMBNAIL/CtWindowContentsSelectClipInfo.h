#ifndef __CtWindowContentsSelectClipInfo_H__
#define __CtWindowContentsSelectClipInfo_H__

#include "CtWindowContentsThumbCommon.h"
#include "CtWindowContentsThumb.h"
#include "CtWindowContentsClipInfo.h"
#include "CtVector.h"

class CtWindowContentsSelectClipInfo : public CtWindowContentsThumb {
public:
	typedef CtVector::Vector<CtClipInfo*> ClipInfoList;
	typedef CtVector::Vector<CtClipInfo*>::iterator ClipInfoListItr;

	CtWindowContentsSelectClipInfo(const CtWindowID WindowID);
	CtWindowContentsSelectClipInfo(CtWindowContentsSelectClipInfo& ContentsClipInfo);
	~CtWindowContentsSelectClipInfo();

	void addClipInfoList(CtClipInfo * pClipInfo);
	ClipInfoList& getClipInfoList();

	void setTopIndex(unsigned long index);
	unsigned long getTopIndex();

private:
	void removeAllClipInfo();

private:
	ClipInfoList m_ClipInfoList;
	unsigned long m_TopIndex;	//�i�[����Ă���N���b�v���̃C���f�b�N�X(�S�̂���݂ĉ��Ԗڂ̃N���b�v��)


};

#endif
