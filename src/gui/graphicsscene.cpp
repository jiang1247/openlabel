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

#include "graphicsscene.h"
#include "openlabel/graphicsevent.h"
#include "openlabel/graphicsobject.h"
#include "graphicsitem.h"

#include <QDebug>

using namespace Gui;

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , _p_scene(nullptr)
{
    qDebug() << "graphics scene is created";
    setSceneRect(-1000.0, -1000.0, 2000, 2000);

    setItemIndexMethod(QGraphicsScene::NoIndex);
}

GraphicsScene::~GraphicsScene()
{
    qDebug() << "graphics scene is destroyed";
    unregisterScene();
}

void GraphicsScene::registerScene(OpenLabel::Scene *scene)
{
    unregisterScene();

    if (scene) {
        qDebug() << "scene registered";
        _p_scene = scene;
        _p_scene->addSceneEventListener(this);
        syncScene();
    }
}

void GraphicsScene::unregisterScene()
{
    if (_p_scene) {
        qDebug() << "scene unregistered";
        _p_scene->removeSceneEventListener(this);
        _p_scene = nullptr;
        clear();
    }
}

void GraphicsScene::onSceneEvent(OpenLabel::SceneEvent *event)
{
    switch (event->type()) {
    case OpenLabel::SceneEventType::GraphicsAdd: {
        auto addEvent = dynamic_cast<OpenLabel::GraphicsAddEvent *>(event);
        if (addEvent) {
            QList<int> ids = addEvent->ids();
            for (auto id : ids) {
                auto object = _p_scene->findRealGraphicsById(id);
                addItem(new GraphicsItem(object));
            }
        }
    } break;
    case OpenLabel::SceneEventType::GraphicsRemove: {
        auto rmEvent = dynamic_cast<OpenLabel::GraphicsRemoveEvent *>(event);
        if (rmEvent) {
            QList<int> ids = rmEvent->ids();
            for (auto id : ids) {
                auto item = findItemById(id);
                if (item) {
                    qDebug() << "graphics scene remove item" << item;
                    removeItem(item);
                    delete item;
                }
            }
        }
    } break;
    case OpenLabel::SceneEventType::GraphicsSelect: {
    } break;
    case OpenLabel::SceneEventType::GraphicsDeselect: {
    } break;
    case OpenLabel::SceneEventType::GraphicsModify: {
        auto modifyEvent = dynamic_cast<OpenLabel::GraphicsModifyEvent *>(event);
        if (modifyEvent) {
            auto item = findItemById(modifyEvent->id());
            if (item) {
                item->forceUpdate();
            }
        }
    } break;
    default:
        break;
    }
}

OpenLabel::Scene *GraphicsScene::scene()
{
    return _p_scene;
}

GraphicsItems GraphicsScene::graphicsItems() const
{
    GraphicsItems gItems;
    auto allItem = this->items();
    for (auto pItem : allItem) {
        GraphicsItem *pGItem = dynamic_cast<GraphicsItem *>(pItem);
        if (pGItem) {
            gItems.append(pGItem);
        }
    }
    return gItems;
}

GraphicsItems GraphicsScene::graphicsItems(const QRectF &rect) const
{
    GraphicsItems gItems;
    auto allItem = this->items(rect);
    for (auto pItem : allItem) {
        GraphicsItem *pGItem = dynamic_cast<GraphicsItem *>(pItem);
        if (pGItem) {
            gItems.append(pGItem);
        }
    }
    return gItems;
}

GraphicsItem *GraphicsScene::graphicsItemAt(const QPointF &pos) const
{
    auto selectedItems = this->items(pos);
    for (auto pItem : selectedItems) {
        GraphicsItem *pGItem = dynamic_cast<GraphicsItem *>(pItem);
        if (pGItem) {
            return pGItem;
        }
    }
    return nullptr;
}

GraphicsItems GraphicsScene::selectedGraphicsItems() const
{
    GraphicsItems gItems;
    auto items = graphicsItems();
    for (auto pItem : items) {
        if (pItem->graphicsIsSelected()) {
            gItems.append(pItem);
        }
    }
    return gItems;
}

bool GraphicsScene::hasSelection() const
{
    auto items = graphicsItems();
    for (auto pItem : items) {
        if (pItem->graphicsIsSelected()) {
            return true;
        }
    }
    return false;
}

void GraphicsScene::doSelection(const GraphicsItems &items)
{
    QList<int> ids;
    for (auto item : items) {
        ids.append(item->graphicsId());
    }
    _p_scene->setSelected(ids);
}

void GraphicsScene::doClearSelection()
{
    _p_scene->clearSelected();
}

void GraphicsScene::syncScene()
{
    clear();

    if (!_p_scene) {
        return;
    }

    auto ids = _p_scene->allGraphicsIds();
    for (auto id : ids) {
        addItem(new GraphicsItem(_p_scene->findRealGraphicsById(id)));
    }
}

GraphicsItem *GraphicsScene::findItemById(int id)
{
    for (auto item : graphicsItems()) {
        if (item->graphicsId() == id) {
            return item;
        }
    }
    return nullptr;
}
