#include "hough.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> inputPaths = {
        "images/imgTresSimple.ppm",
        "images/imageAvecDeuxSegments.ppm",
        "images/imageM1.ppm"
    };

    for (const auto& inputPath : inputPaths) {
        Hough hough;
        std::string outputPath = inputPath.substr(0, inputPath.find_last_of(".")) + "_output.ppm";
        if (!hough.loadImage(inputPath)) {
            std::cerr << "Erreur de chargement : " << inputPath << std::endl;
            continue;
        }

        hough.applyNaiveHough();
        auto lines = hough.findMaxima(5);
        hough.drawLines(lines);
        hough.saveImage(outputPath);
    }

    return 0;
}
