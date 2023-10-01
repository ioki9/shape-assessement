#include "settings.h"
#include "shapes/shapetypededucer.h"
Settings::Settings(QObject *parent)
    : QObject{parent}
{
}

Settings::~Settings()
{

}

void Settings::save_shapes(QList<IShape *> shapes)
{
    if(!m_settings)
        return;
    m_settings->beginWriteArray("shapes");
    ShapeTypeDeducer deducer;
    for (int i = 0; i < shapes.size(); ++i) {
        m_settings->setArrayIndex(i);
        m_settings->setValue("start_point", shapes[i]->get_draw_params().first);
        m_settings->setValue("bounding_rect",shapes[i]->get_draw_params().second);
        m_settings->setValue("id",shapes[i]->id());
        shapes[i]->accept(&deducer);
        m_settings->setValue("type",deducer.get_type());
    }
    m_settings->endArray();
}

void Settings::save_connections(Connections connections)
{
    if(!m_settings)
        return;
    m_settings->beginWriteArray("connections");
    for(int i{0}; i < connections.size();i++)
    {
        m_settings->setArrayIndex(i);
        m_settings->setValue("id_first", connections[i].connection.first->id());
        m_settings->setValue("id_second", connections[i].connection.second->id());
    }
    m_settings->endArray();

}

QList<IShape*> Settings::get_shapes() const
{
    if(!m_settings)
        return {};
    QList<IShape*> result;
    int size = m_settings->beginReadArray("shapes");
    for (int i = 0; i < size; ++i) {
        m_settings->setArrayIndex(i);
        IShape* shape;
        QPair<QPoint,QSize> draw_params;
        shape = ShapeTypeDeducer::get_object_by_type(m_settings->value("type").toString());
        draw_params.first = m_settings->value("start_point").toPoint();
        draw_params.second = m_settings->value("bounding_rect").toSize();
        shape->set_draw_params(draw_params);
        shape->set_id(m_settings->value("id").toInt());
        result.append(shape);
    }
    m_settings->endArray();
    return result;
}

QList<QPair<int,int>> Settings::get_connections() const
{
    if(!m_settings)
        return {};

    QList<QPair<int,int>> result;
    int size = m_settings->beginReadArray("connections");
    for (int i = 0; i < size; ++i) {
        QPair<int,int> pair;
        m_settings->setArrayIndex(i);
        pair.first = m_settings->value("id_first").toInt();
        pair.second = m_settings->value("id_second").toInt();
        result.append(std::move(pair));
    }
    m_settings->endArray();
    return result;
}

void Settings::set_settings_file(const QString& file_name)
{
    if(m_settings)
        m_settings->deleteLater();
    m_settings = new QSettings(file_name,QSettings::Format::IniFormat);
    m_settings->setAtomicSyncRequired(true);

}


