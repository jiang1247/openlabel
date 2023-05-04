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

#include <QHash>
#include <QString>

#define objectPropertyRegister(name) OpenLabel::PropertyIdDispatcher::instance().registerPropertyType(name)
#define objectPropertyId(name) OpenLabel::PropertyIdDispatcher::instance().propertyId(name)
#define objectPropertyName(id) OpenLabel::PropertyIdDispatcher::instance().propertyName(id)

namespace OpenLabel {

class PropertyIdDispatcher
{
  public:
    static PropertyIdDispatcher &instance();

    int registerPropertyType(const QString &propertyName);
    int propertyId(const QString &name) const;
    QString propertyName(int id) const;

  private:
    PropertyIdDispatcher() = default;
    PropertyIdDispatcher(const PropertyIdDispatcher &) = delete;
    PropertyIdDispatcher &operator=(const PropertyIdDispatcher &) = delete;

    int _nextPropertyId = 1;
    QHash<QString, int> _propertyNameToId;
    QHash<int, QString> _propertyIdToName;
};

}
