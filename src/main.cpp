#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window,  2560, 1440, OF_WINDOW);
	ofRunApp(new testApp());
}
