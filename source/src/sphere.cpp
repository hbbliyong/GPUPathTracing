#include "sphere.hpp"

std::optional<float> Sphere::intersect(const Ray& ray) const{
    glm::vec3 oc = ray.origin - center;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc, oc) - radius * radius;
    float delta = b * b - 4 * a * c;

    if (delta < 0) {
        return std::nullopt; // No intersection
    } else {
        float t1 = (-b - sqrt(delta)) / (2.0f * a);
        float t2 = (-b + sqrt(delta)) / (2.0f * a);

        // We want the closest positive intersection
        float t = (t1 > 0) ? t1 : ((t2 > 0) ? t2 : -1);
        if (t < 0) {
            return std::nullopt; // Intersection is behind the ray origin or beyond the ray length
        }

        return t; // Return the distance to the intersection point
    }
}