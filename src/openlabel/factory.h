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
#include "datasource.h"
#include "graphicsobject.h"
#include "shader.h"
#include <QSharedPointer>

namespace OpenLabel {

class Factory
{
  public:
    static QSharedPointer<Shader> createShader(GraphicsTypeId type);
    static QSharedPointer<GraphicsObject> createGraphics(GraphicsTypeId type, int id, Scene *scene);
    static QSharedPointer<DataSource> createDataSource(DataSourceTypeId type, int id, Scene *scene);

  private:
    Factory() = delete;
    Factory(const Factory &) = delete;
    Factory &operator=(const Factory &) = delete;
};

}
