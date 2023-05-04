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

#include "resizehandleitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

using namespace Gui;

ResizeHandleItem::ResizeHandleItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , _handleSize(10.0)
{
    _handlePath.addRect(-_handleSize / 2, -_handleSize / 2, _handleSize, _handleSize);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
}

QRectF ResizeHandleItem::boundingRect() const
{
    return _handlePath.boundingRect();
}

void ResizeHandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#1aad19"));
    painter->drawPath(_handlePath);
}

bool ResizeHandleItem::contains(const QPointF &point) const
{
    return _handlePath.contains(point);
}
