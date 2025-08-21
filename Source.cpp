#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << " Camera is not opening " << endl;
        return -1;
    }

    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");
    if (faceCascade.empty()) {
        cout << "XML file could not be not loaded" << endl;
        return -1;
    }

    Mat frame, mirroredvideo;
    int index = 1;

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            cout << "Error: Frame not captured" << endl;
            break;
        }

        flip(frame, mirroredvideo, index);

        vector<Rect> faces;
        faceCascade.detectMultiScale(mirroredvideo, faces, 1.1, 10);

        // Draw rectangles and count
        for (int i = 0; i < faces.size(); i++) {
            rectangle(mirroredvideo, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 2);
        }

        // Display count on frame
        string text = "Targets Detected : " + to_string(faces.size());
        putText(mirroredvideo, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

        imshow("Target-lock system", mirroredvideo);

        waitKey(1);  
            
        
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
