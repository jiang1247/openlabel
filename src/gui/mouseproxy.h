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

#include "openlabel/sceneeventlistener.h"
#include "selectedboxitem.h"
#include "selectingboxitem.h"
#include <QMouseEvent>
#include <QObject>
#include <QPointF>
#include <QSizeF>

namespace Gui {

class GraphicsView;
class GraphicsScene;

class MouseProxy : public QObject, public OpenLabel::SceneEventListener
{
    Q_OBJECT
  public:
    enum MouseState {
        Idle,
        Selecting,
        Moving,
        Resizing,
    };
    explicit MouseProxy(GraphicsView *view, QObject *parent = nullptr);
    virtual ~MouseProxy();

  protected:
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    virtual void onSceneEvent(OpenLabel::SceneEvent *event) override;

  private:
    void handleSelection(QMouseEvent *event);
    void startSelection();
    void drawSelectionRect(const QPointF &pos);
    void endSelection();

    void handleMove(QMouseEvent *event);
    void startMove();
    void moveSelectedBox(const QPointF &pos);
    void endMove();

    void handleResize(QMouseEvent *event);
    void startResize();
    void resizeSelectedBox(const QPointF &pos);
    void endResize();

    bool isMouseOverSelectedItems(const QPointF &pos);
    void updateCursor(const QPointF &pos);

    qreal scaleMerge(qreal scaleX, qreal scaleY);

    void updateSelectedBox();

  private:
    GraphicsView *_p_view;
    GraphicsScene *_p_scene;
    MouseState _state;
    QPointF _mousePressPos;
    QPointF _selectedBoxStartPos;
    QRectF _selectedBoxStartRect;
    QList<QRectF> _selectedItemsStartRects;
    SelectingBoxItem *_p_selectingBoxItem;
    SelectedBoxItem *_p_selectedBoxItem;
    QSizeF _scaleFactor;
    SelectedBoxItem::ResizeHandleId _resizeHandleId;
    QRectF _originalRect;
};

} // namespace Gui
