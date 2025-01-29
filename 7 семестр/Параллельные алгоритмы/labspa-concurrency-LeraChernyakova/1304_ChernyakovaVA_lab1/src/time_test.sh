run_type="${1}"

case "${run_type}" in
    process)
        time {
            for i in $(seq 100); do
                ./process/start.sh
            done
        }
    ;;
    3thread)
        time {
            for i in $(seq 100); do
                ./object/3_thread 150 150 150 150
            done
        }
    ;;
    pthread)
        time {
            for i in $(seq 100); do
                ./object/p_thread 30 30 30 30 150
            done
        }
    ;;
esac