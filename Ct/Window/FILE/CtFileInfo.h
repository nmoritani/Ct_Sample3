#ifndef __CtFileInfo_H__
#define __CtFileInfo_H__

#include "CtWindowContents.h"

class CtFileInfo : public CtObject {
public :

	static const unsigned long FileNameSize = 8;

    typedef struct FileDate {
        bool ValidFlag;
        unsigned short Year;
		unsigned char Month;
		unsigned char Day;    
    } FileDate;

    typedef struct FileTime {
        bool ValidFlag;
		unsigned char Hour;
		unsigned char Min;
		unsigned char Sec;    
    } FileTime;
	
	typedef struct FileInfo {
		char FileName[FileNameSize];
		FileDate Date;
        FileTime Time;
	} FileInfo;

	CtFileInfo();
	CtFileInfo(CtFileInfo& obj);
	virtual ~CtFileInfo();
	
	FileInfo getFileInfo();
	void setFileInfo(FileInfo& info);

private :
	FileInfo m_FileInfo;
	
};

#endif
