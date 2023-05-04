/*
 * This file is part of the OpenLabel project.
 *
 * Copyright (C) 2023 JunJ <jun4331247@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "datasource.h"
#include "factory.h"

#include <QDebug>

using namespace OpenLabel;

PropertyId DataSource::NamePropertyId = objectPropertyRegister("name");

DataSource::DataSource(int id, Scene *scene)
    : _p_scene(scene)
    , _dataSourceId(id)
{
    qDebug() << "data source is created, id " << _dataSourceId;
}

DataSource::~DataSource()
{
    qDebug() << "data source is destroyed, id " << _dataSourceId;
}

bool DataSource::operator==(const DataSource &other) const
{
    return _dataSourceId == other._dataSourceId;
}

bool DataSource::operator!=(const DataSource &other) const
{
    return !(*this == other);
}

void DataSource::initializeProperties()
{
    _name = globalTr("DataSource", "DataSource");
}

QVariant DataSource::propertyValue(int id) const
{
    if (id == NamePropertyId) {
        return name();
    }
    return BaseObject::propertyValue(id);
}

void DataSource::setProperty(const Property &property)
{
    if (property.id == NamePropertyId) {
        if (property.value.canConvert<QString>()) {
            QString nm = property.value.toString();
            qDebug() << "data source set property, set name" << nm;
            setName(nm);
        }
    } else {
        BaseObject::setProperty(property);
    }
}

Properties DataSource::properties() const
{
    Properties properties = BaseObject::properties();
    properties.append(Property(NamePropertyId, name()));
    return properties;
}

QString DataSource::objectName() const
{
    return QStringLiteral("DataSource");
}

int DataSource::objectType() const
{
    return DataSourceType;
}

QSharedPointer<DataSource> DataSource::clone() const
{
    auto cloned = Factory::createDataSource((DataSourceTypeId)this->dataSourceType(),
                                                this->dataSourceId(), this->_p_scene);
    cloned->_name = this->_name;

    return cloned;
}

void DataSource::onSceneEvent(SceneEvent *event)
{
    Q_UNUSED(event);
}

int DataSource::dataSourceId() const
{
    return _dataSourceId;
}

QString DataSource::name() const
{
    return _name;
}

void DataSource::setName(const QString &name)
{
    if (_name != name) {
        _name = name;
    }
}

Scene *DataSource::scene()
{
    return _p_scene;
}
