#!/usr/bin/bash

# Split
printf "\n"

# COUNT DIRECTORY SIZE
echo Directory Size Is:
du --exclude=.git --exclude=.vscode -sh ./

# Split Output
printf "\n"

# COUNT ENTRANCE OF FILES
echo -ne " LINES:\t WORDS:\t CHARS:\t BYTES:\n"
wc -lwmc *

# Split
printf "\n"
