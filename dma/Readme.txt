
<AVC����API>
INT GDI_DrawFillRectangleSimple(const GDI_DRAW_BUFFER *buffer, INT x, INT y, INT width, INT height, UW forecolor, UW *request)
�E�����̍\���̂ŃR�[���o�b�N�֐����w�肳��Ă���ꍇ�́A�ʃ^�X�N�Ƀ��b�Z�[�W�𓊂��ă��^�[������B
�@�i�w�肪NULL�̏ꍇ�́A�]�������܂Ńt���O�҂�����j
�E���b�Z�[�W�p��MPF���g�p�B

<���������T�v>
GUI_DMA_main()
�E��LAPI�p�̃��b�Z�[�W��M�֐��B
�@K460��VOU�X�V�v���Ɠ����^�X�N�������ׁAK519�Ń^�X�N�����BTSK_PRI�͓����B

gui_dma_fillrect_yuv_simple()
�E���b�Z�[�W��M�ɂĎ��s�B
�ECOLOR_BUFFER 0/1���A���L��DMA�]���֐����Q����s����
�E��L������A�w�肳��Ă���R�[���o�b�N�����s����B
�@�i�w�肪NULL�̏ꍇ�́A�]�������t���O���Z�b�g����j

gui_dma_fillrect()��gui_dma_fillrect_exec()
�EMDMAC�O��API���g�p���āA�p�����[�^�ݒ聕DMA�]�����s
�E�]�������܂Ńt���O�҂�����
