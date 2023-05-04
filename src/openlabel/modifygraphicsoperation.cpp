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

#include "modifygraphicsoperation.h"
#include "graphicsevent.h"
#include "scene.h"

#include <QDebug>

using namespace OpenLabel;

ModifyGraphicsOperation::ModifyGraphicsOperation(int graphicsId, Properties properties,
                                                 Scene *scene, QUndoCommand *parent)
    : Operation(scene, parent)
    , _graphicsId(graphicsId)
    , _properties(properties)
{
}

ModifyGraphicsOperation::~ModifyGraphicsOperation() {}

void ModifyGraphicsOperation::redo()
{
    qDebug() << "ModifyGraphicsOperation::redo";
    swap();
}

void ModifyGraphicsOperation::undo()
{
    qDebug() << "ModifyGraphicsOperation::undo";
    swap();
}

void ModifyGraphicsOperation::swap()
{
    auto graphics = _p_scene->findRealGraphicsById(_graphicsId);
    if (graphics.isNull()) {
        return;
    }
    Properties oldProperties;
    for (const auto &property : _properties) {
        oldProperties.append(graphics->property(property.id));
    }
    graphics->setProperties(_properties);
    auto event = new GraphicsModifyEvent(_graphicsId, _properties);
    _p_scene->processSceneEvent(event);
    delete event;
    _p_scene->selection(_graphicsId, true);

    std::swap(_properties, oldProperties);
}
