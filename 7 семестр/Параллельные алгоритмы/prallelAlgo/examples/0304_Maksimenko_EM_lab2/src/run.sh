print_usage ()
{
    echo "Usage: run.sh [repeat-count] [threads-count] [producers-count] [consumers-count] [tasks-count]"
}

reps_count="${1:-1}"
shift

echo "threading $@"
TIMEFORMAT="Execution time (threading, reps=${reps_count}) real=%R sec, user=%U sec, sys=%S sec"
time {
    for i in $(seq ${reps_count}); do
        ./target/threading "$@"
    done
}
