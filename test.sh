#!/bin/bash

# Path to your binary
BINARY="./philo"

# Arguments for the binary (edit this)
ARGS=("5" "800" "200" "200")

# Output file
OUTPUT="results.txt"

# Number of runs
RUNS=10

# Clear the output file before writing
> "$OUTPUT"

for i in $(seq 1 $RUNS); do
    echo "Running try $i..."

    OUTPUT_TMP=$(mktemp)

    # Run binary with timeout and arguments
    timeout 60s "$BINARY" "${ARGS[@]}" > "$OUTPUT_TMP" 2>/dev/null
    STATUS=$?

    if [ $STATUS -eq 0 ]; then
        # Success: finished within 60s
        LAST_LINE=$(tail -n 1 "$OUTPUT_TMP")
        echo "try $i: pass ($LAST_LINE)" >> "$OUTPUT"
    elif [ $STATUS -eq 124 ]; then
        # Timeout
        echo "try $i: timeout" >> "$OUTPUT"
    else
        # Some other error
        echo "try $i: error (exit code $STATUS)" >> "$OUTPUT"
    fi

    rm -f "$OUTPUT_TMP"
done

echo "Finished. Results are in $OUTPUT"

