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

class GraphicsAddEvent : public SceneEvent
{
  public:
    GraphicsAddEvent(const QList<int> &ids)
        : SceneEvent(GraphicsAdd)
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

class GraphicsRemoveEvent : public SceneEvent
{
  public:
    GraphicsRemoveEvent(const QList<int> &ids)
        : SceneEvent(GraphicsRemove)
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

class GraphicsSelectEvent : public SceneEvent
{
  public:
    GraphicsSelectEvent(const QList<int> &ids)
        : SceneEvent(GraphicsSelect)
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

class GraphicsDeselectEvent : public SceneEvent
{
  public:
    GraphicsDeselectEvent(const QList<int> &ids)
        : SceneEvent(GraphicsDeselect)
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

class GraphicsModifyEvent : public SceneEvent
{
  public:
    GraphicsModifyEvent(int id, const Properties &properties)
        : SceneEvent(GraphicsModify)
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
