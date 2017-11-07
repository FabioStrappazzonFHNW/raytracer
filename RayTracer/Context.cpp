#include "Context.h"
#include "SDL_events.h"
#include "Output.h"
#include "WindowHandle.h"
#include "Vec2d.h"
#include "Vec3d.h"
#include "RendererHandle.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "Ray.h"
#include <cmath>
#include <limits>
#include <algorithm>
#include "Color.h"
#include "Sphere.h"
#include "Plane.h"
#include "HitPoint.h"
#include "TexturedSphere.h"
#include <random>
#include <conio.h>
#include <windows.h> 
#include <csignal>
#include <atomic>

using namespace std;
using namespace std::string_literals;

constexpr long double pi(){
	return 3.141592653589793238L;
}

static atomic<bool> interrupt = true;
BOOL WINAPI handleSignal(DWORD signal) {
	interrupt = true;
	return TRUE;
}


Context::Context():
timer(),
running(true),
eye(0,0,-4),
lookAt(0,0,0),
fow(36),
ambient(0.02, 0.02, 0.02),
reflections(1),
raysPerPixel(1),
aliasingDeviation(0.0),
aperture(0.0),
samples(2),
isPathTracing(false),
sceneN(1),
//scene(), //why does this not work o.O
lights({
	/*Light({-0.4, -0.98, -0.7}, Color(0.2, 0.0, 0.0)),
	Light({ 0.4, -0.98, -0.7}, Color(0.0, 0.2, 0.0)),
	Light({ 0.0, -0.98,  0.0}, Color(0.0, 0.0, 0.2)),*/
	Light({ 0.0, -0.9,  -0.6 }, Color(1.8, 1.8, 1.8)),
	Light({ 5, 0.0, -4.0}, Color(0.6, 0.6, 0.6))
})
{
	SetConsoleCtrlHandler(handleSignal, TRUE);
	switchScene(1);
}


void Context::loop(){
	//render();
	cout << "type render or help\n>";
	while (running){
		handleEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Context::exit(){
	running = false;
}

Color Context::calcPixel(Vec2d pixel, Vec2d windowSize) {
	double relX = (pixel.x - windowSize.x / 2) / (windowSize.x / 2);
	double relY = (pixel.y - windowSize.y / 2) / (windowSize.y / 2);
	auto eyeRay = createEyeRay({ relX, relY });
	return calcColor(eyeRay, reflections, true);
}

void Context::render() {
	timer.restart();
	auto& d = Output::instance();
	auto& re = d.getRenderer();
	auto& w = d.getWindow();
	re.clear();
	w.lock();
	
	interrupt = false;
	#pragma omp parallel for
	for (int y = 0; y < static_cast<int>(w.getSize().y) ; y++) {
		minstd_rand gen(1);
		normal_distribution<> dist(0.0, aliasingDeviation);
		
		for (auto x = 0.0; x < w.getSize().x && !interrupt; x++) {
			Color color;
			for (auto i = 0; i < raysPerPixel; i++) {
				 color += calcPixel({ x + dist(gen), y + dist(gen) }, w.getSize());
			}
			w.drawPoint({  x, static_cast<double>(y) }, color / static_cast<double>(raysPerPixel));
			/*w.drawPoint({ 4 * x, 4 * y+1 }, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x,4 * y +2}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x, 4 * y +3}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x+1,4 * y }, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 1,4 * y +1}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 1, 4 * y+2 }, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 1,4 * y +3}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 2,4 * y }, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 2,4 * y +1}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 2,4 * y +2}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 2,4 * y +3}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 3,4 * y }, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 3,4 * y +1}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 3,4 * y +2}, color / static_cast<double>(raysPerPixel));
			w.drawPoint({ 4 * x + 3,4 * y +3}, color / static_cast<double>(raysPerPixel));*/
		}
		w.unlock();
		w.lock();
	}
	w.unlock();
	//re.render();

	using namespace std::chrono;
	cout <<"rendered in "<< duration_cast<seconds>(timer.getDuration()).count() << " seconds\n";
}

template <typename T>
static void readSetting(T& val) {
	T arg;
	if (cin >> arg) {
		val = arg;
	}
	else {
		cout << "error: wrong argument type\n";
		cin.clear();
	}
}

void Context::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			exit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				Vec2d pix;
				pix.x = event.button.x; 
				pix.y = event.button.y;
				auto col = calcPixel(pix, Output::instance().getWindow().getSize());
				cout << dec << pix.x << "|" << pix.y << ": " << hex<< col << endl;
			}
			break;
		}
	}
	if (!_kbhit()) {
		return;
	}
	string cmd;
	cin >> cmd;
	if (cmd == "render") {
		cout << "(CTRL+C to cancel)\n"<<flush;
		render();
	}
	else if (cmd == "help") {
		cout << "commands:\n"
			"render \t\trenders the scene\n"
			"help \t\tshows this message\n"
			"reflect n\tnumber of reflections\n"
			"rpp n\t\thow many rays per pixel\n"
			"dev r\t\tstandard deviation for aliasing\n"
			"aperture r\taperture for depth of field\n"
			"samples n\tnumber of samples for path tracing\n"
			"scene n\t\t1: cornell, 2: depth, 3: grace, 4: uffizi, 5: random\n"
			"mode \t\ttoggles path tracing and ray tracing\n"
			"current \tshows current settings\n"
			"clear \t\tclears the screen\n"
			"quit \t\tquits the application\n\n";
	}
	else if (cmd == "reflect") {
		readSetting(reflections);
	}
	else if (cmd == "rpp") {
		readSetting(raysPerPixel);
	}
	else if (cmd == "dev") {
		readSetting(aliasingDeviation);
	}
	else if (cmd == "aperture") {
		readSetting(aperture);
	}
	else if (cmd == "samples") {
		readSetting(samples);
	}
	else if (cmd == "mode") {
		isPathTracing = !isPathTracing;
	}
	else if (cmd == "scene") {
		int sceneNr;
		readSetting(sceneNr);
		switchScene(sceneNr);
	}
	else if (cmd == "current") {
		cout << "reflect: " << reflections 
			<<"\nrpp: "<< raysPerPixel 
			<<"\ndev: "<<aliasingDeviation
			<<"\naperture: "<<aperture
			<<"\nsamples: "<<samples
			<<"\nscene: "<<sceneN
			<<"\n"<<(isPathTracing?"path"s : "ray"s)<<" tracing mode\n";
	}
	else if (cmd == "clear") {
		Output::instance().getRenderer().render();
	}
	else if (cmd == "quit") {
		exit();
	}
	else {
		cout << "unknown command " << cmd<<'\n';
	}
	cout << ">";
}

Ray Context::createEyeRay(Vec2d pixel){

	thread_local minstd_rand gen(1);
	uniform_real_distribution<> radiusDist(0, aperture);
	thread_local uniform_real_distribution<> angleDist(0, 2 * pi());
	
	double radius = radiusDist(gen);
	double angle = angleDist(gen);
	double xDev = radius * cos(angle);
	double yDev = radius * sin(angle);


	auto lookDir = (lookAt - eye).normalize();
	auto screenRight = cross({ 0,1,0 }, lookDir).normalize();
	auto screenDown = cross(lookDir, screenRight).normalize();

	auto dev = (screenRight * xDev) + (screenDown * yDev);

	auto devEye = eye + dev;
	auto devLookAt = eye + lookAt - devEye;

	lookDir = (lookAt - devEye).normalize();

	auto tan = std::tan(fow / 180 * pi() / 2);
	Vec3d direction = lookDir + pixel.x * screenRight * tan + pixel.y * screenDown * tan;
	return Ray(devEye, direction);
}

HitPoint Context::findClosestHitpoint(Ray r){
	return bounding->intersects(r);
	
	HitPoint hitpoint(r);
	double closestDistance = std::numeric_limits<double>::infinity();
	for(auto& ss : scene){
		auto& s = *ss;
		auto hits = s.intersects(r);
		for(auto&& hit : hits){
			auto dist = distance(hit, r.getStart());
			if(dist > 0 && dist<closestDistance){
				hitpoint.setObject(&s);
				hitpoint.setHit(hit);
				closestDistance = dist;
			}
		}
	}
	return hitpoint;
}

Color attenuate(Color c, double distanceSq) {

	return (c / (1 + 0.4*distanceSq));
}

double fresnel(Vec3d light, Vec3d normal, double reflect)
{
	return reflect + ((1 - reflect) * pow((1 - (normal * light)), 5.0));
}

Vec3d genSample(Vec3d normal) {
	Vec3d sample;
	static minstd_rand gen(1);
	static uniform_real_distribution<> dist(-1, 1);
	do {
		sample.x = dist(gen);
		sample.y = dist(gen);
		sample.z = dist(gen);
		
	} while (sample.magnitudeSquared() > 1);
	if (normal * sample <= 0) {
		sample *= -1;
	}
	return sample.normalize();
}

Color Context::pathTrace(HitPoint hit, Ray r, int recurse, bool firstIteration) {
	Color color;
	const double pdf = 1 / (2 * pi());
	int s = firstIteration ? samples : 1;
	if (recurse > 0) {
		for (int i = 0; i < s; i++) {
			auto sample = genSample(hit.getNormal());
			Ray next(hit.getPoint() + (sample * 0.001), sample);

			color += (calcColor(next, recurse - 1, true) * (sample * hit.getNormal()) * hit.getColor()) / pdf;

		}
		color /= s;
	}
	color += hit.getEmission();
	return color;
}

Color Context::rayTrace(HitPoint hit, Ray r, int recurse) {
	Color col = ambient;
	if (hit.getEmission() != 0) {
		return hit.getColor();
	}
	for (auto&& light : lights) {


		auto toLight = Ray(hit.getPoint() + ((light.getPosition() - hit.getPoint()).normalize()*0.001), light.getPosition() - hit.getPoint());
		auto toLightHit = findClosestHitpoint(toLight);
		auto distanceSqToLight = distanceSquared(hit.getPoint(), light.getPosition());
		auto distanceSqToHit = distanceSquared(toLightHit.getPoint(), hit.getPoint());

		double shadow = 1.0;
		if (toLightHit.isHit() && distanceSqToHit < distanceSqToLight) {
			shadow = 0.1;
		}

		auto diffuseColor = hit.getDiffuse()*shadow * max(hit.getNormal() * toLight.getDirection(), 0.0) * light.getColor();


		auto specularDir = 2 * (toLight.getDirection() * hit.getNormal()) * hit.getNormal() - toLight.getDirection();
		specularDir = specularDir.normalize();
		auto specularColor =
			hit.getSpecular()
			* light.getColor()
			* shadow
			* pow(max(0.0, -(specularDir * r.getDirection())), hit.getShine());



		col += attenuate(diffuseColor, distanceSqToLight) + attenuate(specularColor, distanceSqToLight);

	}
	if (recurse > 0 && hit.getReflect() > 0) {

		auto reflection = r.getDirection() - 2 * r.getDirection() * hit.getNormal() * hit.getNormal();
		double fr = fresnel(r.getDirection()*-1, hit.getNormal(), hit.getReflect());

		col += fr*calcColor(Ray(hit.getPoint() + reflection*0.001, reflection), recurse - 1, false);
	}
	return hit.getColor() * col;
}

void Context::switchScene(int s)
{
	sceneN = s;
	scene.clear();
	auto* w = Output::instance().getWall();
	auto* g = Output::instance().getGrace();
	auto* u = Output::instance().getUffizi();
	switch (s) {
	case 1:
		//                                             x      y     z  radius     color  shine diffuse specular reflect emission
		scene.push_back(make_unique<Sphere>(Vec3d{ -1001,     0,    0 }, 1000, 0xcc2222, 20.0, 0.4, 0.1, 0.0, 0.0));//left
		scene.push_back(make_unique<Sphere>(Vec3d{ 1001,      0,    0 }, 1000, 0x2222cc, 20.0, 0.4, 0.1, 0.0, 0.0));//right
		scene.push_back(make_unique<Sphere>(Vec3d{ 0,         0, 1001 }, 1000, 0xffffff, 20.0, 0.4, 0.1, 0.0, 0.0));//back
		scene.push_back(make_unique<Sphere>(Vec3d{ 0,     -1001,    0 }, 1000, 0xffffff, 20.0, 0.4, 0.1, 0.0, 0.0));//top
		scene.push_back(make_unique<Sphere>(Vec3d{ 0,      1001,    0 }, 1000, 0xffffff, 20.0, 0.4, 0.1, 0.0, 0.0));//bottom
		scene.push_back(make_unique<TexturedSphere>(Vec3d{ -0.6,    0.7, -0.6 }, 0.3, w, 50.0, 0.7, 0.7, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 0.3,     0.4,  0.3 }, 0.6, 0x888844, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 0.0,     -1.5,  0.3 }, 0.6, Color(1.0, 1.0, 1.0), 100.0, 0.6, 0.8, 0.9, 1.5));
		break;
	case 2:
		scene.push_back(make_unique<Plane>(Vec3d{ 0,1,0 }, Vec3d{ 0,1,0 },200, Color{0.8, 0.8, 0.8}, 20.0, 0.4, 0.1, 0.0, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ -0.5,  0.3,     -2.0 }, 0.4, 0x888844, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 0.0,  0.3,     0.0}, 0.4, 0x998844, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 0.5,  0.3,     2.0 }, 0.4, 0x889944, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 1.0,  0.3,     4.0 }, 0.4, 0x888855, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 1.5,  0.3,     6.0}, 0.4, 0x999944, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 2.0,  0.3,     8.0 }, 0.4, 0x889955, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 2.5,  0.3,     10.0 }, 0.4, 0x998855, 100.0, 0.6, 0.8, 0.9, 0.0));
		break;
	case 3://grace
		scene.push_back(make_unique<TexturedSphere>(Vec3d{ -0.3,  0.3,     -1.0 }, 100, g, 100.0, 0.6, 0.8, 0.9, 1.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ -0.3,  0.3,     -1.0 }, 0.4, 0x555555, 100.0, 0.6, 0.8, 0.9, 0.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ 0.0,  0.3,     0.0 }, 0.4, 0x555555, 100.0, 0.6, 0.8, 0.9, 0.0));
		break;
	case 4://uffizi
		scene.push_back(make_unique<Plane>(Vec3d{ 0,0.72,0 }, Vec3d{ 0,1,0 }, 200, Color{ 0.8, 0.8, 0.8 }, 20.0, 0.4, 0.1, 0.7, 0.0));
		scene.push_back(make_unique<TexturedSphere>(Vec3d{ -0.3,  0.3,     -1.0 }, 100, u, 100.0, 0.6, 0.8, 0.8, 1.0));
		scene.push_back(make_unique<Sphere>(Vec3d{ -0.3,  0.3,     -1.0 }, 0.4, 0x555555, 100.0, 0.6, 0.8, 0.7, 0.0));
		break;
	case 5: {//random
		static minstd_rand gen(0);
		normal_distribution<> dist(0, 2);
		uniform_int_distribution<> colDist(0, 0xffffff);
		for (int i = 0; i < 1000; i++) {
			scene.push_back(make_unique<Sphere>(Vec3d{ 0+dist(gen), 0 + dist(gen),    3 + dist(gen) }, abs(dist(gen))/20, colDist(gen), 20.0, 0.4, 0.1, 0.0, 0.0));
		}
		break;
	}
	}
	bounding = buildBoundingSphere(scene);
}

Color Context::calcColor(Ray r, int recurse, bool firstIteration){
	auto hit = findClosestHitpoint(r);
	if (hit.isHit()) {
		if (isPathTracing) {
			return pathTrace(hit, r, recurse, firstIteration);
		}
		else {
			return rayTrace(hit, r, recurse);
		}
	}
	return ambient;
}