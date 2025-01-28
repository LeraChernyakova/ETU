#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;

//Класс хранение: размер матрицы(квадрата), пропорция(делитель), 
//данный/оптимальный количество квадратов и 2 двухмерных данного/оптимального массива квадрата
class SISS {
    int square_size, proportion, cur_count, optimal_count;
    std::vector<std::vector<int>> optimal_square, cur_square;

public:

	//принимает на вход размер квадрата
    SISS(int n) : square_size(n), proportion(1), cur_count(0), optimal_count(n * n){
		Min_Prime_Nums();   // поиск минимальный простой делитель

        optimal_square = std::vector<std::vector<int>>(square_size, std::vector<int>(square_size, 0));
        cur_square = std::vector<std::vector<int>>(square_size, std::vector<int>(square_size, 0));
        		
        Fill(0, 0, (square_size + 1) / 2);                                    // Самые большие квадраты
        Fill((square_size + 1) / 2, 0, square_size - (square_size + 1) / 2);  // Которые уменьшают площади работы backtracking 
        Fill(0, (square_size + 1) / 2, square_size - (square_size + 1) / 2);  // и ускоряют работу программы
        
        backtracking(square_size / 2, square_size / 2, square_size);
        optimal_square = cur_square;
    }

// в этом методе находится минимальный простой делитель
// для возврата в оригинальный размер при выводе 
// и меняется размер матрицы(квадрата)
// для уменьшение площади работы backtracking
	void Min_Prime_Nums(){                            
		for(int i = 3; i < square_size / 2; i++){    
            if(square_size % i == 0){                 
                proportion = square_size / i;        
                square_size = i;
                break;
            }
        }
	}


// в этом методе добавляется квадрат в optimal_square
// после увеличивается cur_count
	void Fill(int Y, int X, int size){              
        for(int y = Y; y < Y + size; y++){          
            for(int x = X; x < X + size; x++){
                if(optimal_square[y][x] == 0){
                    optimal_square[y][x] = -1;
                }
            }
        }
        optimal_square[Y][X] = size;
        cur_count++;
    }

// в этом методе происходит перебор всех вариантов расстановки
// и находит оптимальную расстановку квадрата
    void backtracking(int start_y, int start_x, int end){
        if(optimal_count <= cur_count){                  
            return;
        }
        int max_size = std::min(end - start_y, end - start_x);
        if(optimal_square[start_y][start_x] == 0){
            for(int i = max_size; i > 0; i--){
                if(Controlled_Fill(start_y, start_x, i)){
                    Next_backtracking(start_y, start_x, end, i);
                    Remove(start_y, start_x, i);
                }
            }
        }else{
            Next_backtracking(start_y, start_x, end, 1);
        }
    }

// в этом методе проверяется возможность добавления квадрата
// в площади работы backtracking
// учитывается выход из границы и занятая область
	bool Controlled_Fill(int Y, int X, int size){            
        if(Y + size > square_size || X + size > square_size){
            return false;                                    
        }
        for(int y = Y; y < Y + size; y++){
            for(int x = X; x < X + size; x++){
                if(optimal_square[y][x] != 0){
                    return false;
                }
            }
        }
        Fill(Y, X, size);
        return true;
    }

// в этом методе происходит поиск следующего квадрата в площади
// и сохраняет результат
	 void Next_backtracking(int start_y, int start_x, int end, int i){
        if(start_x + i < end){                              
            backtracking(start_y, start_x + i, end);        
        }else{
            if(start_y + 1 < end){
                backtracking(start_y + 1, square_size / 2, end);
            }else{
                optimal_count = cur_count;
                for (int y = 0; y < square_size; y++) {
        			for (int x = 0; x < square_size; x++) {
            			cur_square[y][x] = optimal_square[y][x];
        			}
    			}
            }
        }
    }

// в этом методе удаляются не подходящие квадраты
    void Remove(int Y, int X, int size){            
    	for(int y = Y; y < Y + size; y++){
    		for(int x = X; x < X + size; x++){
            	if(optimal_square[y][x] != 0){
            	    optimal_square[y][x] = 0;
            	}
        	}
    	}
    	cur_count--;
	}

// в этом методе происходит вывод лучшего решения
	void result_output() {                          
    	std::cout << optimal_count << std::endl;
    	for(int y = 0; y < square_size; y++){
        	for(int x = 0; x < square_size; x++){
            	if(optimal_square[y][x] > 0){
                	std::cout << (y * proportion + 1) << " " << (x * proportion + 1) << " " << optimal_square[y][x] * proportion << std::endl;
            	}
        	}
    	}
	}
};

int main() {
    int n;
    std::cin >> n;
    
    auto start = high_resolution_clock::now(); 

    SISS solving(n);
    solving.result_output();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout <<"Time:" << duration.count() * 1e-6 << "\n";
    return 0;
}
