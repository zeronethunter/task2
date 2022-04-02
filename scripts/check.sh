#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck . -i./build/ --enable=all --force --inconclusive --error-exitcode=1 -I ./libs/temperature_lib ./libs/buffer_lib --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ./src/*.c ./libs/temperature_lib/src/async/*.c ./libs/temperature_lib/src/sync/*.c ./libs/temperature_lib/include/*.h ./libs/buffer_lib/src/*.c ./libs/buffer_lib/include/*.h -warnings-as-errors=* -extra-arg=-std=c99 -- -I./libs/temperature_lib/include -I./libs/buffer_lib/include" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c,h --filter=-readability/casting,-build/header_guard,-build/include_subdir libs/temperature_lib/src/async/* libs/temperature_lib/src/sync/* libs/buffer_lib/src/* libs/temperature_lib/include/* libs/buffer_lib/include/* src/*" "Can't open for reading"

print_header "SUCCESS"
