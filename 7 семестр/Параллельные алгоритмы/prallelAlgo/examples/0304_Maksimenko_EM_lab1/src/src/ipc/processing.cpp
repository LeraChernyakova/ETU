#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "common/matrix.h"
#include "ipc/defs.h"
#include "ipc/socket.h"
#include "ipc/matrix_algorithms.h"


namespace ipc
{

enum class ProcessType
{
	ReadProcess,
	CalcProcess,
	WriteProcess,
	Unknown
}; // enum class ProcessType


bool ReadProcessDo( ipc::Socket& readCalcSocket );
bool CalcProcessDo( ipc::Socket& readCalcSocket, ipc::Socket& calcWriteSocket );
bool WriteProcessDo( ipc::Socket& calcWriteSocket );

} // namespace ipc


int main()
{
	ipc::ProcessType ptype = ipc::ProcessType::Unknown;
	int socketPairRC[2];
	if ( -1 == socketpair( AF_LOCAL, SOCK_STREAM, 0, socketPairRC ) )
	{
		std::cerr << "Unable to create socket pair for read and calc processes\n";
		return 1;
	}
	pid_t forkedRC = fork();

	switch ( forkedRC )
	{
		case -1: // fork error
			std::cerr << "Unable to fork (read and calc)\n";
			return 1;
		case 0: // child (calc process)
			ptype = ipc::ProcessType::CalcProcess;
		break;
		default: // parent (read process)
			ptype = ipc::ProcessType::ReadProcess;
		break;
	}

	int socketPairCW[2];
	pid_t forkedCW = 0;
	if ( ipc::ProcessType::CalcProcess == ptype )
	{
		if ( -1 == socketpair( AF_LOCAL, SOCK_STREAM, 0, socketPairCW ) )
		{
			std::cerr << "Unable to create socket pair for calc and write processes\n";
			return 1;
		}
		forkedCW = fork();

		switch ( forkedCW )
		{
			case -1: // fork error
				std::cerr << "Unable to fork (calc and write)\n";
				return 1;
			case 0: // child (write process)
				ptype = ipc::ProcessType::WriteProcess;
			break;
			default: // parent (calc process)
				ptype = ipc::ProcessType::CalcProcess;
			break;
		}
	}

	switch ( ptype )
	{
		case ipc::ProcessType::ReadProcess:
		{
			ipc::Socket readCalcSocket{ socketPairRC[ 0 ] };
			if ( !ReadProcessDo( readCalcSocket ) )
			{
				(void) waitpid( forkedRC, nullptr, 0 );
				return 1;
			}
			(void) waitpid( forkedRC, nullptr, 0 );
			break;
		}
		case ipc::ProcessType::CalcProcess:
		{
			ipc::Socket readCalcSocket{ socketPairRC[ 1 ] };
			ipc::Socket calcWriteSocket{ socketPairCW[ 0 ] };
			if ( !CalcProcessDo( readCalcSocket, calcWriteSocket ) )
			{
				(void) waitpid( forkedCW, nullptr, 0 );
				return 1;
			}
			(void) waitpid( forkedCW, nullptr, 0 );
			break;
		}
		case ipc::ProcessType::WriteProcess:
		{
			ipc::Socket calcWriteSocket{ socketPairCW[ 1 ] };
			if ( !WriteProcessDo( calcWriteSocket ) )
			{
				return 1;
			}
			break;
		}
		default:
		return 1; // never here
	}
	return 0;
}


namespace ipc
{

bool ReadProcessDo( ipc::Socket& readCalcSocket )
{
	common::Matrix lhs{ 0, 0 };
	common::Matrix rhs{ 0, 0 };
	/// Чтение матриц из файла
    std::ifstream inStream( common::defs::inFile, std::ios_base::in );
    if ( !inStream.is_open() )
    {
        std::cerr << "Cannot open file " << common::defs::inFile << '\n';
        return false;
    }

    if ( !common::Matrix::read( lhs, inStream ) )
    {
        std::cerr << "Bad data for lhs matrix\n";
        return false;
    }
    if ( !common::Matrix::read( rhs, inStream ) )
    {
        std::cerr << "Bad data for rhs matrix\n";
        return false;
    }
    /// Отправка данных второму процессу
    if ( !readCalcSocket.isValid() )
    {
    	std::cerr << "read-calc socket is invalid\n";
    	return false;
    }
    if ( !common::Matrix::write( lhs, readCalcSocket ) )
    {
        std::cerr << "Could not send lhs matrix\n";
        return false;
    }
    if ( !common::Matrix::write( rhs, readCalcSocket ) )
    {
        std::cerr << "Could not send rhs matrix\n";
        return false;
    }

    return true;
} // ReadProcess


bool CalcProcessDo( ipc::Socket& readCalcSocket, ipc::Socket& calcWriteSocket )
{
	common::Matrix lhs{ 0, 0 };
	common::Matrix rhs{ 0, 0 };
	common::Matrix result{ 0, 0 };
	/// Получение данных от первого процесса
	if ( !readCalcSocket.isValid() )
    {
    	std::cerr << "read-calc socket is invalid\n";
    	return false;
    }
    if ( !common::Matrix::read( lhs, readCalcSocket ) )
    {
        std::cerr << "Could not receive lhs matrix\n";
        return false;
    }
    if ( !common::Matrix::read( rhs, readCalcSocket ) )
    {
        std::cerr << "Could not receive rhs matrix\n";
        return false;
    }
	/// Умножение матриц
    result = ipc::multiplyMatrices( lhs, rhs );
    /// Отправка данных третьему процессу
    if ( !calcWriteSocket.isValid() )
    {
    	std::cerr << "calc-write socket is invalid\n";
    	return false;
    }
    if ( !common::Matrix::write( result, calcWriteSocket ) )
    {
        std::cerr << "Could not send result matrix\n";
        return false;
    }
    return true;
} // CalcProcess


bool WriteProcessDo( ipc::Socket& calcWriteSocket )
{
	common::Matrix result{ 0, 0 };
	/// Получение данных от второго процесса
    if ( !calcWriteSocket.isValid() )
    {
    	std::cerr << "calc-write socket is invalid\n";
    	return false;
    }
    if ( !common::Matrix::read( result, calcWriteSocket ) )
    {
        std::cerr << "Could not receive result matrix\n";
        return false;
    }
	/// Вывод результата в файл
    std::ofstream outStream( common::defs::outFile, std::ios_base::out | std::ios_base::trunc );
    if ( !outStream.is_open() )
    {
        std::cerr << "Cannot open file " << common::defs::outFile << '\n';
        return false;
    }

    if ( !common::Matrix::write( result, outStream ) )
    {
        std::cerr << "Could not write result matrix\n";
        return false;
    }

    return true;
} // WriteProcess

} // namespace ipc
