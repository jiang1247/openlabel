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

#include "recttransform.h"

using namespace Utils;

QRectF RectTransform::subRectTransform(const QRectF &oldRect, const QRectF &newRect,
                                       const QRectF &subRect)
{
    qreal scaleW = newRect.width() / oldRect.width();
    qreal scaleH = newRect.height() / oldRect.height();
    QPointF spos = subRect.topLeft() - oldRect.topLeft();
    spos.setX(spos.x() * scaleW);
    spos.setY(spos.y() * scaleH);
    QPointF pos(newRect.topLeft() + spos);
    QSizeF size = subRect.size();
    size.setWidth(size.width() * scaleW);
    size.setHeight(size.height() * scaleH);
    return QRectF(pos, size);
}
