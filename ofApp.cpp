#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_value += ofMap(ofGetFrameNum() % 50, 0, 25, 10, 0);
	}

	for (int i = 0; i < 800; i++) {

		auto radius = 150;
		auto deg = ofRandom(360);

		auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		this->location_list.push_back(location);
		this->life_list.push_back(0);
	}

	for (int i = 0; i < 800; i++) {

		auto radius = 250;
		auto deg = ofRandom(360);

		auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		this->location_list.push_back(location);
		this->life_list.push_back(0);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (abs(this->location_list[i].x) > 460 || abs(this->location_list[i].y) > 460) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
		}

		if (this->life_list[i] > 30) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.005, this->location_list[i].y * 0.005, this->noise_value), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));
		this->location_list[i] = next;
		this->life_list[i] += 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		auto size = this->life_list[i] < 10 ? ofMap(this->life_list[i], 0, 10, 0, 4) : 4;
		auto alpha = this->life_list[i] > 20 ? ofMap(this->life_list[i], 20, 30, 255, 0) : 255;

		ofSetColor(255, alpha);
		ofDrawCircle(this->location_list[i], size);
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto size = this->life_list[i] < 10 ? ofMap(this->life_list[i], 0, 10, 0, 4) : 4;
		auto alpha = this->life_list[i] > 20 ? ofMap(this->life_list[i], 20, 30, 255, 0) : 255;

		ofSetColor(0, alpha);
		ofDrawCircle(this->location_list[i], size * 0.4);
	}

	/*
	int start = 100;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}