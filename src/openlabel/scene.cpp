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

#include "scene.h"
#include "factory.h"
#include "datasourceevent.h"
#include "graphicsevent.h"
#include "sceneevent.h"
#include "sceneeventlistener.h"

#include <QUndoStack>

#include <QDebug>

using namespace OpenLabel;

Scene::Scene(QObject *parent)
    : QObject(parent)
    , _nextGraphicsId(0)
    , _nextDataSourceId(0)
{
    qDebug() << "scene is created";
    _p_operationStack = new QUndoStack(this);
    connect(_p_operationStack, &QUndoStack::canUndoChanged, this, &Scene::canUndoChanged);
    connect(_p_operationStack, &QUndoStack::canRedoChanged, this, &Scene::canRedoChanged);
}

Scene::~Scene()
{
    qDebug() << "scene is destroyed";
}

QSharedPointer<GraphicsObject> Scene::newGraphics(GraphicsTypeId type, int id,
                                                  const QList<int> &bindDataIds,
                                                  Properties properties)
{
    qDebug() << "begin new graphics";
    auto graphics = Factory::createGraphics(type, id, this);
    _graphics[id] = graphics;
    bindDataToGraphics(id, bindDataIds);
    graphics->initializeProperties();
    graphics->setProperties(properties);
    addSceneEventListener(graphics.data());
    auto addEvent = new GraphicsAddEvent(QList<int>() << id);
    processSceneEvent(addEvent);
    delete addEvent;
    auto modifyEvent = new GraphicsModifyEvent(id, properties);
    processSceneEvent(modifyEvent);
    delete modifyEvent;
    qDebug() << "end new graphics";
    return graphics->clone();
}

void Scene::removeGraphics(int id)
{
    qDebug() << "begin remove graphics";
    if (_graphics.contains(id)) {
        auto event = new GraphicsRemoveEvent(QList<int>() << id);
        processSceneEvent(event);
        delete event;
        removeSceneEventListener(_graphics[id].data());
        _graphics.remove(id);
    }
    unbindAllDataToGraphics(id);
    qDebug() << "end remove graphics";
}

void Scene::setSelected(const QList<int> &graphics)
{
    QList<int> deselectIds;
    QHashIterator<int, QSharedPointer<GraphicsObject>> i(_graphics);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isSelected() && !graphics.contains(i.value()->graphicsId())) {
            i.value()->setSelected(false);
            deselectIds.append(i.value()->graphicsId());
        }
    }
    auto deselectEvent = new GraphicsDeselectEvent(QList<int>() << deselectIds);
    processSceneEvent(deselectEvent);
    delete deselectEvent;
    for (int id : graphics) {
        if (_graphics.contains(id)) {
            _graphics[id]->setSelected(true);
        }
    }
    auto selectEvent = new GraphicsSelectEvent(QList<int>() << graphics);
    processSceneEvent(selectEvent);
    delete selectEvent;
}

void Scene::clearSelected()
{
    QList<int> graphics;
    QHashIterator<int, QSharedPointer<GraphicsObject>> i(_graphics);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isSelected()) {
            i.value()->setSelected(false);
            graphics.append(i.value()->graphicsId());
        }
    }
    auto event = new GraphicsDeselectEvent(QList<int>() << graphics);
    processSceneEvent(event);
    delete event;
}

void Scene::selection(int id, bool select)
{
    if (_graphics.contains(id)) {
        _graphics[id]->setSelected(select);
    }
    if (select) {
        auto event = new GraphicsSelectEvent(QList<int>() << id);
        processSceneEvent(event);
        delete event;
    } else {
        auto event = new GraphicsDeselectEvent(QList<int>() << id);
        processSceneEvent(event);
        delete event;
    }
}

QList<int> Scene::selectedGraphicsIds() const
{
    QList<int> graphics;
    QHashIterator<int, QSharedPointer<GraphicsObject>> i(_graphics);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isSelected()) {
            graphics.append(i.value()->graphicsId());
        }
    }
    return graphics;
}

GraphicsObjects Scene::selectedGraphics() const
{
    GraphicsObjects graphics;
    QHashIterator<int, QSharedPointer<GraphicsObject>> i(_graphics);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isSelected()) {
            graphics.append(i.value()->clone());
        }
    }
    return graphics;
}

bool Scene::hasSelected() const
{
    QList<int> graphics;
    QHashIterator<int, QSharedPointer<GraphicsObject>> i(_graphics);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isSelected()) {
            return true;
        }
    }
    return false;
}

bool Scene::isSelected(int id) const
{
    if (!_graphics.contains(id)) {
        return false;
    }
    return _graphics[id]->isSelected();
}

QList<int> Scene::allGraphicsIds() const
{
    return _graphics.keys();
}

GraphicsObjects Scene::allGraphics() const
{
    GraphicsObjects graphics;
    QHashIterator<int, QSharedPointer<GraphicsObject>> i(_graphics);
    while (i.hasNext()) {
        i.next();
        graphics.append(i.value()->clone());
    }
    return graphics;
}

QSharedPointer<GraphicsObject> Scene::findGraphicsById(int id)
{
    auto realGraphics = findRealGraphicsById(id);
    return realGraphics ? realGraphics->clone() : QSharedPointer<GraphicsObject>(nullptr);
}

QSharedPointer<GraphicsObject> Scene::findRealGraphicsById(int id)
{
    return _graphics.value(id, QSharedPointer<GraphicsObject>(nullptr));
}

QSharedPointer<DataSource> Scene::newDataSource(DataSourceTypeId type, int id,
                                                Properties properties)
{
    auto dataSource = Factory::createDataSource(type, id, this);
    _dataSources[id] = dataSource;
    dataSource->setProperties(properties);
    addSceneEventListener(dataSource.data());
    auto event = new DataSourceAddEvent(QList<int>() << id);
    processSceneEvent(event);
    delete event;
    return dataSource->clone();
}

void Scene::removeDataSource(int id)
{
    if (_dataSources.contains(id)) {
        auto event = new DataSourceRemoveEvent(QList<int>() << id);
        processSceneEvent(event);
        delete event;
        removeSceneEventListener(_dataSources[id].data());
        _dataSources.remove(id);
    }
    unbindDataToAllGraphics(id);
}

DataSources Scene::allDataSources() const
{
    DataSources dataSources;
    QHashIterator<int, QSharedPointer<DataSource>> i(_dataSources);
    while (i.hasNext()) {
        i.next();
        dataSources.append(i.value()->clone());
    }
    return dataSources;
}

QList<int> Scene::allDataSourceIds() const
{
    return _dataSources.keys();
}

QSharedPointer<DataSource> Scene::findDataSourceById(int id)
{
    auto realDataSource = findRealDataSourceById(id);
    return realDataSource ? realDataSource->clone() : QSharedPointer<DataSource>(nullptr);
}

QSharedPointer<DataSource> Scene::findRealDataSourceById(int id)
{
    return _dataSources.value(id, QSharedPointer<DataSource>(nullptr));
}

void Scene::pushOperation(QUndoCommand *operation)
{
    _p_operationStack->push(operation);
}

void Scene::undo()
{
    clearSelected();
    _p_operationStack->undo();
}

void Scene::redo()
{
    clearSelected();
    _p_operationStack->redo();
}

void Scene::clearOperations()
{
    _p_operationStack->clear();
}

bool Scene::canUndo()
{
    return _p_operationStack->canUndo();
}

bool Scene::canRedo()
{
    return _p_operationStack->canRedo();
}

QUndoStack *Scene::operationStack()
{
    return _p_operationStack;
}

void Scene::addSceneEventListener(SceneEventListener *listener)
{
    _sceneListeners.append(listener);
}

void Scene::removeSceneEventListener(SceneEventListener *listener)
{
    _sceneListeners.removeAll(listener);
}

void Scene::processSceneEvent(SceneEvent *event)
{
    for (SceneEventListener *listener : _sceneListeners) {
        listener->onSceneEvent(event);
    }
}

int Scene::takeNextGraphicsId()
{
    return _nextGraphicsId++;
}

int Scene::takeNextDataSourceId()
{
    return _nextDataSourceId++;
}

bool Scene::bindDataToGraphics(int graphicsId, const QList<int> &dataIds)
{
    if (!_graphics.contains(graphicsId)) {
        return false;
    }
    for (auto id : dataIds) {
        if (!_dataSources.contains(id)) {
            return false;
        }
    }
    _graphicsDataMap[graphicsId] = dataIds;
    return true;
}

bool Scene::bindDataToGraphics(int graphicsId, int dataId, int dataIndex)
{
    qDebug() << "bindDataToGraphics" << graphicsId << dataId << dataIndex;
    if (!_graphics.contains(graphicsId) || !_dataSources.contains(dataId)) {
        return false;
    }
    QList<int> ids;
    if (_graphicsDataMap.contains(graphicsId)) {
        ids = _graphicsDataMap[graphicsId];
    }
    if (dataIndex < 0 || dataIndex > ids.size()) {
        return false;
    }
    ids.insert(dataIndex, dataId);
    _graphicsDataMap[graphicsId] = ids;
    return true;
}

bool Scene::unbindDataToGraphics(int graphicsId, int dataId, int dataIndex)
{
    if (!_graphics.contains(graphicsId) || !_dataSources.contains(dataId)) {
        return false;
    }
    if (!_graphicsDataMap.contains(graphicsId)) {
        return false;
    }
    QList<int> ids = _graphicsDataMap[graphicsId];
    if (dataIndex < 0 || dataIndex >= ids.size()) {
        return false;
    }
    if (ids[dataIndex] != dataId) {
        return false;
    }
    ids.removeAt(dataIndex);
    _graphicsDataMap[graphicsId] = ids;
    return true;
}

bool Scene::unbindAllDataToGraphics(int graphicsId)
{
    if (!_graphics.contains(graphicsId)) {
        return false;
    }
    _graphicsDataMap.remove(graphicsId);
    return true;
}

bool Scene::unbindDataToAllGraphics(int dataId)
{
    if (!_dataSources.contains(dataId)) {
        return false;
    }
    for (auto graphics : _graphics) {
        if (!_graphicsDataMap.contains(graphics->graphicsId())) {
            continue;
        }
        QList<int> ids = _graphicsDataMap[graphics->graphicsId()];
        if (!ids.contains(dataId)) {
            continue;
        }
        ids.removeAll(dataId);
        _graphicsDataMap[graphics->graphicsId()] = ids;
    }
}

QList<int> Scene::getDataForGraphics(int graphicsId) const
{
    if (_graphicsDataMap.contains(graphicsId)) {
        return _graphicsDataMap[graphicsId];
    }
    return QList<int>();
}

QVariantList Scene::getDataValueForGraphics(int graphicsId) const
{
    QList<int> ids = getDataForGraphics(graphicsId);
    QVariantList values;
    for (auto id : ids) {
        values.append(_dataSources[id]->data());
    }
    return values;
}
