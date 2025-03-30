#include "image.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

// Charger une image PPM (format P3, RGB)
bool Image::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string line;

    // Lire "P3"
    do std::getline(file, line); while (line.empty() || line[0] == '#');
    if (line != "P3") return false;

    // Lire les dimensions
    do std::getline(file, line); while (line.empty() || line[0] == '#');
    std::istringstream dimStream(line);
    dimStream >> width >> height;

    // Lire valeur maximale (souvent 255)
    do std::getline(file, line); while (line.empty() || line[0] == '#');
    std::istringstream valStream(line);
    int max_val;
    valStream >> max_val;

    // Lire les pixels RGB
    data.resize(height, std::vector<std::vector<int>>(width, std::vector<int>(3)));
    int r, g, b;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file >> r >> g >> b;
            data[y][x][0] = r;
            data[y][x][1] = g;
            data[y][x][2] = b;
        }
    }
    return true;
}

// Sauvegarder l'image au format PPM P3 (RGB)
void Image::save(const std::string& path) const {
    std::ofstream out(path);
    out << "P3\n" << width << " " << height << "\n255\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            out << data[y][x][0] << " " << data[y][x][1] << " " << data[y][x][2] << " ";
        }
        out << "\n";
    }
}

// Conversion vers niveaux de gris (grayscale)
std::vector<std::vector<int>> Image::toGrayscale() const {
    std::vector<std::vector<int>> gray(height, std::vector<int>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int r = data[y][x][0];
            int g = data[y][x][1];
            int b = data[y][x][2];
            gray[y][x] = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
        }
    }
    return gray;
}

// Copier une image niveaux de gris dans une image RGB
void Image::fromGrayscale(const std::vector<std::vector<int>>& gray) {
    height = gray.size();
    width = gray[0].size();
    data.resize(height, std::vector<std::vector<int>>(width, std::vector<int>(3)));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int val = std::clamp(gray[y][x], 0, 255);
            data[y][x][0] = val;
            data[y][x][1] = val;
            data[y][x][2] = val;
        }
    }
}
