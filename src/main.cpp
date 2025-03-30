#include "hough.hpp"
#include "image.hpp"
#include "suppression_doublons.hpp"
#include "detection_contours.hpp"
#include "bresenham.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./detecteur input.ppm" << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = "images/output.ppm";
    std::string houghPath = "images/hough_space.ppm";

    // Charger l'image couleur
    Image image;
    if (!image.load(inputPath)) {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
        return 1;
    }

    // Détection des contours (optionnelle)
    Image contourImage = detectContours(image);  // Seuillage simple ou Sobel (à implémenter)

    // Transformée de Hough polaire (rho, theta)
    Hough hough;
    hough.applyPolarHough(contourImage, 1.0, 1.0);  // pas_rho = 1 pixel, pas_theta = 1 degré

    // Extraire les lignes significatives
    auto lignes = hough.findPolarMaxima(5);  // Top 5 maximas dans l'accumulateur

    // Supprimer les doublons (droites proches)
    auto lignes_filtrees = supprimerDoublons(lignes, 5.0, 10.0); // seuil distance rho et theta

    // Tracer les lignes sur l'image originale
    Image imageAvecLignes = image;  // copie
    for (const auto& [rho, theta] : lignes_filtrees)
        tracerLignePolaire(imageAvecLignes, rho, theta);

    //  Sauvegarder le résultat et l'espace de Hough
    imageAvecLignes.save(outputPath);
    hough.saveHoughImage(houghPath);

    std::cout << "Image sortie sauvegardée dans : " << outputPath << std::endl;
    std::cout << "Espace de Hough sauvegardé dans : " << houghPath << std::endl;
    return 0;

    hough.saveHoughImage(houghPath);

}
