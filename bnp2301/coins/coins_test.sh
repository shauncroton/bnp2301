#!/usr/bin/env sh

BINARY_FILE=${1:-"../cmake-build-debug/coins"}
INPUT_FILE=${2:-"coins_test.input"}
EXPECTED_FILE=${3:-"coins_test.expected"}
OUTPUT_FILE=${4:-"coins_test.output"}

"${BINARY_FILE}" < "${INPUT_FILE}" > "${OUTPUT_FILE}"

diff "${EXPECTED_FILE}" "${OUTPUT_FILE}"
