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

#include "permission.h"
#include <QList>
#include <QMetaType>
#include <QString>

namespace Perm {

class Role
{
  public:
    Role() = default;
    Role(const QString &name);
    Role(const Role &other);

    Role &operator=(const Role &other);
    bool operator==(const Role &other) const;
    bool operator!=(const Role &other) const;

    QString name() const;

    bool hasPermission(const Permission &permission) const;
    void addPermission(const Permission &permission);
    void removePermission(const Permission &permission);

  private:
    QString _name;
    QList<Permission> _permissions;
};

} // namespace Perm

Q_DECLARE_METATYPE(Perm::Role)
