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

#include "openlabel/scene.h"
#include "openlabel/sceneeventlistener.h"
#include "graphicsitem.h"
#include <QGraphicsScene>

namespace Gui {

class GraphicsScene : public QGraphicsScene, public OpenLabel::SceneEventListener
{
    Q_OBJECT
  public:
    explicit GraphicsScene(QObject *parent = nullptr);
    virtual ~GraphicsScene();

    void registerScene(OpenLabel::Scene *scene);
    void unregisterScene();

    GraphicsItems graphicsItems() const;
    GraphicsItems graphicsItems(const QRectF &rect) const;
    GraphicsItem *graphicsItemAt(const QPointF &pos) const;
    GraphicsItems selectedGraphicsItems() const;
    bool hasSelection() const;

    void doSelection(const GraphicsItems &items);
    void doClearSelection();

    virtual void onSceneEvent(OpenLabel::SceneEvent *event) override;

    OpenLabel::Scene *scene();

  private:
    void syncScene();

    GraphicsItem *findItemById(int id);

    OpenLabel::Scene *_p_scene;
};

} // namespace Gui
