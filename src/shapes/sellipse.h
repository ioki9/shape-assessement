#pragma once
#include "ishape.h"
#include <QPainterPath>



class SEllipse : public IShape
{
    Q_OBJECT
public:
    explicit SEllipse(int id,QWidget* parent = nullptr);
    ~SEllipse() override;
    void accept(IShapeVisitor* visitor) override;
    void paintEvent(QPaintEvent* event) override;

};

