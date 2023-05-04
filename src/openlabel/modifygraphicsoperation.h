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

#include "graphicsobject.h"
#include "operation.h"
#include "property.h"
#include <QSharedPointer>

namespace OpenLabel {

class GraphicsObject;

class ModifyGraphicsOperation : public Operation
{
  public:
    ModifyGraphicsOperation(int graphicsId, Properties properties, Scene *scene,
                            QUndoCommand *parent = nullptr);
    virtual ~ModifyGraphicsOperation();

    virtual void redo() override;
    virtual void undo() override;

  private:
    void swap();

    int _graphicsId;
    Properties _properties;
};

}
