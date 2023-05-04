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

#include <QHash>
#include <QObject>

#include "openlabel/property.h"
#include "openlabel/sceneeventlistener.h"

class QtAbstractPropertyBrowser;

namespace OpenLabel {
class Scene;
}

namespace Gui {

class AbstractPropertyManager;

class DynamicPropertyManager : public QObject, public OpenLabel::SceneEventListener
{
    Q_OBJECT
  public:
    explicit DynamicPropertyManager(QtAbstractPropertyBrowser *browser);
    virtual ~DynamicPropertyManager();

    void setScene(OpenLabel::Scene *scene);

  protected:
    virtual void onSceneEvent(OpenLabel::SceneEvent *event);
    void resetManager();
    void updateProperties(int id, const OpenLabel::Properties &properties);
    void resetProperties();

  private:
    QtAbstractPropertyBrowser *_p_browser;
    OpenLabel::Scene *_p_scene;
    QList<int> _selectedIds;
    AbstractPropertyManager *_p_manager;
    QHash<int, AbstractPropertyManager *> _managers;
};

} // namespace Gui
