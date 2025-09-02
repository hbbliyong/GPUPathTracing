#include "camera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(Film& film, const glm::vec3& position, const glm::vec3& viewpoint, float fovy) :
	position(position),
	target(viewpoint),
	up(0, 1, 0),
	fov(fovy),
	film(film)
{
	cameraFromClip = glm::inverse(glm::perspective(glm::radians(fovy),
		static_cast<float>(film.getWidth()) / static_cast<float>(film.getHeight()), 1.0f, 2.0f));
	
	worldFromCamera =glm::inverse( glm::lookAt(position, target, up));
}


Ray Camera::generateRay(const glm::ivec2& pixelCoord, const glm::vec2& offset) const {
	glm::vec2 pixelNDC = { (pixelCoord.x + offset.x) / film.getWidth(), (pixelCoord.y + offset.y) / film.getHeight() };
	pixelNDC.y = 1.0f - pixelNDC.y; // Flip y coordinate to match OpenGL's coordinate system
	pixelNDC = pixelNDC * 2.0f - 1.0f; // Convert to NDC space
	glm::vec4 rayClip = glm::vec4(pixelNDC.x, pixelNDC.y, 0.0f, 1.0f); // Ray in clip space

	glm::vec3 world =worldFromCamera* cameraFromClip * rayClip; // Ray in camera space

	return { position, glm::normalize(world-position) }; // Ray in world space
}