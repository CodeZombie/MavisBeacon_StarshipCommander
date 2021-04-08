#include "Spline.h"

Spline::Spline() {

}
glm::vec3 Spline::getPosition() {
	float t = currentLocation;

	if (reachedEnd()) {
		return points[points.size() - 2];
	}
	int p0, p1, p2, p3;
	if (!looping)
	{
		p1 = (int)t + 1;
		p2 = p1 + 1;
		p3 = p2 + 1;
		p0 = p1 - 1;
	}
	else
	{
		t = fmod(t, points.size());
		p1 = (int)t;
		p2 = (p1 + 1) % points.size();
		p3 = (p2 + 1) % points.size();
		p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
	}

	t = t - (int)t;

	float tt = t * t;
	float ttt = tt * t;

	float q1 = -ttt + 2.0f*tt - t;
	float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
	float q3 = -3.0f*ttt + 4.0f*tt + t;
	float q4 = ttt - tt;

	float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
	float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);
	float tz = 0.5f * (points[p0].z * q1 + points[p1].z * q2 + points[p2].z * q3 + points[p3].z * q4);

	return glm::vec3(tx, ty, tz);
}

bool Spline::reachedEnd() {
	if (looping) {
		return false;
	}
	if (currentLocation >= points.size() - 4) {
		return true;
	}
	return false;
}