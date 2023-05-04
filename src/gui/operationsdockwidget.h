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

#include "documentchangedevent.h"
#include <QDockWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QUndoView>

namespace Gui {

class OperationsDockWidget : public QDockWidget
{
    Q_OBJECT
  public:
    explicit OperationsDockWidget(QWidget *parent = nullptr);

  public slots:
    void onDocumentChanged(const DocumentChangedEvent &event);

  private:
    QTabWidget *_p_tabWidget;
    QTextEdit *_p_logTextEdit;
    QUndoView *_p_historyView;
    QTextEdit *_p_commandLineEdit;
};

} // namespace Gui
