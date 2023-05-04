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

#include "selectingboxitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

using namespace Gui;

SelectingBoxItem::SelectingBoxItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

QRectF SelectingBoxItem::boundingRect() const
{
    return _currentRect;
}

void SelectingBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor blue("#0078d7");
    blue.setAlpha(75);
    painter->fillRect(_currentRect, QBrush(blue));
    blue.setAlpha(255);
    painter->setPen(blue);
    painter->drawRect(_currentRect);
}

void SelectingBoxItem::updateBox(const QRectF &rect)
{
    prepareGeometryChange();
    _currentRect = rect;
    update();
}
