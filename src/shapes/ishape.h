#pragma once

#include <QWidget>
#include <QPainterPath>
#include <QMoveEvent>
class IShapeVisitor;
class IShape : public QWidget
{
    Q_OBJECT
public:
    explicit IShape(int id= -1,QWidget* parent = nullptr);
    virtual ~IShape();
    virtual void draw(const QPoint& start,const QSize& bound_rect);
    //returns center in absolute coords.
    virtual QPoint center() const;
    [[nodiscard]] virtual QPair<QPoint,QSize> get_draw_params() const;
    //override if not using m_path to draw the shape. Using path for shape detection.
    [[nodiscard]] virtual bool contains_shape(const QPointF &point) const;
    void moveEvent(QMoveEvent* event) override;
    void set_id(int id);
    //for redrawing purposes mainly
    void set_draw_params(const QPair<QPoint,QSize>& params);
    [[nodiscard]] int id();
    //for visitors
    virtual void accept(IShapeVisitor* visitor) = 0;

private:
    virtual void paintEvent(QPaintEvent *event) override = 0;
protected:
    static std::atomic_int m_available_id;
    int m_id;
    QPoint m_center;
    QSize m_bound_rect;
    QPoint m_start;
    QPair<QPoint,QSize> m_draw_params;
    QPainterPath m_path;
};


