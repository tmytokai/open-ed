#! /bin/bash

dirs="./page[0-9]*"
for dirpath in $dirs; do

DIRPATH=`basename ${dirpath}`

echo ${DIRPATH}
cd ${DIRPATH}
cp -f ../../../../../../tex/makepdf-page.sh makepdf-tmp.sh
./makepdf-tmp.sh $1 ${DIRPATH}
rm -f ./makepdf-tmp.sh
cd ..

done
