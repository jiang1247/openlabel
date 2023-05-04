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

#include "property.h"
#include "sceneevent.h"

namespace OpenLabel {

class DataSourceAddEvent : public SceneEvent
{
  public:
    DataSourceAddEvent(const QList<int> &ids)
        : SceneEvent(DataSourceAdd)
        , _ids(ids)
    {
    }

    QList<int> ids() const
    {
        return _ids;
    }

  private:
    QList<int> _ids;
};

class DataSourceRemoveEvent : public SceneEvent
{
  public:
    DataSourceRemoveEvent(const QList<int> &ids)
        : SceneEvent(DataSourceRemove)
        , _ids(ids)
    {
    }

    QList<int> ids() const
    {
        return _ids;
    }

  private:
    QList<int> _ids;
};

class DataSourceModifyEvent : public SceneEvent
{
  public:
    DataSourceModifyEvent(int id, const Properties &properties)
        : SceneEvent(DataSourceModify)
        , _id(id)
        , _properties(properties)
    {
    }

    int id() const
    {
        return _id;
    }
    Properties properties() const
    {
        return _properties;
    }

  private:
    int _id;
    Properties _properties;
};

}
