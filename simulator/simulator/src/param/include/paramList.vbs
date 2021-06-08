' Unique Value
Dim FileObject			:	FileObject = "Scripting.FileSystemObject"
Dim TextFileName		:	TextFileName = "\paramString.def"
Dim ExcelFileName		:	ExcelFileName = "\新規ParamService.xlsm"
Dim SheetNum			:	SheetNum = 4
Dim StartRowString		:	StartRowString = "AplParam名"
Dim ExcelVisible		:	ExcelVisible = true
Dim ExcelDisplayAlerts	:	ExcelDisplayAlerts = false

' Usual Value
dim FSO
dim CurrentPath
Dim TextFileStream
Dim row					:	row = 1
Dim column				:	column = 1

'Create FileObject
Set FSO = createObject(FileObject)
If FSO Is Nothing Then
 ' Fail Create FSO
 MsgBox "Fail Create FSO"
 WScript.Quit
End If

' Get Path That Existing This Script 
CurrentPath = FSO.getParentFolderName(WScript.ScriptFullName)

'Create Text File
Set TextFileStream = FSO.CreateTextFile(CurrentPath + TextFileName)
If TextFileStream Is Nothing Then
 ' Fail Create File
 MsgBox "Fail Create File"
 WScript.Quit
End If

' Act Excel
Set oXlsApp = CreateObject("Excel.Application")
If oXlsApp Is Nothing Then
 ' Fail Act Excel
 MsgBox "Fail Act Excel"
Else
 ' #### SETTING EXCEL ####
 ' Disp Excel
 oXlsApp.Application.Visible = ExcelVisible
 ' Disp Excel Alerts
 oXlsApp.Application.DisplayAlerts = ExcelDisplayAlerts
 ' Open WorkBook 
 oXlsApp.Application.Workbooks.Open(CurrentPath + ExcelFileName)
 ' Select Sheet
 Set oSheet = oXlsApp.Worksheets(SheetNum)
 
 ' Searching Starting Word
 Set orange = oSheet.Cells.Find(StartRowString)
 If orange Is Nothing Then
	MsgBox "検索対象が存在しない"
	WScript.Quit
 Else
 	' Search Target Is Next Row 
	 row = orange.Row + 3
	 column = orange.column
	 'Extraction String
	 Do Until oSheet.Cells(row, column).value = ""
	 	Dim StrFormat:StrFormat = vbTab + "{ " + oSheet.Cells(row, column).value + "," + vbTab + vbTab + "STR(" + oSheet.Cells(row, column).value + ")},"
		 TextFileStream.WriteLine(StrFormat)
		 row = row + 1
	 Loop
 End If
End If

' Quit Excel
oXlsApp.Quit
TextFileStream.Close()
' オブジェクトクリア
Set oXlsApp = Nothing
Set TextFileStream = Nothing
Set FSO = Nothing