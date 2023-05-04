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

#include "graphicslistdockwidget.h"
#include "openlabel/document.h"
#include "openlabel/graphicsevent.h"

#include <QDebug>

using namespace Gui;

GraphicsListDockWidget::GraphicsListDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , _p_currentScene(nullptr)
    , _p_listView(new QListView(this))
    , _p_layout(new QVBoxLayout())
    , _p_model(new QStandardItemModel(this))
    , _p_selectionModel(new QItemSelectionModel(_p_model))
    , _isUpdating(false)
{
    setWindowTitle(tr("Graphics list"));

    _p_layout->setMargin(1);
    _p_layout->addWidget(_p_listView);
    _p_listView->setModel(_p_model);
    _p_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _p_listView->setSelectionModel(_p_selectionModel);

    QWidget *containerWidget = new QWidget;
    containerWidget->setLayout(_p_layout);
    setWidget(containerWidget);
}

void GraphicsListDockWidget::onSceneEvent(OpenLabel::SceneEvent *event)
{
    if (_isUpdating || !_p_currentScene) {
        return;
    }

    _isUpdating = true;

    switch (event->type()) {
    case OpenLabel::GraphicsAdd: {
        const OpenLabel::GraphicsAddEvent *addEvent = static_cast<const OpenLabel::GraphicsAddEvent *>(event);
        QList<int> ids = addEvent->ids();
        for (int id : ids) {
            QSharedPointer<OpenLabel::GraphicsObject> graphicsObject =
                _p_currentScene->findGraphicsById(id);
            if (!graphicsObject) {
                continue;
            }
            QStandardItem *item = new QStandardItem(graphicsObject->name());
            item->setData(graphicsObject->graphicsId(), Qt::UserRole);
            _p_model->appendRow(item);
            if (graphicsObject->isSelected()) {
                QModelIndex index = _p_model->index(_p_model->rowCount() - 1, 0);
                _p_selectionModel->select(index, QItemSelectionModel::Select);
            }
        }
        break;
    }
    case OpenLabel::GraphicsRemove: {
        const OpenLabel::GraphicsRemoveEvent *removeEvent =
            static_cast<const OpenLabel::GraphicsRemoveEvent *>(event);
        QList<int> ids = removeEvent->ids();
        for (int id : ids) {
            for (int row = 0; row < _p_model->rowCount(); ++row) {
                QStandardItem *item = _p_model->item(row);
                if (item->data(Qt::UserRole).toInt() == id) {
                    _p_model->removeRow(row);
                    break;
                }
            }
        }
        break;
    }
    case OpenLabel::GraphicsSelect: {
        const OpenLabel::GraphicsSelectEvent *selectEvent =
            static_cast<const OpenLabel::GraphicsSelectEvent *>(event);
        QList<int> ids = selectEvent->ids();
        for (int id : ids) {
            for (int row = 0; row < _p_model->rowCount(); ++row) {
                QStandardItem *item = _p_model->item(row);
                if (item->data(Qt::UserRole).toInt() == id) {
                    QModelIndex index = _p_model->index(row, 0);
                    _p_selectionModel->select(index, QItemSelectionModel::Select);
                    break;
                }
            }
        }
        break;
    }
    case OpenLabel::GraphicsDeselect: {
        const OpenLabel::GraphicsDeselectEvent *deselectEvent =
            static_cast<const OpenLabel::GraphicsDeselectEvent *>(event);
        QList<int> ids = deselectEvent->ids();
        for (int id : ids) {
            for (int row = 0; row < _p_model->rowCount(); ++row) {
                QStandardItem *item = _p_model->item(row);
                if (item->data(Qt::UserRole).toInt() == id) {
                    QModelIndex index = _p_model->index(row, 0);
                    _p_selectionModel->select(index, QItemSelectionModel::Deselect);
                    break;
                }
            }
        }
        break;
    }
    case OpenLabel::GraphicsModify: {
        const OpenLabel::GraphicsModifyEvent *modifyEvent =
            static_cast<const OpenLabel::GraphicsModifyEvent *>(event);
        int id = modifyEvent->id();
        QSharedPointer<OpenLabel::GraphicsObject> graphicsObject = _p_currentScene->findGraphicsById(id);
        if (!graphicsObject) {
            break;
        }
        for (int row = 0; row < _p_model->rowCount(); ++row) {
            QStandardItem *item = _p_model->item(row);
            if (item->data(Qt::UserRole).toInt() == id) {
                item->setText(graphicsObject->name());
                break;
            }
        }
        break;
    }
    default:
        break;
    }

    _isUpdating = false;
}

void GraphicsListDockWidget::onDocumentChanged(const DocumentChangedEvent &event)
{
    if (event.changeType() == DocumentChangedEvent::DocumentOpened) {
        _p_currentScene = event.document()->scene();
        _p_currentScene->addSceneEventListener(this);
        connect(_p_selectionModel, &QItemSelectionModel::selectionChanged, this,
                &GraphicsListDockWidget::onSelectionChanged);
    } else if (event.changeType() == DocumentChangedEvent::DocumentClosed) {
        disconnect(_p_selectionModel, &QItemSelectionModel::selectionChanged, this,
                   &GraphicsListDockWidget::onSelectionChanged);
        _p_currentScene->removeSceneEventListener(this);
        _p_currentScene = nullptr;
    }
}

void GraphicsListDockWidget::onSelectionChanged(const QItemSelection &selected,
                                                const QItemSelection &deselected)
{
    if (_isUpdating || !_p_currentScene) {
        return;
    }

    _isUpdating = true;

    // Process selected items
    QModelIndexList selectedIndexList = selected.indexes();
    for (const QModelIndex &index : selectedIndexList) {
        int id = index.data(Qt::UserRole).toInt();
        _p_currentScene->selection(id, true);
    }

    QModelIndexList deselectedIndexList = deselected.indexes();
    for (const QModelIndex &index : deselectedIndexList) {
        int id = index.data(Qt::UserRole).toInt();
        _p_currentScene->selection(id, false);
    }

    _isUpdating = false;
}
