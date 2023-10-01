#pragma once
#include "Shapes.h"

class IShapeVisitor
{
public:
    virtual void visit(STriangle* shape) = 0;
    virtual void visit(SEllipse* shape) = 0;
    virtual void visit(SLine* shape) = 0;
    virtual void visit(SRectangle* shape) = 0;
};

