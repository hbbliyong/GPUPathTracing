#include "sphere.hpp"

std::optional<HitInfo> Sphere::intersect(const Ray &ray, float t_min, float t_max) const
{
    glm::vec3 oc = ray.origin - center;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc, oc) - radius * radius;
    float delta = b * b - 4 * a * c;

    if (delta < 0)
    {
        return std::nullopt; // No intersection
    }
    else
    {
        float t1 = (-b - sqrt(delta)) / (2.0f * a);
        float t2 = (-b + sqrt(delta)) / (2.0f * a);

        // We want the closest positive intersection
        float t = (t1 > 0) ? t1 : ((t2 > 0) ? t2 : -1);
        if (t < t_min || t > t_max)
        {
            return std::nullopt; // Intersection is behind the ray origin or beyond the ray length
        }
        glm::vec3 hit = ray.hit(t);
        glm::vec3 normal = glm::normalize(hit - center);
        return HitInfo{t, hit, normal}; // Return the distance to the intersection point
    }
}