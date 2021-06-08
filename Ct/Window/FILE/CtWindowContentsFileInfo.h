#ifndef __CtWindowContentsFile_H__
#define __CtWindowContentsFile_H__

#include "CtWindowContents.h"
#include "CtFileInfo.h"
#include "CtVector.h"

class CtWindowContentsFileInfo : public CtWindowContents {
public :

    typedef enum ContentsFileType {
        ContentsFileType_SCENE,
        ContentsFileType_SETUP,
        ContentsFileType_None,   
    } ContentsFileType;

	typedef CtVector::Vector<CtFileInfo*> FileInfoList;
	typedef CtVector::Vector<CtFileInfo*>::iterator FileInfoListItr;
	
	CtWindowContentsFileInfo(const CtWindowID WindowID);
	CtWindowContentsFileInfo(CtWindowContentsFileInfo& contentsFile);
	virtual ~CtWindowContentsFileInfo();
	
	FileInfoList& getFileInfoList();

    void setFileInfoList(CtFileInfo* pCtFileInfo);

    void setContentsFileType( ContentsFileType type );
    ContentsFileType getContentsFileType();

    unsigned long getCurrentIndex();
	void setCurrentIndex(unsigned long Index);

private :
	void removeAllFileInfo();
	
	FileInfoList m_FileInfoList;

    ContentsFileType m_pContentsFileType;

    unsigned long m_Index;
	
};

#endif
