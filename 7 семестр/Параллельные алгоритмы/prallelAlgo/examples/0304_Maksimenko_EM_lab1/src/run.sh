print_usage ()
{
    echo "Usage: run.sh {processing|threading|threading-extended} [repeat-count] [threads-count]"
}

run_type="${1}"
reps_count="${2:-100}"
threads_count="${3:-8}"

case "${run_type}" in
    processing)
        TIMEFORMAT="Execution time (processing, reps=${reps_count}) real=%R user=%U sys=%S"
        time {
            for i in $(seq ${reps_count}); do
                ./target/processing
            done
        }
        mv assets/out.txt target/assets/out.processing.txt
    ;;
    threading)
        TIMEFORMAT="Execution time (threading, reps=${reps_count}) real=%R user=%U sys=%S"
        time {
            for i in $(seq ${reps_count}); do
                ./target/threading
            done
        }
        mv assets/out.txt target/assets/out.threading.txt
    ;;
    threading-extended)
        TIMEFORMAT="Execution time (threading-extended, reps=${reps_count}) real=%R user=%U sys=%S"
        time {
            for i in $(seq "${reps_count}"); do
                ./target/threading_extended "${threads_count}"
            done
        }
        mv assets/out.txt target/assets/out.extended.txt
    ;;
    *)
        print_usage
        exit 1
    ;;
esac
