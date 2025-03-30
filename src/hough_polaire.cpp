#include "hough.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>

#define PI 3.14159265

// Appliquer la transformée de Hough en coordonnées polaires
void Hough::applyPolarHough(const Image& img, double pas_rho, double pas_theta) {
    int height = img.height;
    int width = img.width;

    double diag = std::sqrt(width * width + height * height);
    int rho_max = static_cast<int>(diag);
    int theta_max = 180; // 0 à 180 degrés

    int n_rho = static_cast<int>((2 * rho_max) / pas_rho);
    int n_theta = static_cast<int>(theta_max / pas_theta);

    accumulator.assign(n_rho, std::vector<unsigned int>(n_theta, 0));
    this->rho_values.resize(n_rho);
    this->theta_values.resize(n_theta);

    // Initialiser les axes rho et theta
    for (int i = 0; i < n_rho; ++i)
        rho_values[i] = -rho_max + i * pas_rho;

    for (int j = 0; j < n_theta; ++j)
        theta_values[j] = j * pas_theta;

    // Parcours des pixels non nuls (supposés faire partie des contours)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (img.data[y][x] > 128) { // seuillage simple
                for (int t = 0; t < n_theta; ++t) {
                    double theta = theta_values[t] * PI / 180.0;
                    double rho = x * std::cos(theta) + y * std::sin(theta);
                    int r = static_cast<int>((rho + rho_max) / pas_rho);
                    if (r >= 0 && r < n_rho)
                        accumulator[r][t]++;
                }
            }
        }
    }
}

// Extraire les pics les plus forts de l'accumulateur
std::vector<std::pair<double, double>> Hough::findPolarMaxima(int nb_lignes) {
    std::vector<std::tuple<int, int, unsigned int>> peaks;

    for (int r = 0; r < accumulator.size(); ++r)
        for (int t = 0; t < accumulator[0].size(); ++t)
            peaks.emplace_back(r, t, accumulator[r][t]);

    std::sort(peaks.begin(), peaks.end(), [](auto& a, auto& b) {
        return std::get<2>(a) > std::get<2>(b);
    });

    std::vector<std::pair<double, double>> result;
    for (int i = 0; i < nb_lignes && i < peaks.size(); ++i) {
        int r_idx = std::get<0>(peaks[i]);
        int t_idx = std::get<1>(peaks[i]);
        result.emplace_back(rho_values[r_idx], theta_values[t_idx]);
        std::cout << "Ligne polaire : rho = " << rho_values[r_idx]
                  << ", theta = " << theta_values[t_idx] << std::endl;
    }
    return result;
}

// Exporter l'accumulateur de Hough sous forme d'image
void Hough::saveHoughImage(const std::string& path) {
    int rows = accumulator.size();
    int cols = accumulator[0].size();
    unsigned int maxVal = 0;
    for (const auto& row : accumulator)
        for (auto val : row)
            if (val > maxVal) maxVal = val;

    std::ofstream out(path);
    out << "P3\n" << cols << " " << rows << "\n255\n";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            int val = static_cast<int>((255.0 * accumulator[i][j]) / (maxVal ? maxVal : 1));
            out << val << " " << val << " " << val << "\n";
        }
}


