#!/bin/bash

# Define color
YEL='\033[1;33m'
GRE='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

USAGE="./automate.sh [cycle number] [champion path]"

if [ ${#1} -eq 0 ]; then
	echo -e ${RED}"you must provide a cycle number"${NC}
	echo $USAGE
	exit 1
elif [ ${#2} -eq 0 ]; then
	echo -e ${RED}"you must provide a champion"${NC}
	echo $USAGE
	exit 1
elif [ ${#3} -gt 0 ]; then
	echo -e ${RED}"you must provide 2 arguments"${NC}
	echo $USAGE
	exit 1
elif [ ! -f "./corewar" ]; then
	echo -e ${RED}"Corewar isn't in current dir"${NC}
	read "corewar path: " input 
	if [ -f input ]; then
		echo -e ${RED}"Invalid dir, bye"${NC}
		exit 1
	fi
fi

# Take one arg, and int, return 1 if variable is an INT or 0 if not
function	ft_is_int()
{
	# Check if value is numeric
	if [ "$1" -eq "$1" ] 2>/dev/null
	then
		return 0
	else
		echo -e ${RED}"Value '`echo $1`' isn't numeric"${NC}
		return 1
	fi
}

# Check argument integrity
if ! ft_is_int $1 ; then
	exit 1
fi

if [ ! -f $2 ]; then
	echo -e ${RED}"Value '`echo $2`' isn't a valid path"${NC}
	exit 1
elif [ $1 -eq 0 ]; then
	echo -e ${RED}"argument must be positive"${NC}
	exit 1
fi

CYCLES=$1
CHAMP=$2

# Execute corewar binary with dump option
./corewar -dump $CYCLES $CHAMP

while true; do
	echo "Cycle: "$CYCLES

	read input

	MATCH=$(echo $input | grep -Eo '[+-][0-9]{1,}')
	MATCH_OP=$(echo $input | grep -Eo '[+-]')

	if [ ${#MATCH} -eq 0 ] && [ ${#MATCH_OP} -eq 0 ]; then
		MATCH_NB=$(echo $input | grep -Eo '[0-9]{1,}')
	fi

	if [ ${#MATCH} -ne 0 ]; then
		JUMP=$(echo $MATCH | cut -c 2-)
		OPERAND=$(echo $MATCH | head -c 1)
	elif [ ${#MATCH_OP} -ne 0 ]; then
		OPERAND=$input
	elif [ ${#MATCH_NB} -ne 0 ]; then
		CYCLES=$input
	elif [ ${#OPERAND} -eq 0 ] || [ $CYCLES -eq 1 ]; then
		OPERAND=+
	fi

	if [ ${#MATCH_NB} -ne 0 ]; then
		./corewar -dump $CYCLES $CHAMP
	elif [[ $JUMP -gt 0 ]]; then
		if [[ $OPERAND = "+" ]]; then
			CYCLES=$((CYCLES + JUMP))
		elif [[ $OPERAND = "-" ]]; then
			CYCLES=$((CYCLES - JUMP))
		fi
		if [[ $CYCLES -le 0 ]]; then
			CYCLES=$((1))
			./corewar -dump $CYCLES $CHAMP
			echo -e ${YEL}"Cycles can't get under 0, cyka blyat..."${NC}
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
				echo -e ${YEL}"Cycles can't get under 0, cyka blyat..."${NC}
			else
				./corewar -dump $CYCLES $CHAMP
			fi
		else
			if [ ${#JUMP} -eq 0 ]; then
				JUMP=100
			fi
			CYCLES=$(($JUMP $OPERAND $CYCLES))
			./corewar -dump $CYCLES $CHAMP
		fi
	fi
done
