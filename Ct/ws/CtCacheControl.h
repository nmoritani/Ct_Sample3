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

	/* Font �p */
	GDI_CACHE_FONT* getCache(GDI_FONT_STYLE *style, unsigned short *str); /* �L���b�V���擾 */
	void destroyFontCache();	/* �S�L���b�V���폜 */

	/* SVG �p */
	GDI_CACHE_SVG* getCache(GDI_IMAGE_ID imageId); /* �L���b�V���擾 */
	void destroySVGCache();	/* �S�L���b�V���폜 */

	/* Drawable �p */
	GDI_DRAWABLE_ID getCache(unsigned long id); /* �L���b�V���擾 */
	void setCache(unsigned long userId, GDI_DRAWABLE_ID drawableId); /* �L���b�V�����o�^ */
	void destroyDrawableCache(unsigned long userId); /* �w����̃N���A */
	void destroyDrawableCacheAuto(); /* �����N���A (��ԌÂ���������) */
	void destroyDrawableCache();	 /* �S�L���b�V���N���A */

public:
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
protected:
	virtual ~CtCacheControl();

private:
	static CtCacheControl* m_This;

private:
	/* �L���b�V���Ǘ����֘A */
	enum CacheType {
		NONE,
		FONT,
		SVG,
		DRAWABLE
	};

	typedef unsigned long CacheId;
	struct CacheData {
		CacheType m_Type;			 /* �f�[�^��� */
		CacheId m_Id;				 /* �Ǘ�ID */
		void* mp_Addr;				 /* �L���b�V���A�h���X */
		bool m_IsRefer;				 /* �Q�ƃr�b�g */
		unsigned short m_Frequently; /* �g�p�p�x�J�E���^ */
	};

	/* �L���b�V���Ǘ����N���X */
	class CacheInfo {	/* new ����p�r���Ȃ��̂� CtObject �͌p�����Ȃ� */
	private:
		CacheData m_Info[1024];	/* new �Ƃ��߂�ǂ��̂ŌŒ蒷�ɂ��� */
		unsigned short m_Num;	/* ���������L���b�V���̐� */
		const unsigned short m_NumMax; /* �f�[�^�� */
		static const CacheData m_InitData; /* �������p */
	public:
		CacheInfo();
		CacheData* get(CacheType type, CacheId id);
		bool set(CacheType type, CacheId id, void* addr);
		CacheData* search(CacheType type, CacheId id);
		CacheData* search(unsigned int& progress, CacheType type);
		CacheData* searchEmpty();
		bool clearOld(CacheData& clearData);
		void clear(CacheData& data);
		void aging();			/* �y�[�W�u���A���S���Y�����{ */
	};

	/* �L���b�V���Ǘ����: ���\�[�X���ɎQ�Ɨ̈悪�قȂ� */
	static CacheInfo m_CacheInfo;
	static CacheInfo m_CacheInfoDrawable;

	/* �L���b�V�����ƃf�[�^�̊Ǘ��N���X (���\�[�X���ɍ쐬) */
	class Cache {	/* new ����p�r���Ȃ��̂� CtObject �͌p�����Ȃ� */
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
		unsigned long m_CrcTable[256]; /* CRC �l�v�Z�p�e�[�u�� */
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
	CacheFont m_Font;			/* Font �L���b�V���p */
	CacheSVG m_SVG;		/* SVG �L���b�V���p */
	CacheDrawable m_Drawable;	/* Drawable �L���b�V���p */

private:
	/* ���������p */
	static const unsigned long m_AgingCycle; /* �^�C�}�[���� (ms) */
	unsigned long m_CyclicCounter;
	bool m_IsAgingEnable;

	//virtual void receiveEvent(const CtEvent& event); /* �^�C�}�[�C�x���g��M���� */
	void startAging();
	void stopAging();
};

/* ���������J�n */
inline void CtCacheControl::startAging()
{
	m_IsAgingEnable = true;
	m_CyclicCounter = 0;
}

/* ����������~ */
inline void CtCacheControl::stopAging()
{
	m_IsAgingEnable = false;
}

#endif	/* _CtCacheControl_H_ */
