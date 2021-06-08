#ifndef __CtWindowContentsThumbCommon_H__
#define __CtWindowContentsThumbCommon_H__

typedef enum ContentsThumbResultType {
	ContentsThumbResultType_OK,
	ContentsThumbResultType_NG,
	ContentsThumbResultType_BUSY,
} ContentsThumbResultType;

typedef struct ContentsThumbSize {
	long Width;
	long Height;
} ContentsThumbSize;

typedef struct ContentsThumbInfo {
	ContentsThumbResultType Result;
	unsigned long ClipNum;
	ContentsThumbSize Size;
	void* Yaddr;
	void* Caddr;
} ContentsThumbInfo;

typedef struct ContentsThumbSelectInfo {
	unsigned long ClipNum;
} ContentsThumbSelectInfo;

typedef struct ContentsThumbConfirmInfo {
	unsigned long ClipNum;
	bool bRet;
    unsigned long cnt;
} ContentsThumbConfirmInfo;

typedef void(*ContentsThumbReqClipInfoCallback) (int startIndex, int count);
typedef	void( *ContentsThumbStartDrawCallback )( ContentsThumbInfo );
typedef	bool( *ContentsThumbSyncSelectCallback )( ContentsThumbSelectInfo* );
typedef void(*ContentsThumbSelectIndexCallback)(int index);
typedef void(*ContentsThumbDrawStartCallback)(void);
typedef void(*ContentsThumbDrawEndCallback)(void);

#endif
