#ifndef IMAGEDETECTION_HPP
#define IMAGEDETECTION_HPP

#define G_THRESHOLD 30
#define G_TOLERANCE 10

#define _USE_MATH_DEFINES

#include <iostream>
#include "MultipleImages.hpp"
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>

class ShapeDetector {
public:
    ShapeDetector() : edgeCount(0) {};
    ShapeDetector(std::shared_ptr<cv::Mat> image);

    void detect();
    bool IsNearEdge(int x, int y, int rayon);
    int	PrintCirclePoint(int x, int y, int rayon);

    void operator()();
    void setImage(std::shared_ptr<cv::Mat> image);
private:
    std::shared_ptr<cv::Mat> image;
    int edgeCount;
    std::vector<std::pair<int, int>> edgeCoord;
};

#endif //IMAGEDETECTION_HPP
