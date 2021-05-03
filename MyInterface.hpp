#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef DEBUG
#include <typeinfo>
#include <limits>
#include<cstdarg>
template <typename T>
void print(T smth)
{
	std::cout << smth << std::endl;
}
void print(int count = 0, ...)
{
	if (count == 0)
		return;
	va_list list;
	va_start(list, count);
	for (; count > 0; --count)
		std::cout << va_arg(list, float) << std::endl;
	va_end(list);
}
#endif

#pragma once

constexpr int ARRAY_SIZE = 1000;
constexpr bool BOLD_POINTS = 1;

//The class represents graphics
class Graphic
{
public:
	//The class represents different lines on the same graphic
	class Line
	{
	private:
		Graphic* ptr = NULL;//pointer to a Graphic object that owns this Line object
		std::map<float, float> points;//array of coordinates
		float rgb_red{ 0 }, rgb_green{ 0 }, rgb_blue{ 0 };//color of the line
		std::string name;//name of the line

	public:
		// Adds a new pair of coordinates to this Line object
		void AddPair(const float x, const float y);
		void setColor(const float rgb_red = 0, const float rgb_green = 0, const float rgb_blue = 0);
		void setName(const std::string& name);
		const std::map<float, float>& getMap() const;

		const float& getRGB_red() const { return rgb_red; }
		const float& getRGB_green() const { return rgb_green; }
		const float& getRGB_blue() const { return rgb_blue; }

		friend class Graphic;
	};

private:
	static Graphic* curr;//reference to a current Graphic object needed to be drawn
	std::vector<Line*> data;//array of Line objects
	float min_X{ 3.40282e+38f }, max_X{ 1.17549e-38f }, min_Y{ 3.40282e+38f }, max_Y{ 1.17549e-38f };
	float margin_x{ 0.04f }, margin_y{ 0.04f };

public:
	void AddLine();
	void setGraphTitle(const std::string& title);
	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);
	void Init(int argc, char** argv);
	void Show();

	size_t Count() const { return data.size(); }
	Line& at(size_t n);
	const Line& at(size_t n) const;

	const float& getMin_X() const { return min_X; }
	const float& getMax_X() const { return max_X; }
	const float& getMin_Y() const { return min_Y; }
	const float& getMax_Y() const { return max_Y; }
	const float& getMargin_X() const { return margin_x; }
	const float& getMargin_Y() const { return margin_y; }

	static const Graphic* GetObj();

	// Procedure of directly drawing the graphic
	static void DrawGraphic(const Graphic* curr);

	//Procedures of drawing axes
	void DrawOx() const;// fgfg

	/// <summary>
	/// drawing Oy axis
	/// </summary>
	void DrawOy() const;

	friend class Line;
};