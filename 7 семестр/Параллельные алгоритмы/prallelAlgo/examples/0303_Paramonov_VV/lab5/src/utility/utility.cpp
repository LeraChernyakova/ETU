#include "utility.hpp"

using namespace std;


string read_file(const string& file_name) {
    return string(
        (istreambuf_iterator<char>(
            ifstream(file_name).rdbuf()
        )),
        istreambuf_iterator<char>()
    );
}

void ppm_draw(string const & filename,
              vector<int> const & grid,
              int width, int height, int iterations) {
    ofstream fd(filename);

    // Записываем PPM заголовок.
    fd << "P6 " << width << " " << height
       << " " << 255 << endl;

    // Определяем цвет пикселя по вычисленному значению.
    for(int i=0; i < grid.size(); i++) {
        unsigned char r, g, b;
        if (grid[i] == -1) { 
            r = 0; 
            g = 0; 
            b = 0; 
        } else {
            r = (grid[i] * 255 / iterations);
            g = r;
            b = 255;
        }

        // Записываем пиксель в файл.
        fd << r << g << b;
    }
}