Set objFso = CreateObject("Scripting.FileSystemObject")
Set objWShell = CreateObject("WScript.Shell")

' �t�@�C�����폜,�ړ�
'2017/05/19 ��U�R�����g�A�E�g objFso.DeleteFile "Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx"
'2017/05/19 ��U�R�����g�A�E�g objFso.DeleteFile "Q_�|��V�[�g_POVCAM_�O�񃊃��[�X�Ƃ̍���.xlsx"
'2017/05/19 ��U�R�����g�A�E�g objFso.DeleteFile "Q_�|��V�[�g_POVCAM_�͂ݏo���`�F�b�N.xlsx"
'2017/05/19 ��U�R�����g�A�E�g objFso.MoveFile "Q_�|��V�[�g_POVCAM.xlsx","Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx"
'2017/05/19 ��U�R�����g�A�E�g objFso.MoveFile "Q_�|��V�[�g_POVCAM_DB.xlsx","Q_�|��V�[�g_POVCAM.xlsx"

' Excel�X�^�[�g
Set objExcel = Wscript.CreateObject("Excel.Application")
objExcel.DisplayAlerts = False
objExcel.Visible = True

' �|��V�[�g�I�[�v��
objExcel.Workbooks.Open objWShell.CurrentDirectory & "\C-�|��V�[�g.xlsx"

' �|��V�[�g����
	Set objWorksheet = objExcel.Worksheets(2)	'2017/05/19 �|��V�[�g���A�N�e�B�u�ɂ���
	objWorksheet.Activate						'2017/05/19 �|��V�[�g���A�N�e�B�u�ɂ���
    objExcel.Cells.Select
    objExcel.Selection.NumberFormatLocal = "@"
    objExcel.Range("B2").Select
    objExcel.ActiveWindow.FreezePanes = True
    objExcel.ActiveWindow.Zoom = 75

' M�c�[���I�[�v��
objExcel.Workbooks.Open objWShell.CurrentDirectory & "\M�c�[��v3.02.xlsm"


' STR_ID_SPACE�~�� & NULL��
    objExcel.Windows("C-�|��V�[�g.xlsx").Activate
    objExcel.Run "M�c�[��v3.02.xlsm!STR_ID_SPACE" ' STR_ID_SPACE�~��
'   objExcel.Run "M�c�[��v3.02.xlsm!Change_to_Asterisk" ' �A�X�^���X�N��
'   objExcel.Run "M�c�[��v3.02.xlsm!Add_Asterisk" ' �A�X�^���X�N�ǉ�
    objExcel.Run "M�c�[��v3.02.xlsm!Change_to_Null" ' NULL��
    objExcel.Workbooks("C-�|��V�[�g.xlsx").Save

' String����
    objExcel.Run "M�c�[��v3.02.xlsm!M_TOOL_TOTAL"

' �O�񃊃��[�X�I�[�v��
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks.Open objWShell.CurrentDirectory & "\Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx"

' �O�񃊃��[�X�̃V�[�g���ύX
'2017/05/19 ��U�R�����g�A�E�g objExcel.Sheets("Q_�|��V�[�g_POVCAM").Name = "Q_�|��V�[�g_POVCAM_�O�񃊃��[�X"
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks("Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx").Save

' �V�[�g�̈ړ�

'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks("Q_�|��V�[�g_POVCAM.xlsx").Sheets("Q_�|��V�[�g_POVCAM").Move , objExcel.Workbooks("Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx").Sheets(1)

' ��r�c�[���I�[�v��
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks.Open objWShell.CurrentDirectory & "\DiffCells.xlsm"

' �V�[�g�̔�r
'2017/05/19 ��U�R�����g�A�E�g objExcel.Windows("Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx").Activate
'2017/05/19 ��U�R�����g�A�E�g objExcel.Sheets("Q_�|��V�[�g_POVCAM_�O�񃊃��[�X").Select
'2017/05/19 ��U�R�����g�A�E�g objExcel.Run "DiffCells.xlsm!DiffCells"
'2017/05/19 ��U�R�����g�A�E�g objExcel.Sheets("Q_�|��V�[�g_POVCAM").Select
'2017/05/19 ��U�R�����g�A�E�g objExcel.ActiveWindow.Zoom = 25
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks("Q_�|��V�[�g_POVCAM_�O�񃊃��[�X.xlsx").SaveAs objWShell.CurrentDirectory & "\Q_�|��V�[�g_POVCAM_�O�񃊃��[�X�Ƃ̍���.xlsx"

'Excel�I��
objExcel.Quit

'''''''''''''''''''''''''''''''''''
' Excel�X�^�[�g
'2017/05/19 ��U�R�����g�A�E�g Set objExcel = Wscript.CreateObject("Excel.Application")
'2017/05/19 ��U�R�����g�A�E�g objExcel.DisplayAlerts = False
'2017/05/19 ��U�R�����g�A�E�g objExcel.Visible = True

' �|��V�[�g�I�[�v��
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks.Open objWShell.CurrentDirectory & "\Q_�|��V�[�g_POVCAM.xlsx"

' �͂ݏo���`�F�b�N�c�[���I�[�v��
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks.Open objWShell.CurrentDirectory & "\�e�L�X�g�G���A���ov2.03.xlsm"

'�͂ݏo���`�F�b�N���s
'2017/05/19 ��U�R�����g�A�E�g objExcel.Windows("Q_�|��V�[�g_POVCAM.xlsx").Activate
'2017/05/19 ��U�R�����g�A�E�g objExcel.Run "�e�L�X�g�G���A���ov2.03.xlsm!Extract_Textarea"
'2017/05/19 ��U�R�����g�A�E�g objExcel.Workbooks("Q_�|��V�[�g_POVCAM.xlsx").SaveAs objWShell.CurrentDirectory & "\Q_�|��V�[�g_POVCAM_�͂ݏo���`�F�b�N.xlsx"

'Excel�I��
'2017/05/19 ��U�R�����g�A�E�g objExcel.Quit

Set objExcel = Nothing
Set objWShell = Nothing
Set objFso = Nothing
