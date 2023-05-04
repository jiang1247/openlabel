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

#include "textgraphics.h"
#include "global.h"
#include "scene.h"

#include <QFontMetricsF>

using namespace OpenLabel;

TextGraphics::TextGraphics(int id, Scene *scene)
    : GraphicsObject(id, scene)
{
    setName(globalTr("TextGraphics", "Text"));
}

TextGraphics::~TextGraphics() {}

QSharedPointer<GraphicsObject> TextGraphics::clone() const
{
    auto cloned = GraphicsObject::clone();
    auto textGraphics = qSharedPointerCast<TextGraphics>(cloned);
    if (textGraphics) {
    }
    return textGraphics;
}

QVariant TextGraphics::propertyValue(int id) const
{
    return GraphicsObject::propertyValue(id);
}

int TextGraphics::graphicsType() const
{
    return GraphicsTypeId::TextGraphicsType;
}

QString TextGraphics::graphicsName() const
{
    return QStringLiteral("Text");
}

QSizeF TextGraphics::initialSize()
{
    QVariantList values;
    if (_p_scene) {
        values = _p_scene->getDataValueForGraphics(graphicsId());
    }
    QString string;
    for (auto value : values) {
        string.append(value.toString());
    }
    if (string.isEmpty()) {
        return QSizeF(200.0, 200.0);
    }

    QFont font;
    font.setPixelSize(36);
    QFontMetricsF metrics(font);
    QRectF rect = metrics.boundingRect(string);
    rect.adjust(-1, -1, 1, 1);
    return rect.size();
}

void TextGraphics::initializeProperties()
{
    GraphicsObject::initializeProperties();
    _name = globalTr("TextGraphics", "Text");
}

void TextGraphics::setProperty(const Property &property)
{
    GraphicsObject::setProperty(property);
}

Properties TextGraphics::properties() const
{
    Properties properties = GraphicsObject::properties();
    return properties;
}
