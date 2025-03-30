#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>

// Classe image RGB en format PPM (P3)
class Image {
public:
    int width = 0, height = 0;

    // data[y][x][c] : canal c = 0(R), 1(G), 2(B)
    std::vector<std::vector<std::vector<int>>> data;

    // Charger une image PPM (P3)
    bool load(const std::string& path);

    // Sauvegarder l'image au format PPM (P3)
    void save(const std::string& path) const;

    // Obtenir une version en niveaux de gris (matrice 2D d'intensité)
    std::vector<std::vector<int>> toGrayscale() const;

    // Affecter une version en niveaux de gris dans l'image RGB (copie sur les 3 canaux)
    void fromGrayscale(const std::vector<std::vector<int>>& gray);
};

#endif
