#include "shapetypededucer.h"

void ShapeTypeDeducer::visit(STriangle *shape) {
    m_type_name = "Triangle";
}

void ShapeTypeDeducer::visit(SEllipse *shape) {
    m_type_name = "Ellipse";
}

void ShapeTypeDeducer::visit(SLine *shape) {
    m_type_name = "Line";
}

void ShapeTypeDeducer::visit(SRectangle *shape) {
    m_type_name = "Rectangle";
}

QString ShapeTypeDeducer::get_type() const {
    return m_type_name;
}

IShape *ShapeTypeDeducer::get_object_by_type(QString type_name)
{
    if(type_name == "Triangle")
        return new STriangle(-1);
    else if(type_name == "Rectangle")
        return new SRectangle(-1);
    else if(type_name == "Line")
        return new SLine(-1);
    else if(type_name == "Ellipse")
        return new SEllipse(-1);
    return nullptr;
}
