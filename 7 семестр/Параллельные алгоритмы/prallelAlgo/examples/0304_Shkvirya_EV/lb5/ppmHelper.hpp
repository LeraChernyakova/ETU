#pragma once

#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct PpmPixel {
    int r, g, b;

    PpmPixel(int r, int g, int b) : r(r), g(g), b(b) {}
    PpmPixel() : r(0), g(0), b(0) {}
};


struct PpmImage {
    int h, w;

    vector<vector<PpmPixel>> data;

    PpmImage(int h, int w, const vector<vector<PpmPixel>> &data) : h(h), w(w), data(data) {}

    PpmImage(int h, int w) : h(h), w(w) {
        data = vector<vector<PpmPixel>>();
        data.resize(h);
        for (size_t i = 0; i < h; i++) {
            data[i].resize(w);
        }
    }
};

namespace PpmHelper {
    void save_image(const string &fileName, const PpmImage &image) {
        ofstream imgOut(fileName, ios::binary);
        imgOut << "P6\n";
        imgOut << image.w << " " << image.h << '\n';
        imgOut << "255\n";
        char* buffer = new char[3];
        for (size_t i = 0; i < image.h; i++) {
            for (size_t j = 0; j < image.w; j++) {
                buffer[0] = image.data[i][j].r;
                buffer[1] = image.data[i][j].g;
                buffer[2] = image.data[i][j].b;
                imgOut.write(buffer, 3);
            }
        }
        imgOut.close();
        delete[] buffer;
    }
}