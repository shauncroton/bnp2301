#!/usr/bin/env sh

BINARY_FILE=${1:-"../cmake-build-debug/median"}
INPUT_FILE=${2:-"median_test.input"}
EXPECTED_FILE=${3:-"median_test.expected"}
OUTPUT_FILE=${4:-"median_test.output"}

"${BINARY_FILE}" < "${INPUT_FILE}" > "${OUTPUT_FILE}"

diff "${EXPECTED_FILE}" "${OUTPUT_FILE}"
