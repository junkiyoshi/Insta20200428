#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();

	int radius = 150;
	int deg_span = 1;
	for (int z = -150; z <= 150; z += 1) {

		int deg_start_ini = ofMap(ofNoise(z * 0.005 + ofGetFrameNum() * 0.035), 0, 1, 0, 720);
		for (int deg_start = deg_start_ini; deg_start < deg_start_ini + 360; deg_start += 120) {

			for (int deg = deg_start; deg < deg_start + 75; deg += deg_span) {

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(this->make_point(radius, deg), z + 0.5));
				vertices.push_back(glm::vec3(this->make_point(radius, deg), z - 0.5));
				vertices.push_back(glm::vec3(this->make_point(radius, deg + deg_span), z - 0.5));
				vertices.push_back(glm::vec3(this->make_point(radius, deg + deg_span), z + 0.5));

				int face_index = this->face.getNumVertices();
				this->face.addVertices(vertices);

				this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2);
				this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 3);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->face.draw();

	//ofSetColor(239);
	//this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int radius, int deg) {

	deg = deg % 360;

	int deg_a = (deg / 120) * 120;
	int deg_b = deg_a + 120;

	int remainder = deg % 120;
	int diff = deg - deg_a;

	auto point_a = glm::vec2(radius * cos(deg_a * DEG_TO_RAD), radius * sin(deg_a * DEG_TO_RAD));
	auto point_b = glm::vec2(radius * cos(deg_b * DEG_TO_RAD), radius * sin(deg_b * DEG_TO_RAD));
	auto distance = point_b - point_a;

	return point_a + (distance / 120) * diff;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}