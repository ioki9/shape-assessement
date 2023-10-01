#pragma once
#include "ishapevisitor.h"

class ShapeTypeDeducer : public IShapeVisitor
{
public:
    ShapeTypeDeducer() = default;
    void visit(STriangle* shape) override;

    void visit(SEllipse* shape) override;

    void visit(SLine* shape) override;

    void visit(SRectangle* shape) override;
    QString get_type() const;
    static IShape* get_object_by_type(QString type_name);
private:
    QString m_type_name;
};

