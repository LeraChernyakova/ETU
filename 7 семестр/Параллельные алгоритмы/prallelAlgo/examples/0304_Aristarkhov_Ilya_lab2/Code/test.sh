#!/bin/bash

cd ./cmake-build-debug/ || exit
echo "" > text_results.txt

n=1
matrix_size=40
multi_threads_count=5

for is_fine in 0 1; do
    for producer_count in 1 5 10 20 50; do
        max_value=0

        for (( i = 1; i <= n; i++ )); do
            result=$(./PA_Lab_2 "$is_fine" "$producer_count" "$multi_threads_count" "$matrix_size")
            max_value=$((max_value<result ? result : max_value))
            echo "Calculating...i: $i/$n; is_fine: $is_fine; producer_count: $producer_count; multi_threads_count: $multi_threads_count; matrix_size:$matrix_size; > $max_value"

        done

        echo "Calculating...        is_fine: $is_fine; producer_count: $producer_count; multi_threads_count: $multi_threads_count; matrix_size:$matrix_size; > $max_value"
        echo "is_fine: $is_fine; producer_count: $producer_count; multi_threads_count: $multi_threads_count; matrix_size:$matrix_size; > $max_value" >> text_results.txt

    done
done

