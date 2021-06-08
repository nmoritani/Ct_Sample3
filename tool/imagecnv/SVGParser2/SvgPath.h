#ifndef _SVGPATH_H_
#define _SVGPATH_H_

#include "SvgObject.h"

class SvgPath : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	SVGCMDS			m_commands;
	SVGCOORDS		m_coords;
public:
	//�R���X�g���N�^
	SvgPath(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_PATH;
	}
	//�R���X�g���N�^(�p�X�ϊ��p)	//���I�u�W�F�N�g�̏����R�s�[����
	SvgPath(SvgObject *src)
		: SvgObject(src) {
		m_type = SVG_TYPE_PATH;
	}
	//�f�X�g���N�^
	virtual ~SvgPath();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//�p�X�f�[�^���
	PARSE_RESULT parse_d(const char *data);
	//�R�}���h�ǉ�
	void add_command(SVG_CMD cmd) {
		m_commands.push_back(cmd);
	}
	//���W�ǉ�
	void add_coord(float coord) {
		m_coords.push_back(coord);
	}
	//
	const SVGCOORDS *coords() const {return &m_coords; }
	const SVGCMDS *commands() const {return &m_commands; }
};

#endif
