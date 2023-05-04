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

#include "adddatasourceoperation.h"
#include "openlabel/scene.h"

using namespace OpenLabel;

AddDataSourceOperation::AddDataSourceOperation(DataSourceTypeId dataType, Properties properties,
                                               Scene *scene, QUndoCommand *parent)
    : Operation(scene, parent)
    , _dataType(dataType)
    , _initProperties(properties)
{
    setText(globalTr("AddDataSourceOperation", "Add %1").arg(dataSourceTypeString(dataType)));
    _dataId = scene->takeNextDataSourceId();
}

AddDataSourceOperation::~AddDataSourceOperation() {}

void AddDataSourceOperation::redo()
{
    _p_scene->newDataSource(_dataType, _dataId, _initProperties);
}

void AddDataSourceOperation::undo()
{
    _p_scene->removeDataSource(_dataId);
}
