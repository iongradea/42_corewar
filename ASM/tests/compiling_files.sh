#!/bin/bash

ZAZ_CHAMPS_DIR="../../vm_champs/champs"
TST_CHAMPS_DIR="../../VM/tests"
EXEC_PATH=".."
EXEC="asm"

for f in $ZAZ_CHAMPS_DIR/*.s ; do
	./$EXEC_PATH/$EXEC "$f"
done

for f in $TST_CHAMPS_DIR/*.s ; do
	./$EXEC_PATH/$EXEC "$f"
done
