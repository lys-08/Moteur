#include "ofMain.h"
#include "ofApp.h"
#include "ofApp2.h"

#include "../tests/test_vector3d.h"
#include "../tests/test_matrix3.h"
#include "../tests/test_matrix4.h"
#include "../tests/test_quaternion.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_FULLSCREEN; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	Test_vector3d test_vector3d;
	test_vector3d.tests_all();
	
	Test_matrix3 test_matrix3;
	test_matrix3.tests_all();

	Test_matrix4 test_matrix4;
	test_matrix4.tests_all();

	Test_quaternion test_quaternion;
	test_quaternion.tests_all();

	ofRunApp(window, make_shared<ofApp2>());
	ofRunMainLoop();

}
