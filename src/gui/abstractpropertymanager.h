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

#include <QObject>

#include "openlabel/property.h"

class QtAbstractPropertyBrowser;

namespace OpenLabel {
class Scene;
}

namespace Gui {

class AbstractPropertyHandler;

class AbstractPropertyManager : public QObject
{
    Q_OBJECT
  public:
    explicit AbstractPropertyManager();
    virtual ~AbstractPropertyManager();

    void setSelectedIds(OpenLabel::Scene *scene, const QList<int> &ids);
    virtual void setPropertyBrowser(QtAbstractPropertyBrowser *browser);
    virtual void resetProperties();
    virtual void updateProperties(int id, const OpenLabel::Properties &properties);

  protected:
    QList<AbstractPropertyHandler *> _handlers;
};

} // namespace Gui
