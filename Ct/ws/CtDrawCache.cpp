/**
 *  Element:			CtDrawCache
 */
#include "CtDrawCache.h"

CtDrawCache* CtDrawCache::m_pInstance = NULL;
CtDrawCache::CacheData*	CtDrawCache::m_Head[CtDrawCache::Type_Max];
CtDrawCache::CacheData	CtDrawCache::m_Data[CtDrawCache::DataMax];

CtDrawCache::CtDrawCache() :
	m_CrcTableNum(sizeof m_CrcTable / sizeof m_CrcTable[0])
{
	setClassType(CtClassType_CacheControl);

	for (int i = 0; i < DataMax; i++) {
		m_Data[i].Type = Type_None;
		m_Data[i].Key = 0;
		m_Data[i].pCache = NULL;

		m_Data[i].Prev = &m_Data[i-1];
		m_Data[i].Next = &m_Data[i+1];
	}

	m_Data[DataMax-1].Next = NULL;
	
	m_Head[Type_None]     = &m_Data[0];
	m_Head[Type_PathFont] = NULL;
	m_Head[Type_PathSVG]  = NULL;
	m_Head[Type_Image] = NULL;
		
	/* CRC の計算に使うテーブルを作成 */
	for (int ii = 0; ii < m_CrcTableNum; ii++) {
		unsigned long seed = ii;
		for (int jj = 0; jj < 8; jj++) {
			if (seed & 1) {
				seed = 0xedb88320L ^ (seed >> 1);
			} else {
				seed >>= 1;
			}
		}
		m_CrcTable[ii] = seed;
	}
}

CtDrawCache::~CtDrawCache()
{
}

CtDrawCache* CtDrawCache::getInstance()
{
	if (m_pInstance == NULL) {
		m_pInstance = new CtDrawCache();
	}
	return m_pInstance;
}


GDI_CACHE_FONT* CtDrawCache::referCache(CtString& DrawInfo)
{
	CacheKey Key = (CacheKey)DrawInfo.getPathKey();
	CacheData* pData = NULL;
	GDI_CACHE_FONT* pCache = NULL;

	if ((pData = searchCache(Type_PathFont, Key)) != NULL) {
		CtList::list<CtDrawInfo*>::iterator Itr = find(pData->Refer.begin(), pData->Refer.end(), &DrawInfo);
		if (Itr == pData->Refer.end()) {
			pData->Refer.push_back(&DrawInfo);
		}
		return (GDI_CACHE_FONT*)pData->pCache;
	}
	
	pCache = GDI_CreateCacheFont(&DrawInfo.m_String.font_style, DrawInfo.m_String.str);
	pData = putCache(Type_PathFont, Key, pCache);
	pData->Refer.push_back(&DrawInfo);

	return pCache;
}

GDI_CACHE_SVG* CtDrawCache::referCache(CtSVG& DrawInfo)
{
	CacheKey Key = (CacheKey)DrawInfo.getPathKey();
	CacheData* pData = NULL;
	GDI_CACHE_SVG* pCache = NULL;

	if ((pData = searchCache(Type_PathSVG, Key)) != NULL) {
		CtList::list<CtDrawInfo*>::iterator Itr = find(pData->Refer.begin(), pData->Refer.end(), &DrawInfo);
		if (Itr == pData->Refer.end()) {
			pData->Refer.push_back(&DrawInfo);
		}
		return (GDI_CACHE_SVG*)pData->pCache;
	}

	pCache = GDI_CreateCacheSVG(DrawInfo.getSVG());
	pData = putCache(Type_PathSVG, Key, pCache);
	pData->Refer.push_back(&DrawInfo);
	
	return pCache;
}

GDI_DRAWABLE_ID CtDrawCache::referCache(CtDrawInfo& DrawInfo, unsigned long DrawKey)
{
	CacheKey Key = (CacheKey)DrawKey;
	CacheData* pData = NULL;

	if ((pData = searchCache(Type_Image, Key)) != NULL) {
		CtList::list<CtDrawInfo*>::iterator Itr = find(pData->Refer.begin(), pData->Refer.end(), &DrawInfo);
		if (Itr == pData->Refer.end()) {
			pData->Refer.push_back(&DrawInfo);
		}
		return (GDI_DRAWABLE_ID)pData->pCache;
	}

	return GDI_INVALID_ID;
}

bool CtDrawCache::setCache(CtDrawInfo& DrawInfo, unsigned long DrawKey, GDI_DRAWABLE_ID id)
{
	CacheData* pData = NULL;
	GDI_DRAWABLE_ID pCache = id;

	pData = putCache(Type_Image, DrawKey, (void*)pCache);
	pData->Refer.push_back(&DrawInfo);
	return true;
}


bool CtDrawCache::unreferCache(CtString& DrawInfo)
{
	CacheData* pData = NULL;
	
	if ((pData = searchCache(Type_PathFont, DrawInfo.m_pCache)) != NULL) {
		CtList::list<CtDrawInfo*>::iterator Itr = find(pData->Refer.begin(), pData->Refer.end(), &DrawInfo);
		if (Itr != pData->Refer.end()) {
			pData->Refer.erase(Itr);

			if (pData->Refer.size() == 0) {
				GDI_DeleteCache((GDI_CACHE_BASE*)pData->pCache);
				remove(Type_PathFont, pData);
			}
			return true;
		}
	}
	return false;
}

bool CtDrawCache::unreferCache(CtSVG& DrawInfo)
{
	CacheData* pData = NULL;
	
	if ((pData = searchCache(Type_PathSVG, DrawInfo.m_pCache)) != NULL) {
		CtList::list<CtDrawInfo*>::iterator Itr = find(pData->Refer.begin(), pData->Refer.end(), &DrawInfo);
		if (Itr != pData->Refer.end()) {
			pData->Refer.erase(Itr);

			if (pData->Refer.size() == 0) {
				GDI_DeleteCache((GDI_CACHE_BASE*)pData->pCache);
				remove(Type_PathSVG, pData);
			}
			return true;
		}
	}
	return false;
}

bool CtDrawCache::unreferCache(CtDrawInfo& DrawInfo)
{
	CacheData* pData = NULL;
	
	if ((pData = searchCache(Type_Image, (void*)DrawInfo.m_DrawImage)) != NULL) {
		CtList::list<CtDrawInfo*>::iterator Itr = find(pData->Refer.begin(), pData->Refer.end(), &DrawInfo);
		if (Itr != pData->Refer.end()) {
			pData->Refer.erase(Itr);

			if (pData->Refer.size() == 0) {
				GDI_DeleteDrawable((GDI_DRAWABLE_ID)pData->pCache);
				remove(Type_Image, pData);
			}
			return true;
		}
	}
	return false;
}

bool CtDrawCache::deleteAll(CtDrawCache::CacheType Type)
{
	CacheData* pData = m_Head[Type];
	CtList::list<CtDrawInfo*>::iterator Itr;

	while(1) {
		if (pData == NULL)
			break;
		
		switch (Type) {
		case Type_PathFont:
		case Type_PathSVG:
			for (Itr = pData->Refer.begin(); Itr != pData->Refer.end(); ++Itr) {
				(*Itr)->lostCache();
				pData->Refer.erase(Itr);
			}
			GDI_DeleteCache((GDI_CACHE_BASE*)pData->pCache);
			break;
		case Type_Image:
		case Type_Drawable:
			for (Itr = pData->Refer.begin(); Itr != pData->Refer.end(); ++Itr) {
				(*Itr)->lostDrawImage();
				pData->Refer.erase(Itr);
			}
			GDI_DeleteDrawable((GDI_DRAWABLE_ID)pData->pCache);
			break;
		}
		remove(Type, pData);
		pData = m_Head[Type];
	}
		
	return true;
}


// 従来仕様互換用↓
bool CtDrawCache::deleteCache(unsigned long key)
{
	CacheData* pData = NULL;
	
	if ((pData = searchCache(Type_Drawable, key)) != NULL) {
		GDI_DeleteDrawable((GDI_DRAWABLE_ID)pData->pCache);
		remove(Type_Drawable, pData);
		return true;
	}
	return false;
}

bool CtDrawCache::setCache(unsigned long key, GDI_DRAWABLE_ID id)
{
	CacheData* pData = NULL;
	GDI_DRAWABLE_ID pCache = id;

	pData = putCache(Type_Drawable, key, (void*)id);
	return true;
}

GDI_DRAWABLE_ID CtDrawCache::getCache(unsigned long key)
{
	CacheData* pData = NULL;
	
	if ((pData = searchCache(Type_Drawable, key)) != NULL) {
		return (GDI_DRAWABLE_ID)pData->pCache;
	}
	return GDI_INVALID_ID;
}
// 従来仕様互換用↑

int CtDrawCache::cacheSize(CacheType Type)
{
	CacheData* pTmp = m_Head[Type];
	int size = 0;

	while(1) {
		if (pTmp == NULL)
			break;

		pTmp = pTmp->Next;
		size++;
	}
	return size;
}

bool CtDrawCache::printAll(CacheType Type)
{
	CacheData* pTmp = m_Head[Type];
	int size = 0;
	char tmp[128];

	return false;
	
	if (Type != Type_PathFont)
		return false;
	
	while(1) {
		if (pTmp == NULL)
			break;

		for (CtList::list<CtDrawInfo*>::iterator Itr = pTmp->Refer.begin();  Itr != pTmp->Refer.end(); ++Itr) {
			CtString *pString = (CtString*)(*Itr);
			convert_ushort_str_to_char_str(tmp, pString->m_String.str);
			CtDebugPrint(CtDbg, "    DrawInfo:%p, str[%s]=%08X ", pString, tmp, *tmp);
			unsigned short* p = pString->m_String.str;
			while (1) {
				CtDebugPrint(CtDbg, "%04x, ", *p);
				p++;
				if (*p == 0)
					break;
			}
			CtDebugPrint(CtDbg, "\n");
		}

		pTmp = pTmp->Next;
		size++;
	}
	return true;
}

CtDrawCache::CacheData* CtDrawCache::searchCache(CacheType Type, CacheKey Key)
{
	CacheData* pTmp = m_Head[Type];

	while(1) {
		if ((pTmp == NULL) || (pTmp->Key == Key))
			break;

		pTmp = pTmp->Next;
	}
	return pTmp;
}

CtDrawCache::CacheData* CtDrawCache::searchCache(CacheType Type, void* pCache)
{
	CacheData* pTmp = m_Head[Type];

	while(1) {
		if ((pTmp == NULL) || (pTmp->pCache == pCache))
			break;

		pTmp = pTmp->Next;
	}
	return pTmp;
}

CtDrawCache::CacheData* CtDrawCache::putCache(CacheType Type, CacheKey Key, void* pCache)
{
	CacheData* pTmp = get(Type_None);
	if (pTmp != NULL) {
		pTmp->Type = Type;
		pTmp->Key = Key;
		pTmp->pCache = pCache;
		put(Type, pTmp);
	}
	return pTmp;
}

bool CtDrawCache::removeCache(CacheType Type, CacheKey Key)
{
	CacheData* pTmp = searchCache(Type, Key);

	if (pTmp != NULL) {
		GDI_DeleteCache((GDI_CACHE_BASE*)pTmp->pCache);
		remove(Type, pTmp);
		return true;
	}
	return false;
}

bool CtDrawCache::removeCache(CacheType Type, void* pCache)
{
	CacheData* pTmp = searchCache(Type, pCache);

	if (pTmp != NULL) {
		GDI_DeleteCache((GDI_CACHE_BASE*)pTmp->pCache);
		remove(Type, pTmp);
		return true;
	}
	return false;
}

CtDrawCache::CacheData* CtDrawCache::get(CacheType Type)
{
	CtDrawCache::CacheData* pHead = m_Head[Type];

	if (pHead == NULL)
		return NULL;

	if (pHead->Next == NULL) {
		m_Head[Type] = NULL;
	} else {
		m_Head[Type] = pHead->Next;
		pHead->Next->Prev = NULL;
	}

	pHead->Next = NULL;
	pHead->Prev = NULL;

	return pHead;
}

bool CtDrawCache::put(CacheType Type, CacheData* pData)
{
	if ((Type >= Type_Max) || (pData == NULL))
		return false;
	
	CtDrawCache::CacheData* pHead = m_Head[Type];

	if (pHead == NULL) {
		m_Head[Type] = pData;
		pData->Next = NULL;
		pData->Prev = NULL;
	} else {
		m_Head[Type] = pData;
		pData->Next = pHead;
		pData->Prev = NULL;
		pHead->Prev = pData;
	}
	return true;
}

bool CtDrawCache::remove(CacheType Type, CacheData* pData)
{
	if ((Type >= Type_Max) || (pData == NULL))
		return false;

	if (pData->Next == NULL) {
		if (pData->Prev == NULL) {
			m_Head[Type] = NULL;
		} else {
			pData->Prev->Next = NULL;
		}
	} else {
		if (pData->Prev == NULL) {
			m_Head[Type] = pData->Next;
			pData->Next->Prev = NULL;
		} else {
			pData->Prev->Next = pData->Next;
			pData->Next->Prev = pData->Prev;
		}
	}
	pData->Type = Type_None;
	pData->pCache = NULL;
	pData->Key = 0;
	
	put(Type_None, pData);
	return true;
}

#if 0
CacheData* CtDrawCache::refer(CacheType Type, CacheKey Key)
{
	CacheData* pCache;
	
	for (pCache = m_Head[Type]; pCache->Next != NULL; pCache = pCache->Next) {
		if (pCache->Key == Key) {
			//			pCache->Refer++;
			return pCache;
		}
	}
	return NULL;
}

CacheData* CtDrawCache::refer(CacheType Type, void* pData)
{
	CacheData* pCache;
	
	for (pCache = m_Head[Type]; pCache->Next != NULL; pCache = pCache->Next) {
		if (pCache->pData == pData) {
			//			pCache->Refer++;
			return pCache;
		}
	}
	return NULL;
}

CacheData* CtDrawCache::unrefer(CacheType Type, CacheKey Key)
{
	CacheData* pCache;
	
	for (pCache = m_Head[Type]; pCache->Next != NULL; pCache = pCache->Next) {
		if (pCache->Key == Key) {
			//			if (pCache->Refer > 0)	pCache->Refer--;
			return pCache;
		}
	}
	return NULL;
}

CacheData* CtDrawCache::unrefer(CacheType Type, void* pData)
{
	CacheData* pCache;
	
	for (pCache = m_Head[Type]; pCache->Next != NULL; pCache = pCache->Next) {
		if (pCache->pData == pData) {
			//			if (pCache->Refer > 0)	pCache->Refer--;
			return pCache;
		}
	}
	return NULL;
}
#endif

/* フォントデータのバイナリから CRC を計算 */
CtDrawCache::CacheKey CtDrawCache::createCacheKey(const GDI_FONT_STYLE *style, const unsigned short *str)
{
	static const unsigned short dummyStr[] = {'N', 'o', ' ', 'S', 't', 'r', 'i', 'n', 'g', '\0'};

	if (str == NULL) {
		str = dummyStr;
	}

	int length = get_ushort_string_length(str);

	CacheKey crc = 0;
	crc = calcCrc(crc, (unsigned char*)style, sizeof *style);
	crc = calcCrc(crc, (unsigned char*)str, length * (sizeof *str));
	return crc;
}

/* バイナリデータの CRC を計算する */
CtDrawCache::CacheKey CtDrawCache::calcCrc(CacheKey base, const unsigned char* binary, unsigned int size)
{
	if (binary == NULL) {
		CtDebugPrint(CtDbg, "data nothing!!\n");
		return 0;
	}

	CacheKey crc = base;
	for (unsigned int ii = 0; ii < size; ii++) {
		crc = m_CrcTable[(crc ^ binary[ii]) % m_CrcTableNum] ^ (crc >> 8);
	}
	return crc ^ ~0L;
}

