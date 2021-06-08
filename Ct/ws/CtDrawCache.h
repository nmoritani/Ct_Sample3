/**
 *  Element:			CtDrawCache
 */
#ifndef _CtDrawCache_H_
#define _CtDrawCache_H_

#include "CtDrawInfo.h"
#include "CtDraw.h"

class CtDrawCache : public CtObject
{
public:
	/* キャッシュ管理情報関連 */
	enum CacheType {
		Type_None,
		Type_PathFont,	// FontのVGPath
		Type_PathSVG,	// SVGのVGPath
		Type_Image,		// 高速描画のDrawable用
		Type_Drawable,	// Thumbnail用(従来仕様の互換用)
		Type_Max
	};
	
	static CtDrawCache* getInstance();

	GDI_CACHE_FONT* referCache(CtString& DrawInfo);
	GDI_CACHE_SVG* referCache(CtSVG& DrawInfo);
	GDI_DRAWABLE_ID referCache(CtDrawInfo& DrawInfo, unsigned long DrawKey);
	bool setCache(CtDrawInfo& DrawInfo, unsigned long DrawKey, GDI_DRAWABLE_ID cache);
	
	bool unreferCache(CtString& DrawInfo);
	bool unreferCache(CtSVG& DrawInfo);
	bool unreferCache(CtDrawInfo& DrawInfo);

	bool deleteAll(CtDrawCache::CacheType Type);
	
	// 従来仕様互換用
	bool deleteCache(unsigned long key);
	bool setCache(unsigned long key, GDI_DRAWABLE_ID id);
	GDI_DRAWABLE_ID getCache(unsigned long key);
	
	int cacheSize(CacheType Type);
	bool printAll(CacheType Type);

protected:
	virtual ~CtDrawCache();

private:
	static const int 		DataMax = 1024;
	typedef unsigned long CacheKey;
	
	struct CacheData {
		CacheData*		Prev;
		CacheData*		Next;
		
		CacheType 		Type;		// データ種類
		CacheKey 		Key;		// キャッシュキー
		void*			pCache;		// キャッシュ(vgPath or DRAWABLE_ID)
		CtList::list<CtDrawInfo*>	Refer;		// 参照Widget数	
	};
	
	CtDrawCache();
	
	CacheData* searchCache(CacheType Type, CacheKey Key);
	CacheData* searchCache(CacheType Type, void* pCache);
	CacheData* putCache(CacheType Type, CacheKey Key, void* pCache);
	bool removeCache(CacheType Type, CacheKey Key);
	bool removeCache(CacheType Type, void* pCache);

	CtDrawCache::CacheKey createCacheKey(const GDI_FONT_STYLE *style, const unsigned short *str);
	CtDrawCache::CacheKey calcCrc(CacheKey base, const unsigned char* binary, unsigned int size);

	bool put(CacheType Type, CacheData* pData);
	bool remove(CacheType Type, CacheData* pData);
	CacheData* get(CacheType Type);

	static CtDrawCache*		m_pInstance;
	static CacheData*		m_Head[Type_Max];
	static CacheData		m_Data[DataMax];

	unsigned long m_CrcTable[256]; /* CRC 値計算用テーブル */
	const int m_CrcTableNum;
	
};

#endif	/* _CtDrawCache_H_ */
