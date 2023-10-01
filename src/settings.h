#pragma once
#include <QObject>
#include <QApplication>
#include <QSettings>
#include "shapes/Shapes.h"
#include "connectionmanager.h"

using Connections = QList<ConnectionManager::Connection>;
class Settings : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Settings)
public:
    static Settings *get_instance()
    {
        static Settings instance{};
        return &instance;
    }
    void save_shapes(QList<IShape*> shapes);
    void save_connections(Connections connections);
    [[nodiscard]] QList<IShape*> get_shapes() const;
    [[nodiscard]] QList<QPair<int,int>> get_connections() const;
    void set_settings_file(const QString &file_name);
signals:
private:
    explicit Settings(QObject *parent = nullptr);
    ~Settings() override;
    QSettings* m_settings;
};

