#! /bin/bash

TEXFILE=tmp/$2.tex
#DVIFILE=$2.dvi
#PDFFILE=$2.pdf

mkdir -p tmp

echo \\documentclass[a4paper]{jlreq}           >  ${TEXFILE}
echo \\def\\rootdir{../../}                   >>  ${TEXFILE}
echo \\def\\texdir{../../../../../../tex}     >>  ${TEXFILE}
echo \\input{\\texdir/common-exam-lua}        >>  ${TEXFILE}
echo \\def\\examname{過去問一覧}              >>  ${TEXFILE}
echo \\def\\examdate{}                        >>  ${TEXFILE}

dirs="./[0-9]*"
for dirpath in $dirs; do

DIRPATH=`basename ${dirpath}`
QFILE=tmp/${DIRPATH}.tex

echo \\readinfo{tmp/${DIRPATH}}               >>  ${TEXFILE}

echo \\def\\qpath{$1/$2/${DIRPATH}}            >  ${QFILE}
echo \\def\\qpoint{10}                        >>  ${QFILE}
echo \\def\\afile{a1}                         >>  ${QFILE}
echo \\def\\bfile{a2}                         >>  ${QFILE}
echo \\def\\cfile{a3}                         >>  ${QFILE}
echo \\def\\dfile{a4}                         >>  ${QFILE}

done

echo \\begin{document}                       >>  ${TEXFILE}
echo \\Large                                 >>  ${TEXFILE}
echo \\initbb                                >>  ${TEXFILE}
echo %\\makeq[f]                             >>  ${TEXFILE}
echo \\makeq[q]                              >>  ${TEXFILE}
echo \\end{document}                         >>  ${TEXFILE}

lualatex ${TEXFILE}
#dvipdfmx ${DVIFILE}

rm -f *.aux *.log *.dvi *~
rm -rf ./tmp
