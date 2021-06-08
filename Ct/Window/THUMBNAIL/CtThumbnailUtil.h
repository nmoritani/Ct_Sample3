/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbnailUtil
*/


#ifndef __CtThumbnailUtil_H__
#define __CtThumbnailUtil_H__

class CtThumbnailUtil {
public:

	//インデックス値(0始まり)をクリップ番号(1始まり)に変換
	static unsigned long IndexToClipNo(int index) {
		return index + 1;
	}
	//クリップ番号(1始まり)をインデックス値(0始まり)に変換
	static int ClipNoToIndex(unsigned long clipNo) {
		return (0 < clipNo) ? (clipNo - 1) : 0;
	}

	//サムネイル画像用のドロアブルIDの取得
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
