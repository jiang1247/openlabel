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

#include "selectedboxitem.h"
#include "resizehandleitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

using namespace Gui;

SelectedBoxItem::SelectedBoxItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    _resizeHandles[TopHandle] = new ResizeHandleItem(this);
    _resizeHandles[BottomHandle] = new ResizeHandleItem(this);
    _resizeHandles[LeftHandle] = new ResizeHandleItem(this);
    _resizeHandles[RightHandle] = new ResizeHandleItem(this);
    _resizeHandles[TopLeftHandle] = new ResizeHandleItem(this);
    _resizeHandles[TopRightHandle] = new ResizeHandleItem(this);
    _resizeHandles[BottomLeftHandle] = new ResizeHandleItem(this);
    _resizeHandles[BottomRightHandle] = new ResizeHandleItem(this);

    //    for(auto handle : resizeHandles.values()) {
    //        handle->setFlag(QGraphicsItem::ItemStacksBehindParent);
    //    }
}

QRectF SelectedBoxItem::boundingRect() const
{
    return QRectF(0.0, 0.0, _size.width(), _size.height());
}

void SelectedBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QColor("#1aad19"));
    painter->drawRect(boundingRect());
}

void SelectedBoxItem::updateHandle()
{
    QRectF rect = boundingRect();
    _resizeHandles[TopHandle]->setPos(rect.center().x(), rect.top());
    _resizeHandles[BottomHandle]->setPos(rect.center().x(), rect.bottom());
    _resizeHandles[LeftHandle]->setPos(rect.left(), rect.center().y());
    _resizeHandles[RightHandle]->setPos(rect.right(), rect.center().y());
    _resizeHandles[TopLeftHandle]->setPos(rect.left(), rect.top());
    _resizeHandles[TopRightHandle]->setPos(rect.right(), rect.top());
    _resizeHandles[BottomLeftHandle]->setPos(rect.left(), rect.bottom());
    _resizeHandles[BottomRightHandle]->setPos(rect.right(), rect.bottom());
}

void SelectedBoxItem::updateSize(const QSizeF &size)
{
    prepareGeometryChange();
    _size = size;
    update();
    updateHandle();
}

SelectedBoxItem::ResizeHandleId SelectedBoxItem::mouseOverHandle(const QPointF &scenePos)
{
    for (auto it = _resizeHandles.constBegin(); it != _resizeHandles.constEnd(); ++it) {
        if (it.value()->contains(it.value()->mapFromScene(scenePos))) {
            return it.key();
        }
    }
    return NoHandle;
}
