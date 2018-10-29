#ifndef IMAGEDETECTION_HPP
#define IMAGEDETECTION_HPP

#define G_THRESHOLD 30
#define G_TOLERANCE 10

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>

class ShapeDetector {
public:
    ShapeDetector() : edgeCount(0) {};
    ShapeDetector(const std::string& fileName);

    void detect();
    bool IsNearEdge(int x, int y, int rayon);
    int	PrintCirclePoint(int x, int y, int rayon);
    void print();

    void operator()();
    void setImage(const std::string& fileName);
private:
    cv::Mat image;
    cv::Mat copy;
    int edgeCount;
    std::vector<std::pair<int, int>> edgeCoord;
};

#endif //IMAGEDETECTION_HPP
