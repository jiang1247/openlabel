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

#include "docnewaction.h"
#include "openlabel/document.h"
#include "mainwindow.h"

using namespace Gui;

DocNewAction::DocNewAction(QObject *parent)
    : Action(parent)
{
    setText(tr("New"));
    setIcon(QIcon(":/icons/doc_new.png"));
    setShortcut(QKeySequence::New);
    setFlags(RequirePermission);

    setPermissionId("doc_new");
}

void DocNewAction::execute()
{
    MainWindow::window().registerDocument(new OpenLabel::Document());
}
