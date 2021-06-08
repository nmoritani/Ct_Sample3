
■SVG出力
□制限事項
・'A','a'は非対応
・transformに回転が含まれていると正確に変換できない
・同一のlinearGradientが複数の要素から参照されている場合transformの解決が正しくできない
・transformに複数の変換が指定されている場合はエラーとなる

□SVG仕様との差異
・出力はGENSKETCHにあわせているためSVG仕様とは一部異なる部分がある（COMPATIBLE_GENSKETCH）
　・fill-ruleのデフォルトがSVGFILLRULE_EVENODD（SVG仕様ではSVGFILLRULE_NONZERO)
　・opacityをfillにしか適用しない（SVG仕様ではstrokeにも適用する)

□GENSKETCH互換出力の制限
・groupの出力は対応していない
　・groupに含まれているオブジェクトもすべて１つのグループにまとめられて出力される
　・groupが含まれる場合オブジェクトの出力順がGENSKETCHと異なる場合がある
・groupに指定されているtransfromの扱いが異なる
　・GENSKETCHと異なりgroupのtransformを無視しない



