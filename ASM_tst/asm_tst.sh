#!/bin/bash

ASM="asm"
EXEC_PATH="../ASM"
EXEC_PATH_ZAZ="../vm_champs"
SRC="../vm_champs/champs"
DEST="src"
DEST_ION="dst_ion"
DEST_ZAZ="dst_zaz"

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

for f in $DEST_ION/*.s ; do
	printf "`echo "ION |$f| :"` `$DEST_ION/$ASM "$f"`\n"
done

for f in $DEST_ZAZ/*.s ; do
	printf "`echo "ZAZ |$f| :"` `$DEST_ZAZ/$ASM "$f"`\n"
done
