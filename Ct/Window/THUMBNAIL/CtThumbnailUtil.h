/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbnailUtil
*/


#ifndef __CtThumbnailUtil_H__
#define __CtThumbnailUtil_H__

class CtThumbnailUtil {
public:

	//�C���f�b�N�X�l(0�n�܂�)���N���b�v�ԍ�(1�n�܂�)�ɕϊ�
	static unsigned long IndexToClipNo(int index) {
		return index + 1;
	}
	//�N���b�v�ԍ�(1�n�܂�)���C���f�b�N�X�l(0�n�܂�)�ɕϊ�
	static int ClipNoToIndex(unsigned long clipNo) {
		return (0 < clipNo) ? (clipNo - 1) : 0;
	}

	//�T���l�C���摜�p�̃h���A�u��ID�̎擾
	static unsigned long GetThumbnailDrawableID(int index)
	{
		static const int WidgetTHUMB_OFFSET = 1000;
		unsigned long ThumBaseID = 0x100000 + WidgetTHUMB_OFFSET + 1;

		return index + ThumBaseID;
	}

private:
	CtThumbnailUtil() {};
	virtual ~CtThumbnailUtil() {};
};
	
#endif
