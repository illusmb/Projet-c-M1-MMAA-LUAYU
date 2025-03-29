#ifndef HOUGH_HPP
#define HOUGH_HPP

#include <vector>
#include <string>

class Hough {
public:
    std::vector<std::vector<int>> image;
    std::vector<std::vector<unsigned int>> accumulator;
    std::vector<double> m_values;
    std::vector<int> b_values;
    int width, height, max_val;

    bool loadImage(const std::string& path);
    void applyNaiveHough(double m_step = 0.1, int b_step = 1);
    std::vector<std::pair<double, int>> findMaxima(int numLines = 5);
    void drawLines(const std::vector<std::pair<double, int>>& lines);
    void saveImage(const std::string& outputPath);
};

#endif
