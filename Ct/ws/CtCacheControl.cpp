/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtCacheControl
 */
#include "CtCacheControl.h"
#include "CtDebugPrint.h"
#include "CtTimer.h"
#include "CtEventHandler.h"

const unsigned long CtCacheControl::m_AgingCycle = 1000;	/* タイマー周期。とりま 1 秒 */
CtCacheControl::CacheInfo CtCacheControl::m_CacheInfo;
CtCacheControl::CacheInfo CtCacheControl::m_CacheInfoDrawable;

CtCacheControl* CtCacheControl::m_This(NULL);

CtCacheControl::CtCacheControl() :
	m_Font(m_CacheInfo),
	m_SVG(m_CacheInfo),		/* 情報は FONT と共通管理 */
	m_Drawable(m_CacheInfoDrawable),
	m_CyclicCounter(0),
	m_IsAgingEnable(false)
{
	setClassType(CtClassType_CacheControl);

	/* タイマーイベントを受けるためのオブザーバー登録 */
	CtTimer::getInstance()->startCyclic(CT_CACHE_CTRL_TIMER_ID, m_AgingCycle, this);
	startAging();
}

CtCacheControl::~CtCacheControl()
{
	/* 周期処理止める */
	stopAging();

	/* 生成したキャッシュを消す */
	m_Font.destroy();
	m_SVG.destroy();
	m_Drawable.destroy();
	CtTimer::getInstance()->stopCyclic(CT_CACHE_CTRL_TIMER_ID, this);
	m_This = NULL;
}

CtCacheControl* CtCacheControl::getInstance()
{
	if (!m_This) {
		m_This = new CtCacheControl();
	}
	return m_This;
}

/* キャッシュ取得 (Font キャッシュ) */
GDI_CACHE_FONT* CtCacheControl::getCache(GDI_FONT_STYLE *style, unsigned short *str)
{
	return m_Font.getAddr(style, str);
}

/* キャッシュ取得 (SVG キャッシュ) */
GDI_CACHE_SVG* CtCacheControl::getCache(GDI_IMAGE_ID imageId)
{
	return m_SVG.getAddr(imageId);
}

/* Drawable 用キャッシュを取得 */
GDI_DRAWABLE_ID CtCacheControl::getCache(unsigned long userId)
{
	/* 情報があるかだけ参照する。ない場合は NULL を返して先方に作成してもらう */
	CacheId id = static_cast<CacheId>(userId);
	return reinterpret_cast<GDI_DRAWABLE_ID>(m_Drawable.getAddr(id));
}

/* Drawable 用キャッシュを設定 */
void CtCacheControl::setCache(unsigned long userId, GDI_DRAWABLE_ID drawableId)
{
	m_Drawable.setAddr(userId, drawableId);
}

/* Font キャッシュの全クリア */
void CtCacheControl::destroyFontCache()
{
	stopAging();				/* 周期処理を止める */
	m_Font.destroy();
	startAging();
}

/* SVG キャッシュの全クリア */
void CtCacheControl::destroySVGCache()
{
	stopAging();				/* 周期処理を止める */
	m_SVG.destroy();
	startAging();
}

/* Drawable キャッシュの全クリア */
void CtCacheControl::destroyDrawableCache()
{
	stopAging();				/* 周期処理を止める */
	m_Drawable.destroy();
	startAging();
}

/* Drawable キャッシュの指定クリア */
void CtCacheControl::destroyDrawableCache(unsigned long userId)
{
	stopAging();				/* 周期処理を止める */
	m_Drawable.destroy(userId);
	startAging();
}

/* Drawable キャッシュの自動クリア (一番古いものを消す) */
void CtCacheControl::destroyDrawableCacheAuto()
{
	stopAging();				/* 周期処理を止める */
	m_Drawable.destroyOld();
	startAging();
}

bool CtCacheControl::handleTimerEvent(const CtEventTimer& Timer) {
	if (m_IsAgingEnable) {
		m_CyclicCounter += Timer.getCycTim(); /* タイマー周期分だけカウンタを進める */
		if (m_CyclicCounter >= m_AgingCycle) { /* 周期になったら実行 */
											   /* キャッシュ管理情報の更新を行う */
			m_CacheInfo.aging();
			m_CacheInfoDrawable.aging();
			m_CyclicCounter -= m_AgingCycle;
		}
	}
	return false;
};

/* --- キャッシュ情報管理クラス ------------------------------------ */
const CtCacheControl::CacheData CtCacheControl::CacheInfo::m_InitData = {NONE, 0, NULL, false, 0};
CtCacheControl::CacheInfo::CacheInfo() :
	m_Num(0),
	m_NumMax(sizeof m_Info / sizeof m_Info[0])
{
	/* このクラスは static 領域に配置される想定なので、 m_Info[] は特に初期化しない */
}

/* キャッシュデータ取得 */
CtCacheControl::CacheData* CtCacheControl::CacheInfo::get(CacheType type, CacheId id)
{
	CacheData* data = search(type, id);
	if (data != NULL) {
		data->m_IsRefer = true; /* 取得したので参照あり */
	}
	return data;
}

/* キャッシュデータ登録 */
bool CtCacheControl::CacheInfo::set(CacheType type, CacheId id, void* addr)
{
	if (addr == NULL) {
		return false;
	}

	void* releaseAddr = NULL;
	CacheData* blankData = searchEmpty();
	if (blankData == NULL) {	/* 管理情報が満杯 */
		CtDebugPrint(CtDbg, "Cache info full! Type=%d, ID=%d, CacheNum=%d\n", type, id, m_Num);
		return false;
	}
	blankData->mp_Addr = addr;
	blankData->m_Type = type;
	blankData->m_Id = id;
	blankData->m_Frequently = 0;  /* 最低値に戻す */
	blankData->m_IsRefer = true;  /* 設定されたので参照あり */
	m_Num++;

	return true;
}

/* キャッシュデータ検索 */
CtCacheControl::CacheData* CtCacheControl::CacheInfo::search(CacheType type, CacheId id)
{
	CacheData* data = NULL;
	for (unsigned int ii = 0; ii < m_NumMax; ii++) {
		if ((m_Info[ii].m_Type == type) && (m_Info[ii].m_Id == id)) {
			data = &m_Info[ii];
			break;
		}
	}
	return data;
}

/* キャッシュデータ検索 ※途中から再開機能付き */
CtCacheControl::CacheData* CtCacheControl::CacheInfo::search(unsigned int& progress, CacheType type)
{
	CacheData* data = NULL;
	for (; progress < m_NumMax; progress++) {
		if (m_Info[progress].m_Type == type) {
			data = &m_Info[progress];
			break;
		}
	}
	return data;
}

/* キャッシュデータ取得 (空き) */
CtCacheControl::CacheData* CtCacheControl::CacheInfo::searchEmpty()
{
	if (m_Num >= m_NumMax) {   /* 登録数 MAX ならいちいち検索しない */
		CtDebugPrint(CtDbg, "CacheInfo num=%d, not have empty info.\n", m_Num);
		return NULL;
	}

	unsigned int progress = 0;
	return search(progress, NONE);
}

/* (エージングアルゴリズムで算出された) 一番古いキャッシュを解放 */
bool CtCacheControl::CacheInfo::clearOld(CacheData& clearData)
{
	CacheData base = m_InitData; /* 最低値を求めるための比較用初期値 */
	base.m_Frequently = 0xFFFF;	 /* 初期値なので MAX にする */
	CacheData *minimum = &base;
	for (unsigned int ii = 0; ii < m_NumMax; ii++) {
		if (m_Info[ii].m_Type == NONE) continue; /* 未登録データは飛ばす */
		if (m_Info[ii].m_IsRefer == true) continue; /* 参照 (or 作成) 直後のデータは使用前なので飛ばす */
		//m_Frequentlyの値は、最近の参照に対応した値は大きく、
		//過去に遡るほど値が小さくなるので、minimum->m_Frequentlyより小さい値を探す
		if (minimum->m_Frequently > m_Info[ii].m_Frequently) {
			minimum = &m_Info[ii];
			if (minimum->m_Frequently == 0) { /* 0 (最低値) が出たら以降は比較の必要なし */
				break;
			}
		}
	}
	if (minimum == &base) {		/* データがないなど、最低値が見付からなかった */
		return false;
	}
	clearData = *minimum;		/* 消すデータのコピー (戻り値) */
	clear(*minimum);
	return true;
}

/* キャッシュデータの削除 */
void CtCacheControl::CacheInfo::clear(CacheData& data)
{
	if (data.m_Type == NONE) { /* 無いものは消せません */
		return;
	}

	if (m_Num == 0) {
		CtDebugPrint(CtDbg, "set CacheInfo and clear CacheInfo don't match!!\n");
	} else {
		m_Num--;
	}
	data = m_InitData;
}

/* エージング (ページ置換アルゴリズム) の参照重み付け */
void CtCacheControl::CacheInfo::aging()
{
	/**
	 * エージング・アルゴリズムは NFU アルゴリズムを改良したもので、単純にキャッシュの参照回数だけでなく
	 * そのキャッシュが最近参照されたかどうかも含めて残すデータの重み付けをする。
	 * 【重み付け方法】
	 * キャッシュの参照カウンタを右シフトしてからカウントアップする。
	 * 例えば、あるキャッシュについて周期チェック 6 回分の参照ビットが 1 → 0 → 0 → 1 → 1 → 0 の変化だった場合、
	 * 参照カウンタは 10000000 → 01000000 → 00100000 → 10010000 → 11001000 → 01100100 のように変化するので
	 * 最近の参照に対応した値は大きく、過去に遡るほど値が小さくなる。
	 * ※つまり、参照ビットの履歴を新しいものから MSB → LSB の順で保持していることになる
	 */
	for (unsigned int ii = 0; ii < m_NumMax; ii++) {
		CacheData& data = m_Info[ii];
		if (data.m_Type != NONE) { /* キャッシュありだけチェックする */
			data.m_Frequently >>= 1;
			if (data.m_IsRefer) {
				data.m_IsRefer = false;
				data.m_Frequently |= 0x8000; /* MSB に 1 を立てる */
			}
		}
	}
}

/* --- キャッシュ情報とデータの管理クラス (親) -------------------- */
/* キャッシュ情報の取得 */
void* CtCacheControl::Cache::getAddr(CacheId id)
{
	CacheData* data = m_Info.get(m_Type, id);
	if (data == NULL) {
		return NULL;
	}
	return data->mp_Addr;
}

/* キャッシュ情報を設定 */
bool CtCacheControl::Cache::setAddr(CacheData& clearData, CacheId id, void* addr)
{
	bool isClear = false;
	bool isSet = m_Info.set(m_Type, id, addr);
	if (isSet == false) {		/* 情報が満杯 */
		/* 古いキャッシュを捨てて管理情報の空きを確保 */
		isClear = m_Info.clearOld(clearData);
		if (isClear) {
			m_Info.set(m_Type, id, addr);
		}
	}
	return isClear;
}

/* --- キャッシュ情報とデータの管理クラス (FONT) ------------------ */
CtCacheControl::CacheFont::CacheFont(CacheInfo& resouce) :
	Cache(FONT, resouce),
	m_CrcTableNum(sizeof m_CrcTable / sizeof m_CrcTable[0])
{
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

/* Font 用 GDI キャッシュデータの生成 */
void* CtCacheControl::CacheFont::create(GDI_FONT_STYLE *style, unsigned short *str)
{
	GDI_CACHE_FONT* cacheAddr = GDI_CreateCacheFont(style, str);
	return cacheAddr;
}

/* Font 用 GDI キャッシュデータの解放 */
void CtCacheControl::CacheFont::release(void *addr)
{
	GDI_ERRCODE err = GDI_DeleteCache(static_cast<GDI_CACHE_BASE*>(addr));
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_DeleteCache(%08x)=%08x\n", addr, err);
	}
}

/* Font 用キャッシュを取得 */
GDI_CACHE_FONT* CtCacheControl::CacheFont::getAddr(GDI_FONT_STYLE *style, unsigned short *str)
{
	CacheId id = createCacheId(style, str); /* データから CRC を計算して固有 ID として使う */
	void* cacheAddr = Cache::getAddr(id);
	CacheData clearData;

	if (cacheAddr == NULL) {	/* キャッシュなしの場合は作成 */
		while (GDI_checkRemainMpl(80) == TRUE) {
			bool isClear = m_Info.clearOld(clearData);
			if (isClear == false) {
				break;
			}
			release(clearData.mp_Addr);
		}
		
		cacheAddr = create(style, str);
		if (cacheAddr != NULL) {
			bool isClear;
			isClear = setAddr(clearData, id, cacheAddr);
			if (isClear == true) { /* set する際にキャッシュ情報の削除が発生 */
				release(clearData.mp_Addr);
			}
		}

		if (cacheAddr == NULL) {	/* キャッシュ生成失敗 */
			CtDebugPrint(CtDbg, "Cache creation failed. Type=%d, ID=%d\n", m_Type, id);
		}
	}
	return static_cast<GDI_CACHE_FONT*>(cacheAddr);
}

/* Font 用キャッシュの全解放  */
void CtCacheControl::CacheFont::destroy()
{
	unsigned int progress = 0;
	CacheData* data;
	while (data = m_Info.search(progress, m_Type)) {
		release(data->mp_Addr);
		m_Info.clear(*data);
		progress++;				/* 次のデータから検索 */
	}
}

/* フォントデータのバイナリから CRC を計算 */
CtCacheControl::CacheId CtCacheControl::CacheFont::createCacheId(const GDI_FONT_STYLE *style, const unsigned short *str)
{
	static const unsigned short dummyStr[] = {'N', 'o', ' ', 'S', 't', 'r', 'i', 'n', 'g', '\0'};

	if (str == NULL) {
		str = dummyStr;
	}

	int length = get_ushort_string_length(str);

	CacheId crc = 0;
	crc = calcCrc(crc, (unsigned char*)style, sizeof *style);
	crc = calcCrc(crc, (unsigned char*)str, length * (sizeof *str));
	return crc;
}

/* バイナリデータの CRC を計算する */
CtCacheControl::CacheId CtCacheControl::CacheFont::calcCrc(CacheId base, const unsigned char* binary, unsigned int binarySize)
{
	if (binary == NULL) {
		CtDebugPrint(CtDbg, "data nothing!!\n");
		return 0;
	}

	CacheId crc = base;
	for (unsigned int ii = 0; ii < binarySize; ii++) {
		crc = m_CrcTable[(crc ^ binary[ii]) % m_CrcTableNum] ^ (crc >> 8);
	}
	return crc ^ ~0L;
}

/* --- キャッシュ情報とデータの管理クラス (SVG) ---------------- */
/* SVG 用 GDI キャッシュデータの生成 */
void* CtCacheControl::CacheSVG::create(GDI_IMAGE_ID imageId)
{
	GDI_IMAGE_SVG* svg = GDI_GetImageSVG(imageId);
	GDI_CACHE_SVG* cacheAddr = GDI_CreateCacheSVG(svg);
	return cacheAddr;
}

/* SVG 用 GDI キャッシュデータの解放 */
void CtCacheControl::CacheSVG::release(void* addr)
{
	GDI_ERRCODE err = GDI_DeleteCache(static_cast<GDI_CACHE_BASE*>(addr));
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_DeleteCache(%08x)=%08x\n", addr, err);
	}
}

/* SVG 用キャッシュを取得  */
GDI_CACHE_SVG* CtCacheControl::CacheSVG::getAddr(GDI_IMAGE_ID imageId)
{
	CacheId id = static_cast<CacheId>(imageId);
	void* cacheAddr = Cache::getAddr(id);
	CacheData clearData;

	if (cacheAddr == NULL) {	/* キャッシュなしの場合は作成 */
		while (GDI_checkRemainMpl(80) == TRUE) {
			bool isClear = m_Info.clearOld(clearData);
			if (isClear == false) {
				break;
			}
			release(clearData.mp_Addr);
		}
		
		cacheAddr = create(imageId);
		if (cacheAddr != NULL) {
			bool isClear = setAddr(clearData, id, cacheAddr);
			if (isClear == true) { /* set する際にキャッシュ情報の削除が発生 */
				release(clearData.mp_Addr);
			}
		}

		if (cacheAddr == NULL) {	/* キャッシュ生成失敗 */
			CtDebugPrint(CtDbg, "Cache creation failed. Type=%d, ID=%d\n", m_Type, imageId);
		}
	}
	return static_cast<GDI_CACHE_SVG*>(cacheAddr);
}

/* SVG 用キャッシュの全解放  */
void CtCacheControl::CacheSVG::destroy()
{
	unsigned int progress = 0;
	CacheData* data;
	while (data = m_Info.search(progress, m_Type)) {
		release(data->mp_Addr);
		m_Info.clear(*data);
		progress++;				/* 次のデータから検索 */
	}
}

/* --- キャッシュ情報とデータの管理クラス (DRAWABLE) -------------- */
/* Drawable 用キャッシュデータ設定 */
void CtCacheControl::CacheDrawable::setAddr(unsigned long userId, GDI_DRAWABLE_ID drawableId)
{
	/* データは先方が作ってくれるので、こちらは情報を登録するだけ */
	CacheData clearData;
	bool isClear = Cache::setAddr(clearData, static_cast<CacheId>(userId), reinterpret_cast<void*>(drawableId));
	if (isClear == true) {
		release(clearData.mp_Addr);
	}
}

/* Drawable 用 GDI キャッシュデータの解放 */
void CtCacheControl::CacheDrawable::release(void* addr)
{
	GDI_ERRCODE err = GDI_DeleteDrawable(reinterpret_cast<GDI_HANDLER>(addr));
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_DeleteDrawable(%08x)=%08x\n", addr, err);
	}
}

/* Drawable 用キャッシュの全解放 */
void CtCacheControl::CacheDrawable::destroy()
{
	unsigned int progress = 0;
	CacheData* data;
	while (data = m_Info.search(progress, m_Type)) {
		release(data->mp_Addr);
		m_Info.clear(*data);
		progress++;				/* 次のデータから検索 */
	}
}

/* Drawable 用指定キャッシュの解放 */
void CtCacheControl::CacheDrawable::destroy(unsigned long userId)
{
	CacheData* data = m_Info.get(m_Type, static_cast<CacheId>(userId));
	if (data != NULL) {
		release(data->mp_Addr);
		m_Info.clear(*data);
	}
}

/* Drawable 用自動キャッシュ解放 */
void CtCacheControl::CacheDrawable::destroyOld()
{
	CacheData clearData;
	bool isClear = m_Info.clearOld(clearData);
	if (isClear) {
		release(clearData.mp_Addr);
	}
}
