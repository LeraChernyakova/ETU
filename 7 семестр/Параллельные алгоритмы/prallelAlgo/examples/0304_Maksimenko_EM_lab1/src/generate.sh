in_file="assets/in.txt"
lower_bound=-3
upper_bound=3

generate_matrix()
{
    local -r rows="${1:-0}"
    local -r columns="${2:-0}"
    local element

    if [ "${rows}" = 0 ] || [ "${columns}" = 0 ]; then
        echo "rows or columns are empty"
        exit 1
    fi

    echo "${rows} ${columns}" >>"${in_file}"
    for i in $(seq $rows); do
        for j in $(seq $columns); do
            element="$((lower_bound+RANDOM%(upper_bound-lower_bound))).$((RANDOM%999))"
            echo -n "${element} " >>"${in_file}"
        done
        echo "" >>"${in_file}"
    done
}

if [ $# -ne 3 ]; then
    echo "Usage: generate.sh int int int" >&2
    exit 1
fi

>"${in_file}"
generate_matrix "$1" "$2"
generate_matrix "$2" "$3"