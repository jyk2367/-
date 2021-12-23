#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;

void laplacianfilter(Mat& image, Mat& convertedImg, int r, int c, const int& filtersize);
void pixellaplacianfilter(Mat& image, Mat& convertedImg, int x, int y, const int& filtersize);
int filter_laplacian[3][3] = {
	{0,-1,0},
	{-1,4,-1},
	{0,-1,0}
};

int main() {
	while (1) {
		string filename;
		int filtersize = 3;

		cout << "어떤 이미지를 입력하시겠습니까?\n";
		cin >> filename;
		Mat img = imread(filename,IMREAD_GRAYSCALE);
		if (img.empty()) {
			cout << "파일이름이 잘못되었습니다!!\n";
			return -1;
		}
		Mat convertedImg = img.clone(), resultImg;

		int r = img.rows;
		int c = img.cols;
		
		cout << "잠시만 기다려주세요....\n";
		laplacianfilter(img, convertedImg, r, c, filtersize);


		hconcat(img, convertedImg, resultImg);
		imshow("origin->laplacian", resultImg);
		waitKey(0);
	}
	return 0;
}

void pixellaplacianfilter(Mat& image, Mat& convertedImg, int x, int y, const int& filtersize) {
	int FSize = pow(filtersize, 2);
	int nc = image.channels();

	int* SUM= new int[nc];
	for (int i = 0; i < nc; i++) {
		SUM[i] = 0;
	}
	for (int dirX = -(filtersize / 2); dirX <= filtersize / 2; dirX++) {
		for (int dirY = -(filtersize / 2); dirY <= filtersize / 2; dirY++) {
			int nextX = x + dirX;
			int nextY = y + dirY;

			if (nextX < 0 || nextX >= image.rows || nextY < 0 || nextY >= image.cols) {
				return;
			}
			uchar* nextPixel = image.ptr<uchar>(nextX, nextY);
			for (int i = 0; i < nc; i++) {
				SUM[i]+= (int)nextPixel[i] * filter_laplacian[dirX + 1][dirY + 1];
			}

			//cout << "이전 : " << (int)nextPixel[0] << "\n";
		}
	}


	uchar* convertedPixel = convertedImg.ptr<uchar>(x, y);
	for (int i = 0; i < nc; i++) {
		convertedPixel[i]= (uchar)saturate_cast<int>(SUM[i]);
	}
	
	//cout << "이후 : " << (int)convertedPixel[0] << "\n";
}

void laplacianfilter(Mat& image, Mat& convertedImg, int r, int c, const int& filtersize) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			pixellaplacianfilter(image, convertedImg, i, j, filtersize);
		}
	}
}