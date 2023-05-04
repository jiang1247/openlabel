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
#include "documentchangedevent.h"
#include <QDockWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>

namespace Gui {

class DataListDockWidget : public QDockWidget, public OpenLabel::SceneEventListener
{
    Q_OBJECT
  public:
    explicit DataListDockWidget(QWidget *parent = nullptr);

    // SceneEventListener interface
    void onSceneEvent(OpenLabel::SceneEvent *event) override;

  public slots:
    void onDocumentChanged(const DocumentChangedEvent &event);
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

  private:
    OpenLabel::Scene *_p_currentScene;
    QListView *_p_listView;
    QVBoxLayout *_p_layout;
    QStandardItemModel *_p_model;
    QItemSelectionModel *_p_selectionModel;
    bool _isUpdating;
};

} // namespace Gui
