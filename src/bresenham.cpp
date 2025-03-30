#include "bresenham.hpp"
#define PI 3.14159265

// Tracer une droite en coordonnées polaires sur une image RGB avec épaisseur de 2 pixels
void tracerLignePolaire(Image& image, double rho, double theta_deg) {
    int width = image.width;
    int height = image.height;
    double theta = theta_deg * PI / 180.0;

    double cos_t = cos(theta);
    double sin_t = sin(theta);

    int x0, y0, x1, y1;
    if (std::abs(sin_t) > std::abs(cos_t)) {
        x0 = 0;
        y0 = static_cast<int>((rho - x0 * cos_t) / sin_t);
        x1 = width - 1;
        y1 = static_cast<int>((rho - x1 * cos_t) / sin_t);
    } else {
        y0 = 0;
        x0 = static_cast<int>((rho - y0 * sin_t) / cos_t);
        y1 = height - 1;
        x1 = static_cast<int>((rho - y1 * sin_t) / cos_t);
    }

    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        // Tracer le pixel principal + épaisseur (1 pixel autour)
        for (int dy_ = -1; dy_ <= 1; ++dy_) {
            for (int dx_ = -1; dx_ <= 1; ++dx_) {
                int px = x0 + dx_;
                int py = y0 + dy_;
                if (px >= 0 && px < width && py >= 0 && py < height) {
                    image.data[py][px][0] = 255;
                    image.data[py][px][1] = 255;
                    image.data[py][px][2] = 255;
                }
            }
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}
