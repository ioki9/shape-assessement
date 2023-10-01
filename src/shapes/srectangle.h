#pragma once
#include "ishape.h"
#include <QPainterPath>

class SRectangle : public IShape
{
    Q_OBJECT
public:
    SRectangle(int id,QWidget* parent = nullptr);
    ~SRectangle() override;
    void accept(IShapeVisitor* visitor) override;
    void paintEvent(QPaintEvent* event) override;

};


