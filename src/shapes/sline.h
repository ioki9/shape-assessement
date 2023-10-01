#pragma once
#include "ishape.h"



class SLine : public IShape
{
    Q_OBJECT
public:
    explicit SLine(int id,QWidget* parent = nullptr);
    ~SLine() override;
    void accept(IShapeVisitor* visitor) override;
    void draw(const QPoint& start,const QSize& bound_rect) override;
    virtual void draw(const QPoint& start, const QPoint& end);
    QPoint center() const override;
    [[nodiscard]] bool contains_shape(const QPointF &point) const override;
    void paintEvent(QPaintEvent* event) override;
private:

    bool m_mirrored{false};
};
