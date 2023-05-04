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

#include "addgraphicsoperation.h"
#include "factory.h"
#include "graphicsevent.h"
#include "graphicsobject.h"
#include "scene.h"

#include <QDebug>

using namespace OpenLabel;

AddGraphicsOperation::AddGraphicsOperation(GraphicsTypeId graphicsType, Properties properties,
                                           const QList<int> &dataSourceIds, Scene *scene,
                                           QUndoCommand *parent)
    : Operation(scene, parent)
    , _graphicsType(graphicsType)
    , _initProperties(properties)
    , _dataSourceIds(dataSourceIds)
{
    setText(globalTr("AddGraphicsOperation", "Add %1").arg(graphicsTypeString(graphicsType)));
    _graphicsId = scene->takeNextGraphicsId();
}

AddGraphicsOperation::~AddGraphicsOperation() {}

void AddGraphicsOperation::redo()
{
    _p_scene->clearSelected();
    Properties properties;
    properties.append(_initProperties);
    properties.append(Property(objectPropertyId("Selected"), QVariant(true)));
    _p_scene->newGraphics(_graphicsType, _graphicsId, _dataSourceIds, properties);
    _p_scene->selection(_graphicsType, true);
}

void AddGraphicsOperation::undo()
{
    _p_scene->selection(_graphicsType, false);
    _p_scene->removeGraphics(_graphicsId);
}
