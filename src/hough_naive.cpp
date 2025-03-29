// hough_naive.cpp
#include "hough.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

// Chargement d'une image PPM et conversion en niveaux de gris
bool Hough::loadImage(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string line;
    // Lire la première ligne non vide et non commentée (numéro magique P3)
    do std::getline(file, line); while (line.empty() || line[0] == '#');
    if (line != "P3") return false;

    // Lire les dimensions : largeur et hauteur
    do std::getline(file, line); while (line.empty() || line[0] == '#');
    std::istringstream dimStream(line);
    dimStream >> width >> height;

    // Lire la valeur maximale des composantes de couleur (souvent 255)
    do std::getline(file, line); while (line.empty() || line[0] == '#');
    std::istringstream valStream(line);
    valStream >> max_val;

    // Initialiser l'image en niveaux de gris
    image.resize(height, std::vector<int>(width));
    int r, g, b;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            file >> r >> g >> b;
            // Conversion perceptuelle en gris
            image[i][j] = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
        }

    return true;
}

// Transformée de Hough naïve (y = mx + b)
void Hough::applyNaiveHough(double m_step, int b_step) {
    double m_min = -5.0, m_max = 5.0;
    int b_min = -height, b_max = height;

    int m_size = static_cast<int>((m_max - m_min) / m_step) + 1;
    int b_size = static_cast<int>((b_max - b_min) / b_step) + 1;

    m_values.resize(m_size);
    b_values.resize(b_size);
    accumulator.assign(b_size, std::vector<unsigned int>(m_size, 0));

    for (int mi = 0; mi < m_size; ++mi)
        m_values[mi] = m_min + mi * m_step;
    for (int bi = 0; bi < b_size; ++bi)
        b_values[bi] = b_min + bi * b_step;

    int threshold = 40;  // Seuil pour considérer un pixel comme contour

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            if (image[y][x] > threshold)
                for (int mi = 0; mi < m_size; ++mi) {
                    double m = m_values[mi];
                    int b = static_cast<int>(y - m * x); // b = y - mx
                    int bi = (b - b_min) / b_step;       // indice de b
                    if (bi >= 0 && bi < b_size)
                        accumulator[bi][mi]++;
                }
}

// Trouver les maximas dans l'accumulateur
std::vector<std::pair<double, int>> Hough::findMaxima(int numLines) {
    std::vector<std::tuple<int, int, unsigned int>> all;

    for (int b = 0; b < accumulator.size(); ++b)
        for (int m = 0; m < accumulator[0].size(); ++m)
            all.emplace_back(m, b, accumulator[b][m]);

    std::sort(all.begin(), all.end(), [](auto a, auto b) {
        return std::get<2>(a) > std::get<2>(b);  // Tri décroissant par votes
    });

    std::vector<std::pair<double, int>> lines;
    for (int i = 0; i < numLines && i < all.size(); ++i) {
        int m_idx = std::get<0>(all[i]);
        int b_idx = std::get<1>(all[i]);
        double m = m_values[m_idx];
        int b = b_values[b_idx];
        std::cout << "Ligne détectée : y = " << m << "x + " << b << "\n";
        lines.emplace_back(m, b);
    }

    return lines;
}

// Tracer les lignes détectées (épaisseur = 3 pixels)
void Hough::drawLines(const std::vector<std::pair<double, int>>& lines) {
    for (auto [m, b] : lines) {
        for (int x = 0; x < width; ++x) {
            int y = static_cast<int>(m * x + b);
            // Tracer une ligne verticale de 3 pixels autour de y
            for (int dy = -1; dy <= 1; ++dy)
                if (y + dy >= 0 && y + dy < height)
                    image[y + dy][x] = 255;
        }
    }
}

// Sauvegarder l'image au format PPM (P3)
void Hough::saveImage(const std::string& path) {
    std::ofstream out(path);
    out << "P3\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            out << image[i][j] << " " << image[i][j] << " " << image[i][j] << "\n";
}
