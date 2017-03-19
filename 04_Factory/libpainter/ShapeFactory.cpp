#include "stdafx.h"
#include "ShapeFactory.h"
#include <sstream>
#include <exception>
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

using namespace std;

CShapeFactory::CShapeFactory()
{
	m_shapeFactoryMap.emplace("rectangle", boost::bind(&CShapeFactory::CreateRectangle, *this, _1));
	m_shapeFactoryMap.emplace("triangle", boost::bind(&CShapeFactory::CreateTriangle, *this, _1));
	m_shapeFactoryMap.emplace("ellipse", boost::bind(&CShapeFactory::CreateEllipse, *this, _1));
	m_shapeFactoryMap.emplace("regular_polygon", boost::bind(&CShapeFactory::CreateRegularPolygon, *this, _1));
}

unique_ptr<CShape> CShapeFactory::CreateShape(const string & description)
{
	try
	{
		istringstream strm(description);
		strm.exceptions(ios_base::failbit | ios_base::badbit);

		string shapeType;
		strm >> shapeType;

		return m_shapeFactoryMap.at(shapeType)(strm);
	}
	catch (...)
	{
		throw runtime_error("Invalid shape description");
	}
}

unique_ptr<CShape> CShapeFactory::CreateRectangle(istream & istream)
{
	Color color;
	SPoint leftTop, bottomRight;
	istream >> color >> leftTop >> bottomRight;
	return make_unique<CRectangle>(color, leftTop, bottomRight);
}

unique_ptr<CShape> CShapeFactory::CreateTriangle(istream & istream)
{
	Color color;
	SPoint v1, v2, v3;
	istream >> color >> v1 >> v2 >> v3;
	return make_unique<CTriangle>(color, v1, v2, v3);
}

unique_ptr<CShape> CShapeFactory::CreateEllipse(istream & istream)
{
	Color color;
	SPoint center;
	double hRadius, vRadius;
	istream >> color >> center >> hRadius >> vRadius;
	return make_unique<CEllipse>(color, center, hRadius, vRadius);
}

unique_ptr<CShape> CShapeFactory::CreateRegularPolygon(istream & istream)
{
	Color color;
	unsigned vertexCount;
	double radius;
	SPoint center;
	istream >> color >> vertexCount >> center >> radius;
	return make_unique<CRegularPolygon>(color, vertexCount, center, radius);
}

std::map<std::string, Color> colorMap = {
	{ "green", Color::Green },
	{ "red", Color::Red },
	{ "blue", Color::Blue },
	{ "yellow", Color::Yellow },
	{ "pink", Color::Pink },
	{ "black", Color::Black }
};

istream & operator >> (istream & istream, Color & color) {

	string colorDescription;
	istream >> colorDescription;
	color = colorMap.at(colorDescription);
	return istream;
}

istream & operator >> (istream & istream, SPoint & point) {

	istream >> point.x >> point.y;
	return istream;
}