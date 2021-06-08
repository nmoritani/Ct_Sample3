@prompt $s

REM ビルド実行(デバッグビルド)：msbuild /p:Configuration=Debug
REM ビルド実行(リリースビルド)：msbuild /p:Configuration=Release
REM リビルド実行(デバッグビルド)：msbuild /t:Rebuild /p:Configuration=Debug
REM リビルド実行(リリースビルド)：msbuild /t:Rebuild /p:Configuration=Release
REM クリーン実行：msbuild /t:clean

SET PARAM="%1"

SET COMMAND=/p:Configuration=Debug
if /i %PARAM% EQU "clean" SET COMMAND=/t:clean
if /i %PARAM% EQU "Release" SET COMMAND=/p:Configuration=Release

msbuild %COMMAND%

@prompt $p$g
