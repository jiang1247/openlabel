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

#include <QDockWidget>

#include "openlabel/sceneeventlistener.h"

class QtTreePropertyBrowser;

namespace OpenLabel {
class Scene;
}
namespace Gui {

class DynamicPropertyManager;

class GraphicsPropertyDockWidget : public QDockWidget, public OpenLabel::SceneEventListener
{
    Q_OBJECT
  public:
    explicit GraphicsPropertyDockWidget(QWidget *parent = nullptr);
    virtual ~GraphicsPropertyDockWidget();

    void setScene(OpenLabel::Scene *scene);

  protected:
    virtual void onSceneEvent(OpenLabel::SceneEvent *event) override;

  private:
    QtTreePropertyBrowser *_p_propertyBrowser;
    OpenLabel::Scene *_p_scene;
    DynamicPropertyManager *_p_propertyManager;
};

} // namespace Gui
