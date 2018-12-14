#!/bin/bash

ASM="asm"
EXEC_PATH=".."
EXEC_PATH_ZAZ="../../vm_champs"
SRC="../../vm_champs/champs"
DEST="src"
DEST_ION="dst_ion"
DEST_ZAZ="dst_zaz"
FILE_DST="res_tst"
DIFF="-diff"

# Colors settings
ION='\033[1;36m'
ZAZ='\033[1;32m'
OK='\033[0;32m'
KO='\033[0;31m'
NC='\033[0m'


mkdir $DEST 2> /dev/null || true
mkdir $DEST_ION 2> /dev/null || true
mkdir $DEST_ZAZ 2> /dev/null || true
rm -rf $DEST/*
rm -rf $DEST_ION/*
rm -rf $DEST_ZAZ/*

cp -r $SRC/* $DEST

for f in $DEST/*.s ; do
	cp "$f" $DEST_ION
	cp "$f" $DEST_ZAZ
done

for f in $DEST/*/*.s ; do
	cp "$f" $DEST_ION
	cp "$f" $DEST_ZAZ
done

cp $EXEC_PATH/$ASM $DEST_ION
cp $EXEC_PATH_ZAZ/$ASM $DEST_ZAZ

chmod 744 $DEST_ION/*
chmod 744 $DEST_ZAZ/*

for f in $DEST_ION/*.s ; do
   file="$(echo "$f" | rev | cut -d '/' -f 1 | rev)"
   if [[ $1 = $DIFF ]]; then
       echo -e "${ION}ION${NC} |$f| :" `$DEST_ION/$ASM $DEST_ION/$file`
       echo -e "${ZAZ}ZAZ${NC} |$f| :" `$DEST_ZAZ/$ASM $DEST_ZAZ/$file`
       echo ""
   else
       echo -e "${ION}ION${NC} |$f| :" `$DEST_ION/$ASM $DEST_ION/$file` > /dev/null
       echo -e "${ZAZ}ZAZ${NC} |$f| :" `$DEST_ZAZ/$ASM $DEST_ZAZ/$file` > /dev/null
   fi
done

for f in $DEST_ION/*.cor ; do
	spl="$(echo "$f" | rev | cut -d '/' -f 1 | rev)"
	spl2=`echo $spl | cut -d '.' -f 1`
	rm $DEST_ION/$spl2.hex 2> /dev/null || true
	hexdump "$f" > $DEST_ION/$spl2.hex
done

for f in $DEST_ZAZ/*.cor ; do
	spl="$(echo "$f" | rev | cut -d '/' -f 1 | rev)"
	spl2=`echo $spl | cut -d '.' -f 1`
	rm $DEST_ZAZ/$spl2.hex 2> /dev/null || true
	hexdump "$f" > $DEST_ZAZ/$spl2.hex
done

for f in $DEST_ION/*.hex ; do
	spl="$(echo "$f" | rev | cut -d '/' -f 1 | rev)"
    diff=`diff "$f" $DEST_ZAZ/$spl`
    if [ `echo -n $diff | wc -m` -eq 0 ]; then
        printf "\n`echo $spl : [${OK}OK${NC}] $diff`\n\n"
    else
        printf "\n`echo $spl : [${KO}KO${NC}] $diff`\n\n"
    fi
done
