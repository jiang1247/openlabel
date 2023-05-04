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

#include "stringdata.h"
#include "global.h"

using namespace OpenLabel;

PropertyId StringData::StringPropertyId = objectPropertyRegister("String");

StringData::StringData(int id, Scene *scene)
    : DataSource(id, scene)
{
    setName(globalTr("StringData", "String"));
}

QSharedPointer<DataSource> StringData::clone() const
{
    auto cloned = DataSource::clone();
    auto stringData = qSharedPointerCast<StringData>(cloned);
    if (stringData) {
        stringData->_string = this->_string;
    }

    return stringData;
}

QVariant StringData::propertyValue(int id) const
{
    if (id == StringPropertyId) {
        return string();
    }
    return DataSource::propertyValue(id);
}

void StringData::setProperty(const Property &property)
{
    if (property.id == StringPropertyId) {
        if (property.value.canConvert<QString>()) {
            setString(property.value.toString());
        }
    } else {
        DataSource::setProperty(property);
    }
}

Properties StringData::properties() const
{
    Properties properties = DataSource::properties();
    properties.append(Property(StringPropertyId, string()));
    return properties;
}

int StringData::dataSourceType() const
{
    return StringDataSouceType;
}

QString StringData::dataSourceName() const
{
    return QStringLiteral("StringData");
}

QVariant StringData::data() const
{
    return _string;
}

QString StringData::string() const
{
    return _string;
}

void StringData::setString(const QString &string)
{
    if (_string != string) {
        _string = string;
    }
}
