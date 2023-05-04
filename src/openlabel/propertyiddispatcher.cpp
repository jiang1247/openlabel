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

#include "propertyiddispatcher.h"

#include <QDebug>

using namespace OpenLabel;

PropertyIdDispatcher &PropertyIdDispatcher::instance()
{
    static PropertyIdDispatcher instance;
    return instance;
}

int PropertyIdDispatcher::registerPropertyType(const QString &propertyName)
{
    if (_propertyNameToId.contains(propertyName)) {
        return _propertyNameToId[propertyName];
    }

    qDebug() << "register property type " << propertyName;

    int propertyId = _nextPropertyId++;
    _propertyNameToId[propertyName] = propertyId;
    _propertyIdToName[propertyId] = propertyName;
    return propertyId;
}

int PropertyIdDispatcher::propertyId(const QString &name) const
{
    return _propertyNameToId.value(name, -1);
}

QString PropertyIdDispatcher::propertyName(int id) const
{
    return _propertyIdToName.value(id, QString());
}
