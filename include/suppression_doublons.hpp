#ifndef SUPPRESSION_DOUBLONS_HPP
#define SUPPRESSION_DOUBLONS_HPP

#include <vector>
#include <utility>

// Supprimer les droites proches dans une liste de (rho, theta)
std::vector<std::pair<double, double>> supprimerDoublons(
    const std::vector<std::pair<double, double>>& lignes,
    double seuil_rho, double seuil_theta);

#endif
