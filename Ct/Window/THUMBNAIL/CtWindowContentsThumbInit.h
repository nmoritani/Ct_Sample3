#ifndef __CtWindowContentsThumbInit_H__
#define __CtWindowContentsThumbInit_H__

#include "CtWindowContentsThumbCommon.h"
#include "CtWindowContentsThumb.h"

class CtWindowContentsThumbInit : public CtWindowContentsThumb {
public:
	CtWindowContentsThumbInit(const CtWindowID WindowID);
	CtWindowContentsThumbInit(CtWindowContentsThumbInit& contents);
	~CtWindowContentsThumbInit();

	//総クリップ数
	void setClipCount(int count);
	int getClipCount();

	//初期表示するクリップのインデックス
	void setCurrentIndex(unsigned long index);
	unsigned long getCurrentIndex();

	//ClipInfoの読み込み要求用のコールバック
	void setFuncRequestClipInfo(ContentsThumbReqClipInfoCallback callback);
	ContentsThumbReqClipInfoCallback getFuncRequestClipInfo();						

	//サムネイル画像読み込み用のコールバック
	void setFuncRequestPicture(ContentsThumbStartDrawCallback callback);				
	ContentsThumbStartDrawCallback getFuncRequestPicture();							

	//クリップ情報の同期用のコールバック
	void setFuncSelectClip(ContentsThumbSyncSelectCallback callback);			
	ContentsThumbSyncSelectCallback getFuncSelectClip();						

	//選択中クリップの通知用のコールバック
	void setFuncSetFocus(ContentsThumbSelectIndexCallback callback);
	ContentsThumbSelectIndexCallback getFuncSetFocus();

	void setFuncNotifyDrawStart(ContentsThumbDrawStartCallback callback);

	ContentsThumbDrawStartCallback getFuncNotifyDrawStart();

	void setFuncNotifyDrawEnd(ContentsThumbDrawEndCallback callback);

	ContentsThumbDrawEndCallback getFuncNotifyDrawEnd();

	// 互換用
	void setReqClipInfoCallback(ContentsThumbReqClipInfoCallback callback);
	void setStartDrawCallback(ContentsThumbStartDrawCallback callback);				
	void setSyncSelectCallback(ContentsThumbSyncSelectCallback callback);			
	void setSelectIndexCallback(ContentsThumbSelectIndexCallback callback);
	void setThumbDrawStartCallback(ContentsThumbDrawStartCallback callback);
	void setThumbDrawEndCallback(ContentsThumbDrawEndCallback callback);
	
private:
	int m_ClipCount;				//クリップの数
	unsigned long m_CurrentIndex;	//初期表示するクリップ番号

	ContentsThumbReqClipInfoCallback	m_RequestClipInfo;		//クリップ情報要求
	ContentsThumbStartDrawCallback		m_RequestPicture;		//サムネイル画像要求
	ContentsThumbSyncSelectCallback		m_SelectClip;			//クリップ選択を通知
	ContentsThumbSelectIndexCallback	m_SetFocus;				//フォーカスしているクリップを通知
	ContentsThumbDrawStartCallback		m_NotifyDrawStart;		//サムネイル描画開始通知用
	ContentsThumbDrawEndCallback		m_NotifyDrawEnd;		//サムネイル描画終了通知用

};

#endif
