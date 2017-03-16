#pragma once
#include "IShapeFactory.h"
#include "Shape.h"
#include <map>
#include <memory>
#include <boost/function.hpp>
#include <boost/bind.hpp>

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description) override;

private:
	typedef boost::function<std::unique_ptr<CShape>(std::istream &)> CreateShapeFunction;
	typedef std::map<std::string, CreateShapeFunction> ShapeFactoryMap;

	std::unique_ptr<CShape> CreateRectangle(std::istream & istream);
	std::unique_ptr<CShape> CreateTriangle(std::istream & istream);
	std::unique_ptr<CShape> CreateEllipse(std::istream & istream);

	ShapeFactoryMap m_shapeFactoryMap;
};

