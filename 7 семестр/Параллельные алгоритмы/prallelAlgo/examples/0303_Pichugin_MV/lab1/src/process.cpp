#include "matrix.h"
using namespace std;
int main() {
	int n = 10;
	vector<vector<int>> a(n,vector<int>(n));
	vector<vector<int>> b(n, vector<int>(n));
	vector<vector<int>> c(n, vector<int>(n));
	fill_matrix(a, n);
	fill_matrix(b, n);
	int fd[2];
	int r = 0;
	int w = 1;
	
	if (pipe(fd) < 0) {
        perror("pipe:");
        return 1;
    }
	int id = fork();
    if (id == -1) { 
        perror("fork:");
        return 2;
    }
	if (id == 0) {// если процесс ребёнка 
        std::cout << "id Процесса:" << getpid()  << std::endl; //получить и вывести id процесса ребёнка
        close(fd[r]); // закрыть файловый дескриптор чтения
		multi_matrix(a, b, c, n);
        int* buf = matrix_to_array(c,n); // получить представление результирующей матрицы в виде массива
        write(fd[w], buf,sizeof(int)*n*n); // записать в канал данные
        delete[] buf; // освободить память
        exit(10); // завершение процесса
    }
	close(fd[w]); // закрыть файловый дескриптор записи
    int* parent_buf = new int[n*n]; // сгенерировать буффер
    int status = 0; 
    wait(&status);//ждём завершение дочернего процесса
    cout << "Статус процесса ребёнка: " << WEXITSTATUS(status) << endl; // статус процесса ребёнка, ожидаемый 10
    read(fd[r], parent_buf,sizeof(int)*n*n);  // читаем из файлового дескриптора, то, что записано первым процессом
    if (pipe(fd) < 0) { // создание канала не удалось
        perror("pipe:");
        return 1;
    }
	// Третий процесс - вывод результата
    id = fork();
    if (id == -1) { // создать процесс не удалось
        perror("fork:");
        return 2;
    }
    if (id == 0) {// если процесс ребёнка 
        int* buf = new int [n*n]; // создаём буффер
        close(fd[w]);  // закрываем канал записи
        read(fd[r], buf, sizeof(int)*n*n); // читаем данные из дескриптора
        write_matrix(buf,n);
        delete[] buf; // удаляем буфер
        exit(11); 
    }
    close(fd[r]); // закрываем канал чтения
    write(fd[w], parent_buf,sizeof(int)*n*n); // записываем буфер в дескриптор
    wait(&status);
    cout << "Статус процесса ребёнка: " << WEXITSTATUS(status) << endl; // статус процесса ребёнка, ожидаемый 21
    delete[] parent_buf; // удаляем буфер
	a.clear();
	b.clear();
	c.clear();
	return 0;
}