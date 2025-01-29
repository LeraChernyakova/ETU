#ifndef LAB1_COMMON_H
#define LAB1_COMMON_H

#include <cstddef>

class Socket;
class UnixSocket;
class Matrix;

constexpr char indata_socket[] = "/tmp/in_socket";
constexpr char outdata_socket[] = "/tmp/out_socket";

bool read_sizes( int argc, char *argv[], std::size_t *sizes );

bool make_server( UnixSocket& socket );
bool make_client( UnixSocket& socket );

bool read_matrix( Socket& socket, Matrix& matr );
bool write_matrix( Socket& socket, const Matrix& matr );

#endif // LAB1_COMMON_H
