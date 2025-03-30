#include "image.hpp"
#include <vector>
#include <algorithm>

// Appliquer un seuillage adaptatif sur les niveaux de gris pour extraire les contours
Image detectContours(const Image& input, int seuil) {
    auto gray = input.toGrayscale();
    int h = gray.size();
    int w = gray[0].size();

    std::vector<std::vector<int>> contours(h, std::vector<int>(w, 0));

    // Seuillage : détecter si le pixel est plus lumineux que la moyenne locale (filtre Sobel simplifié)
    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            int gx = -gray[y-1][x-1] + gray[y-1][x+1]
                   -2*gray[y][x-1]   + 2*gray[y][x+1]
                   -gray[y+1][x-1] + gray[y+1][x+1];

            int gy = -gray[y-1][x-1] - 2*gray[y-1][x] - gray[y-1][x+1]
                     +gray[y+1][x-1] + 2*gray[y+1][x] + gray[y+1][x+1];

            int mag = std::sqrt(gx * gx + gy * gy);
            contours[y][x] = (mag > seuil) ? 255 : 0;
        }
    }

    Image result;
    result.fromGrayscale(contours);
    return result;
}
