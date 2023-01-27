#!/usr/bin/env sh

BINARY_FILE=${1:-"../cmake-build-debug/squares"}
INPUT_FILE=${2:-"squares_test.input"}
EXPECTED_FILE=${3:-"squares_test.expected"}
OUTPUT_FILE=${4:-"squares_test.output"}

"${BINARY_FILE}" < "${INPUT_FILE}" > "${OUTPUT_FILE}"

diff "${EXPECTED_FILE}" "${OUTPUT_FILE}"
