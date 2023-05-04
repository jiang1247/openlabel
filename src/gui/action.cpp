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

#include "action.h"

using namespace Gui;

Action::Action(QObject *parent)
    : QAction(parent)
{
    connect(this, &Action::triggered, this, &Action::onTriggered);
}

void Action::updateState()
{
    if (_flags.testFlag(RequirePermission)) {
    }

    if (_flags.testFlag(RequireDocument)) {
    }

    if (_flags.testFlag(RequireSelection)) {
    }

    setEnabled(true);
}

const Action::Flags &Action::flags() const
{
    return _flags;
}

void Action::setFlags(const Flags &newFlags)
{
    _flags = newFlags;
}

void Action::onTriggered()
{
    execute();
}

const QString &Action::permissionId() const
{
    return _permissionId;
}

void Action::setPermissionId(const QString &permissionId)
{
    _permissionId = permissionId;
}
