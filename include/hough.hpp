#ifndef HOUGH_HPP
#define HOUGH_HPP

#include "image.hpp"
#include <vector>
#include <string>

class Hough {
public:
    // Accumulateur polaire
    std::vector<std::vector<unsigned int>> accumulator;
    std::vector<double> rho_values;
    std::vector<double> theta_values;

    // Appliquer la transformée de Hough en coordonnées polaires
    void applyPolarHough(const Image& img, double pas_rho = 1.0, double pas_theta = 1.0);

    // Extraire les maxima
    std::vector<std::pair<double, double>> findPolarMaxima(int nb_lignes);

    // Sauvegarde visuelle de l'accumulateur
    void saveHoughImage(const std::string& path) const;
};

#endif
