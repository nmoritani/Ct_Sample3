/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtCacheControl
 */
#include "CtCacheControl.h"
#include "CtDebugPrint.h"
#include "CtTimer.h"
#include "CtEventHandler.h"

const unsigned long CtCacheControl::m_AgingCycle = 1000;	/* �^�C�}�[�����B�Ƃ�� 1 �b */
CtCacheControl::CacheInfo CtCacheControl::m_CacheInfo;
CtCacheControl::CacheInfo CtCacheControl::m_CacheInfoDrawable;

CtCacheControl* CtCacheControl::m_This(NULL);

CtCacheControl::CtCacheControl() :
	m_Font(m_CacheInfo),
	m_SVG(m_CacheInfo),		/* ���� FONT �Ƌ��ʊǗ� */
	m_Drawable(m_CacheInfoDrawable),
	m_CyclicCounter(0),
	m_IsAgingEnable(false)
{
	setClassType(CtClassType_CacheControl);

	/* �^�C�}�[�C�x���g���󂯂邽�߂̃I�u�U�[�o�[�o�^ */
	CtTimer::getInstance()->startCyclic(CT_CACHE_CTRL_TIMER_ID, m_AgingCycle, this);
	startAging();
}

CtCacheControl::~CtCacheControl()
{
	/* ���������~�߂� */
	stopAging();

	/* ���������L���b�V�������� */
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

/* �L���b�V���擾 (Font �L���b�V��) */
GDI_CACHE_FONT* CtCacheControl::getCache(GDI_FONT_STYLE *style, unsigned short *str)
{
	return m_Font.getAddr(style, str);
}

/* �L���b�V���擾 (SVG �L���b�V��) */
GDI_CACHE_SVG* CtCacheControl::getCache(GDI_IMAGE_ID imageId)
{
	return m_SVG.getAddr(imageId);
}

/* Drawable �p�L���b�V�����擾 */
GDI_DRAWABLE_ID CtCacheControl::getCache(unsigned long userId)
{
	/* ��񂪂��邩�����Q�Ƃ���B�Ȃ��ꍇ�� NULL ��Ԃ��Đ���ɍ쐬���Ă��炤 */
	CacheId id = static_cast<CacheId>(userId);
	return reinterpret_cast<GDI_DRAWABLE_ID>(m_Drawable.getAddr(id));
}

/* Drawable �p�L���b�V����ݒ� */
void CtCacheControl::setCache(unsigned long userId, GDI_DRAWABLE_ID drawableId)
{
	m_Drawable.setAddr(userId, drawableId);
}

/* Font �L���b�V���̑S�N���A */
void CtCacheControl::destroyFontCache()
{
	stopAging();				/* �����������~�߂� */
	m_Font.destroy();
	startAging();
}

/* SVG �L���b�V���̑S�N���A */
void CtCacheControl::destroySVGCache()
{
	stopAging();				/* �����������~�߂� */
	m_SVG.destroy();
	startAging();
}

/* Drawable �L���b�V���̑S�N���A */
void CtCacheControl::destroyDrawableCache()
{
	stopAging();				/* �����������~�߂� */
	m_Drawable.destroy();
	startAging();
}

/* Drawable �L���b�V���̎w��N���A */
void CtCacheControl::destroyDrawableCache(unsigned long userId)
{
	stopAging();				/* �����������~�߂� */
	m_Drawable.destroy(userId);
	startAging();
}

/* Drawable �L���b�V���̎����N���A (��ԌÂ����̂�����) */
void CtCacheControl::destroyDrawableCacheAuto()
{
	stopAging();				/* �����������~�߂� */
	m_Drawable.destroyOld();
	startAging();
}

bool CtCacheControl::handleTimerEvent(const CtEventTimer& Timer) {
	if (m_IsAgingEnable) {
		m_CyclicCounter += Timer.getCycTim(); /* �^�C�}�[�����������J�E���^��i�߂� */
		if (m_CyclicCounter >= m_AgingCycle) { /* �����ɂȂ�������s */
											   /* �L���b�V���Ǘ����̍X�V���s�� */
			m_CacheInfo.aging();
			m_CacheInfoDrawable.aging();
			m_CyclicCounter -= m_AgingCycle;
		}
	}
	return false;
};

/* --- �L���b�V�����Ǘ��N���X ------------------------------------ */
const CtCacheControl::CacheData CtCacheControl::CacheInfo::m_InitData = {NONE, 0, NULL, false, 0};
CtCacheControl::CacheInfo::CacheInfo() :
	m_Num(0),
	m_NumMax(sizeof m_Info / sizeof m_Info[0])
{
	/* ���̃N���X�� static �̈�ɔz�u�����z��Ȃ̂ŁA m_Info[] �͓��ɏ��������Ȃ� */
}

/* �L���b�V���f�[�^�擾 */
CtCacheControl::CacheData* CtCacheControl::CacheInfo::get(CacheType type, CacheId id)
{
	CacheData* data = search(type, id);
	if (data != NULL) {
		data->m_IsRefer = true; /* �擾�����̂ŎQ�Ƃ��� */
	}
	return data;
}

/* �L���b�V���f�[�^�o�^ */
bool CtCacheControl::CacheInfo::set(CacheType type, CacheId id, void* addr)
{
	if (addr == NULL) {
		return false;
	}

	void* releaseAddr = NULL;
	CacheData* blankData = searchEmpty();
	if (blankData == NULL) {	/* �Ǘ���񂪖��t */
		CtDebugPrint(CtDbg, "Cache info full! Type=%d, ID=%d, CacheNum=%d\n", type, id, m_Num);
		return false;
	}
	blankData->mp_Addr = addr;
	blankData->m_Type = type;
	blankData->m_Id = id;
	blankData->m_Frequently = 0;  /* �Œ�l�ɖ߂� */
	blankData->m_IsRefer = true;  /* �ݒ肳�ꂽ�̂ŎQ�Ƃ��� */
	m_Num++;

	return true;
}

/* �L���b�V���f�[�^���� */
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

/* �L���b�V���f�[�^���� ���r������ĊJ�@�\�t�� */
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

/* �L���b�V���f�[�^�擾 (��) */
CtCacheControl::CacheData* CtCacheControl::CacheInfo::searchEmpty()
{
	if (m_Num >= m_NumMax) {   /* �o�^�� MAX �Ȃ炢�������������Ȃ� */
		CtDebugPrint(CtDbg, "CacheInfo num=%d, not have empty info.\n", m_Num);
		return NULL;
	}

	unsigned int progress = 0;
	return search(progress, NONE);
}

/* (�G�[�W���O�A���S���Y���ŎZ�o���ꂽ) ��ԌÂ��L���b�V������� */
bool CtCacheControl::CacheInfo::clearOld(CacheData& clearData)
{
	CacheData base = m_InitData; /* �Œ�l�����߂邽�߂̔�r�p�����l */
	base.m_Frequently = 0xFFFF;	 /* �����l�Ȃ̂� MAX �ɂ��� */
	CacheData *minimum = &base;
	for (unsigned int ii = 0; ii < m_NumMax; ii++) {
		if (m_Info[ii].m_Type == NONE) continue; /* ���o�^�f�[�^�͔�΂� */
		if (m_Info[ii].m_IsRefer == true) continue; /* �Q�� (or �쐬) ����̃f�[�^�͎g�p�O�Ȃ̂Ŕ�΂� */
		//m_Frequently�̒l�́A�ŋ߂̎Q�ƂɑΉ������l�͑傫���A
		//�ߋ��ɑk��قǒl���������Ȃ�̂ŁAminimum->m_Frequently��菬�����l��T��
		if (minimum->m_Frequently > m_Info[ii].m_Frequently) {
			minimum = &m_Info[ii];
			if (minimum->m_Frequently == 0) { /* 0 (�Œ�l) ���o����ȍ~�͔�r�̕K�v�Ȃ� */
				break;
			}
		}
	}
	if (minimum == &base) {		/* �f�[�^���Ȃ��ȂǁA�Œ�l�����t����Ȃ����� */
		return false;
	}
	clearData = *minimum;		/* �����f�[�^�̃R�s�[ (�߂�l) */
	clear(*minimum);
	return true;
}

/* �L���b�V���f�[�^�̍폜 */
void CtCacheControl::CacheInfo::clear(CacheData& data)
{
	if (data.m_Type == NONE) { /* �������̂͏����܂��� */
		return;
	}

	if (m_Num == 0) {
		CtDebugPrint(CtDbg, "set CacheInfo and clear CacheInfo don't match!!\n");
	} else {
		m_Num--;
	}
	data = m_InitData;
}

/* �G�[�W���O (�y�[�W�u���A���S���Y��) �̎Q�Əd�ݕt�� */
void CtCacheControl::CacheInfo::aging()
{
	/**
	 * �G�[�W���O�E�A���S���Y���� NFU �A���S���Y�������ǂ������̂ŁA�P���ɃL���b�V���̎Q�Ɖ񐔂����łȂ�
	 * ���̃L���b�V�����ŋߎQ�Ƃ��ꂽ���ǂ������܂߂Ďc���f�[�^�̏d�ݕt��������B
	 * �y�d�ݕt�����@�z
	 * �L���b�V���̎Q�ƃJ�E���^���E�V�t�g���Ă���J�E���g�A�b�v����B
	 * �Ⴆ�΁A����L���b�V���ɂ��Ď����`�F�b�N 6 �񕪂̎Q�ƃr�b�g�� 1 �� 0 �� 0 �� 1 �� 1 �� 0 �̕ω��������ꍇ�A
	 * �Q�ƃJ�E���^�� 10000000 �� 01000000 �� 00100000 �� 10010000 �� 11001000 �� 01100100 �̂悤�ɕω�����̂�
	 * �ŋ߂̎Q�ƂɑΉ������l�͑傫���A�ߋ��ɑk��قǒl���������Ȃ�B
	 * ���܂�A�Q�ƃr�b�g�̗�����V�������̂��� MSB �� LSB �̏��ŕێ����Ă��邱�ƂɂȂ�
	 */
	for (unsigned int ii = 0; ii < m_NumMax; ii++) {
		CacheData& data = m_Info[ii];
		if (data.m_Type != NONE) { /* �L���b�V�����肾���`�F�b�N���� */
			data.m_Frequently >>= 1;
			if (data.m_IsRefer) {
				data.m_IsRefer = false;
				data.m_Frequently |= 0x8000; /* MSB �� 1 �𗧂Ă� */
			}
		}
	}
}

/* --- �L���b�V�����ƃf�[�^�̊Ǘ��N���X (�e) -------------------- */
/* �L���b�V�����̎擾 */
void* CtCacheControl::Cache::getAddr(CacheId id)
{
	CacheData* data = m_Info.get(m_Type, id);
	if (data == NULL) {
		return NULL;
	}
	return data->mp_Addr;
}

/* �L���b�V������ݒ� */
bool CtCacheControl::Cache::setAddr(CacheData& clearData, CacheId id, void* addr)
{
	bool isClear = false;
	bool isSet = m_Info.set(m_Type, id, addr);
	if (isSet == false) {		/* ��񂪖��t */
		/* �Â��L���b�V�����̂ĂĊǗ����̋󂫂��m�� */
		isClear = m_Info.clearOld(clearData);
		if (isClear) {
			m_Info.set(m_Type, id, addr);
		}
	}
	return isClear;
}

/* --- �L���b�V�����ƃf�[�^�̊Ǘ��N���X (FONT) ------------------ */
CtCacheControl::CacheFont::CacheFont(CacheInfo& resouce) :
	Cache(FONT, resouce),
	m_CrcTableNum(sizeof m_CrcTable / sizeof m_CrcTable[0])
{
	/* CRC �̌v�Z�Ɏg���e�[�u�����쐬 */
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

/* Font �p GDI �L���b�V���f�[�^�̐��� */
void* CtCacheControl::CacheFont::create(GDI_FONT_STYLE *style, unsigned short *str)
{
	GDI_CACHE_FONT* cacheAddr = GDI_CreateCacheFont(style, str);
	return cacheAddr;
}

/* Font �p GDI �L���b�V���f�[�^�̉�� */
void CtCacheControl::CacheFont::release(void *addr)
{
	GDI_ERRCODE err = GDI_DeleteCache(static_cast<GDI_CACHE_BASE*>(addr));
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_DeleteCache(%08x)=%08x\n", addr, err);
	}
}

/* Font �p�L���b�V�����擾 */
GDI_CACHE_FONT* CtCacheControl::CacheFont::getAddr(GDI_FONT_STYLE *style, unsigned short *str)
{
	CacheId id = createCacheId(style, str); /* �f�[�^���� CRC ���v�Z���ČŗL ID �Ƃ��Ďg�� */
	void* cacheAddr = Cache::getAddr(id);
	CacheData clearData;

	if (cacheAddr == NULL) {	/* �L���b�V���Ȃ��̏ꍇ�͍쐬 */
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
			if (isClear == true) { /* set ����ۂɃL���b�V�����̍폜������ */
				release(clearData.mp_Addr);
			}
		}

		if (cacheAddr == NULL) {	/* �L���b�V���������s */
			CtDebugPrint(CtDbg, "Cache creation failed. Type=%d, ID=%d\n", m_Type, id);
		}
	}
	return static_cast<GDI_CACHE_FONT*>(cacheAddr);
}

/* Font �p�L���b�V���̑S���  */
void CtCacheControl::CacheFont::destroy()
{
	unsigned int progress = 0;
	CacheData* data;
	while (data = m_Info.search(progress, m_Type)) {
		release(data->mp_Addr);
		m_Info.clear(*data);
		progress++;				/* ���̃f�[�^���猟�� */
	}
}

/* �t�H���g�f�[�^�̃o�C�i������ CRC ���v�Z */
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

/* �o�C�i���f�[�^�� CRC ���v�Z���� */
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

/* --- �L���b�V�����ƃf�[�^�̊Ǘ��N���X (SVG) ---------------- */
/* SVG �p GDI �L���b�V���f�[�^�̐��� */
void* CtCacheControl::CacheSVG::create(GDI_IMAGE_ID imageId)
{
	GDI_IMAGE_SVG* svg = GDI_GetImageSVG(imageId);
	GDI_CACHE_SVG* cacheAddr = GDI_CreateCacheSVG(svg);
	return cacheAddr;
}

/* SVG �p GDI �L���b�V���f�[�^�̉�� */
void CtCacheControl::CacheSVG::release(void* addr)
{
	GDI_ERRCODE err = GDI_DeleteCache(static_cast<GDI_CACHE_BASE*>(addr));
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_DeleteCache(%08x)=%08x\n", addr, err);
	}
}

/* SVG �p�L���b�V�����擾  */
GDI_CACHE_SVG* CtCacheControl::CacheSVG::getAddr(GDI_IMAGE_ID imageId)
{
	CacheId id = static_cast<CacheId>(imageId);
	void* cacheAddr = Cache::getAddr(id);
	CacheData clearData;

	if (cacheAddr == NULL) {	/* �L���b�V���Ȃ��̏ꍇ�͍쐬 */
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
			if (isClear == true) { /* set ����ۂɃL���b�V�����̍폜������ */
				release(clearData.mp_Addr);
			}
		}

		if (cacheAddr == NULL) {	/* �L���b�V���������s */
			CtDebugPrint(CtDbg, "Cache creation failed. Type=%d, ID=%d\n", m_Type, imageId);
		}
	}
	return static_cast<GDI_CACHE_SVG*>(cacheAddr);
}

/* SVG �p�L���b�V���̑S���  */
void CtCacheControl::CacheSVG::destroy()
{
	unsigned int progress = 0;
	CacheData* data;
	while (data = m_Info.search(progress, m_Type)) {
		release(data->mp_Addr);
		m_Info.clear(*data);
		progress++;				/* ���̃f�[�^���猟�� */
	}
}

/* --- �L���b�V�����ƃf�[�^�̊Ǘ��N���X (DRAWABLE) -------------- */
/* Drawable �p�L���b�V���f�[�^�ݒ� */
void CtCacheControl::CacheDrawable::setAddr(unsigned long userId, GDI_DRAWABLE_ID drawableId)
{
	/* �f�[�^�͐��������Ă����̂ŁA������͏���o�^���邾�� */
	CacheData clearData;
	bool isClear = Cache::setAddr(clearData, static_cast<CacheId>(userId), reinterpret_cast<void*>(drawableId));
	if (isClear == true) {
		release(clearData.mp_Addr);
	}
}

/* Drawable �p GDI �L���b�V���f�[�^�̉�� */
void CtCacheControl::CacheDrawable::release(void* addr)
{
	GDI_ERRCODE err = GDI_DeleteDrawable(reinterpret_cast<GDI_HANDLER>(addr));
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_DeleteDrawable(%08x)=%08x\n", addr, err);
	}
}

/* Drawable �p�L���b�V���̑S��� */
void CtCacheControl::CacheDrawable::destroy()
{
	unsigned int progress = 0;
	CacheData* data;
	while (data = m_Info.search(progress, m_Type)) {
		release(data->mp_Addr);
		m_Info.clear(*data);
		progress++;				/* ���̃f�[�^���猟�� */
	}
}

/* Drawable �p�w��L���b�V���̉�� */
void CtCacheControl::CacheDrawable::destroy(unsigned long userId)
{
	CacheData* data = m_Info.get(m_Type, static_cast<CacheId>(userId));
	if (data != NULL) {
		release(data->mp_Addr);
		m_Info.clear(*data);
	}
}

/* Drawable �p�����L���b�V����� */
void CtCacheControl::CacheDrawable::destroyOld()
{
	CacheData clearData;
	bool isClear = m_Info.clearOld(clearData);
	if (isClear) {
		release(clearData.mp_Addr);
	}
}
