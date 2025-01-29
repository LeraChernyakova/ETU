#!/bin/bash

cd ./cmake-build-debug/ || exit
echo "" > text_results.txt

n=100
matrix_size=40
multi_threads_count=5

for producer_count in 50; do
        max_value=0

        for (( i = 1; i <= n; i++ )); do
            result=$(./0304_Aristarkhov_Ilya_lab3 "$producer_count" "$multi_threads_count" "$matrix_size")
            max_value=$((max_value<result ? result : max_value))
            echo "Calculating...i: $i/$n; producer_count: $producer_count; multi_threads_count: $multi_threads_count; matrix_size:$matrix_size; > $max_value"

        done

        echo "Calculating...        producer_count: $producer_count; multi_threads_count: $multi_threads_count; matrix_size:$matrix_size; > $max_value"
        echo "is_fine: producer_count: $producer_count; multi_threads_count: $multi_threads_count; matrix_size:$matrix_size; > $max_value" >> text_results.txt

    done

