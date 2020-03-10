
//카메라로부터 이미지를 캡쳐하여 화면에 보여주는 것을 반복하여,
// 영상처럼 보이도록 한다.

#include <opencv2/core.hpp> // Mat 객체를 사용하기 위한 CORE 모듈.
#include <opencv2/videoio.hpp>// 비디오 디바이스 접근하여 비디오 객체를 가져오기 위한 VideoIO 모듈
#include <opencv2/highgui.hpp>// 인터페이스를 위한 모듈.
#include <opencv2/imgproc.hpp> // cvtColor 함수를 포함한 헤더파일.
#include <iostream> // console 입출력을 위한 io 스트림 모듈


using namespace cv;
using namespace std;

int main()
{
	Mat frame; // 입력이미지를 저장할 Mat 객체


	//비디오 캡쳐 객체를 사용하여, PC에 연결되어 있는 첫번째 카메라에 연결되도록 한다.
	// 두 대이상의 카메라를 사용한다면, 2번째 카메라는 1, 세번째 카메라는 2가 된다.
	// 카메라의 연결순서가 빠를수록 낮은 아이디 값을 갖는다.
	VideoCapture cap(0);


	// 카메라에 접근할 수 없는 경우,
	// 에러를 출력하고 카메라를 종료한다.
	if (!cap.isOpened())
	{
		cerr << "카메라를 열 수 없습니다." << endl;
		return -1;
	}


	//카메라로부터 초당 프레임 수를 가져온다.
	// 한장의 이미지를 가져오고 다음 이미지를 가져오기 전까지 대기시간으로 사용.
	int fps = cap.get(CAP_PROP_FPS);

	//영상을 가져오고 화면에 보여주는 것을 반복하기 위하여, 루프를 추가한다.
	while (1)
	{

		// 비디오 캡쳐 객체의 read 함수를 사용하여, 카메라로부터 이미지 한장을 가져온다.
		cap.read(frame);

		// 대부분의 카메라에서는 문제가 없지만, 일부 카메라에서는 처음 이미지를 가져올 경우,
		// 문제가 발생할 수도 있다.  이 경우를 체크하여, 프로그램을 종료하여야 한다.
		if (frame.empty())
		{
			cerr << "캡쳐 실패" << endl;
			//이미지를 가져오고, 문제가 발생했을 경우, 루프에서 빠져나오도록 설정.
			break;
		}


		//영상처리 함수 추가.
		// 영상처리 함수는 화면에 이미지를 읽어오는 read함수와 화면에 출력하는 imshow함수 사이에 넣는다.
		// void cv::cvtColor(InputArray src, OutputArray dst, int code, int dstCn =0)
		//void cv::cvtColor(입력, 출력, 변환코드 , int dstCn =0)
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		

		//이미지를 화면에 출력.
		imshow("Live", frame);

		//앞에서 가져온 fps 값을 고려하여, 이미지를 가져올 사이 대기시간을 설정한다.

		int wait = int(1.0 / fps * 1000);

		//아무키나 입력시 프로그램 종료.  (5000)으로 설정 시 5초 후에 프로그램이 종료된다.
		if (waitKey(wait) >= 0)
			break;
	}
	return 0;

}