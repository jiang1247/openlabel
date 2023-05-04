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

#include "global.h"
#include "datasource.h"
#include "graphicsobject.h"
#include <QList>
#include <QObject>
#include <QSharedPointer>

class QUndoCommand;
class QUndoStack;

namespace OpenLabel {

class SceneEventListener;
class SceneEvent;

class Scene : public QObject
{
    Q_OBJECT
  public:
    explicit Scene(QObject *parent = nullptr);
    virtual ~Scene();

    // Graphics object management
    QSharedPointer<GraphicsObject> newGraphics(GraphicsTypeId type, int id,
                                               const QList<int> &bindDataIds,
                                               Properties properties = Properties());
    void removeGraphics(int id);
    void setSelected(const QList<int> &graphics);
    void clearSelected();
    void selection(int id, bool select);
    QList<int> selectedGraphicsIds() const;
    GraphicsObjects selectedGraphics() const;
    bool hasSelected() const;
    bool isSelected(int id) const;
    QList<int> allGraphicsIds() const;
    GraphicsObjects allGraphics() const;
    QSharedPointer<GraphicsObject> findGraphicsById(int id);
    QSharedPointer<GraphicsObject> findRealGraphicsById(int id);

    // Data source management
    QSharedPointer<DataSource> newDataSource(DataSourceTypeId type, int id,
                                             Properties properties = Properties());
    void removeDataSource(int id);
    DataSources allDataSources() const;
    QList<int> allDataSourceIds() const;
    QSharedPointer<DataSource> findDataSourceById(int id);
    QSharedPointer<DataSource> findRealDataSourceById(int id);

    // Operation management
    void pushOperation(QUndoCommand *operation);
    void undo();
    void redo();
    void clearOperations();
    bool canUndo();
    bool canRedo();
    QUndoStack *operationStack();

    // Listener management
    void addSceneEventListener(SceneEventListener *listener);
    void removeSceneEventListener(SceneEventListener *listener);
    void processSceneEvent(SceneEvent *event);

    int takeNextGraphicsId();
    int takeNextDataSourceId();

    bool bindDataToGraphics(int graphicsId, const QList<int> &dataIds);
    bool bindDataToGraphics(int graphicsId, int dataId, int dataIndex);
    bool unbindDataToGraphics(int graphicsId, int dataId, int dataIndex);
    bool unbindAllDataToGraphics(int graphicsId);
    bool unbindDataToAllGraphics(int dataId);
    QList<int> getDataForGraphics(int graphicsId) const;
    QVariantList getDataValueForGraphics(int graphicsId) const;

  Q_SIGNALS:
    void canUndoChanged(bool canUndo);
    void canRedoChanged(bool canRedo);

  private:
    QHash<int, QSharedPointer<GraphicsObject>> _graphics;
    QHash<int, QSharedPointer<DataSource>> _dataSources;
    QUndoStack *_p_operationStack;
    QList<SceneEventListener *> _sceneListeners;
    int _nextGraphicsId;
    int _nextDataSourceId;
    QHash<int, QList<int>> _graphicsDataMap;
};

}
