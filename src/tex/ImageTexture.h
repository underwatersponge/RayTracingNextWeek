#pragma once
#include "../utility/Interval.h"
#include "Texture.h"
#include "load/RTWImage.h"
//#include "imp_stbImage.h"

class ImageTexture : public Texture {
public:
	ImageTexture(std::string fileName): image(fileName.c_str()){}

	Color value(float u, float v, const Point3& point)const override;

private:
	RTWImage image;
};