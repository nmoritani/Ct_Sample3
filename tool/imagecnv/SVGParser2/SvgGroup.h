#ifndef _SVGGROUP_H_
#define _SVGGROUP_H_

#include "SvgObject.h"

class SvgParser;

class SvgGroup : public SvgObject {
	typedef SvgObject	super;
protected:
	SVGOBJECTLIST	m_objects;
public:
	//�R���X�g���N�^
	SvgGroup(SvgParser *parser, SvgObject *parent);
	//�f�X�g���N�^
	virtual ~SvgGroup();
	//�e�I�u�W�F�N�g�擾 (SvgGroup�ɃL���X�g���邽�߂ɍ쐬)
	SvgGroup *parent() const {
		return (SvgGroup*)SvgObject::parent();
	}
	//�I�u�W�F�N�g���X�g
	SVGOBJECTLIST *objects() { return &m_objects; }
	//�I�u�W�F�N�g�ǉ�
	void add(SvgObject *obj) {
		m_objects.push_back(obj);
	}
	//id����I�u�W�F�N�g������
	SvgObject *find_object(const char *id);
	//�I�u�W�F�N�g���폜
	void delete_object(SvgObject *obj);
	//�I�u�W�F�N�g���폜
	void delete_all();
};

#endif
