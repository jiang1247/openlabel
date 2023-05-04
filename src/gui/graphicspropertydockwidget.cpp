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

#include "graphicspropertydockwidget.h"
#include "dynamicpropertymanager.h"
#include "mainwindow.h"

#include "qttreepropertybrowser.h"

#include "openlabel/scene.h"

using namespace Gui;

GraphicsPropertyDockWidget::GraphicsPropertyDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , _p_scene(nullptr)
{
    setWindowTitle(tr("Graphics property"));

    _p_propertyBrowser = new QtTreePropertyBrowser(this);
    setWidget(_p_propertyBrowser);

    _p_propertyManager = new DynamicPropertyManager(_p_propertyBrowser);
}

GraphicsPropertyDockWidget::~GraphicsPropertyDockWidget()
{
    if (_p_scene) {
        _p_scene->removeSceneEventListener(this);
    }
}

void GraphicsPropertyDockWidget::setScene(OpenLabel::Scene *scene)
{
    if (_p_scene) {
        _p_scene->removeSceneEventListener(this);
    }
    _p_scene = scene;
    if (_p_scene) {
        _p_scene->addSceneEventListener(this);
    }
    _p_propertyManager->setScene(scene);
}

void GraphicsPropertyDockWidget::onSceneEvent(OpenLabel::SceneEvent *event)
{
    if (!_p_scene) {
        return;
    }
    if (_p_scene->hasSelected()) {
        //        show();
    } else {
        //        hide();
    }
}
