#pragma once
#include <filesystem>
#include <vector>
#include <glm/glm.hpp>

class Film
{
public:
    Film(size_t width, size_t height);
    void save(const std::filesystem::path &fileName);

    size_t getWidth() const { return mWidth; }
    size_t getHeight() const { return mHeight; }
    glm::vec3 getPixel(size_t x, size_t y) { return mPixels[y * mWidth + x]; }
    void ssetPixel(size_t x, size_t y, const glm::vec3 &color) { mPixels[y * mWidth + x] = color; }

private:
    size_t mWidth, mHeight;
    std::vector<glm::vec3> mPixels;
};
