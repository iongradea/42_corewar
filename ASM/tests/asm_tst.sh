#!/bin/bash

ASM="asm"
EXEC_PATH=".."
EXEC_PATH_ZAZ="../../vm_champs"
SRC="../../vm_champs/champs"
DEST="src"
DEST_ION="dst_ion"
DEST_ZAZ="dst_zaz"
FILE_DST="res_tst"

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
rm $FILE_DST 2> /dev/null || true
touch $FILE_DST

for f in $DEST_ION/*.s ; do
	printf "`echo "ION |$f| :"` `$DEST_ION/$ASM "$f"`\n" >> $FILE_DST
done

for f in $DEST_ZAZ/*.s ; do
	printf "`echo "ZAZ |$f| :"` `$DEST_ZAZ/$ASM "$f"`\n" >> $FILE_DST
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
	printf "\n`echo $spl : ` `diff "$f" $DEST_ZAZ/$spl`\n\n"
done
