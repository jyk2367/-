#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
using namespace std;
using namespace cv;

void meanfilter(Mat& image, Mat& convertedImg, int r, int c, const int& filtersize);
void pixelmeanfilter(Mat& image, Mat& convertedImg, int x, int y, const int& filtersize);

void pixelmedianfilter(Mat& image, Mat& convertedImg, int x, int y, const int& filtersize, const int& filtertype);
void medianfilter(Mat& image, Mat& convertedImg, int r, int c, const int& filtersize, const int& filtertype);

int main() {
	while (1) {
		string filename;
		int selectFilter = 1;
		int filtersize = 3;

		cout << "� �̹����� �Է��Ͻðڽ��ϱ�?\n";
		cin >> filename;


		Mat img = imread(filename);

		if (img.empty()) {
			cout << "�����̸��� �߸��Ǿ����ϴ�!!\n";
			return -1;
		}

		cout << "� ���͸� �����Ͻðڽ��ϱ�?(1.Mean 2.Median)\n";
		cin >> selectFilter;
		cout << "���� ũ�⸦ �Է��ϼ���(¦�� ���� �Ұ�)\n";
		cin >> filtersize;
		while (filtersize % 2 == 0) {
			cout << "���� ũ�⸦ �ٽ� �Է��ϼ���\n";
			cin >> filtersize;
		}

		Mat convertedImg = img.clone(),convertedImg2 = img.clone(),convertedImg3 = img.clone();
		Mat resultImg,resultImg2,resultImg3;
		int r = img.rows;
		int c = img.cols;
		cout << "��ø� ��ٷ��ּ���....(median filter�� ���ÿ� 3���� ��ȯ�� �ؼ� �ð��� �� �ɸ��ϴ�.)\n";

		if (selectFilter == 1) {
			meanfilter(img, convertedImg, r, c, filtersize);
			hconcat(img, convertedImg, resultImg);
			imshow("origin->mean", resultImg);
		}
		else {
			// 1 : midpoint, 2 : min, 3 : max
			medianfilter(img, convertedImg, r, c, filtersize, 1);
			medianfilter(img, convertedImg2, r, c, filtersize, 2);
			medianfilter(img, convertedImg3, r, c, filtersize, 3);
			hconcat(img, convertedImg, resultImg);

			
			imshow("origin->midpoint(" + to_string(filtersize) + ")", resultImg);
			hconcat(img, convertedImg2, resultImg2);
			imshow("origin->min(" + to_string(filtersize) + ")", resultImg2);
			hconcat(img, convertedImg3, resultImg3);
			imshow("origin->max(" + to_string(filtersize) + ")", resultImg3);

		}
		waitKey(0);
	}

	return 0;
}


void pixelmeanfilter(Mat& image, Mat& convertedImg, int x, int y, const int& filtersize) {
	int FSize = pow(filtersize, 2);
	int B_sum = NULL, G_sum = NULL, R_sum = NULL;


	for (int dirX = -(filtersize / 2); dirX <= filtersize / 2; dirX++) {
		for (int dirY = -(filtersize / 2); dirY <= filtersize / 2; dirY++) {
			int nextX = x + dirX;
			int nextY = y + dirY;

			if (nextX < 0 || nextX >= image.rows || nextY < 0 || nextY >= image.cols)
				return;
			Vec3b nextPixel = image.at<Vec3b>(nextX, nextY);
			B_sum += (int)nextPixel[0];
			G_sum += (int)nextPixel[1];
			R_sum += (int)nextPixel[2];
		}
	}
	//cout << "��ġ : " << x << " " << y << "\n";
	//cout<<"���� : "<<(int)R<<" "<<(int)G<<" "<<(int)B<<"\n";
	Vec3b& convertedPixel = convertedImg.at<Vec3b>(x, y);
	convertedPixel[0] = (uchar)(B_sum / FSize);
	convertedPixel[1] = (uchar)(G_sum / FSize);
	convertedPixel[2] = (uchar)(R_sum / FSize);
	//cout << "���� : " << (int)convertedPixel[0] << " " << (int)convertedPixel[1] << " " << (int)convertedPixel[2] << "\n";

}

void meanfilter(Mat& image, Mat& convertedImg, int r, int c, const int& filtersize) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			pixelmeanfilter(image, convertedImg, i, j, filtersize);
		}
	}
}



void pixelmedianfilter(Mat& image, Mat& convertedImg, int x, int y, const int& filtersize,const int &filtertype) {
	vector<uchar> vec_B,vec_G,vec_R;


	for (int dirX = -(filtersize / 2); dirX <= filtersize / 2; dirX++) {
		for (int dirY = -(filtersize / 2); dirY <= filtersize / 2; dirY++) {
			int nextX = x + dirX;
			int nextY = y + dirY;

			if (nextX < 0 || nextX >= image.rows || nextY < 0 || nextY >= image.cols)
				return;
			Vec3b nextPixel = image.at<Vec3b>(nextX, nextY);
			vec_B.push_back(nextPixel[0]);
			vec_G.push_back(nextPixel[1]);
			vec_R.push_back(nextPixel[2]);
		}
	}
	//cout << "��ġ : " << x << " " << y << "\n";
	//cout<<"���� : "<<(int)R<<" "<<(int)G<<" "<<(int)B<<"\n";
	Vec3b& convertedPixel = convertedImg.at<Vec3b>(x, y);
	sort(vec_B.begin(), vec_B.end());
	sort(vec_G.begin(), vec_G.end());
	sort(vec_R.begin(), vec_R.end());
	switch (filtertype) {
	case 1://midpoint
		convertedPixel[0] = vec_B[vec_B.size()/2];
		convertedPixel[1] = vec_G[vec_G.size()/2];
		convertedPixel[2] = vec_R[vec_R.size()/2];
		//cout << "midpoint�� : " << (int)convertedPixel[0] << " " << (int)convertedPixel[1] << " " << (int)convertedPixel[2] << "\n";
		break;
	case 2://min
		convertedPixel[0] = vec_B[0];
		convertedPixel[1] = vec_G[0];
		convertedPixel[2] = vec_R[0];
		//cout << "min�� : " << (int)convertedPixel[0] << " " << (int)convertedPixel[1] << " " << (int)convertedPixel[2] << "\n";
		break;
	case 3://max
		convertedPixel[0] = vec_B[vec_B.size()-1];
		convertedPixel[1] = vec_G[vec_G.size()-1];
		convertedPixel[2] = vec_R[vec_R.size()-1];
		//cout << "max�� : " << (int)convertedPixel[0] << " " << (int)convertedPixel[1] << " " << (int)convertedPixel[2] << "\n";
		break;
	}

	//cout << "���� : " << (int)convertedPixel[0] << " " << (int)convertedPixel[1] << " " << (int)convertedPixel[2] << "\n";
}

void medianfilter(Mat& image, Mat& convertedImg, int r, int c, const int& filtersize,const int& filtertype) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			pixelmedianfilter(image, convertedImg, i, j, filtersize,filtertype);
		}
	}
}