#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)

CYAN='\033[0;36m'
BLUE='\033[0;34m'
RED='\033[0;31m'
PURPLE='\033[0;35m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
RESET='\033[0m'

REAL_OUTFILE=../outfile_real
AMOUNT_OK=0

# My program
echo -e "${BLUE}My command:\t\t${RESET} ../pipex $1 \"$2\" \"$3\" $4"

echo -e "${PURPLE}Real command:\t\t${RESET} < $1 $2 | $3 $REAL_OUTFILE\n"

echo -n -e "${BLUE}My error message:\t${RESET}"
../pipex $1 "$2" "$3" $4
MY_EXITCODE=$(echo $?)
MY_OUTPUT=$(cat $4)

echo -n -e "${PURPLE}\nReal error message:\t${RESET}"
< $1 $2 | $3 > $REAL_OUTFILE
REAL_EXITCODE=$(echo $?)
REAL_OUTPUT=$(cat $REAL_OUTFILE)

echo -e "${BLUE}\n\nMy exitcode:\t\t${RESET} $MY_EXITCODE"
echo -e "${PURPLE}Real exitcode:\t\t${RESET} $REAL_EXITCODE\n"

if [ "$MY_EXITCODE" == "$REAL_EXITCODE" ]
    then
        AMOUNT_OK=$(($AMOUNT_OK + 1))
fi

echo -e "${BLUE}My output:\t${RESET} $MY_OUTPUT"
echo -e "${PURPLE}Real output:\t${RESET} $REAL_OUTPUT\n"

if [ "$MY_OUTPUT" == "$REAL_OUTPUT" ]
    then
        AMOUNT_OK=$(($AMOUNT_OK + 1))
fi

if [ $AMOUNT_OK == 2 ]
    then
        echo -e "${GREEN}OK!"
    else
        echo -e "${RED}KO!"
        EXIT_CODE=1
fi

exit $EXIT_CODE
# echo "${bold}my command:${normal}      ./pipex infile \"echo Hello World\" \"wc -w\" outfile"
# echo "${bold}my outfile${normal} =     2"
# echo -e "${bold}my exitcode${normal} =    0\n"

# echo "${bold}real command:${normal}    < infile echo \"Hello World\" | wc -w > outfile"
# echo "${bold}real outfile${normal} =   2"
# echo "${bold}real exitcode${normal} =  0"

#test 2

## my command: ./pipex infilee "echo Hello World" "wc -w" outfile
## my error message ---> File: No such file or directory
## outfile = 
## my exitcode = 0

## real command: < infilee echo "Hello World" | wc -w > outfile
## real error message: ----> zsh: no such file or directory: infilee
## outfile_real = 0
## real exitcode = 0

#test 3

## my command: ./pipex infilee "echo Hello World" "wc -w" outfile
## my error message ---> File: No such file or directory
## my exitcode = 0

## real command: < infilee echo "Hello World" | wc -w > outfile
## real error message: ----> zsh: no such file or directory: infilee
## real exitcode = 0
