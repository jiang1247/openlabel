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

#include "ellipseshader.h"
#include "ellipsegraphics.h"
#include <QPainter>
#include <QSharedPointer>

using namespace OpenLabel;

EllipseShader::EllipseShader()
    : Shader()
{
}

EllipseShader::~EllipseShader() {}

void EllipseShader::paint(QPainter *painter, const QSharedPointer<GraphicsObject> &object)
{
    auto ellipse = qSharedPointerDynamicCast<EllipseGraphics>(object);
    if (!ellipse) {
        return;
    }

    // Setup pen
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidthF(1.0f);
    painter->setPen(pen);

    // Draw ellipse
    QSizeF size = ellipse->initialSize();
    QRectF rect(QPointF(0.0, 0.0), size);
    painter->drawEllipse(ellipse->transform().mapRect(rect));
}
