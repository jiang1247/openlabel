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

#include "basepropertyhandler.h"
#include "auxiliary/recttransform.h"
#include "openlabel/modifygraphicsoperation.h"
#include "openlabel/scene.h"
#include "qtvariantproperty.h"

#include <QDebug>

using namespace Gui;

BasePropertyHandler::BasePropertyHandler() {}

BasePropertyHandler::~BasePropertyHandler() {}

void BasePropertyHandler::initProperies()
{
    if (!_p_scene || !_p_manager) {
        return;
    }
    if (_ids.isEmpty()) {
        return;
    }
    if (!_qProperties.isEmpty()) {
        _qProperties.clear();
    }
    QRectF boundingRect(0.0, 0.0, 0.0, 0.0);
    for (auto id : _ids) {
        auto graphics = _p_scene->findRealGraphicsById(id);
        if (!graphics) {
            continue;
        }
        boundingRect = boundingRect.united(graphics->boundingRect());
    }
    QtVariantProperty *pPos = _p_manager->addProperty(QVariant::PointF, tr("Position"));
    pPos->setValue(boundingRect.topLeft());
    _p_browser->addProperty(pPos);
    _qProperties[objectPropertyId("Position")] = pPos;
    QtVariantProperty *pSize = _p_manager->addProperty(QVariant::SizeF, tr("Size"));
    pSize->setValue(boundingRect.size());
    _p_browser->addProperty(pSize);
    _qProperties[objectPropertyId("Size")] = pSize;
}

void BasePropertyHandler::resetProperties()
{
    if (_updating) {
        return;
    }
    if (!_p_scene || !_p_manager) {
        return;
    }
    if (_ids.isEmpty()) {
        return;
    }
    _updating = true;
    QRectF boundingRect(0.0, 0.0, 0.0, 0.0);
    for (auto id : _ids) {
        auto graphics = _p_scene->findRealGraphicsById(id);
        if (!graphics) {
            continue;
        }
        boundingRect = boundingRect.united(graphics->boundingRect());
    }
    int posId = objectPropertyId("Position");
    int sizeId = objectPropertyId("Size");
    if (_qProperties.contains(posId)) {
        _p_manager->setValue(_qProperties[posId], boundingRect.topLeft());
    }
    if (_qProperties.contains(sizeId)) {
        _p_manager->setValue(_qProperties[sizeId], boundingRect.size());
    }
    _updating = false;
}

void BasePropertyHandler::setPropertyValue(QtProperty *property, const QVariant &val)
{
    if (_updating) {
        return;
    }
    if (!_p_scene || !_p_manager) {
        return;
    }
    if (_ids.isEmpty()) {
        return;
    }
    if (!_qProperties.values().contains(property)) {
        return;
    }
    _updating = true;
    QRectF boundingRect(0.0, 0.0, 0.0, 0.0);
    for (auto id : _ids) {
        auto graphics = _p_scene->findRealGraphicsById(id);
        if (!graphics) {
            continue;
        }
        boundingRect = boundingRect.united(graphics->boundingRect());
    }
    int propertyId = _qProperties.key(property);
    int posId = objectPropertyId("Position");
    int sizeId = objectPropertyId("Size");
    if (propertyId == posId && val.canConvert<QPointF>()) {
        QPointF delta = val.toPointF() - boundingRect.topLeft();
        QUndoCommand *pCommand = new QUndoCommand(tr("Move graphics"));
        for (auto id : _ids) {
            auto graphics = _p_scene->findGraphicsById(id);
            if (!graphics) {
                continue;
            }
            QPointF newPos = graphics->position() + delta;
            OpenLabel::Properties properties;
            properties << OpenLabel::Property(posId, newPos);
            new OpenLabel::ModifyGraphicsOperation(id, properties, _p_scene, pCommand);
        }
        _p_scene->pushOperation(pCommand);
    } else if (propertyId == sizeId && val.canConvert<QSizeF>()) {
        QSizeF newSize = val.toSizeF();
        QRectF newRect(boundingRect.x(), boundingRect.y(), newSize.width(), newSize.height());
        QUndoCommand *pCommand = new QUndoCommand(tr("Resize graphics"));
        for (auto id : _ids) {
            auto graphics = _p_scene->findGraphicsById(id);
            if (!graphics) {
                continue;
            }
            QRectF rect = Utils::RectTransform::subRectTransform(boundingRect, newRect,
                                                                 graphics->boundingRect());
            OpenLabel::Properties properties;
            properties << OpenLabel::Property(posId, rect.topLeft())
                       << OpenLabel::Property(sizeId, rect.size());
            new OpenLabel::ModifyGraphicsOperation(id, properties, _p_scene, pCommand);
        }
        _p_scene->pushOperation(pCommand);
    }
    _updating = false;
}
