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

#include <QDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace Gui {

class BindingDataSourceDialog : public QDialog
{
    Q_OBJECT
  public:
    explicit BindingDataSourceDialog(QWidget *parent = nullptr);
    QList<int> getSelectedDataSourceIds() const;

  private slots:
    void onAddButtonClicked();

  private:
    void initializeDataSourceList();

    QListWidget *_p_availableDataSourcesList;
    QListWidget *_p_selectedDataSourcesList;
    QPushButton *_p_addButton;
    QPushButton *_p_applyButton;
    QPushButton *_p_cancelButton;
};

} // namespace Gui
