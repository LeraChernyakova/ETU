print_usage ()
{
    echo "Usage: run.sh [repeat-count] ..."
}

reps_count="${1:-1}"
shift

echo "lab4 $@"
TIMEFORMAT="Execution time (lab4, reps=${reps_count}) real=%R sec, user=%U sec, sys=%S sec"
time {
    for i in $(seq ${reps_count}); do
        target/lab4 "$@"
    done
}
