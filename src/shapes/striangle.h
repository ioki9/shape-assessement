#pragma once
#include "ishape.h"
#include <QPainterPath>


class STriangle : public IShape
{
    Q_OBJECT
public:
    explicit STriangle(int id,QWidget* parent = nullptr);
    ~STriangle() override;
    void accept(IShapeVisitor* visitor) override;
    void draw(const QPoint& start, const QSize& bound_rect) override;
    void paintEvent(QPaintEvent* event) override;

private:
    bool m_upwards{false};

};

