#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(int argc, char** argv) {
	using namespace std;
	using namespace cv;
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
	int skip=0;
	if(argc >= 4){
		skip = atoi(argv[3]);
	}
	cout << "file: " << argv[1] << endl;
	cout << "out : " << dir << endl;
	cout << "skip : " << skip << endl;
	double const fps = cap.get(CV_CAP_PROP_FPS);
	int const width = 640;
	int const height = 360;
	vector<Mat> frames(150);
	int i = 0;
	namedWindow("frame",1);
	int found = 0;
	Mat frame;
	while(cap.read(frame)){
		int const current = (int)cap.get(CV_CAP_PROP_POS_FRAMES);
		Mat& now = frames[i];
		cv::resize(frame, now, cv::Size(width,height),cv::INTER_CUBIC);
		imshow("frame", now);
		if(waitKey(30) >= 0) break;
		if(skip > 0){
			skip--;
			continue;
		}
		int near = 0;
		bool sameFrame = false;
		double maxd = 0;
		double mind = DBL_MAX;
		for(int j=(int)(fps/2);j<frames.size();++j) {
			Mat& target = frames[((i-j) + frames.size()) % frames.size()];
			if(target.size().width != now.size().width && target.size().height != now.size().height){
				break;
			}
			double const diff = norm(now,target,NORM_L2) / (width*height*3);
			maxd = std::max(maxd, diff);
			mind = std::min(mind, diff);
			if(diff < 0.01){
				near = j;
				sameFrame = true;
			}
		}
		if(sameFrame && maxd > 0.13){
			cout << "Found(" << found << "): " <<  (current - near) << " -> " << (current) << endl;
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
