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

#include "factory.h"

#include "ellipseshader.h"
#include "textshader.h"

#include "ellipsegraphics.h"
#include "textgraphics.h"

#include "stringdata.h"

using namespace OpenLabel;

QSharedPointer<Shader> Factory::createShader(GraphicsTypeId type)
{
    switch (type) {
    case GraphicsTypeId::EllipseGraphicsType:
        return QSharedPointer<EllipseShader>(new EllipseShader);
    case GraphicsTypeId::TextGraphicsType:
        return QSharedPointer<TextShader>(new TextShader);
    default:
        return nullptr;
    }
}

QSharedPointer<GraphicsObject> Factory::createGraphics(GraphicsTypeId type, int id,
                                                           Scene *scene)
{
    switch (type) {
    case GraphicsTypeId::EllipseGraphicsType:
        return QSharedPointer<EllipseGraphics>(new EllipseGraphics(id, scene));
    case GraphicsTypeId::TextGraphicsType:
        return QSharedPointer<TextGraphics>(new TextGraphics(id, scene));
    default:
        return nullptr;
    }
}

QSharedPointer<DataSource> Factory::createDataSource(DataSourceTypeId type, int id,
                                                         Scene *scene)
{
    switch (type) {
    case DataSourceTypeId::StringDataSouceType:
        return QSharedPointer<StringData>(new StringData(id, scene));
    default:
        return nullptr;
    }
}
