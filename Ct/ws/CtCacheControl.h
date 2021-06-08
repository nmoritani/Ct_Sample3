/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtCacheControl
 */
#ifndef _CtCacheControl_H_
#define _CtCacheControl_H_

#include "CtDrawInfo.h"
#include "CtEvent.h"
#include "CtEventHandler.h"

const int CT_CACHE_CTRL_TIMER_ID = 0;

class CtCacheControl : public CtEventHandler
{
public:
	CtCacheControl();
	static CtCacheControl* getInstance();

	/* Font 用 */
	GDI_CACHE_FONT* getCache(GDI_FONT_STYLE *style, unsigned short *str); /* キャッシュ取得 */
	void destroyFontCache();	/* 全キャッシュ削除 */

	/* SVG 用 */
	GDI_CACHE_SVG* getCache(GDI_IMAGE_ID imageId); /* キャッシュ取得 */
	void destroySVGCache();	/* 全キャッシュ削除 */

	/* Drawable 用 */
	GDI_DRAWABLE_ID getCache(unsigned long id); /* キャッシュ取得 */
	void setCache(unsigned long userId, GDI_DRAWABLE_ID drawableId); /* キャッシュ情報登録 */
	void destroyDrawableCache(unsigned long userId); /* 指定情報のクリア */
	void destroyDrawableCacheAuto(); /* 自動クリア (一番古い情報を消す) */
	void destroyDrawableCache();	 /* 全キャッシュクリア */

public:
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
protected:
	virtual ~CtCacheControl();

private:
	static CtCacheControl* m_This;

private:
	/* キャッシュ管理情報関連 */
	enum CacheType {
		NONE,
		FONT,
		SVG,
		DRAWABLE
	};

	typedef unsigned long CacheId;
	struct CacheData {
		CacheType m_Type;			 /* データ種類 */
		CacheId m_Id;				 /* 管理ID */
		void* mp_Addr;				 /* キャッシュアドレス */
		bool m_IsRefer;				 /* 参照ビット */
		unsigned short m_Frequently; /* 使用頻度カウンタ */
	};

	/* キャッシュ管理情報クラス */
	class CacheInfo {	/* new する用途がないので CtObject は継承しない */
	private:
		CacheData m_Info[1024];	/* new とかめんどいので固定長にする */
		unsigned short m_Num;	/* 生成したキャッシュの数 */
		const unsigned short m_NumMax; /* データ数 */
		static const CacheData m_InitData; /* 初期化用 */
	public:
		CacheInfo();
		CacheData* get(CacheType type, CacheId id);
		bool set(CacheType type, CacheId id, void* addr);
		CacheData* search(CacheType type, CacheId id);
		CacheData* search(unsigned int& progress, CacheType type);
		CacheData* searchEmpty();
		bool clearOld(CacheData& clearData);
		void clear(CacheData& data);
		void aging();			/* ページ置換アルゴリズム実施 */
	};

	/* キャッシュ管理情報: リソース毎に参照領域が異なる */
	static CacheInfo m_CacheInfo;
	static CacheInfo m_CacheInfoDrawable;

	/* キャッシュ情報とデータの管理クラス (リソース毎に作成) */
	class Cache {	/* new する用途がないので CtObject は継承しない */
	protected:
		CacheType m_Type;
		CacheInfo& m_Info;
	public:
		Cache(CacheType type, CacheInfo& resouce) : m_Type(type), m_Info(resouce){}
		virtual ~Cache(){};
		virtual void* getAddr(CacheId id);
		virtual bool setAddr(CacheData& clearData, CacheId id, void* addr);
	};
	class CacheFont : public Cache {
	private:
		unsigned long m_CrcTable[256]; /* CRC 値計算用テーブル */
		const int m_CrcTableNum;
		CacheId createCacheId(const GDI_FONT_STYLE *style, const unsigned short *str);
		CacheId calcCrc(CacheId base, const unsigned char* binary, unsigned int binarySize);
	public:
		CacheFont(CacheInfo& resouce);
		void* create(GDI_FONT_STYLE *style, unsigned short *str);
		void release(void* addr);
		GDI_CACHE_FONT* getAddr(GDI_FONT_STYLE *style, unsigned short *str);
		void destroy();
	};
	class CacheSVG : public Cache {
	public:
		CacheSVG(CacheInfo& resouce) : Cache(SVG, resouce){}
		void* create(GDI_IMAGE_ID imageId);
		void release(void* addr);
		GDI_CACHE_SVG* getAddr(GDI_IMAGE_ID imageId);
		void destroy();
	};
	class CacheDrawable : public Cache {
	public:
		CacheDrawable(CacheInfo& resouce) : Cache(DRAWABLE, resouce){}
		void release(void* addr);
		void setAddr(unsigned long userId, GDI_DRAWABLE_ID drawableId);
		void destroy();
		void destroy(unsigned long userId);
		void destroyOld();
	};
	CacheFont m_Font;			/* Font キャッシュ用 */
	CacheSVG m_SVG;		/* SVG キャッシュ用 */
	CacheDrawable m_Drawable;	/* Drawable キャッシュ用 */

private:
	/* 周期処理用 */
	static const unsigned long m_AgingCycle; /* タイマー周期 (ms) */
	unsigned long m_CyclicCounter;
	bool m_IsAgingEnable;

	//virtual void receiveEvent(const CtEvent& event); /* タイマーイベント受信処理 */
	void startAging();
	void stopAging();
};

/* 周期処理開始 */
inline void CtCacheControl::startAging()
{
	m_IsAgingEnable = true;
	m_CyclicCounter = 0;
}

/* 周期処理停止 */
inline void CtCacheControl::stopAging()
{
	m_IsAgingEnable = false;
}

#endif	/* _CtCacheControl_H_ */
