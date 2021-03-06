#include "Camera.h"
#include "Detector.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "mropencv.h"
const char *WINDOW_NAME = "Display Window";
const char *OUTPUT_FILE = "output.avi";
const bool output_flag = true;
const char *OUTPUT_FILE1 = "values.csv";
std::ofstream filestream;

void DrawFace(IplImage *img, Features &f, bool col = true) {
  static CvScalar colors[] = 
  {
      {{0,0,255}},
      {{0,128,255}},
      {{0,255,255}},
      {{0,255,0}},
      {{255,128,0}},
      {{255,255,0}},
      {{255,0,0}},
      {{255,0,255}}
  };
  
  int radius;
  radius = cvRound(f.face_size*0.5);
  
  if(col) {
   cvCircle( img, f.face_position, radius, colors[0], 3, 8, 0 ); // draw face

   // draw lips
   cvCircle(img, cvPoint(f.lip_positions[0].x,f.lip_positions[0].y), 1, colors[1], 3, 8, 0);
   cvCircle(img, cvPoint(f.lip_positions[1].x,f.lip_positions[1].y), 1, colors[1], 3, 8, 0);

 	// draw nostrils
 	cvCircle(img, cvPoint(f.nostril_positions[0].x,f.nostril_positions[0].y), 1, colors[0], 3, 8, 0);
 	cvCircle(img, cvPoint(f.nostril_positions[1].x,f.nostril_positions[1].y), 1, colors[0], 3, 8, 0);

 	// draw nose bridge
 	cvCircle(img, cvPoint(f.nose_bridge.x,f.nose_bridge.y), 1, colors[2], 3, 8, 0);

 	// draw pupils
 	cvCircle(img, cvPoint(f.pupils[0].x,f.pupils[0].y), 1, colors[3], 3, 8, 0);
 	cvCircle(img, cvPoint(f.pupils[1].x,f.pupils[1].y), 1, colors[3], 3, 8, 0);

  	// draw eyebrow ends
  	cvCircle(img, cvPoint(f.eyebrow_ends[0].x,f.eyebrow_ends[0].y), 1, colors[1], 3, 8, 0);
  	cvCircle(img, cvPoint(f.eyebrow_ends[1].x,f.eyebrow_ends[1].y), 1, colors[1], 3, 8, 0);
	  
// 	cvEllipse(img,f.centers[0],f.sizes[0],f.theta*180/3.14,0,360,cvScalar(0,0,0),4,8,0);
// 	  cvEllipse(img,f.centers[1],f.sizes[1],f.theta*180/3.14,0,360,cvScalar(0,0,0),4,8,0);
	  
	  
  } else {    
    // draw lips
    cvCircle(img, cvPoint(f.lip_positions[0].x,f.lip_positions[0].y), 1, colors[5], 3, 8, 0);
    cvCircle(img, cvPoint(f.lip_positions[1].x,f.lip_positions[1].y), 1, colors[5], 3, 8, 0);
    cvLine(img, cvPoint(f.lip_positions[0].x,f.lip_positions[0].y), cvPoint(f.nostril_positions[0].x,f.nostril_positions[0].y), colors[5], 1);
    cvLine(img, cvPoint(f.lip_positions[1].x,f.lip_positions[1].y), cvPoint(f.nostril_positions[1].x,f.nostril_positions[1].y), colors[5], 1);

  	// draw nostrils
  	cvCircle(img, cvPoint(f.nostril_positions[0].x,f.nostril_positions[0].y), 1, colors[5], 3, 8, 0);
  	cvCircle(img, cvPoint(f.nostril_positions[1].x,f.nostril_positions[1].y), 1, colors[5], 3, 8, 0);
  	cvLine(img, cvPoint(f.nostril_positions[0].x,f.nostril_positions[0].y), cvPoint(f.nose_bridge.x,f.nose_bridge.y), colors[5], 1);
  	cvLine(img, cvPoint(f.nostril_positions[1].x,f.nostril_positions[1].y), cvPoint(f.nose_bridge.x,f.nose_bridge.y), colors[5], 1);

  	// draw nose bridge
  	cvCircle(img, cvPoint(f.nose_bridge.x,f.nose_bridge.y), 1, colors[5], 3, 8, 0);

  	// draw pupils
  	cvCircle(img, cvPoint(f.pupils[0].x,f.pupils[0].y), 1, colors[5], 3, 8, 0);
  	cvCircle(img, cvPoint(f.pupils[1].x,f.pupils[1].y), 1, colors[5], 3, 8, 0);
  	cvLine(img, cvPoint(f.pupils[0].x,f.pupils[0].y), cvPoint(f.nose_bridge.x,f.nose_bridge.y), colors[5], 1);
  	cvLine(img, cvPoint(f.pupils[1].x,f.pupils[1].y), cvPoint(f.nose_bridge.x,f.nose_bridge.y), colors[5], 1);

  	// draw eyebrow ends
  	cvCircle(img, cvPoint(f.eyebrow_ends[0].x,f.eyebrow_ends[0].y), 1, colors[5], 3, 8, 0);
  	cvCircle(img, cvPoint(f.eyebrow_ends[1].x,f.eyebrow_ends[1].y), 1, colors[5], 3, 8, 0);
  	cvLine(img, cvPoint(f.eyebrow_ends[0].x,f.eyebrow_ends[0].y), cvPoint(f.pupils[0].x,f.pupils[0].y), colors[5], 1);
  	cvLine(img, cvPoint(f.eyebrow_ends[1].x,f.eyebrow_ends[1].y), cvPoint(f.pupils[1].x,f.pupils[1].y), colors[5], 1);

	  filestream<<","<<f.eyebrow_ends[0].x<<","<<f.eyebrow_ends[0].y<<","<<f.eyebrow_ends[1].x<<","<<f.eyebrow_ends[1].y<<","<<f.pupils[0].x<<","<<f.pupils[0].y<<","<<f.nose_bridge.x<<","<<f.nose_bridge.y<<","<<f.pupils[1].x<<","<<f.pupils[1].y<<","<<f.nostril_positions[0].x<<","<<f.nostril_positions[0].y<<","<<f.nostril_positions[1].x<<","<<f.nostril_positions[1].y<<","<<f.lip_positions[0].x<<","<<f.lip_positions[0].y<<","<<f.lip_positions[1].x<<","<<f.lip_positions[1].y;
  }
}

void draw_cross(IplImage *img, Features& f) {
  static CvScalar colors[] = 
  {
      {{0,0,255}},
      {{0,128,255}},
      {{0,255,255}},
      {{0,255,0}},
      {{255,128,0}},
      {{255,255,0}},
      {{255,0,0}},
      {{255,0,255}}
  };
  
  double theta = f.theta;
  double phi = theta+1.57;
  cvLine(img, cvPoint(f.face_position.x-(50.0*tan(phi)), f.face_position.y-50.0), cvPoint(f.face_position.x+(50.0*tan(phi)), f.face_position.y+50.0), colors[0], 1);
  cvLine(img, cvPoint(f.face_position.x-(50.0*tan(theta)), f.face_position.y-50.0), cvPoint(f.face_position.x+(50.0*tan(theta)), f.face_position.y+50.0), colors[0], 1);
}

int main(int argc, char **argv) {
  const char *filename = NULL;
  if(argc > 1)
    filename = argv[1];
filestream.open(OUTPUT_FILE1);
	if (!filestream.is_open()) {
		std::cout << "FILE OPEN FAIL" << std::endl;
	}
	
  cvNamedWindow (WINDOW_NAME, CV_WINDOW_AUTOSIZE);
  
  const IplImage *current_frame;
  IplImage *gray = cvCreateImage(cvSize(640,480), 8, 1);
  IplImage *small_img = cvCreateImage(cvSize(640,480), 8, 3);
  Camera cam(filename);
  Detector detector;
  Features f,mf;
  bool track = false, docoldstart=false;
  double model[9][3];

  CvVideoWriter* vid_writer;
  if (output_flag) {
    vid_writer = cvCreateVideoWriter("result.avi", CV_FOURCC('D', 'I', 'V', 'X'), 25,  cvSize(640, 480));
  }
    int frameno = 1;

  while((current_frame = cam.GetFrame())) {
	  filestream<<frameno;
	  frameno++;
    cvResize(current_frame, small_img, CV_INTER_LINEAR);
    cvFlip(small_img, small_img, 1);
    cvCvtColor(small_img, gray, CV_BGR2GRAY);
//    cvEqualizeHist(gray,gray);
    
    if(track) {
      detector.TrackFeatures(gray, f, model);
      detector.FitModel(f, model, &mf);
      DrawFace(small_img, mf, false);
		  detector.FitGlasses(gray,f,model);
      CvFont font;
      double hScale=0.5;
      double vScale=0.5;
      int    lineWidth=1;
      cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, hScale,vScale,0,lineWidth);
      char buf[50];
      sprintf(buf,"tz:%f",f.theta);
      cvPutText (small_img,buf,cvPoint(200,400), &font, cvScalar(255,255,0));
      draw_cross(small_img,f);
    } else {
      f = detector.ColdStart(gray);
    }
    
    if(f.face_size) {
      DrawFace(small_img, f);
    }
	  filestream<<std::endl;
    cvShowImage(WINDOW_NAME, small_img);
	  char key = cvWaitKey(10);
	  if(key == 't') {
		  track = true;
		  detector.GetModel(f, model);
		  detector.SetupTracking(gray,f);
	  }
	  if(key == 'a' || (fabs(f.theta) < 0.1 && docoldstart)) {
		  printf("Auto Restart\n");
		  f = detector.ColdStart(gray);
		  track = true;
		  docoldstart = false;
		  detector.GetModel(f, model);
		  detector.SetupTracking(gray,f);
		  
	  }

	  if(key == 'q') {
      break;
	  }

    if (output_flag) {
      cvWriteFrame(vid_writer, small_img);
    }
	  
	  if((fabs(detector.speed[0]) > 2 && fabs(detector.speed[1]) > 2)) {
		  docoldstart = true;  
	  }
	  if(key=='l') {
		  f.rot_dir[0] = -1;
	  }
	  if(key=='r') {
		  f.rot_dir[0] = 1;
	  }
	  if(key=='u') {
		  f.rot_dir[1] = -1;
	  }
	  if(key=='d') {
		  f.rot_dir[1] = 1;
	  }
//	  if(f.horiz_rotation <0.1)
//		  f.rot_dir[0] = 0;
//	  if(f.vert_rotation <0.1)
//		  f.rot_dir[1] = 0;
	  docoldstart = false;
  }
  
  if(output_flag)
    cvReleaseVideoWriter(&vid_writer);
  cvReleaseImage( &gray );
  cvReleaseImage( &small_img );
	filestream.close();
	
	std::cout<<frameno<<std::endl;
  return 0;
}
