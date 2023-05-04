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

#include "graphicsitem.h"
#include "openlabel/global.h"
#include "openlabel/shader.h"

#include <QDebug>

using namespace Gui;

GraphicsItem::GraphicsItem(QSharedPointer<OpenLabel::GraphicsObject> object, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , _object(object)
{
    setPos(_object->position());
}

GraphicsItem::~GraphicsItem() {}

QSharedPointer<OpenLabel::GraphicsObject> GraphicsItem::graphicsObject() const
{
    return _object->clone();
}

int GraphicsItem::graphicsId() const
{
    return _object->graphicsId();
}

bool GraphicsItem::graphicsIsSelected() const
{
    return _object->isSelected();
}

QRectF GraphicsItem::boundingRect() const
{
    if (!_object)
        return QRectF(0.0, 0.0, 200.0, 200.0);
    return QRectF(QPointF(0.0, 0.0), _object->size());
}

void GraphicsItem::forceUpdate()
{
    qDebug() << "forceUpdate";
    prepareGeometryChange();
    setPos(_object->position());
    update();
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!_object) {
        return;
    }

    int typeId = _object->graphicsType();
    auto shader = OpenLabel::Factory::createShader(static_cast<OpenLabel::GraphicsTypeId>(typeId));
    if (shader) {
        shader->paint(painter, _object);
    }
}
