#pragma once

#include "film.hpp"
#include "ray.hpp"

class Camera
{
public:
	Camera(Film& film, const glm::vec3& position, const glm::vec3& viewpoint, float fovy);

	Ray generateRay(const glm::ivec2& pixelCoord, const glm::vec2& offset = { .5,.5 }) const;

	void setFilm(Film& film)
	{
		this->film = film;
	}
	Film& getFilm()
	{
		return film;
	}
private:
	glm::vec3 position; // Camera position in world space
	glm::vec3 target; // Target point the camera is looking at
	glm::vec3 up; // Up vector for the camera
	glm::vec3 forward; // Forward vector for the camera
	glm::vec3 right; // Right vector for the camera
	float fov; // Field of view in degrees
	float aspectRatio; // Aspect ratio of the camera
	Film& film; // Pointer to the film object

	glm::mat4 cameraFromClip; // Transformation matrix from camera space to clip space
	glm::mat4 worldFromCamera; // Transformation matrix from world space to camera space
};