#!/bin/bash
# Test replies

# import functions
. ./tests/common.sh

BIND_ADDR="0.0.0.0"
PORT="2727"

# run server in background
./$EXE $BIND_ADDR $PORT "" &
sleep 1

# Compare outputs

# Unknown command
assert_exec "echo foo | nc -q 1 $BIND_ADDR $PORT" ":irc.42.fr 421 foo :Unknown command" "" 0
# Wrong command format is silently ignored
assert_exec "echo 123 | nc -q 1 $BIND_ADDR $PORT" "" "" 0
# Quit
assert_exec "echo QUIT | nc -q 1 $BIND_ADDR $PORT" "" "" 0
