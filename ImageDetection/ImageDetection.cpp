#include "ImageDetection.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}
	cv::Mat image;
	cv::Mat copy_image;
	image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	copy_image = image.clone();

	if (image.empty()) {
		std::cout << "Couldn't find the image" << std::endl;
		return -1;
	}

	for (int y = 3; y < image.rows - 3; y++) {
		for (int x = 3; x < image.cols - 3; x++) {
			PrintCirclePoint(x, y, 3, image, copy_image);
		}
	}

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display window", copy_image);
	cv::waitKey(0);
	return 0;
}

// Select 16 points around center and change it color to blue
void	PrintCirclePoint(int x, int y, int rayon, cv::Mat image, cv::Mat copy) {
	int new_x, new_y;
	double rad;
	int threshold = 40;
	int	maxSuite = 0;
	int subSuite = 0;
	int addSuite = 0;

	int original = static_cast<int>(image.at<uchar>(y, x));
	for (double cursor = 0.0; cursor < 360.0; cursor += 22.5) {
		rad = cursor * (M_PI / 180.0);
		new_x = static_cast<int>(round(x + rayon * cos(rad)));
		new_y = static_cast<int>(round(y + rayon * sin(rad)));
		int intensity = static_cast<int>(image.at<uchar>(new_y, new_x));

		if (original - threshold > intensity)
			subSuite++;
		else if (original + threshold < intensity)
			addSuite++;
	}
	if (addSuite && subSuite)
		maxSuite = (addSuite > subSuite) ? addSuite : subSuite;

	if (maxSuite >= 10) {
		for (double cursor = 0.0; cursor < 360.0; cursor += 22.5) {
			rad = cursor * (M_PI / 180.0);
			new_x = static_cast<int>(round(x + 3 * cos(rad)));
			new_y = static_cast<int>(round(y + 3 * sin(rad)));
			copy.at<uchar>(new_y, new_x) = 190;
		}
	}
}