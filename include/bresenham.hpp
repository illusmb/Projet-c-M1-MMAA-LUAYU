#ifndef BRESENHAM_HPP
#define BRESENHAM_HPP

#include "image.hpp"
#include <cmath>

// Tracer une ligne (rho, theta) sur une image RGB en blanc
void tracerLignePolaire(Image& image, double rho, double theta_deg);

#endif
