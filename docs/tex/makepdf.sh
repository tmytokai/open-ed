#! /bin/bash

dirs="./text[0-9]*"
for dirpath in $dirs; do

DIRPATH=`basename ${dirpath}`

echo ${DIRPATH}
cd ${DIRPATH}
cp -f ../../../../../tex/makepdf-text.sh makepdf-tmp.sh
./makepdf-tmp.sh ${DIRPATH}
rm -f ./makepdf-tmp.sh
cd ..

done
