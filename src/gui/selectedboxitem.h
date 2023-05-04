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

#include <QGraphicsItem>
#include <QMap>

namespace Gui {

class ResizeHandleItem;

class SelectedBoxItem : public QGraphicsItem
{
  public:
    enum ResizeHandleId {
        NoHandle,
        TopHandle,
        BottomHandle,
        LeftHandle,
        RightHandle,
        TopLeftHandle,
        TopRightHandle,
        BottomLeftHandle,
        BottomRightHandle,
    };
    SelectedBoxItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updateSize(const QSizeF &size);

    ResizeHandleId mouseOverHandle(const QPointF &scenePos);

  private:
    void updateHandle();

    QSizeF _size;
    QMap<ResizeHandleId, ResizeHandleItem *> _resizeHandles;
};

} // namespace Gui
