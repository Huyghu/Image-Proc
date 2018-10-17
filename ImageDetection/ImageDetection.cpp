#include "ImageDetection.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}
	cv::Mat image;
	image = cv::imread(argv[1], cv::IMREAD_COLOR);

	if (image.empty()) {
		std::cout << "Couldn't find the image" << std::endl;
		return -1;
	}

	int threshold = 30;
	for (int y = 3; y <= image.rows - 3; y += 6) {
		for (int x = 3; x <= image.cols - 3; x += 6) {
			PrintCirclePoint(x, y, 3, image);
		}
	}

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display window", image);
	cv::waitKey(0);
	return 0;
}

// Select 16 points around center and change it color to blue
void	PrintCirclePoint(int x, int y, int rayon, cv::Mat image) {
	int new_x, new_y;
	double rad;

	for (double cursor = 0.0; cursor < 360.0; cursor += 22.5) {
		rad = cursor * (M_PI / 180.0);
		new_x = static_cast<int>(round(x + rayon * cos(rad)));
		new_y = static_cast<int>(round(y + rayon * sin(rad)));
		uchar intensity = image.at<uchar>(new_y, new_x);

		image.at<cv::Vec3b>(new_y, new_x) = 280;
	}
}