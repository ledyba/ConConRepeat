#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;
double calcDiff(Mat a, Mat b){
	int d = 0;
	auto aptr = a.begin<unsigned char>();
	auto bptr = b.begin<unsigned char>();
	auto aend = a.end<unsigned char>();
	for(;aptr != aend; ++aptr, ++bptr){
		if(abs((*aptr)-(*bptr)) > 20){
			++d;
		}
	}
	return (double)d / (double)(a.rows * a.cols * a.channels());
}

int main(int argc, char** argv) {
	VideoCapture cap;
	if(argc <= 1){
		cerr << "usage: ConConRepeat <fname> [dir]" << endl;
		return -1;
	}
	if(!cap.open(argv[1])){
		cerr << "Could not open: " << argv[1] << endl;
		return -1;
	}
	string dir = ".";
	if(argc >= 3){
		dir = argv[2];
	}
	double skip=0;
	if(argc >= 4){
		skip = atof(argv[3])*1000.0;
	}
	cout << "file: " << argv[1] << endl;
	cout << "out : " << dir << endl;
	cout << "skip : " << (skip/1000) <<" sec"<< endl;
	double const fps = cap.get(CV_CAP_PROP_FPS);
	int const width = 640;
	int const height = 360;
	vector<Mat> frames((int)(fps*2.5));
	int i = 0;
	namedWindow("frame",1);
	int found = 0;
	Mat frame;
	cap.set(CV_CAP_PROP_POS_MSEC, skip);
	while(cap.read(frame)){
		int const current = (int)cap.get(CV_CAP_PROP_POS_FRAMES);
		Mat& now = frames[i];
		cv::resize(frame, now, cv::Size(width,height),cv::INTER_CUBIC);
		imshow("frame", now);
		if(waitKey(30) >= 0) break;
		int near = 0;
		int far = 0;
		int cfar = 0;
		bool sameFrame = false;
		double mind = DBL_MAX;
		for(int j=(int)(fps/2);j<frames.size();++j) {
			Mat& target = frames[((i-j) + frames.size()) % frames.size()];
			if(target.size().width != now.size().width && target.size().height != now.size().height){
				break;
			}
			double const dinf = calcDiff(target, now);
			//double const dl2 = norm(target, now, NORM_L2) / (width*height*3);
			if(dinf < 0.01) {
				near = j;
			}
			mind = std::min(mind, dinf);
			if(dinf > 0.01){
				far++;
			}
		}
		auto dtime = (double)far/near;
		if(mind < 0.01 && dtime > 0.1){
			cout << "Found(" << found << "): " <<  (current - near) << " -> " << (current) << ", "<< ((double)near/fps) <<"sec, range=("<<mind<<", "<<dtime<<")"<< endl;
			for(int j=near, f=0;j>=0;--j,++f) {
				std::string fname = dir+cv::format("/anime-%03d-%03d.png",found,f);
				Mat& frame = frames[((i-j) + frames.size()) % frames.size()];
				if(!imwrite(fname, frame)){
					cerr << "Failed to write: " << fname << endl;
					return -1;
				}
			}
			found++;
		}
		i = (i+1) % frames.size();
	}
	return 0;
}
