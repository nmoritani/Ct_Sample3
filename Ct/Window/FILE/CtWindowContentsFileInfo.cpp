#include "CtWindowContentsFileInfo.h"


CtWindowContentsFileInfo::CtWindowContentsFileInfo(const CtWindowID WindowID) : CtWindowContents(WindowID), m_FileInfoList(0), m_Index(0)  {
	m_pContentsFileType = ContentsFileType_None;
}

CtWindowContentsFileInfo::CtWindowContentsFileInfo(CtWindowContentsFileInfo& contentsFile) : CtWindowContents(contentsFile.getType()) {
	
    m_pContentsFileType = contentsFile.getContentsFileType();
	m_Index = contentsFile.getCurrentIndex();
    FileInfoList& list = contentsFile.getFileInfoList();

	for (FileInfoListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
		CtFileInfo* CopyInfo = new CtFileInfo(*(*Itr));
		m_FileInfoList.push_back(CopyInfo);
	}
}

void CtWindowContentsFileInfo::setFileInfoList(CtFileInfo* pCtFileInfo){

    CtFileInfo* p1 = pCtFileInfo;
    int index = this->getCurrentIndex();
    int i = 0;
	if( p1 != NULL ){
	    for (; p1 != NULL; p1++,i++){	/* pgr0689 */
	        if (i > index){
	            break;
	        }else{
	            m_FileInfoList.push_back(p1);
	        }
	    }
	}
}
	
CtWindowContentsFileInfo::~CtWindowContentsFileInfo() {
	removeAllFileInfo();
}
	
CtWindowContentsFileInfo::FileInfoList& CtWindowContentsFileInfo::getFileInfoList() {
	return m_FileInfoList;
}

void CtWindowContentsFileInfo::removeAllFileInfo() {
	for (int i = 0; i< m_FileInfoList.size(); i++) {
		if (m_FileInfoList[i] != NULL) {
			delete m_FileInfoList[i];
		}
	}
}

void CtWindowContentsFileInfo::setContentsFileType( ContentsFileType type ) {
    m_pContentsFileType = type;
}

CtWindowContentsFileInfo::ContentsFileType CtWindowContentsFileInfo::getContentsFileType() {
    return m_pContentsFileType;
}

void CtWindowContentsFileInfo::setCurrentIndex(unsigned long Index) {
	m_Index = Index;
}

unsigned long CtWindowContentsFileInfo::getCurrentIndex() {
	return m_Index;
}
