@prompt $s

REM �r���h���s(�f�o�b�O�r���h)�Fmsbuild /p:Configuration=Debug
REM �r���h���s(�����[�X�r���h)�Fmsbuild /p:Configuration=Release
REM ���r���h���s(�f�o�b�O�r���h)�Fmsbuild /t:Rebuild /p:Configuration=Debug
REM ���r���h���s(�����[�X�r���h)�Fmsbuild /t:Rebuild /p:Configuration=Release
REM �N���[�����s�Fmsbuild /t:clean

SET PARAM="%1"

SET COMMAND=/p:Configuration=Debug
if /i %PARAM% EQU "clean" SET COMMAND=/t:clean
if /i %PARAM% EQU "Release" SET COMMAND=/p:Configuration=Release

msbuild %COMMAND%

@prompt $p$g
