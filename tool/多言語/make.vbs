Set objFso = CreateObject("Scripting.FileSystemObject")
Set objWShell = CreateObject("WScript.Shell")

' ファイルを削除,移動
'2017/05/19 一旦コメントアウト objFso.DeleteFile "Q_翻訳シート_POVCAM_前回リリース.xlsx"
'2017/05/19 一旦コメントアウト objFso.DeleteFile "Q_翻訳シート_POVCAM_前回リリースとの差分.xlsx"
'2017/05/19 一旦コメントアウト objFso.DeleteFile "Q_翻訳シート_POVCAM_はみ出しチェック.xlsx"
'2017/05/19 一旦コメントアウト objFso.MoveFile "Q_翻訳シート_POVCAM.xlsx","Q_翻訳シート_POVCAM_前回リリース.xlsx"
'2017/05/19 一旦コメントアウト objFso.MoveFile "Q_翻訳シート_POVCAM_DB.xlsx","Q_翻訳シート_POVCAM.xlsx"

' Excelスタート
Set objExcel = Wscript.CreateObject("Excel.Application")
objExcel.DisplayAlerts = False
objExcel.Visible = True

' 翻訳シートオープン
objExcel.Workbooks.Open objWShell.CurrentDirectory & "\C-翻訳シート.xlsx"

' 翻訳シート調整
	Set objWorksheet = objExcel.Worksheets(2)	'2017/05/19 翻訳シートをアクティブにする
	objWorksheet.Activate						'2017/05/19 翻訳シートをアクティブにする
    objExcel.Cells.Select
    objExcel.Selection.NumberFormatLocal = "@"
    objExcel.Range("B2").Select
    objExcel.ActiveWindow.FreezePanes = True
    objExcel.ActiveWindow.Zoom = 75

' Mツールオープン
objExcel.Workbooks.Open objWShell.CurrentDirectory & "\Mツールv3.02.xlsm"


' STR_ID_SPACE救済 & NULL化
    objExcel.Windows("C-翻訳シート.xlsx").Activate
    objExcel.Run "Mツールv3.02.xlsm!STR_ID_SPACE" ' STR_ID_SPACE救済
'   objExcel.Run "Mツールv3.02.xlsm!Change_to_Asterisk" ' アスタリスク化
'   objExcel.Run "Mツールv3.02.xlsm!Add_Asterisk" ' アスタリスク追加
    objExcel.Run "Mツールv3.02.xlsm!Change_to_Null" ' NULL化
    objExcel.Workbooks("C-翻訳シート.xlsx").Save

' String生成
    objExcel.Run "Mツールv3.02.xlsm!M_TOOL_TOTAL"

' 前回リリースオープン
'2017/05/19 一旦コメントアウト objExcel.Workbooks.Open objWShell.CurrentDirectory & "\Q_翻訳シート_POVCAM_前回リリース.xlsx"

' 前回リリースのシート名変更
'2017/05/19 一旦コメントアウト objExcel.Sheets("Q_翻訳シート_POVCAM").Name = "Q_翻訳シート_POVCAM_前回リリース"
'2017/05/19 一旦コメントアウト objExcel.Workbooks("Q_翻訳シート_POVCAM_前回リリース.xlsx").Save

' シートの移動

'2017/05/19 一旦コメントアウト objExcel.Workbooks("Q_翻訳シート_POVCAM.xlsx").Sheets("Q_翻訳シート_POVCAM").Move , objExcel.Workbooks("Q_翻訳シート_POVCAM_前回リリース.xlsx").Sheets(1)

' 比較ツールオープン
'2017/05/19 一旦コメントアウト objExcel.Workbooks.Open objWShell.CurrentDirectory & "\DiffCells.xlsm"

' シートの比較
'2017/05/19 一旦コメントアウト objExcel.Windows("Q_翻訳シート_POVCAM_前回リリース.xlsx").Activate
'2017/05/19 一旦コメントアウト objExcel.Sheets("Q_翻訳シート_POVCAM_前回リリース").Select
'2017/05/19 一旦コメントアウト objExcel.Run "DiffCells.xlsm!DiffCells"
'2017/05/19 一旦コメントアウト objExcel.Sheets("Q_翻訳シート_POVCAM").Select
'2017/05/19 一旦コメントアウト objExcel.ActiveWindow.Zoom = 25
'2017/05/19 一旦コメントアウト objExcel.Workbooks("Q_翻訳シート_POVCAM_前回リリース.xlsx").SaveAs objWShell.CurrentDirectory & "\Q_翻訳シート_POVCAM_前回リリースとの差分.xlsx"

'Excel終了
objExcel.Quit

'''''''''''''''''''''''''''''''''''
' Excelスタート
'2017/05/19 一旦コメントアウト Set objExcel = Wscript.CreateObject("Excel.Application")
'2017/05/19 一旦コメントアウト objExcel.DisplayAlerts = False
'2017/05/19 一旦コメントアウト objExcel.Visible = True

' 翻訳シートオープン
'2017/05/19 一旦コメントアウト objExcel.Workbooks.Open objWShell.CurrentDirectory & "\Q_翻訳シート_POVCAM.xlsx"

' はみ出しチェックツールオープン
'2017/05/19 一旦コメントアウト objExcel.Workbooks.Open objWShell.CurrentDirectory & "\テキストエリア抽出v2.03.xlsm"

'はみ出しチェック実行
'2017/05/19 一旦コメントアウト objExcel.Windows("Q_翻訳シート_POVCAM.xlsx").Activate
'2017/05/19 一旦コメントアウト objExcel.Run "テキストエリア抽出v2.03.xlsm!Extract_Textarea"
'2017/05/19 一旦コメントアウト objExcel.Workbooks("Q_翻訳シート_POVCAM.xlsx").SaveAs objWShell.CurrentDirectory & "\Q_翻訳シート_POVCAM_はみ出しチェック.xlsx"

'Excel終了
'2017/05/19 一旦コメントアウト objExcel.Quit

Set objExcel = Nothing
Set objWShell = Nothing
Set objFso = Nothing
