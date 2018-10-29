#include "ImageDetection.hpp"

int main(int argc, char **argv)
{
    if (argc == 1 || argv[1] == "-h")
    {
        std::cout << "Usage: ImageDetection [ImageToLoadAndDisplay1, ImageToLoadAndDisplay2, ...]" << std::endl;
        return (1);
    }

    ShapeDetector detector;
    for (size_t i = 1; i < argc; ++i) {
        detector.setImage(argv[i]);
        detector();
    }

    return 0;
}

ShapeDetector::ShapeDetector(const std::string & fileName) : edgeCount(0)
{
    image = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cout << "Couldn't find the image: " << fileName << std::endl;
        return;
    }

    copy = image.clone();
}

void ShapeDetector::detect()
{
    if (image.empty()) {
        return;
    }

    for (int y = 3; y < image.rows - 3; y++) {
        for (int x = 3; x < image.cols - 3; x++) {
            int original = image.at<uchar>(y, x);
            if (!IsNearEdge(x, y, 3)) {
                edgeCount += PrintCirclePoint(x, y, 3);
            }
        }
    }
}

bool ShapeDetector::IsNearEdge(int x, int y, int rayon)
{
    const auto& lambda = [x, y](std::pair<int, int> coord) {
        if (std::abs(x - coord.first) <= 15 && std::abs(y - coord.second) <= 15)
            return true;
        return false;
    };
    for (const auto& it : edgeCoord) {
        if (lambda(it))
            return true;
    }
    return false;
}

int ShapeDetector::PrintCirclePoint(int x, int y, int rayon)
{
    int new_x, new_y;
    double rad;
    int	maxSuite = 0;
    int subSuite = 0;
    int addSuite = 0;

    int original = image.at<uchar>(y, x);
    for (double cursor = 0.0; cursor < 360.0; cursor += 22.5) {
        rad = cursor * (M_PI / 180.0);
        new_x = static_cast<int>(round(x + rayon * cos(rad)));
        new_y = static_cast<int>(round(y + rayon * sin(rad)));
        int intensity = image.at<uchar>(new_y, new_x);

        if (original - G_THRESHOLD > intensity)
            subSuite++;
        else if (original + G_THRESHOLD < intensity)
            addSuite++;
    }
    if (addSuite || subSuite)
        maxSuite = (addSuite > subSuite) ? addSuite : subSuite;

    if (maxSuite >= G_TOLERANCE) {
        for (double cursor = 0.0; cursor < 360.0; cursor += 22.5) {
            rad = cursor * (M_PI / 180.0);
            new_x = static_cast<int>(round(x + 3 * cos(rad)));
            new_y = static_cast<int>(round(y + 3 * sin(rad)));
            copy.at<uchar>(new_y, new_x) = 125;
        }
        edgeCoord.push_back({ x, y });
        return 1;
    }
    return 0;
}

void ShapeDetector::print()
{
    if (edgeCount == 3) {
        cv::putText(copy, "Triangle", cv::Point(10, 20), CV_FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
    }
    else if (edgeCount >= 3) {
        cv::putText(copy, "Star", cv::Point(10, 20), CV_FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", copy);
    cv::waitKey(0);
}

void ShapeDetector::operator()()
{
    detect();
    print();
}

void ShapeDetector::setImage(const std::string & fileName)
{
    edgeCount = 0;
    edgeCoord.clear();

    image = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cout << "Couldn't find the image: " << fileName << std::endl;
        return;
    }

    copy = image.clone();
}
