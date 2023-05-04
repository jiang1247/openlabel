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

#include "datalistdockwidget.h"
#include "openlabel/datasourceevent.h"
#include "openlabel/document.h"
#include "openlabel/sceneevent.h"

#include <QDebug>

using namespace Gui;

DataListDockWidget::DataListDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , _p_currentScene(nullptr)
    , _p_listView(new QListView(this))
    , _p_layout(new QVBoxLayout())
    , _p_model(new QStandardItemModel(this))
    , _p_selectionModel(new QItemSelectionModel(_p_model))
    , _isUpdating(false)
{
    setWindowTitle(tr("Data list"));

    _p_layout->setMargin(1);
    _p_layout->addWidget(_p_listView);
    _p_listView->setModel(_p_model);
    _p_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _p_listView->setSelectionModel(_p_selectionModel);

    QWidget *containerWidget = new QWidget;
    containerWidget->setLayout(_p_layout);
    setWidget(containerWidget);
}

void DataListDockWidget::onSceneEvent(OpenLabel::SceneEvent *event)
{
    if (_isUpdating || !_p_currentScene) {
        return;
    }

    _isUpdating = true;

    switch (event->type()) {
    case OpenLabel::DataSourceAdd: {
        const OpenLabel::DataSourceAddEvent *addEvent =
            static_cast<const OpenLabel::DataSourceAddEvent *>(event);
        QList<int> ids = addEvent->ids();
        for (int id : ids) {
            QSharedPointer<OpenLabel::DataSource> dataSource = _p_currentScene->findDataSourceById(id);
            if (!dataSource) {
                continue;
            }
            QStandardItem *item = new QStandardItem(dataSource->name());
            item->setData(dataSource->dataSourceId(), Qt::UserRole);
            _p_model->appendRow(item);
        }
        break;
    }
    case OpenLabel::DataSourceRemove: {
        const OpenLabel::DataSourceRemoveEvent *removeEvent =
            static_cast<const OpenLabel::DataSourceRemoveEvent *>(event);
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
    case OpenLabel::DataSourceModify: {
        const OpenLabel::DataSourceModifyEvent *modifyEvent =
            static_cast<const OpenLabel::DataSourceModifyEvent *>(event);
        int id = modifyEvent->id();
        QSharedPointer<OpenLabel::DataSource> dataSource = _p_currentScene->findDataSourceById(id);
        if (!dataSource) {
            break;
        }
        for (int row = 0; row < _p_model->rowCount(); ++row) {
            QStandardItem *item = _p_model->item(row);
            if (item->data(Qt::UserRole).toInt() == id) {
                item->setText(dataSource->dataSourceName());
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

void DataListDockWidget::onDocumentChanged(const DocumentChangedEvent &event)
{
    if (event.changeType() == DocumentChangedEvent::DocumentOpened) {
        _p_currentScene = event.document()->scene();
        _p_currentScene->addSceneEventListener(this);
        connect(_p_selectionModel, &QItemSelectionModel::selectionChanged, this,
                &DataListDockWidget::onSelectionChanged);
    } else if (event.changeType() == DocumentChangedEvent::DocumentClosed) {
        disconnect(_p_selectionModel, &QItemSelectionModel::selectionChanged, this,
                   &DataListDockWidget::onSelectionChanged);
        _p_currentScene->removeSceneEventListener(this);
        _p_currentScene = nullptr;
    }
}

void DataListDockWidget::onSelectionChanged(const QItemSelection &selected,
                                            const QItemSelection &deselected)
{
    // TODO: Handle selection changes
}
