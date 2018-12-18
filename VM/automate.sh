#!/bin/bash

CYCLES=$1

CHAMP=$2

./corewar -dump $CYCLES $CHAMP

while true; do
	echo $CYCLES

	read input

	MATCH=$(echo $input | grep -Eo '[+-][0-9]{1,}')

	JUMP=$(echo $MATCH | cut -c 2-)

	OPERAND=$(echo $MATCH | head -c 1)

	if [[ $JUMP -gt 0 ]]; then
		if [[ $OPERAND = "+" ]]; then
			CYCLES=$((CYCLES + JUMP))
		elif [[ $OPERAND = "-" ]]; then
			CYCLES=$((CYCLES - JUMP))
		fi
		if [[ $CYCLES -le 0 ]]; then
			CYCLES=$((1))
			./corewar -dump $CYCLES $CHAMP
			echo "Cycles can't get under 0, cyka blyat..."
		else
			./corewar -dump $CYCLES $CHAMP
		fi
	else
		if [[ $input = "+" ]]; then
			CYCLES=$((CYCLES + 100))
			./corewar -dump $CYCLES $CHAMP
		fi
		if [[ $input = "-" ]]; then
			CYCLES=$((CYCLES - 100))
			if [[ $CYCLES -le 0 ]]; then
				CYCLES=$((1))
				./corewar -dump $CYCLES $CHAMP
				echo "Cycles can't get under 0, cyka blyat..."
			else
				./corewar -dump $CYCLES $CHAMP
			fi
		fi
	fi
done
