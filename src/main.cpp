#pragma once
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#pragma warning(disable:4267)
#pragma warning(disable:4018)
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/calib3d.hpp>
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<direct.h>
#include<io.h>
#include<Windows.h>
#include<algorithm>
#include"boards_from_corners.h"
#include"config.h"
#include"find_corners.h"
#include"plot_boards.h"
#include"plot_corners.h"
#include <chrono>
using namespace cv;
using namespace std;
#define ShowDetectValidBoards_
#define ShowUndistortImg_


int main(int argc, char* argv[])
{
	//cout << 000 << endl;
	string picStr("..//pic//1.jpg");
	cv::Mat img = cv::imread(picStr, cv::IMREAD_GRAYSCALE);
	if (img.empty())
		return -1;


	cbdetect::Corner corners;
	std::vector<cbdetect::Board> boards;
	cbdetect::Params params;
	params.show_processing = false;
	params.corner_type = cbdetect::SaddlePoint;
	params.show_debug_image = false;
	params.norm = false;


	

	auto start = std::chrono::high_resolution_clock::now();
	cbdetect::find_corners(img, corners, params);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "during time: " << duration.count() << "ms" << std::endl;



	cv::Mat img2show = cv::imread(picStr, IMREAD_COLOR);
	if (img2show.empty())
		return -1;
	for (int i = 0; i<corners.p.size(); i++)
	{
			circle(img2show, corners.p[i], 6, Scalar(0, 0, 255), 3);
	}
	cv::imwrite("im2gshow.jpg", img2show);
	waitKey(0);

	return 0;
}