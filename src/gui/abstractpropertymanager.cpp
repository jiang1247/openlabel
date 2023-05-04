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

#include "abstractpropertymanager.h"
#include "abstractpropertyhandler.h"

#include "openlabel/property.h"
#include "openlabel/propertyiddispatcher.h"

#include <QDebug>

using namespace Gui;

AbstractPropertyManager::AbstractPropertyManager() {}

AbstractPropertyManager::~AbstractPropertyManager()
{
    qDeleteAll(_handlers);
    _handlers.clear();
}

void AbstractPropertyManager::setSelectedIds(OpenLabel::Scene *scene, const QList<int> &ids)
{
    for (auto handler : _handlers) {
        handler->setSelectedIds(scene, ids);
        handler->initProperies();
    }
}

void AbstractPropertyManager::setPropertyBrowser(QtAbstractPropertyBrowser *browser)
{
    for (auto handler : _handlers) {
        handler->setPropertyBrowser(browser);
    }
}

void AbstractPropertyManager::resetProperties()
{
    for (auto handler : _handlers) {
        handler->resetProperties();
    }
}

void AbstractPropertyManager::updateProperties(int id, const OpenLabel::Properties &properties)
{
    for (auto property : properties) {
        QString name = objectPropertyName(property.id);
        qDebug() << "update properties name " << name;
        for (auto handler : _handlers) {
            auto qProperty = handler->findProperty(name);
            qDebug() << "find property" << qProperty;
            if (qProperty) {
                handler->updateProperty(id, property);
            }
        }
    }
}
