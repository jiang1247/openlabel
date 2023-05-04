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

#include "operationsdockwidget.h"
#include "openlabel/document.h"
#include "openlabel/scene.h"

using namespace Gui;

OperationsDockWidget::OperationsDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , _p_tabWidget(new QTabWidget(this))
    , _p_logTextEdit(new QTextEdit(this))
    , _p_historyView(new QUndoView(this))
    , _p_commandLineEdit(new QTextEdit(this))
{
    setWindowTitle(tr("Operations"));

    _p_logTextEdit->setReadOnly(true);
    _p_commandLineEdit->setReadOnly(true);

    _p_tabWidget->addTab(_p_historyView, tr("History"));
    _p_tabWidget->addTab(_p_logTextEdit, tr("Log"));
    _p_tabWidget->addTab(_p_commandLineEdit, tr("Command Line"));

    setWidget(_p_tabWidget);
}

void OperationsDockWidget::onDocumentChanged(const DocumentChangedEvent &event)
{
    if (event.changeType() == DocumentChangedEvent::DocumentOpened) {
        OpenLabel::Document *document = event.document();
        OpenLabel::Scene *scene = document->scene();
        _p_historyView->setStack(scene->operationStack());
    } else if (event.changeType() == DocumentChangedEvent::DocumentClosed) {
        _p_historyView->setStack(nullptr);
    }
}
