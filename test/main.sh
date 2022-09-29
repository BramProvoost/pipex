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

TOTAL_KO=0
## this script runs several tests with the ./pipex executable.
## Each test checks whether the output (displayed in the outfile) is the same;
## whether the exitcodes and in case of error, the error messages are the same

echo -e "${BLUE}============================ ${PURPLE}MY PIPEX TESTER${BLUE} ===================================\n"
printf "$RESET"

#test 1 - valid test
echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 1 - valid test" # valid arguments
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "echo Hello World" "wc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 2 - valid test" # valid arguments (command with flag)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "ls -la" "wc -l" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 3 - valid test" # valid arguments (command with flag and extra input)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "grep -c unix" "wc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 4 - input file does not exist" # infile does not exist (second command should be executed)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infilee "echo Hello World" "wc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 5 - first command does not exist" # first command does not exist(second command should only be executed)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "echsdo Hello World" "wc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 6 - flag of first command does not exist" # first command flag does not exist(second command should only be executed)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "ls -=" "wc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 7 second command does not exist" # second command does not exist (first command should only be executed)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "echo Hello World" "wdc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 8 - flag of second command does not exist" # second command flag does not exist (first command should only be executed)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "echo Hello World" "wdc -w" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 9 - both commands do not exist" # both commands do not exist
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "seddd "s/unix/linux/"" casft ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 10 - both flags do not exist" # both flags do not exist
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "sed "s/unix/linux"" "wc -jasf" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 11 - special case 'sed'" # sed
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "sed "s/unix/linux/"" cat ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 12 - first command does not exist, second command does not need input" # first command does not exist, second command does not need input
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile hello "ls hi" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 13 - input file does not have the executable rights" # first command does not exist, second command does not need input
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../xfile hello "ls hi" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 14 - commands passed with full path" # first command does not exist, second command does not need input
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "/bin/ls -la" "/usr/bin/wc -l" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 15 - not existing commands passed with full path" # first command does not exist, second command does not need input
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "/bin/lsdsd -la" "/usr/bin/wc -l" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 16 " # first command does not exist, second command does not need input
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infiledsd "cat /dev/random" "wc" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 17 " # first command does not exist, second command does not need input
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

VAR1="hello"
VAR2="world"
bash test.sh ../env_var "/dev/null" "cat" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 18 - input file does not exist" # infile does not exist (second command should be executed)
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infilee "echo Hello World" "ls -la" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 19" 
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "/bin/ls -la" "/usr/bin/wcfs" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 20" 
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "ls -la" "wc -lagdg" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "${ORANGE}--------------------------------------------------------------------------------"
echo -e "TEST 21"
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

bash test.sh ../infile "ls -ladsf" "wc -lagdg" ../outfile
EXIT_CODE=$?
TOTAL_KO=$(($TOTAL_KO + $EXIT_CODE))

echo -e "\n${ORANGE}--------------------------------------------------------------------------------"
if [ $TOTAL_KO == 0 ]
    then
        echo -e "${GREEN}YOU PASSED!" # second command flag does not exist (first command should only be executed)
    else
        echo -e "${RED} YOU FAILED $TOTAL_KO OF 21 TESTS"
fi
echo -e "${ORANGE}--------------------------------------------------------------------------------${RESET}"

echo -e "\nAll done!"
