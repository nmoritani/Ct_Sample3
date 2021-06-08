#include "CtWindowContentsClipInfo.h"

CtClipInfo::CtClipInfo() {
	memset(&m_ClipInfo, 0, sizeof(m_ClipInfo));
}

CtClipInfo::CtClipInfo(CtClipInfo& obj) {  /*•Ï”‚ÆŠÖ”“¯–¼‚Å‚·*//* pgr2222 */
	memset(&m_ClipInfo, 0, sizeof(m_ClipInfo));
	m_ClipInfo = obj.getClipInfo();		/* pgr2222 */
}

CtClipInfo::~CtClipInfo() {
}

CtClipInfo::ClipInfo CtClipInfo::getClipInfo() {
	return m_ClipInfo;
}

void CtClipInfo::setClipInfo(CtClipInfo::ClipInfo& info) {
	m_ClipInfo = info;
}


CtWindowContentsClipInfo::CtWindowContentsClipInfo(const CtWindowID WindowID) : CtWindowContentsThumb(WindowID), m_CurrentIndex(0), m_StartDrawCallback(NULL), m_ClipInfoList(0), m_SyncSelectCallback(NULL), m_SelectIndexCallback(NULL) {
	m_ThumbType = CtWindowContentsClipInfo::ContentsThumbType_ClipInfo;
}

CtWindowContentsClipInfo::CtWindowContentsClipInfo(CtWindowContentsClipInfo& ContentsClipInfo)  : CtWindowContentsThumb(ContentsClipInfo.getType()), m_CurrentIndex(0), m_StartDrawCallback(NULL) {
	m_ThumbType = CtWindowContentsClipInfo::ContentsThumbType_ClipInfo;
	
	m_CurrentIndex = ContentsClipInfo.getCurrentIndex();
	m_StartDrawCallback = ContentsClipInfo.getStartDrawCallback();
    m_SyncSelectCallback = ContentsClipInfo.getSyncSelectCallback();
	m_SelectIndexCallback = ContentsClipInfo.getSelectIndexCallback();
	ClipInfoList& list = ContentsClipInfo.getClipInfoList();

	for (ClipInfoListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
		CtClipInfo* CopyInfo = new CtClipInfo(*(*Itr));
		m_ClipInfoList.push_back(CopyInfo);
	}
}
/* ForTest */
void CtWindowContentsClipInfo::setClipInfoList(CtClipInfo* pCtClipInfo){

    if (pCtClipInfo == NULL) return;
    CtClipInfo* p1 = pCtClipInfo;
    int index = this->getCurrentIndex();
    int i = 0;
	if( p1 != NULL ){
	    for (; p1 != NULL; p1++,i++){	/* pgr0689 */
	        if (i > index){
	            break;
	        }else{
	            m_ClipInfoList.push_back(p1);
	        }
	    }
	}
}
CtWindowContentsClipInfo::~CtWindowContentsClipInfo() {
	removeAllClipInfo();
}

void CtWindowContentsClipInfo::removeAllClipInfo() {
	for (int i = 0; i< m_ClipInfoList.size(); i++) {
		if (m_ClipInfoList[i] != NULL) {
			delete m_ClipInfoList[i];
		}
	}
}

void CtWindowContentsClipInfo::setCurrentIndex(unsigned long Index) {
	m_CurrentIndex = Index;
}

unsigned long CtWindowContentsClipInfo::getCurrentIndex() {
	return m_CurrentIndex;
}

CtWindowContentsClipInfo::ClipInfoList& CtWindowContentsClipInfo::getClipInfoList() {
	return m_ClipInfoList;
}

void CtWindowContentsClipInfo::setStartDrawCallback(ContentsThumbStartDrawCallback callback) {
	m_StartDrawCallback = callback;
}

ContentsThumbStartDrawCallback CtWindowContentsClipInfo::getStartDrawCallback() {
	return m_StartDrawCallback;
}

void CtWindowContentsClipInfo::setSyncSelectCallback(ContentsThumbSyncSelectCallback callback) {
	m_SyncSelectCallback = callback;
}

ContentsThumbSyncSelectCallback CtWindowContentsClipInfo::getSyncSelectCallback() {
	return m_SyncSelectCallback;
}

void CtWindowContentsClipInfo::setSelectIndexCallback(ContentsThumbSelectIndexCallback callback)
{
	m_SelectIndexCallback = callback;
}

ContentsThumbSelectIndexCallback CtWindowContentsClipInfo::getSelectIndexCallback()
{
	return m_SelectIndexCallback;
}

