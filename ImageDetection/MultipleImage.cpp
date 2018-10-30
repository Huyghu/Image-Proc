#include "MultipleImages.hpp"

void ShowManyImages(std::string title, std::vector<std::shared_ptr<cv::Mat>> images) {
	int size;
	int i;
	int m, n;
	int x, y;
	int w, h;
	float scale;
	int max;

	if (images.size() == 1) {
		w = h = 1;
		size = 300;
	}
	else if (images.size() == 2) {
		w = 2; h = 1;
		size = 300;
	}
	else if (images.size() == 3 || images.size() == 4) {
		w = 2; h = 2;
		size = 300;
	}
	else if (images.size() == 5 || images.size() == 6) {
		w = 3; h = 2;
		size = 200;
	}
	else if (images.size() == 7 || images.size() == 8) {
		w = 4; h = 2;
		size = 200;
	}
	else {
		w = 4; h = 3;
		size = 150;
	}

	cv::Mat DispImage(cv::Size(100 + size * w, 60 + size * h), CV_8UC1, cv::Scalar::all(0));

	for (i = 0, m = 20, n = 20; i < images.size(); i++, m += (20 + size)) {
		cv::Mat img = *(images[i]);

		if (img.empty()) {
			printf("Invalid arguments");
			return;
		}

		x = img.cols;
		y = img.rows;
		max = (x > y) ? x : y;
		scale = (float)((float)max / size);
		if (i % w == 0 && m != 20) {
			m = 20;
			n += 20 + size;
		}

		cv::Mat matRoi = DispImage(cv::Rect(m, n, (int)(x / scale), (int)(y / scale)));
		cv::Mat temp; resize(img, temp, cv::Size((int)(x / scale), (int)(y / scale)));
		temp.copyTo(matRoi);
	}

	cv::namedWindow(title, 1);
	cv::imshow(title, DispImage);
	cv::waitKey();
}