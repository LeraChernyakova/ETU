#include "head.h" 
static void handler( int signo, siginfo_t* info, void* context ) { 
   cout << "CHILD\t[" << getpid() << ":" << getppid() << "] : " 
        << "received signal " << signo << endl; 
}; 
 int main( int argc, char *argv[] ) { 
   int opt, val, beg = _SIGMAX, num = 3, fin = _SIGMAX - num, seq = 3; 
   bool wait = false; 
   while ( ( opt = getopt( argc, argv, "b:e:n:w") ) != -1 ) { 
      switch( opt ) { 
         case 'b' : if( atoi( optarg ) > 0 ) beg = atoi( optarg ); break; 
         case 'e' : 
            if( ( atoi( optarg ) != 0 ) && ( atoi( optarg ) < _SIGMAX ) ) fin = atoi( optarg ); 
            break;
         case 'n' : if( atoi( optarg ) > 0 ) seq = atoi( optarg ); break; 
         case 'w' : wait = true; break; 
         default : 
            cout << "usage: " << argv[ 0 ] 
                 << " [-b #signal] [-e #signal] [-n #loop] [-w]" << endl;
            exit( EXIT_FAILURE ); 
            break;
      } 
   }; 
   num = fin - beg; 
   fin += num > 0 ? 1 : -1; 
   sigset_t sigset; 
   sigemptyset( &sigset ); 
   for( int i = beg; i != fin; i += ( num > 0 ? 1 : -1 ) ) sigaddset( &sigset, i ); 
   pid_t pid;
   if( pid = fork() == 0 ) { 
      // дочерний процесс: здесь сигналы обрабатываются 
      sigprocmask( SIG_BLOCK, &sigset, NULL ); 
      for( int i = beg; i != fin; i += ( num > 0 ? 1 : -1 ) ) { 
         struct sigaction act, oact; 
         sigemptyset( &act.sa_mask ); 
         act.sa_sigaction = handler; 
         act.sa_flags = SA_SIGINFO;         // вот оно - реальное время! 
         if( sigaction( i, &act, NULL ) < 0 ) perror( "set signal handler: " ); 
      }; 
      cout << "CHILD\t[" << getpid() << ":" << getppid() << "] : " 
           << "signal mask set" << endl; 
      sleep( 3 );                           // пауза для отсылки сигналов родителем 
      cout << "CHILD\t[" << getpid() << ":" << getppid() << "] : " 
           << "signal mask unblock" << endl; 
      sigprocmask( SIG_UNBLOCK, &sigset, NULL ); 
      sleep( 3 );                           // пауза для получения сигналов 
      cout << "CHILD\t[" << getpid() << ":" << getppid() << "] : " 
           << "finished" << endl; 
      exit( EXIT_SUCCESS ); 
   } 
   // родительский процесс: отсюда сигналы посылаются 
   sigprocmask( SIG_BLOCK, &sigset, NULL ); 
   sleep( 1 );                               // пауза для установок дочерним процессом 
   for( int i = beg; i != fin; i += ( num > 0 ? 1 : -1 ) ) { 
      for( int j = 0; j < seq; j++ ) { 
         kill( pid, i ); 
         cout << "PARENT\t[" << getpid() << ":" << getppid() << "] : " 
              << "signal sent: " << i << endl; 
      }; 
   }; 
   if( wait ) waitpid( pid, NULL, 0 ); 
   cout << "PARENT\t[" << getpid() << ":" << getppid() << "] : " 
        << "finished" << endl; 
   exit( EXIT_SUCCESS ); 
}; 