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

#pragma once

#include "baseobject.h"
#include "propertyiddispatcher.h"
#include "sceneeventlistener.h"
#include <QSharedPointer>

namespace OpenLabel {

class Scene;

class DataSource : public BaseObject, public SceneEventListener
{
    static const PropertyId NamePropertyId;

  public:
    explicit DataSource(int id, Scene *scene = nullptr);
    DataSource(const DataSource &other) = delete;
    virtual ~DataSource();

    DataSource &operator=(const DataSource &other) = delete;
    bool operator==(const DataSource &other) const;
    bool operator!=(const DataSource &other) const;

    virtual void initializeProperties();

    virtual QVariant propertyValue(int id) const override;
    virtual void setProperty(const Property &property) override;
    virtual Properties properties() const override;

    virtual QVariant data() const = 0;

    virtual QString objectName() const override;
    virtual int objectType() const override;

    virtual int dataSourceType() const = 0;
    virtual QString dataSourceName() const = 0;

    virtual QSharedPointer<DataSource> clone() const;

    virtual void onSceneEvent(SceneEvent *event) override;

    int dataSourceId() const;

    QString name() const;
    void setName(const QString &name);

    Scene *scene();

  protected:
    Scene *_p_scene;

    int _dataSourceId;
    QString _name;
};

using DataSources = QList<QSharedPointer<DataSource>>;

}
