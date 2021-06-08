#include "CtWindowContentsThumbInit.h"

CtWindowContentsThumbInit::CtWindowContentsThumbInit(const CtWindowID WindowID) : 
	CtWindowContentsThumb(WindowID), 
	m_CurrentIndex(0),
	m_ClipCount(0),
	m_RequestClipInfo(NULL),
	m_RequestPicture(NULL),
	m_SelectClip(NULL),
	m_SetFocus(NULL),
	m_NotifyDrawStart(NULL),
	m_NotifyDrawEnd(NULL)
{
	m_ThumbType = CtWindowContentsThumbInit::ContentsThumbType_Init;
}

CtWindowContentsThumbInit::CtWindowContentsThumbInit(CtWindowContentsThumbInit & contents) : 
	CtWindowContentsThumb(contents.getType()), 
	m_CurrentIndex(0),
	m_ClipCount(0),
	m_RequestClipInfo(NULL),
	m_RequestPicture(NULL),
	m_SelectClip(NULL),
	m_SetFocus(NULL),
	m_NotifyDrawStart(NULL),
	m_NotifyDrawEnd(NULL)

{
	m_ThumbType = CtWindowContentsThumbInit::ContentsThumbType_Init;

	m_CurrentIndex = contents.getCurrentIndex();
	m_ClipCount = contents.getClipCount();

	m_RequestClipInfo = contents.getFuncRequestClipInfo();
	m_RequestPicture = contents.getFuncRequestPicture();
	m_SelectClip = contents.getFuncSelectClip();
	m_SetFocus = contents.getFuncSetFocus();
	m_NotifyDrawStart = contents.getFuncNotifyDrawStart();
	m_NotifyDrawEnd = contents.getFuncNotifyDrawEnd();

}

CtWindowContentsThumbInit::~CtWindowContentsThumbInit()
{
}

void CtWindowContentsThumbInit::setClipCount(int count)
{
	m_ClipCount = count;
}

int CtWindowContentsThumbInit::getClipCount()
{
	return m_ClipCount;
}

void CtWindowContentsThumbInit::setCurrentIndex(unsigned long index)
{
	m_CurrentIndex = index;
}

unsigned long CtWindowContentsThumbInit::getCurrentIndex()
{
	return m_CurrentIndex;
}

void CtWindowContentsThumbInit::setFuncRequestClipInfo(ContentsThumbReqClipInfoCallback callback)
{
	m_RequestClipInfo = callback;
}
void CtWindowContentsThumbInit::setReqClipInfoCallback(ContentsThumbReqClipInfoCallback callback)
{
	m_RequestClipInfo = callback;
}

ContentsThumbReqClipInfoCallback CtWindowContentsThumbInit::getFuncRequestClipInfo()
{
	return m_RequestClipInfo;
}
void CtWindowContentsThumbInit::setFuncRequestPicture(ContentsThumbStartDrawCallback callback)
{
	m_RequestPicture = callback;
}
void CtWindowContentsThumbInit::setStartDrawCallback(ContentsThumbStartDrawCallback callback)
{
	m_RequestPicture = callback;
}

ContentsThumbStartDrawCallback CtWindowContentsThumbInit::getFuncRequestPicture()
{
	return m_RequestPicture;
}

void CtWindowContentsThumbInit::setFuncSelectClip(ContentsThumbSyncSelectCallback callback)
{
	m_SelectClip = callback;
}
void CtWindowContentsThumbInit::setSyncSelectCallback(ContentsThumbSyncSelectCallback callback)
{
	m_SelectClip = callback;
}

ContentsThumbSyncSelectCallback CtWindowContentsThumbInit::getFuncSelectClip()
{
	return m_SelectClip;
}

void CtWindowContentsThumbInit::setFuncSetFocus(ContentsThumbSelectIndexCallback callback)
{
	m_SetFocus = callback;
}
void CtWindowContentsThumbInit::setSelectIndexCallback(ContentsThumbSelectIndexCallback callback)
{
	m_SetFocus = callback;
}

ContentsThumbSelectIndexCallback CtWindowContentsThumbInit::getFuncSetFocus()
{
	return m_SetFocus;
}

void CtWindowContentsThumbInit::setFuncNotifyDrawStart(ContentsThumbDrawStartCallback callback)
{
	m_NotifyDrawStart = callback;
}
void CtWindowContentsThumbInit::setThumbDrawStartCallback(ContentsThumbDrawStartCallback callback)
{
	m_NotifyDrawStart = callback;
}

ContentsThumbDrawStartCallback CtWindowContentsThumbInit::getFuncNotifyDrawStart()
{
	return m_NotifyDrawStart;
}

void CtWindowContentsThumbInit::setFuncNotifyDrawEnd(ContentsThumbDrawEndCallback callback)
{
	m_NotifyDrawEnd = callback;
}
void CtWindowContentsThumbInit::setThumbDrawEndCallback(ContentsThumbDrawEndCallback callback)
{
	m_NotifyDrawEnd = callback;
}

ContentsThumbDrawEndCallback CtWindowContentsThumbInit::getFuncNotifyDrawEnd()
{
	return m_NotifyDrawEnd;
}

