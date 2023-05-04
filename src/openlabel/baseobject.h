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
#include <QVariant>

namespace OpenLabel {

class BaseObject
{
  public:
    BaseObject() = default;
    virtual ~BaseObject() = default;

    Property property(int id) const;
    virtual QVariant propertyValue(int id) const;
    virtual void setProperty(const Property &property);
    void setProperties(const Properties &properties);
    virtual Properties properties() const;

    virtual QString objectName() const = 0;
    virtual int objectType() const = 0;

  protected:
    QVector<Property> _properties;
};

}
