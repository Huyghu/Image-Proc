#ifndef MULTIPLEIMAGE_HPP
#define MULTIPLEIMAGE_HPP

#include <opencv2/opencv.hpp>

#include <stdio.h>
#include <stdarg.h>
#include <vector>

void ShowManyImages(std::string title, std::vector<std::shared_ptr<cv::Mat>>);

#endif //MULTIPLEIMAGE_HPP