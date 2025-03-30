#ifndef DETECTION_CONTOURS_HPP
#define DETECTION_CONTOURS_HPP

#include "image.hpp"

// Fonction de seuillage simple pour détecter les contours
Image detectContours(const Image& input, int seuil = 100);

#endif
