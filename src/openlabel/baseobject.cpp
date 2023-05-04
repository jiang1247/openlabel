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

#include "baseobject.h"

using namespace OpenLabel;

Property BaseObject::property(int id) const
{
    return Property(id, propertyValue(id));
}

QVariant BaseObject::propertyValue(int id) const
{
    for (auto it = _properties.begin(); it != _properties.end(); ++it) {
        if (it->id == id) {
            return it->value;
        }
    }
    return QVariant();
}

void BaseObject::setProperty(const Property &property)
{
    for (int i = 0; i < _properties.size(); i++) {
        if (_properties.at(i).id == property.id) {
            _properties.replace(i, property);
            break;
        }
    }
}

void BaseObject::setProperties(const Properties &properties)
{
    for (const auto &value : properties) {
        setProperty(value);
    }
}

Properties BaseObject::properties() const
{
    return _properties;
}
