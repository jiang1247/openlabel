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

#include "textshader.h"
#include "scene.h"
#include "textgraphics.h"

#include <QPainter>
#include <QSharedPointer>

using namespace OpenLabel;

TextShader::TextShader()
    : Shader()
{
}

TextShader::~TextShader() {}

void TextShader::paint(QPainter *painter, const QSharedPointer<GraphicsObject> &object)
{
    auto textGraphics = qSharedPointerDynamicCast<TextGraphics>(object);
    if (!textGraphics) {
        return;
    }
    auto scene = textGraphics->scene();
    Q_ASSERT(scene);
    QVariantList values = scene->getDataValueForGraphics(textGraphics->graphicsId());
    QString string;
    for (auto value : values) {
        string.append(value.toString());
    }

    // Setup font and pen
    QFont font;
    font.setPixelSize(36);
    painter->setFont(font);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidthF(1.0f);
    painter->setPen(pen);

    // Save the current painter state
    painter->save();

    // Apply transform
    painter->setTransform(textGraphics->transform(), true);

    // Draw text
    QSizeF size = textGraphics->initialSize();
    QRectF rect(QPointF(0.0, 0.0), size);
    painter->drawText(rect, string, QTextOption(Qt::AlignCenter));

    // Restore the painter state
    painter->restore();
}
