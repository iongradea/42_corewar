#!/bin/bash

ZAZ_CHAMPS_DIR="../../vm_champs/champs"
TST_CHAMPS_DIR="../../VM/tests"
EXEC_PATH=".."
EXEC="asm"

if [ ! -d $ZAZ_CHAMPS_DIR ]; then
	echo "Champ dir doesn't exist"
	exit 1
fi

if [ ! -d $TST_CHAMPS_DIR ]; then
	echo "Test dir doesn't exist"
	exit 1
fi

if [ ! -f ${EXEC_PATH}/${EXEC} ]; then
	echo "asm binary doesn't exist"
	exit 1
elif [ -f ${EXEC_PATH}/${EXEC} ] && [ ! -x ${EXEC_PATH}/${EXEC} ]; then
	echo "asm file is not an executable"
	exit 1
fi

for f in $ZAZ_CHAMPS_DIR/*.s ; do
	./$EXEC_PATH/$EXEC "$f"
done

for f in $TST_CHAMPS_DIR/*.s ; do
	./$EXEC_PATH/$EXEC "$f"
done
