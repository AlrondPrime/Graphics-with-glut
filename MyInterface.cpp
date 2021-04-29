//#include <C:\Sources and dependencies\freeglut-3.2.1\include\GL\freeglut.h>
#include <freeglut.h>
//#include "tinyxml.h"
//#include "tinystr.h"
#include "MyInterface.hpp"

void display();
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}
void mouseMove(int x, int y)
{
	//print("mouseMove");
}
void mouseButton(int button, int state, int x, int y)
{
	//print("mouseButton");
}
void reshape(int width, int height)
{
	//print("reshape");
}

Graphic* Graphic::curr{ NULL };

#pragma region Line class definitions

void Graphic::Line::AddPair(const float x, const float y)
{
	if (x < ptr->min_X)
		ptr->min_X = x;
	if (x > ptr->max_X)
		ptr->max_X = x;
	if (y > ptr->max_Y)
		ptr->max_Y = y;
	if (y < ptr->min_Y)
		ptr->min_Y = y;
	points.insert(std::make_pair(x, y));
}

void Graphic::Line::setColor(const float rgb_red, const float rgb_green, const float rgb_blue)
{
	this->rgb_red = rgb_red;
	this->rgb_green = rgb_green;
	this->rgb_blue = rgb_blue;
}

void Graphic::Line::setName(const std::string& name)
{
	this->name = name;
}

const std::map<float, float>& Graphic::Line::getMap() const
{
	return points;
}

#pragma endregion



#pragma region Graphic class definitions

void Graphic::AddLine()
{
	data.push_back(new Line);
	data[data.size() - 1]->ptr = this;
}

void Graphic::setGraphTitle(const std::string& title)
{

}

void Graphic::SaveToFile(const std::string& path)
{

}

void Graphic::LoadFromFile(const std::string& path)
{

}

Graphic::Line& Graphic::at(size_t n)
{
	if (n >= data.size())
		throw std::out_of_range("vector out of range");
	return *data[n];
}

const Graphic::Line& Graphic::at(size_t n) const
{
	if (n >= data.size())
		throw std::out_of_range("vector out of range");
	return *data[n];
}

void Graphic::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
}

void Graphic::Show()
{
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1500, 1000);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("developed by @AlrondPrime");
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Сглаживание точек
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	// Сглаживание линий
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	// Функции обработки ввода
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
	glutReshapeFunc(reshape);

	curr = this;// Sets the static pointer to current Graphic object needed to be drawn to this object

	glutDisplayFunc(display);
	glutMainLoop();
}

const Graphic* Graphic::GetObj()
{
	return curr;
}

void Graphic::DrawOx() const
{
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_LINES);
	{
		glVertex2f(1, -(1 - margin_x));
		glVertex2f(-1, -(1 - margin_x));
		glVertex2f(1, -(1 - margin_x));
		glVertex2f(1 - 0.05f, -(1 - margin_x) + 0.05f);
		glVertex2f(1, -(1 - margin_x));
		glVertex2f(1 - 0.05f, -(1 - margin_x) - 0.05f);
	}
	glEnd();

	glPopMatrix();
}

void Graphic::DrawOy() const
{
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_LINES);
	{
		glVertex2f(-(1 - margin_y), 1);
		glVertex2f(-(1 - margin_y), -1);
		glVertex2f(-(1 - margin_y), 1);
		glVertex2f(-(1 - margin_y) + 0.05f, 1 - 0.05f);
		glVertex2f(-(1 - margin_y), 1);
		glVertex2f(-(1 - margin_y) - 0.05f, 1 - 0.05f);
	}
	glEnd();

	glPopMatrix();
}

void Graphic::DrawGraphic(const Graphic* curr)
{
	for (size_t i{ 0 }; i < curr->Count(); ++i)
	{
		const Graphic::Line& current_line = curr->at(i);//current Line object
		const std::map<float, float>& map = current_line.getMap();//reference to array of coordinates

		float sx = 2.0 / (double(curr->getMax_X()) - curr->getMin_X());
		float sy = 2.0 / (double(curr->getMax_Y()) - curr->getMin_Y());

		float dx = (curr->getMin_X() + curr->getMax_X()) / 2;
		float dy = (curr->getMin_Y() + curr->getMax_Y()) / 2;
		 
		glPushMatrix();
		glLoadIdentity();
		glScalef(sx, sy, 1);
		glTranslatef(-dx + curr->getMargin_X() / sx, -dy + curr->getMargin_Y() / sy, 0);
		glColor3f(current_line.getRGB_red(), current_line.getRGB_green(), current_line.getRGB_blue());

		// Drawing the graphic
		glBegin(GL_LINE_STRIP);
		{
			for (const auto& [key, value] : map)
				glVertex2f(key, value);
		}
		glEnd();

		// Drawing bold points if it is requered
		if (BOLD_POINTS)
		{
			glPointSize(10);
			glEnable(GL_POINT_SMOOTH);
			glBegin(GL_POINTS);
			{
				for (const auto& [key, value] : map)
					glVertex2f(key, value);
			}
			glEnd();
		}
		glPopMatrix();
	}
}

#pragma endregion



#pragma region freeGLUT and OpenGL functions

//Procedure is used in the rendering cycle
void display()
{
	auto current_craphic = Graphic::GetObj();// Gets a pointer to the current Graphic object needed to be drawn

	glClear(GL_COLOR_BUFFER_BIT);//очищаем буфер
	glColor3f(0, 0, 0);//задаем цвет рисования
	glLineWidth(3);//задаем толщину линии

	current_craphic->DrawOx();//drawing Ox axis
	current_craphic->DrawOy();//drawing Oy axis
	Graphic::DrawGraphic(current_craphic);//drawing graphic

	glutSwapBuffers();//прорисовываем буфер на экран
}

#pragma endregion