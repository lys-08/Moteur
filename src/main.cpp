#include "ofMain.h"
#include "ofApp.h"
#include "ofApp2.h"
#include "ofApp3.h"



//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp3>());
	ofRunMainLoop();

}
