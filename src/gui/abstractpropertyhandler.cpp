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

#include "abstractpropertyhandler.h"

#include "openlabel/propertyiddispatcher.h"
#include "qtpropertybrowser.h"
#include "qtvariantproperty.h"

using namespace Gui;

AbstractPropertyHandler::AbstractPropertyHandler()
    : _updating(false)
    , _p_browser(nullptr)
    , _p_factory(nullptr)
    , _p_manager(nullptr)
    , _p_scene(nullptr)
{
}

AbstractPropertyHandler::~AbstractPropertyHandler()
{
    if (_p_browser && _p_manager) {
        _p_browser->unsetFactoryForManager(_p_manager);
    }
    if (_p_manager) {
        delete _p_manager;
    }
    if (_p_factory) {
        delete _p_factory;
    }
}

void AbstractPropertyHandler::setSelectedIds(OpenLabel::Scene *scene, const QList<int> &ids)
{
    _p_scene = scene;
    _ids = ids;
}

void AbstractPropertyHandler::setPropertyBrowser(QtAbstractPropertyBrowser *browser)
{
    if (_p_browser && _p_manager) {
        _p_browser->unsetFactoryForManager(_p_manager);
    }
    if (_p_manager) {
        delete _p_manager;
        _p_manager = nullptr;
    }
    if (_p_factory) {
        delete _p_factory;
        _p_factory = nullptr;
    }
    _qProperties.clear();
    if (!browser) {
        return;
    }
    _p_browser = browser;
    _p_manager = new QtVariantPropertyManager;
    _p_factory = new QtVariantEditorFactory;
    _p_browser->setFactoryForManager(_p_manager, _p_factory);
    connect(_p_manager, SIGNAL(valueChanged(QtProperty *, QVariant)), this,
            SLOT(onValueChanged(QtProperty *, QVariant)));
}

QtProperty *AbstractPropertyHandler::findProperty(const QString &name) const
{
    if (!_p_manager) {
        return nullptr;
    }
    QSetIterator<QtProperty *> i(_p_manager->properties());
    while (i.hasNext()) {
        QtProperty *qProperty = i.next();
        if (qProperty->propertyName() == name) {
            return qProperty;
        }
    }
    return nullptr;
}

void AbstractPropertyHandler::updateProperty(int id, const OpenLabel::Property &property)
{
    if (_updating) {
        return;
    }
    if (!_p_manager) {
        return;
    }
    if (_ids.size() != 1 && !_ids.contains(id)) {
        return;
    }
    _updating = true;
    if (_qProperties.contains(property.id)) {
        _p_manager->setValue(_qProperties[property.id], property.value);
    }
    _updating = false;
}

void AbstractPropertyHandler::onValueChanged(QtProperty *property, const QVariant &val)
{
    setPropertyValue(property, val);
}
