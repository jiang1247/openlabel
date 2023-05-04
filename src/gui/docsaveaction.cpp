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

#include "docsaveaction.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>

using namespace Gui;

DocSaveAction::DocSaveAction(QObject *parent)
    : Action(parent)
{
    setText(tr("Save"));
    setIcon(QIcon(":/icons/doc_save.png"));
    setShortcut(QKeySequence::Save);
    setFlags(RequirePermission | RequireDocument);

    setPermissionId("doc_save");
}

void DocSaveAction::execute()
{
    QString fileName = QFileDialog::getSaveFileName(&MainWindow::window(), tr("Save Document"),
                                                    QString(), tr("Document Files (*.mkr)"));
    if (!fileName.isEmpty()) {
        //        mainWindow->saveDocument(fileName);
    }
}
