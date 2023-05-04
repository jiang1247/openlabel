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

#include "global.h"
#include "operation.h"
#include "property.h"

namespace OpenLabel {

class GraphicsObject;

class AddGraphicsOperation : public Operation
{
  public:
    AddGraphicsOperation(GraphicsTypeId graphicsType, Properties properties,
                         const QList<int> &dataSourceIds, Scene *scene,
                         QUndoCommand *parent = nullptr);
    virtual ~AddGraphicsOperation();

    void redo() override;
    void undo() override;

  private:
    int _graphicsId;
    GraphicsTypeId _graphicsType;
    Properties _initProperties;
    QList<int> _dataSourceIds;
};

}
