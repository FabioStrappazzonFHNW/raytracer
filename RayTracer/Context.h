#pragma once

#include "Timer.h"
#include "Vec3d.h"
#include "Object.h"
#include "Light.h"
#include "Color.h"
#include "BoundingSphere.h"
#include <vector>
#include <memory>

class Ray;
class Vec2d;
class HitPoint;

class Context
{
public:
	Context();
	~Context()=default;
	Context(const Context&) = delete;
	Context(Context&&) = delete;
	Context& operator=(const Context&) = delete;
	Context& operator=(Context&&) = delete;
	
	void loop();
	void exit();
private:
	Timer timer;
	void handleEvents();
	void render();

	Ray createEyeRay(Vec2d pixel);
	HitPoint findClosestHitpoint(Ray r);
	Color calcColor(Ray r, int recurse, bool firstIteration);
	Color calcPixel(Vec2d pixel, Vec2d windowSize);
	Color pathTrace(HitPoint hit, Ray r, int recurse, bool firstIteration);
	Color rayTrace(HitPoint hit, Ray r, int recurse);
	void switchScene(int s);

	bool running;
	
	
	Vec3d eye;
	Vec3d lookAt;
	const double fow;
	int reflections;
	int raysPerPixel;
	double aliasingDeviation;
	double aperture;
	int samples;
	bool isPathTracing;
	int sceneN;
	Color ambient;
	std::vector<std::unique_ptr<Object>> scene;
	std::unique_ptr<BoundingSphere> bounding;
	std::vector<Light> lights;
	
};


