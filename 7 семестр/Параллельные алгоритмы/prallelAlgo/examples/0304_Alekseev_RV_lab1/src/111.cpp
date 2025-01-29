#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define NAMED_PIPE_1 "/var/lock/pipename1"
#define NAMED_PIPE_2 "/var/lock/pipename2"

#define MAT_Y 100
#define MAT_N 100
#define MAT_X 100

struct matrixes {
	int left [MAT_Y][MAT_N];
	int right [MAT_N][MAT_X];
	int result [MAT_Y][MAT_X];
};

int main(){
	pid_t pid_1;
	pid_t pid_2;

	int ret_1 = mkfifo(NAMED_PIPE_1, 0666);

	pid_1 = fork();

	switch (pid_1) {
		// Неудачная попытка создания процесса-потомка
		case -1: {
			exit(-1);
		}

		// Потомок
		// Создаем матрицы
		case 0: {
			int fd = open(NAMED_PIPE_1, O_WRONLY);
			matrixes matrixes;

			int j = 1;
			for(int y = 0; y < MAT_Y; y++) {
				for(int x = 0; x < MAT_N; x++) {
					matrixes.left[y][x] = j;
					j++;
				}
			}

			j = 1;
			for(int y = 0; y < MAT_N; y++) {
				for(int x = 0; x < MAT_X; x++) {
					matrixes.right[y][x] = j;
					j++;
				}
			}
			
			write(fd, &matrixes, sizeof(matrixes));
			close(fd);
			//std::cout<<"1CHILD:: final "<<std::endl;
			exit(0);
		}

		// Родитель
		default: {
			int ret_2 = mkfifo(NAMED_PIPE_2, 0666);

			pid_2 = fork();

			switch (pid_2) {
				// Неудачная попытка создания процесса-потомка
				case -1: {
					exit(-1);
				}

				// Потомок
				// Умножаем матрицы
				case 0: {
					int fd_1 = open(NAMED_PIPE_1, O_RDONLY);
					matrixes matrixes;
					read(fd_1, &matrixes, sizeof(matrixes));
					
					for(int y = 0; y < MAT_Y; y++) {
						for(int x = 0; x < MAT_X; x++) {
							for(int i = 0; i < MAT_N; i++) {
								matrixes.result[y][x] += matrixes.left[y][i] * matrixes.right[i][x];
							}
						}
					}

					int fd_2 = open(NAMED_PIPE_2, O_WRONLY);
					write(fd_2, &matrixes, sizeof(matrixes));
					close(fd_1);
					close(fd_2);
					exit(0);
				}

				// Родитель
				// Выводим результат
				default: {
					int fd = open(NAMED_PIPE_2, O_RDONLY);
					matrixes matrixes;
					read(fd, &matrixes, sizeof(matrixes));

					for(int y = 0; y < MAT_Y; y++) {
						for(int x = 0; x < MAT_X; x++) {
							std::cout << matrixes.result[y][x] << " ";
						}
						std::cout << std::endl;
					}

					close(fd);
					waitpid(pid_1, nullptr, 0);
					waitpid(pid_2, nullptr, 0);
				}
			}
		}
	}
	unlink(NAMED_PIPE_1);
	unlink(NAMED_PIPE_2);
	return 0;
}
