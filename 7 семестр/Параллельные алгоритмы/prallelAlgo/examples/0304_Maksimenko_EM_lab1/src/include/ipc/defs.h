#ifndef IPC_DEFS_H
#define IPC_DEFS_H

#include "common/defs.h"

namespace ipc
{

namespace defs
{

constexpr char inCalcProcsSocket[]  = "/tmp/in_calc_procs.sock";    ///< Путь до сокета процессов ввода и обработки.
constexpr char calcOutProcsSocket[] = "/tmp/calc_out_procs.sock";   ///< Путь до сокета процессов обработки и вывода.

}; // namespace defs

}; // namespace ipc

#endif // IPC_DEFS_H