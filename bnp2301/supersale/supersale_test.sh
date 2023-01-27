#!/usr/bin/env sh

BINARY_FILE=${1:-"../cmake-build-debug/supersale"}
INPUT_FILE=${2:-"supersale_test.input"}
EXPECTED_FILE=${3:-"supersale_test.expected"}
OUTPUT_FILE=${4:-"supersale_test.output"}

"${BINARY_FILE}" < "${INPUT_FILE}" > "${OUTPUT_FILE}"

diff "${EXPECTED_FILE}" "${OUTPUT_FILE}"
