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
#include "role.h"
#include <QMap>
#include <QString>

namespace Perm {

class PermissionManager
{
  public:
    static PermissionManager &instance();

    bool addPermission(const Permission &permission);
    bool removePermission(const QString &permissionId);
    Permission getPermission(const QString &permissionId) const;
    bool updatePermission(const Permission &permission);

    bool addRole(const Role &role);
    bool removeRole(const QString &roleName);
    Role getRole(const QString &roleName) const;
    bool updateRole(const Role &role);

  private:
    PermissionManager() = default;

    QMap<QString, Permission> _permissions;
    QMap<QString, Role> _roles;
};

} // namespace Perm
