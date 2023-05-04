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

#include "removegraphicsoperation.h"
#include "factory.h"
#include "graphicsobject.h"
#include "scene.h"

#include <QDebug>

using namespace OpenLabel;

RemoveGraphicsOperation::RemoveGraphicsOperation(int graphicsId, Scene *scene, QUndoCommand *parent)
    : Operation(scene, parent)
    , _graphicsId(graphicsId)
{
    _graphics = scene->findGraphicsById(graphicsId);
    if (_graphics) {
        _dataSourceIds = scene->getDataForGraphics(graphicsId);
        setText(globalTr("RemoveGraphicsOperation", "Remove %1")
                    .arg(graphicsTypeString(_graphics->graphicsType())));
    }
}

RemoveGraphicsOperation::~RemoveGraphicsOperation() {}

void RemoveGraphicsOperation::redo()
{
    if (_p_scene->isSelected(_graphicsId)) {
        _p_scene->selection(_graphicsId, false);
    }
    _p_scene->removeGraphics(_graphicsId);
}

void RemoveGraphicsOperation::undo()
{
    _p_scene->newGraphics((GraphicsTypeId)_graphics->graphicsType(), _graphics->graphicsId(),
                          _dataSourceIds, _graphics->properties());
    _p_scene->selection(_graphics->graphicsId(), true);
}
