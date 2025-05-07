#include "film.hpp"
#include <fstream>
Film::Film(size_t width, size_t height)
    : mWidth(width), mHeight(height)
{
    mPixels.resize(width * height);
}
void Film::save(const std::filesystem::path &fileName)
{
    std::ofstream file(fileName);
    file << "P3\n"
         << mWidth << ' ' << mHeight << "\n255\n";
    for (size_t y = 0; y < mHeight; y++)
    {
        for (size_t x = 0; x < mWidth; x++)
        {
            const glm::vec3 &color = getPixel(x, y);
            glm::ivec3 color_i = glm::clamp(color * 255.f, 0.f, 255.f);
            file << color_i.x << ' ' << color_i.y << ' ' << color_i.z << '\n';
        }
    }
}