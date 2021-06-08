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
	/* �L���b�V���Ǘ����֘A */
	enum CacheType {
		Type_None,
		Type_PathFont,	// Font��VGPath
		Type_PathSVG,	// SVG��VGPath
		Type_Image,		// �����`���Drawable�p
		Type_Drawable,	// Thumbnail�p(�]���d�l�̌݊��p)
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
	
	// �]���d�l�݊��p
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
		
		CacheType 		Type;		// �f�[�^���
		CacheKey 		Key;		// �L���b�V���L�[
		void*			pCache;		// �L���b�V��(vgPath or DRAWABLE_ID)
		CtList::list<CtDrawInfo*>	Refer;		// �Q��Widget��	
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

	unsigned long m_CrcTable[256]; /* CRC �l�v�Z�p�e�[�u�� */
	const int m_CrcTableNum;
	
};

#endif	/* _CtDrawCache_H_ */
