[ -n "$_BENCHMARK_LIB" ] && return || readonly _BENCHMARK_LIB=1

declare -r TIMEFORMAT="Elapsed time: %U sec (user), %S (system), %R (real)"

function benchmark()
{
  local -r command="${1}"
  local -r count="${2:-1}"
  time {
    for i in $(seq "${count}"); do
      ${command} > out.txt
      if [ "${?}" != 0 ]; then
        break
      fi
    done
  }
}
