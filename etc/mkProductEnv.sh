#!/bin/sh

tmpdir="testEnv"

if [ -e $1 ]; then
    echo "work $1 folder"
else
    echo "project not found... $1"
    exit
fi

rm -fr $tmpdir
mkdir $tmpdir
svn export http://10.78.121.15/svnrepos/soft/blocks/apl/src/work/Gui/Ct_k519_TestEnv $tmpdir/Gui
echo "sjis -> euc"
find $tmpdir -type f -exec nkf -e -Lu --overwrite {} \;

echo "copy TestEnviroment to ProductEnv: [ $1 ] "
rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/*/
rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/*.*
mv $tmpdir/Gui/*/ $1/BE_Soft/MovieSoft/Mid/Gui/
mv $tmpdir/Gui/*.* $1/BE_Soft/MovieSoft/Mid/Gui

echo "Remove TestEnv Folder"
rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/etc
rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/simulator
rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/tool
# rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/Ct/dbg
rm -fr $1/BE_Soft/MovieSoft/Mid/Gui/Ct/Window/SANDBOX

find $1/BE_Soft/MovieSoft/Mid/Gui/ -name "*.xlsm" -exec rm {} \;

# PHLOX DigiType ÇÃï∂éöÉRÅ[Éhïœä∑èCê≥
echo "Revert BinFile"
svn revert -R $1/BE_Soft/MovieSoft/Mid/Gui/gdi/PHLOX
svn revert -R $1/BE_Soft/MovieSoft/Mid/Gui/gdi/DigiType

rm -fr $tmpdir

echo "end..."
