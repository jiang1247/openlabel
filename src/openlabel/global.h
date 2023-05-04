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

#include <QCoreApplication>

#define globalTr(name, msg) QCoreApplication::translate(name, msg)

namespace OpenLabel {

enum ObjectTypeId {
    GraphicsObjectType = 1,
    DataSourceType,
};

enum GraphicsTypeId {
    EllipseGraphicsType = 1,
    TextGraphicsType,
    BarcodeGraphicsType,
    ImageGraphicsType,
};

enum DataSourceTypeId {
    StringDataSouceType = 1,
    DateDataSourceType,
    TimeDataSourceType,
    SerialNumberDataSourceType
};

inline QString graphicsTypeString(int type)
{
    QString msg;
    switch (type) {
    case EllipseGraphicsType:
        msg = globalTr("Global", "Ellipse");
        break;
    case TextGraphicsType:
        msg = globalTr("Global", "Text");
        break;
    case BarcodeGraphicsType:
        msg = globalTr("Global", "Barcode");
        break;
    case ImageGraphicsType:
        msg = globalTr("Global", "Image");
        break;
    default:
        msg = globalTr("Global", "Unknow Graphics");
        break;
    }
    return msg;
}

inline QString dataSourceTypeString(int type)
{
    QString msg;
    switch (type) {
    case StringDataSouceType:
        msg = globalTr("Global", "String");
        break;
    case DateDataSourceType:
        msg = globalTr("Global", "Date");
        break;
    case TimeDataSourceType:
        msg = globalTr("Global", "Time");
        break;
    case SerialNumberDataSourceType:
        msg = globalTr("Global", "Serial Number");
        break;
    default:
        msg = globalTr("Global", "Unknow Data Source");
        break;
    }
    return msg;
}

}
