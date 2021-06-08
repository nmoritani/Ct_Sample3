
<AVC向けAPI>
INT GDI_DrawFillRectangleSimple(const GDI_DRAW_BUFFER *buffer, INT x, INT y, INT width, INT height, UW forecolor, UW *request)
・引数の構造体でコールバック関数が指定されている場合は、別タスクにメッセージを投げてリターンする。
　（指定がNULLの場合は、転送完了までフラグ待ちする）
・メッセージ用にMPFを使用。

<内部処理概要>
GUI_DMA_main()
・上記API用のメッセージ受信関数。
　K460でVOU更新要求と同じタスクだった為、K519でタスク分離。TSK_PRIは同じ。

gui_dma_fillrect_yuv_simple()
・メッセージ受信にて実行。
・COLOR_BUFFER 0/1分、下記のDMA転送関数を２回実行する
・上記完了後、指定されているコールバックを実行する。
　（指定がNULLの場合は、転送完了フラグをセットする）

gui_dma_fillrect()→gui_dma_fillrect_exec()
・MDMAC外部APIを使用して、パラメータ設定＆DMA転送実行
・転送完了までフラグ待ちする
