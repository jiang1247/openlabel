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

#include "addstringaction.h"
#include "openlabel/adddatasourceoperation.h"
#include "openlabel/document.h"
#include "openlabel/stringdata.h"
#include "mainwindow.h"

#include <QDebug>
#include <QInputDialog>
#include <QUndoStack>

using namespace Gui;

AddStringAction::AddStringAction(QObject *parent)
    : Action(parent)
{
    setText(tr("Add String"));
    setIcon(QIcon(":/icons/string.png"));
    setToolTip(tr("Add a new string to the scene"));

    setFlags(Action::RequireDocument);
}

void AddStringAction::execute()
{
    qDebug() << "begin execute add string action";
    auto document = MainWindow::window().document();
    Q_ASSERT(document);
    auto scene = document->scene();
    Q_ASSERT(scene);

    bool ok;
    QString initialText = QInputDialog::getMultiLineText(
        &MainWindow::window(), tr("Add String"), tr("Enter the initial text:"), QString(), &ok);

    if (ok && !initialText.isEmpty()) {
        OpenLabel::Properties properties;
        qDebug() << "string ide " << objectPropertyId("String");
        properties.append(OpenLabel::Property(objectPropertyId("String"), initialText));
        auto addStringOperation =
            new OpenLabel::AddDataSourceOperation(OpenLabel::StringDataSouceType, properties, scene);
        scene->pushOperation(addStringOperation);
        qDebug() << "end execute add string action";
    } else {
        qDebug() << "user canceled or provided empty input";
    }
}
