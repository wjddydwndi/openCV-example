
//카메라로부터 이미지를 캡쳐하여 화면에 보여주는 것을 반복하여,
// 영상처럼 보이도록 한다.

#include <opencv2/core.hpp> // Mat 객체를 사용하기 위한 CORE 모듈.
#include <opencv2/videoio.hpp>// 비디오 디바이스 접근하여 비디오 객체를 가져오기 위한 VideoIO 모듈
#include <opencv2/highgui.hpp>// 인터페이스를 위한 모듈.

#include <iostream> // console 입출력을 위한 io 스트림 모듈


using namespace cv;
using namespace std;

int main123()
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



		// 비디오 캡쳐 객체의 read 함수를 사용하여, 카메라로부터 이미지 한장을 가져온다.
		cap.read(frame);

		// 대부분의 카메라에서는 문제가 없지만, 일부 카메라에서는 처음 이미지를 가져올 경우,
		// 문제가 발생할 수도 있다.  이 경우를 체크하여, 프로그램을 종료하여야 한다.
		if (frame.empty())
		{
			cerr << "캡쳐 실패" << endl;

	
			return -1;
		}
	


	//이미지를 화면에 출력.
	imshow("Live", frame);

	

	//아무키나 입력시 프로그램 종료.  (5000)으로 설정 시 5초 후에 프로그램이 종료된다.
	waitKey(0);

	return 0;


}