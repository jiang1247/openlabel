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

#include "removedatasourceoperation.h"
#include "openlabel/scene.h"

using namespace OpenLabel;

RemoveDataSourceOperation::RemoveDataSourceOperation(int dataSourceId, Scene *scene,
                                                     QUndoCommand *parent)
    : Operation(scene, parent)
    , _dataSourceId(dataSourceId)
{
    _dataSource = scene->findDataSourceById(dataSourceId);
    if (_dataSource) {
        setText(globalTr("RemoveDataSourceOperation", "Remove %1")
                    .arg(dataSourceTypeString(_dataSource->dataSourceType())));
    }
}

RemoveDataSourceOperation::~RemoveDataSourceOperation() {}

void RemoveDataSourceOperation::redo()
{
    _p_scene->removeDataSource(_dataSourceId);
}

void RemoveDataSourceOperation::undo()
{
    _p_scene->newDataSource((DataSourceTypeId)_dataSource->dataSourceType(),
                            _dataSource->dataSourceId(), _dataSource->properties());
}