#include "ImageDetection.hpp"

int main(int argc, char **argv)
{
    if (argc == 1 || argv[1] == "-h")
    {
        std::cout << "Usage: ImageDetection [ImageToLoadAndDisplay1, ImageToLoadAndDisplay2, ...]" << std::endl;
        return (1);
    }

    ShapeDetector detector;
	std::vector<std::shared_ptr<cv::Mat>> images;
    for (size_t i = 1; i < argc; ++i) {
		images.push_back(std::make_shared<cv::Mat>(cv::imread(argv[i], cv::IMREAD_GRAYSCALE)));
		if (images[i - 1]->empty()) {
			std::cout << "Couldn't find the image: " << argv[i] << std::endl;
			return 1;
		}
      detector.setImage(images[i - 1]);
      detector();
    }
	ShowManyImages("Result", images);
    return 0;
}

ShapeDetector::ShapeDetector(std::shared_ptr<cv::Mat> _image) : edgeCount(0)
{
    image = _image;
}

void ShapeDetector::detect()
{
    if (image->empty()) {
        return;
    }

    for (int y = 3; y < image->rows - 3; y++) {
        for (int x = 3; x < image->cols - 3; x++) {
            int original = image->at<uchar>(y, x);
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

    int original = image->at<uchar>(y, x);
    for (double cursor = 0.0; cursor < 360.0; cursor += 22.5) {
        rad = cursor * (M_PI / 180.0);
        new_x = static_cast<int>(round(x + rayon * cos(rad)));
        new_y = static_cast<int>(round(y + rayon * sin(rad)));
        int intensity = image->at<uchar>(new_y, new_x);

        if (original - G_THRESHOLD > intensity)
            subSuite++;
        else if (original + G_THRESHOLD < intensity)
            addSuite++;
    }
    if (addSuite || subSuite)
        maxSuite = (addSuite > subSuite) ? addSuite : subSuite;

    if (maxSuite >= G_TOLERANCE) {
        edgeCoord.push_back({ x, y });
        return 1;
    }
    return 0;
}

void ShapeDetector::operator()()
{
    detect();
	if (edgeCount == 3) {
		cv::putText(*image, "Triangle", cv::Point(40, 40), CV_FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 0 , 255), 2);
	}
	else if (edgeCount >= 3) {
		cv::putText(*image, "Star", cv::Point(40, 40), CV_FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
	}
}

void ShapeDetector::setImage(std::shared_ptr<cv::Mat> _image)
{
    edgeCount = 0;
    edgeCoord.clear();

	image = _image;
}
