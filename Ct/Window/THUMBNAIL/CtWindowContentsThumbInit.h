#ifndef __CtWindowContentsThumbInit_H__
#define __CtWindowContentsThumbInit_H__

#include "CtWindowContentsThumbCommon.h"
#include "CtWindowContentsThumb.h"

class CtWindowContentsThumbInit : public CtWindowContentsThumb {
public:
	CtWindowContentsThumbInit(const CtWindowID WindowID);
	CtWindowContentsThumbInit(CtWindowContentsThumbInit& contents);
	~CtWindowContentsThumbInit();

	//���N���b�v��
	void setClipCount(int count);
	int getClipCount();

	//�����\������N���b�v�̃C���f�b�N�X
	void setCurrentIndex(unsigned long index);
	unsigned long getCurrentIndex();

	//ClipInfo�̓ǂݍ��ݗv���p�̃R�[���o�b�N
	void setFuncRequestClipInfo(ContentsThumbReqClipInfoCallback callback);
	ContentsThumbReqClipInfoCallback getFuncRequestClipInfo();						

	//�T���l�C���摜�ǂݍ��ݗp�̃R�[���o�b�N
	void setFuncRequestPicture(ContentsThumbStartDrawCallback callback);				
	ContentsThumbStartDrawCallback getFuncRequestPicture();							

	//�N���b�v���̓����p�̃R�[���o�b�N
	void setFuncSelectClip(ContentsThumbSyncSelectCallback callback);			
	ContentsThumbSyncSelectCallback getFuncSelectClip();						

	//�I�𒆃N���b�v�̒ʒm�p�̃R�[���o�b�N
	void setFuncSetFocus(ContentsThumbSelectIndexCallback callback);
	ContentsThumbSelectIndexCallback getFuncSetFocus();

	void setFuncNotifyDrawStart(ContentsThumbDrawStartCallback callback);

	ContentsThumbDrawStartCallback getFuncNotifyDrawStart();

	void setFuncNotifyDrawEnd(ContentsThumbDrawEndCallback callback);

	ContentsThumbDrawEndCallback getFuncNotifyDrawEnd();

	// �݊��p
	void setReqClipInfoCallback(ContentsThumbReqClipInfoCallback callback);
	void setStartDrawCallback(ContentsThumbStartDrawCallback callback);				
	void setSyncSelectCallback(ContentsThumbSyncSelectCallback callback);			
	void setSelectIndexCallback(ContentsThumbSelectIndexCallback callback);
	void setThumbDrawStartCallback(ContentsThumbDrawStartCallback callback);
	void setThumbDrawEndCallback(ContentsThumbDrawEndCallback callback);
	
private:
	int m_ClipCount;				//�N���b�v�̐�
	unsigned long m_CurrentIndex;	//�����\������N���b�v�ԍ�

	ContentsThumbReqClipInfoCallback	m_RequestClipInfo;		//�N���b�v���v��
	ContentsThumbStartDrawCallback		m_RequestPicture;		//�T���l�C���摜�v��
	ContentsThumbSyncSelectCallback		m_SelectClip;			//�N���b�v�I����ʒm
	ContentsThumbSelectIndexCallback	m_SetFocus;				//�t�H�[�J�X���Ă���N���b�v��ʒm
	ContentsThumbDrawStartCallback		m_NotifyDrawStart;		//�T���l�C���`��J�n�ʒm�p
	ContentsThumbDrawEndCallback		m_NotifyDrawEnd;		//�T���l�C���`��I���ʒm�p

};

#endif
