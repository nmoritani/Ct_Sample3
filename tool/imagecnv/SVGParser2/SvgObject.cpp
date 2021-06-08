#include "stdafx.h"
#include "SvgParser.h"
#include "SvgObject.h"
#include "SvgUtil.h"

//GENSKETCH�݊���̓t���O �Ăяo���O�ɂ��̕ϐ��𒼐ڕύX���Ă���
int	g_SVGPARSER_COMPATIBLE_GENSKETCH_EVENODD = 0;

SvgObject::SvgObject(SvgParser *parser, SvgObject *parent) {
	m_ref_count = 0;
	m_parser = parser;
	m_parent = parent;
	m_transform = NULL;
	m_abs_transform = NULL;
	if (parent != NULL) {
		const SvgTransform *t = parent->abs_transform();
		if (t != NULL) {
			m_abs_transform = NEW SvgTransform(t);
		}
		m_style.copy_from(parent->style());
	}
}

//�R���X�g���N�^(���I�u�W�F�N�g�̏����R�s�[)
SvgObject::SvgObject(SvgObject *src)
{
	m_ref_count = 0;
	m_parser = src->parser();
	m_parent = src->parent();
	m_transform = NULL;
	if (src->transform() != NULL) {
		m_transform = NEW SvgTransform(src->transform());
	}
	m_abs_transform = NULL;
	if (src->abs_transform() != NULL) {
		m_abs_transform = NEW SvgTransform(src->abs_transform());
	}

	m_user_data = src->user_data();
}

SvgObject::~SvgObject()
{
	delete m_transform;
	delete m_abs_transform;
}

//�����̔z��̉��
//parse_attribute�����z�֐��ŌĂԂ��߂Ƀ��\�b�h�Ƃ��ēƗ�
//���R���X�g���N�^���ł͉��z�֐��Ăяo�������z�ɂȂ�Ȃ�
PARSE_RESULT SvgObject::parse_atts(const char *atts[])
{
	PARSE_RESULT ret = PARSED;
	//�����̃p�[�X
	while(*atts != NULL) {
		SVG_DPRINTF("attribute:%s=%s\n", atts[0], atts[1]);
		//��� ���̃��\�b�h��virtual�Ȃ̂Ŏ��ۂ̃N���X�̃��\�b�h���Ă΂�邱�Ƃɒ���
		
		PARSE_RESULT r;
		r = parse_attribute(atts);
		if (r == NOT_PARSED) {
			SVG_DPRINTF(" ignore attribute\n");
		} else
		if (r != PARSED) {
			fprintf(stderr, "ERROR: attribute:%s=%s\n", atts[0], atts[1]);
			ret = r;
		}
		
		atts += 2;
	}
	
	//������͌��ʂ��`�F�b�N
	if (ret != PARSE_ERROR) {
		PARSE_RESULT result;
		result = parse_attribute_end();
		if (result == PARSE_ERROR) {
			ret = result;
		}
	}
	
#if SVGDEBUGOUT
	if (m_abs_transform != NULL) {
		SVG_DPRINTF("ABS Transform\n");
		m_abs_transform->debug_print();
	}
#endif
	if (ret != PARSED) {
		m_parser->set_error(-1);
	}
	return ret;
}

PARSE_RESULT SvgObject::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "transform") || !strcmp(att[0], "gradientTransform")) {
		PARSE_RESULT ret;
		delete m_transform;
		m_transform = NEW SvgTransform();
		ret = m_transform->parse(att[1]);
		//abs_transform�ɔ��f
		if (m_abs_transform == NULL) {
			m_abs_transform = NEW SvgTransform(m_transform);
		} else {
			m_abs_transform->mul(m_transform);
		}
		return ret;
	} else
	if (!strcmp(att[0], "style")) {
		return m_style.parse_style(m_parser, this, att[1]);
	} else
	if (!strcmp(att[0], "class")) {
		SVG_DPRINTF("Class:%s\n", att[1]);
		// Parser�ɃX�^�C���₢���킹
		SvgStyle *style = m_parser->find_style_by_class(att[1]);

		if(style){
			// �X�^�C���㏑��
			// �{���͊����X�^�C���ɑ΂��ă}�[�W����̂��������͂�
			m_style.copy_from(style);
		}
		return PARSED;
	} else
	{
		//Style���m���Ă��邩������Ȃ��̂œn��
		return m_style.parse_attribute(m_parser, this, att);
	}
}

//������͌��ʂ��`�F�b�N
PARSE_RESULT SvgObject::parse_attribute_end()
{
	return PARSED;
}

//�p�X�ɕϊ�
SvgPath *SvgObject::cnv_to_path()
{
	return NULL;
}

