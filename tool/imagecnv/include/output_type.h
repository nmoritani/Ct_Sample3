#ifndef __OUTPUT_TYPE_H__
#define __OUTPUT_TYPE_H__

//�f�[�^�̏��Ԃ�ύX�����image_resource_db.xls�ɉe������̂ŋ֎~ */
typedef enum {
	OUTPUT_TYPE_1BPP,
	OUTPUT_TYPE_8BPP,
	OUTPUT_TYPE_8BPP_RLE,
    OUTPUT_TYPE_16BPP,
	//    OUTPUT_TYPE_16BPP_DMP,
	OUTPUT_TYPE_32BPP,
	//	OUTPUT_TYPE_32BPP_DMP,
	OUTPUT_TYPE_32BPP_RLE2,
	OUTPUT_TYPE_MAX
} OUTPUT_TYPE;

/* �o�̓t���O �� */
#define		OUTPUT_SVG_ABSCOORD			0x00010000			//��΍��W�ɕϊ�
#define		OUTPUT_SVG_CNV_TO_PATH		0x00020000			//path�ȊO�̃I�u�W�F�N�g��path�ɕϊ����ďo��
#define     OUTPUT_DMP_ALIGNMENT        0x00040000          //DMP GE�p��Width:16, height:8�̃A���C�����g(padding)

#endif
