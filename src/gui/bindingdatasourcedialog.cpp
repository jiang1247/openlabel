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

#include "bindingdatasourcedialog.h"
#include "openlabel/datasource.h"
#include "openlabel/document.h"
#include "openlabel/scene.h"
#include "mainwindow.h"

using namespace Gui;

BindingDataSourceDialog::BindingDataSourceDialog(QWidget *parent)
    : QDialog(parent)
    , _p_availableDataSourcesList(new QListWidget(this))
    , _p_selectedDataSourcesList(new QListWidget(this))
    , _p_addButton(new QPushButton(tr("Add"), this))
    , _p_applyButton(new QPushButton(tr("Apply"), this))
    , _p_cancelButton(new QPushButton(tr("Cancel"), this))
{
    setWindowTitle(tr("Bind Data Sources"));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *listLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    listLayout->addWidget(_p_availableDataSourcesList);
    listLayout->addWidget(_p_addButton);
    listLayout->addWidget(_p_selectedDataSourcesList);

    buttonLayout->addStretch();
    buttonLayout->addWidget(_p_applyButton);
    buttonLayout->addWidget(_p_cancelButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Connect add button clicked signal to onAddButtonClicked slot
    connect(_p_addButton, &QPushButton::clicked, this, &BindingDataSourceDialog::onAddButtonClicked);
    connect(_p_applyButton, &QPushButton::clicked, this, &BindingDataSourceDialog::accept);
    connect(_p_cancelButton, &QPushButton::clicked, this, &BindingDataSourceDialog::reject);

    initializeDataSourceList();
}

void BindingDataSourceDialog::onAddButtonClicked()
{
    auto selectedItems = _p_availableDataSourcesList->selectedItems();
    for (auto item : selectedItems) {
        _p_selectedDataSourcesList->addItem(item->clone());
    }
}

QList<int> BindingDataSourceDialog::getSelectedDataSourceIds() const
{
    QList<int> dataSourceIds;
    for (int i = 0; i < _p_selectedDataSourcesList->count(); ++i) {
        QListWidgetItem *item = _p_selectedDataSourcesList->item(i);
        dataSourceIds.append(item->data(Qt::UserRole).toInt());
    }
    return dataSourceIds;
}

void BindingDataSourceDialog::initializeDataSourceList()
{
    auto document = MainWindow::window().document();
    if (!document) {
        return;
    }

    auto scene = document->scene();
    if (!scene) {
        return;
    }

    QList<int> dataSourceIds = scene->allDataSourceIds();
    for (int id : dataSourceIds) {
        QSharedPointer<OpenLabel::DataSource> dataSource = scene->findDataSourceById(id);
        if (!dataSource) {
            continue;
        }

        QListWidgetItem *item = new QListWidgetItem(dataSource->name());
        item->setData(Qt::UserRole, dataSource->dataSourceId());
        _p_availableDataSourcesList->addItem(item);
    }
}
