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

#include "dynamicpropertymanager.h"
#include "qtpropertybrowser.h"

#include "multigraphicspropertymanager.h"

#include "openlabel/graphicsevent.h"
#include "openlabel/scene.h"
#include "openlabel/sceneevent.h"

using namespace Gui;

DynamicPropertyManager::DynamicPropertyManager(QtAbstractPropertyBrowser *browser)
    : QObject()
    , _p_browser(browser)
    , _p_scene(nullptr)
    , _p_manager(nullptr)
{
    _managers[OpenLabel::GraphicsTypeId::EllipseGraphicsType] = new MultiGraphicsPropertyManager;
    _managers[OpenLabel::GraphicsTypeId::TextGraphicsType] = new MultiGraphicsPropertyManager;
}

DynamicPropertyManager::~DynamicPropertyManager()
{
    if (_p_scene) {
        _p_scene->removeSceneEventListener(this);
    }
}

void DynamicPropertyManager::setScene(OpenLabel::Scene *scene)
{
    if (_p_scene) {
        _p_scene->removeSceneEventListener(this);
    }
    _p_scene = scene;
    if (_p_scene) {
        _p_scene->addSceneEventListener(this);
    }
}

void DynamicPropertyManager::resetManager()
{
    _p_browser->clear();
    if (_p_manager) {
        _p_manager->setPropertyBrowser(nullptr);
        _p_manager = nullptr;
    }
    if (!_p_scene) {
        return;
    }
    if (_selectedIds.isEmpty()) {
        return;
    }
    int type = -1;
    for (auto id : _selectedIds) {
        auto graphics = _p_scene->findGraphicsById(id);
        if (type < 0) {
            type = graphics->graphicsType();
            continue;
        }
        if (type != graphics->graphicsType()) {
            type = -1;
            break;
        }
    }
    _p_manager = _managers.value(type, new MultiGraphicsPropertyManager);
    _p_manager->setPropertyBrowser(_p_browser);
    _p_manager->setSelectedIds(_p_scene, _selectedIds);
}

void DynamicPropertyManager::updateProperties(int id, const OpenLabel::Properties &properties)
{
    if (!_p_manager) {
        return;
    }
    _p_manager->updateProperties(id, properties);
}

void DynamicPropertyManager::resetProperties()
{
    if (!_p_manager) {
        return;
    }
    _p_manager->resetProperties();
}

void DynamicPropertyManager::onSceneEvent(OpenLabel::SceneEvent *event)
{
    if (!_p_scene) {
        return;
    }
    if (event->type() == OpenLabel::SceneEventType::GraphicsSelect ||
        event->type() == OpenLabel::SceneEventType::GraphicsDeselect) {
        auto newIds = _p_scene->selectedGraphicsIds();
        if (newIds != _selectedIds) {
            _selectedIds = newIds;
            resetManager();
        }
    } else if (event->type() == OpenLabel::SceneEventType::GraphicsModify) {
        auto modifyEvent = dynamic_cast<OpenLabel::GraphicsModifyEvent *>(event);
        if (modifyEvent) {
            if (_selectedIds.size() == 1 && _selectedIds[0] == modifyEvent->id()) {
                updateProperties(modifyEvent->id(), modifyEvent->properties());
            } else {
                resetProperties();
            }
        }
    }
}
