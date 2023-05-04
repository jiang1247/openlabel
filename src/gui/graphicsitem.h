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

#include "openlabel/factory.h"
#include "openlabel/graphicsobject.h"
#include <QGraphicsItem>

namespace Gui {

class GraphicsItem : public QGraphicsItem
{
  public:
    explicit GraphicsItem(QSharedPointer<OpenLabel::GraphicsObject> object,
                          QGraphicsItem *parent = nullptr);
    virtual ~GraphicsItem();

    QSharedPointer<OpenLabel::GraphicsObject> graphicsObject() const;

    int graphicsId() const;
    bool graphicsIsSelected() const;

    virtual QRectF boundingRect() const override;

    //    virtual QPainterPath shape() const;

    void forceUpdate();

  protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  private:
    QSharedPointer<OpenLabel::GraphicsObject> _object;
};

typedef QList<GraphicsItem *> GraphicsItems;

} // namespace Gui
