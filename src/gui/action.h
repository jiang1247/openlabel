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

#include <QAction>

namespace Gui {
class Operation;

class Action : public QAction
{
    Q_OBJECT
  public:
    enum Flag {
        RequirePermission = 0x01,
        RequireDocument = 0x02,
        RequireSelection = 0x04,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    explicit Action(QObject *parent = nullptr);
    virtual ~Action() = default;

    virtual void updateState();

    const Flags &flags() const;
    void setFlags(const Flags &newFlags);

    virtual void execute() = 0;

    const QString &permissionId() const;
    void setPermissionId(const QString &permissionId);

  public slots:
    void onTriggered();

  protected:
    Flags _flags;
    QString _permissionId;
};

} // namespace Gui

Q_DECLARE_OPERATORS_FOR_FLAGS(Gui::Action::Flags)
