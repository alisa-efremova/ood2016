#include "stdafx.h"
#include "ShapeFactory.h"
#include <iostream>
#include <sstream>
#include <exception>
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "SPoint.h"

CShapeFactory::CShapeFactory()
{
	m_shapeFactoryMap.emplace("rectangle", boost::bind(&CShapeFactory::CreateRectangle, *this, _1));
	m_shapeFactoryMap.emplace("triangle", boost::bind(&CShapeFactory::CreateTriangle, *this, _1));
	m_shapeFactoryMap.emplace("ellipse", boost::bind(&CShapeFactory::CreateEllipse, *this, _1));
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description)
{
	try
	{
		std::string shapeType;
		std::istringstream strm(description);
		strm.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		strm >> shapeType;

		return m_shapeFactoryMap.at(shapeType)(strm);
	}
	catch (...)
	{
		throw std::runtime_error("Shape creation error");
	}
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(std::istream & istream)
{
	std::cout << "Create rectangle" << std::endl;
	std::string color;
	double x0, y0, x1, y1;
	istream >> color >> x0 >> y0 >> x1 >> y1;
	std::cout << "Color: " << color << std::endl;
	return std::make_unique<CRectangle>(Color::Black, SPoint(x0, y0), SPoint(x1, y1));
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(std::istream & istream)
{
	return CreateRectangle(istream);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(std::istream & istream)
{
	return CreateRectangle(istream);
}
