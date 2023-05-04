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

#include "mouseproxy.h"
#include "openlabel/modifygraphicsoperation.h"
#include "openlabel/propertyiddispatcher.h"
#include "openlabel/sceneevent.h"
#include "graphicsscene.h"
#include "graphicsview.h"

#include <QEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include <QDebug>

using namespace Gui;

MouseProxy::MouseProxy(GraphicsView *view, QObject *parent)
    : QObject(parent)
    , _p_view(view)
    , _state(MouseState::Idle)
{
    view->viewport()->setMouseTracking(true);
    view->viewport()->installEventFilter(this);

    auto *pQScene = view->scene();
    Q_ASSERT(pQScene);
    _p_scene = qobject_cast<GraphicsScene *>(pQScene);
    Q_ASSERT(_p_scene);

    _p_selectingBoxItem = new SelectingBoxItem();
    _p_selectingBoxItem->setZValue(std::numeric_limits<qreal>::max());
    _p_selectingBoxItem->hide();
    _p_scene->addItem(_p_selectingBoxItem);

    _p_selectedBoxItem = new SelectedBoxItem();
    _p_selectedBoxItem->setZValue(std::numeric_limits<qreal>::max());
    _p_selectedBoxItem->hide();
    _p_scene->addItem(_p_selectedBoxItem);

    _p_scene->scene()->addSceneEventListener(this);
}

MouseProxy::~MouseProxy()
{
    if (_p_scene->scene()) {
        _p_scene->scene()->removeSceneEventListener(this);
    }
}

bool MouseProxy::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == _p_view->viewport()) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            handleSelection(mouseEvent);
            handleMove(mouseEvent);
            handleResize(mouseEvent);
        } else if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QPointF scenePos = _p_view->mapToScene(mouseEvent->pos());
            updateCursor(scenePos);
            if (_state == MouseState::Selecting) {
                drawSelectionRect(scenePos);
            } else if (_state == MouseState::Moving) {
                moveSelectedBox(scenePos);
            } else if (_state == MouseState::Resizing) {
                resizeSelectedBox(scenePos);
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            if (_state == MouseState::Selecting) {
                endSelection();
            } else if (_state == MouseState::Moving) {
                endMove();
            } else if (_state == MouseState::Resizing) {
                endResize();
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void MouseProxy::onSceneEvent(OpenLabel::SceneEvent *event)
{
    if (_state != MouseState::Idle) {
        return;
    }
    if (event->type() == OpenLabel::SceneEventType::GraphicsAdd ||
        event->type() == OpenLabel::SceneEventType::GraphicsRemove ||
        event->type() == OpenLabel::SceneEventType::GraphicsSelect ||
        event->type() == OpenLabel::SceneEventType::GraphicsDeselect ||
        event->type() == OpenLabel::SceneEventType::GraphicsModify) {
        updateSelectedBox();
    }
}

void MouseProxy::handleSelection(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
        !isMouseOverSelectedItems(_p_view->mapToScene(event->pos()))) {
        _state = MouseState::Selecting;
        _mousePressPos = _p_view->mapToScene(event->pos());
        startSelection();
    }
}

void MouseProxy::startSelection()
{
    _p_selectingBoxItem->show();
    _p_selectingBoxItem->setPos(_mousePressPos);
    _p_selectingBoxItem->updateBox(QRectF());
}

void MouseProxy::drawSelectionRect(const QPointF &pos)
{
    QPointF currentPos = pos;
    QRectF selectionRect = QRectF(_mousePressPos, currentPos).normalized();
    _p_selectingBoxItem->setPos(selectionRect.topLeft());
    selectionRect.moveTo(QPointF(0.0, 0.0));
    _p_selectingBoxItem->updateBox(selectionRect);
}

void MouseProxy::endSelection()
{
    QRectF selectionRect = _p_selectingBoxItem->boundingRect();
    selectionRect.moveTo(_p_selectingBoxItem->pos());
    auto selectedItems = _p_scene->graphicsItems(selectionRect);
    _p_scene->doSelection(selectedItems);
    _p_selectingBoxItem->hide();
    _state = MouseState::Idle;
    updateSelectedBox();
}

void MouseProxy::handleMove(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
        isMouseOverSelectedItems(_p_view->mapToScene(event->pos()))) {
        _state = MouseState::Moving;
        _mousePressPos = _p_view->mapToScene(event->pos());
        _selectedBoxStartPos = _p_selectedBoxItem->pos();
        startMove();
    }
}

void MouseProxy::startMove() {}

void MouseProxy::moveSelectedBox(const QPointF &pos)
{
    QPointF currentPos = pos;
    QPointF delta = currentPos - _mousePressPos;
    _p_selectedBoxItem->setPos(_selectedBoxStartPos + delta);
}

void MouseProxy::endMove()
{
    int propertyId = objectPropertyId("Position");
    QPointF delta = _p_selectedBoxItem->pos() - _selectedBoxStartPos;
    QUndoCommand *pCommand = new QUndoCommand(tr("Move graphics"));
    for (auto item : _p_scene->selectedGraphicsItems()) {
        QPointF pos(item->pos() + delta);
        OpenLabel::Properties properties;
        properties << OpenLabel::Property(propertyId, pos);
        new OpenLabel::ModifyGraphicsOperation(item->graphicsId(), properties, _p_scene->scene(),
                                          pCommand);
    }
    _p_scene->scene()->pushOperation(pCommand);
    _state = MouseState::Idle;
    updateSelectedBox();
}

void MouseProxy::handleResize(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF scenePos = _p_view->mapToScene(event->pos());
        SelectedBoxItem::ResizeHandleId handleId = _p_selectedBoxItem->mouseOverHandle(scenePos);
        if (handleId != SelectedBoxItem::NoHandle) {
            _state = MouseState::Resizing;
            _resizeHandleId = handleId;
            _mousePressPos = scenePos;
            _originalRect = _p_selectedBoxItem->boundingRect();
            _originalRect.moveTo(_p_selectedBoxItem->pos());
            startResize();
        }
    }
}

void MouseProxy::startResize() {}

void MouseProxy::resizeSelectedBox(const QPointF &pos)
{
    QPointF resizeEndPos = pos;
    QRectF newRect = _originalRect;
    QPointF newPos = _p_selectedBoxItem->pos();
    qreal scaleFactor;

    switch (_resizeHandleId) {
    case SelectedBoxItem::TopHandle: {
        qreal deltaY = resizeEndPos.y() - _originalRect.top();
        newRect.setTop(newRect.top() + deltaY);

        if (newRect.height() < 1) {
            return;
        }

        newPos.setY(resizeEndPos.y());
        scaleFactor = newRect.height() / _originalRect.height();
        newRect.setWidth(_originalRect.width() * scaleFactor);

        qreal deltaX = (_originalRect.width() - newRect.width()) / 2;
        newPos.setX(_originalRect.left() + deltaX);
    } break;
    case SelectedBoxItem::BottomHandle: {
        qreal deltaY = resizeEndPos.y() - _originalRect.bottom();
        newRect.setBottom(newRect.bottom() + deltaY);

        if (newRect.height() < 1) {
            return;
        }

        scaleFactor = newRect.height() / _originalRect.height();
        newRect.setWidth(_originalRect.width() * scaleFactor);

        qreal deltaX = (_originalRect.width() - newRect.width()) / 2;
        newPos.setX(_originalRect.left() + deltaX);
    } break;
    case SelectedBoxItem::LeftHandle: {
        qreal deltaX = resizeEndPos.x() - _originalRect.left();
        newRect.setLeft(newRect.left() + deltaX);

        if (newRect.width() < 1) {
            return;
        }

        newPos.setX(resizeEndPos.x());
        scaleFactor = newRect.width() / _originalRect.width();
        newRect.setHeight(_originalRect.height() * scaleFactor);

        qreal deltaY = (_originalRect.height() - newRect.height()) / 2;
        newPos.setY(_originalRect.top() + deltaY);
    } break;
    case SelectedBoxItem::RightHandle: {
        qreal deltaX = resizeEndPos.x() - _originalRect.right();
        newRect.setRight(newRect.right() + deltaX);

        if (newRect.width() < 1) {
            return;
        }

        scaleFactor = newRect.width() / _originalRect.width();
        newRect.setHeight(_originalRect.height() * scaleFactor);

        qreal deltaY = (_originalRect.height() - newRect.height()) / 2;
        newPos.setY(_originalRect.top() + deltaY);
    } break;
    case SelectedBoxItem::TopRightHandle: {
        qreal deltaY = resizeEndPos.y() - _originalRect.top();
        qreal deltaX = resizeEndPos.x() - _originalRect.right();
        qreal scaleY = 1 - deltaY / _originalRect.height();
        qreal scaleX = 1 + deltaX / _originalRect.width();
        qreal scaleFactor = scaleMerge(scaleX, scaleY);

        qreal newWidth = _originalRect.width() * scaleFactor;
        qreal newHeight = _originalRect.height() * scaleFactor;
        if (newWidth < 1 || newHeight < 1) {
            return;
        }

        newRect.setRight(_originalRect.right() + (newWidth - _originalRect.width()));
        newRect.setTop(_originalRect.top() - (newHeight - _originalRect.height()));
        newPos.setX(_originalRect.left());
        newPos.setY(newRect.top());
    } break;
    case SelectedBoxItem::TopLeftHandle: {
        qreal deltaX = resizeEndPos.x() - _originalRect.left();
        qreal deltaY = resizeEndPos.y() - _originalRect.top();
        qreal scaleX = 1 - deltaX / _originalRect.width();
        qreal scaleY = 1 - deltaY / _originalRect.height();
        scaleFactor = scaleMerge(scaleX, scaleY);

        qreal newWidth = _originalRect.width() * scaleFactor;
        qreal newHeight = _originalRect.height() * scaleFactor;
        if (newWidth < 1 || newHeight < 1) {
            return;
        }

        newPos = _originalRect.bottomRight() - QPointF(newWidth, newHeight);
        newRect.setTopLeft(newPos);
    } break;
    case SelectedBoxItem::BottomRightHandle: {
        qreal deltaX = resizeEndPos.x() - _originalRect.right();
        qreal deltaY = resizeEndPos.y() - _originalRect.bottom();
        qreal scaleX = 1 + deltaX / _originalRect.width();
        qreal scaleY = 1 + deltaY / _originalRect.height();
        scaleFactor = scaleMerge(scaleX, scaleY);

        qreal newWidth = _originalRect.width() * scaleFactor;
        qreal newHeight = _originalRect.height() * scaleFactor;
        if (newWidth < 1 || newHeight < 1) {
            return;
        }

        newRect.setBottomRight(_originalRect.topLeft() + QPointF(newWidth, newHeight));
        newPos = newRect.topLeft();
    } break;
    case SelectedBoxItem::BottomLeftHandle: {
        qreal deltaX = resizeEndPos.x() - _originalRect.left();
        qreal deltaY = resizeEndPos.y() - _originalRect.bottom();
        qreal scaleX = 1 - deltaX / _originalRect.width();
        qreal scaleY = 1 + deltaY / _originalRect.height();
        scaleFactor = scaleMerge(scaleX, scaleY);

        qreal newWidth = _originalRect.width() * scaleFactor;
        qreal newHeight = _originalRect.height() * scaleFactor;
        if (newWidth < 1 || newHeight < 1) {
            return;
        }

        newPos.setX(_originalRect.right() - newWidth);
        newPos.setY(_originalRect.top());
        newRect.setTopRight(_originalRect.topRight());
        newRect.setBottomLeft(QPointF(newPos.x(), _originalRect.top() + newHeight));
    } break;
    default:
        return;
    }

    _p_selectedBoxItem->setPos(newPos);
    _p_selectedBoxItem->updateSize(newRect.size());
}

void MouseProxy::endResize()
{
    int posId = objectPropertyId("Position");
    int sizeId = objectPropertyId("Size");
    qreal scaleW = _p_selectedBoxItem->boundingRect().width() / _originalRect.width();
    qreal scaleH = _p_selectedBoxItem->boundingRect().height() / _originalRect.height();
    QUndoCommand *pCommand = new QUndoCommand(tr("Resize graphics"));
    for (auto item : _p_scene->selectedGraphicsItems()) {
        QPointF spos = item->pos() - _originalRect.topLeft();
        spos.setX(spos.x() * scaleW);
        spos.setY(spos.y() * scaleH);
        QPointF pos(_p_selectedBoxItem->pos() + spos);
        QSizeF size = item->boundingRect().size();
        size.setWidth(size.width() * scaleW);
        size.setHeight(size.height() * scaleH);
        OpenLabel::Properties properties;
        properties << OpenLabel::Property(posId, pos) << OpenLabel::Property(sizeId, size);
        new OpenLabel::ModifyGraphicsOperation(item->graphicsId(), properties, _p_scene->scene(),
                                          pCommand);
    }
    _p_scene->scene()->pushOperation(pCommand);
    _state = MouseState::Idle;
    updateSelectedBox();
}

bool MouseProxy::isMouseOverSelectedItems(const QPointF &pos)
{
    GraphicsItem *item = _p_scene->graphicsItemAt(pos);
    if (item) {
        return item->graphicsIsSelected();
    }
    return false;
}

void MouseProxy::updateCursor(const QPointF &pos)
{
    if (_state == MouseState::Idle) {
        SelectedBoxItem::ResizeHandleId handle = _p_selectedBoxItem->mouseOverHandle(pos);
        if (handle == SelectedBoxItem::TopHandle || handle == SelectedBoxItem::BottomHandle) {
            _p_view->viewport()->setCursor(Qt::SizeVerCursor);
        } else if (handle == SelectedBoxItem::LeftHandle ||
                   handle == SelectedBoxItem::RightHandle) {
            _p_view->viewport()->setCursor(Qt::SizeHorCursor);
        } else if (handle == SelectedBoxItem::TopLeftHandle ||
                   handle == SelectedBoxItem::BottomRightHandle) {
            _p_view->viewport()->setCursor(Qt::SizeFDiagCursor);
        } else if (handle == SelectedBoxItem::TopRightHandle ||
                   handle == SelectedBoxItem::BottomLeftHandle) {
            _p_view->viewport()->setCursor(Qt::SizeBDiagCursor);
        } else if (isMouseOverSelectedItems(pos)) {
            _p_view->viewport()->setCursor(Qt::SizeAllCursor);
        } else {
            _p_view->viewport()->setCursor(Qt::ArrowCursor);
        }
    } else if (_state == MouseState::Moving) {
        _p_view->viewport()->setCursor(Qt::SizeAllCursor);
    } else if (_state == MouseState::Resizing) {
    } else {
        _p_view->viewport()->setCursor(Qt::ArrowCursor);
    }
}

void MouseProxy::updateSelectedBox()
{
    auto items = _p_scene->selectedGraphicsItems();
    if (items.isEmpty()) {
        _p_selectedBoxItem->hide();
        return;
    }
    QRectF rect(0.0, 0.0, 0.0, 0.0);
    for (auto item : items) {
        QRectF iRect = item->boundingRect();
        iRect.moveTo(item->pos());
        rect = rect.united(iRect);
    }
    rect = rect.normalized();
    _p_selectedBoxItem->setPos(rect.topLeft());
    _p_selectedBoxItem->updateSize(rect.size());
    _p_selectedBoxItem->show();
}

qreal MouseProxy::scaleMerge(qreal scaleX, qreal scaleY)
{
    qreal scaleMax = qMax(scaleX, scaleY);
    qreal scaleMin = qMin(scaleX, scaleY);
    return qMax(0.0001, (scaleMax * 0.6 + scaleMin * 0.4));
}
