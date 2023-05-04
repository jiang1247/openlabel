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

#include "addtextaction.h"
#include "bindingdatasourcedialog.h"
#include "openlabel/addgraphicsoperation.h"
#include "openlabel/document.h"
#include "openlabel/textgraphics.h"
#include "mainwindow.h"

#include <QUndoStack>

#include <QDebug>

using namespace Gui;

AddTextAction::AddTextAction(QObject *parent)
    : Action(parent)
{
    setText(tr("Add Text"));
    setIcon(QIcon(":/icons/text.png"));
    setToolTip(tr("Add a new text to the scene"));

    setFlags(Action::RequireDocument);
}

void AddTextAction::execute()
{
    BindingDataSourceDialog dlg;
    if (!dlg.exec()) {
        return;
    }
    QList<int> dsIds = dlg.getSelectedDataSourceIds();
    if (dsIds.isEmpty()) {
        return;
    }
    qDebug() << "begin execute add text action";
    auto document = MainWindow::window().document();
    Q_ASSERT(document);
    auto scene = document->scene();
    Q_ASSERT(scene);
    auto addTextOperation =
        new OpenLabel::AddGraphicsOperation(OpenLabel::TextGraphicsType, OpenLabel::Properties(), dsIds, scene);
    scene->pushOperation(addTextOperation);
    qDebug() << "end execute add text action";
}
