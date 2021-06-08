#ifndef __OUTPUT_TYPE_H__
#define __OUTPUT_TYPE_H__

//�f�[�^�̏��Ԃ�ύX�����image_resource_db.xls�ɉe������̂ŋ֎~ */
typedef enum {
	OUTPUT_TYPE_1BPP,
	OUTPUT_TYPE_8BPP,
	OUTPUT_TYPE_8BPP_RLE,
	OUTPUT_TYPE_HR_8BPP_PAL,
	OUTPUT_TYPE_HR_8BPP_PAL_RLE2,
	OUTPUT_TYPE_8BPP_STRETCH_H,			//(���Ή�)�c���L�� �{�^���p�摜
	OUTPUT_TYPE_8BPP_STRETCH_V,			//(���Ή�)�c���L�� �{�^���p�摜
	OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_H,	//�c���L�� �{�^���p�摜
	OUTPUT_TYPE_HR_8BPP_PAL_STRETCH_V,	//�c���L�� �{�^���p�摜
	OUTPUT_TYPE_HR_32BPP,
	OUTPUT_TYPE_HR_32BPP_RLE2,
	OUTPUT_TYPE_HR_AUTO,				//8bpp�摜->8BPP_PAL		32bpp�摜->32BPP
	OUTPUT_TYPE_HR_AUTO_RLE2,			//8bpp�摜->8BPP_PAL_RLE2	32bpp�摜->32BPP_RLE2
	OUTPUT_TYPE_1BPP_REVERSE,			//���m�N�� �������]
	OUTPUT_TYPE_MAX
} OUTPUT_TYPE;

/* �o�̓t���O �� */
#define		OUTPUT_SVG_ABSCOORD			0x00010000			//��΍��W�ɕϊ�
#define		OUTPUT_SVG_CNV_TO_PATH		0x00020000			//path�ȊO�̃I�u�W�F�N�g��path�ɕϊ����ďo��
#define		OUTPUT_FOR_HIRESO_APL		0x00040000			//���𑜓x�A�v���p�o�́iHR�`���̃T�C�Y��1/2���Ȃ�)


#endif
