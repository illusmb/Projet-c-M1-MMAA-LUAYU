#include <vector>
#include <cmath>
#include <utility>

// Fonction de distance entre deux droites en coordonnées polaires
bool sontProches(double rho1, double theta1, double rho2, double theta2, double seuil_rho, double seuil_theta) {
    return std::abs(rho1 - rho2) < seuil_rho && std::abs(theta1 - theta2) < seuil_theta;
}

// Supprimer les droites trop proches dans (rho, theta)
std::vector<std::pair<double, double>> supprimerDoublons(
    const std::vector<std::pair<double, double>>& lignes,
    double seuil_rho, double seuil_theta)
{
    std::vector<std::pair<double, double>> filtrées;

    for (const auto& [rho, theta] : lignes) {
        bool est_doublon = false;
        for (const auto& [r2, t2] : filtrées) {
            if (sontProches(rho, theta, r2, t2, seuil_rho, seuil_theta)) {
                est_doublon = true;
                break;
            }
        }
        if (!est_doublon) filtrées.emplace_back(rho, theta);
    }
    return filtrées;
}
