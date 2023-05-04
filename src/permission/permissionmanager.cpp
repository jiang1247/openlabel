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

#include "permissionmanager.h"

using namespace Perm;

PermissionManager &PermissionManager::instance()
{
    static PermissionManager instance;
    return instance;
}

bool PermissionManager::addPermission(const Permission &permission)
{
    if (_permissions.contains(permission.permissionId())) {
        return false;
    }

    _permissions.insert(permission.permissionId(), permission);
    return true;
}

bool PermissionManager::removePermission(const QString &permissionId)
{
    return _permissions.remove(permissionId) > 0;
}

Permission PermissionManager::getPermission(const QString &permissionId) const
{
    return _permissions.value(permissionId);
}

bool PermissionManager::updatePermission(const Permission &permission)
{
    if (!_permissions.contains(permission.permissionId())) {
        return false;
    }

    _permissions.insert(permission.permissionId(), permission);
    return true;
}

bool PermissionManager::addRole(const Role &role)
{
    if (_roles.contains(role.name())) {
        return false;
    }

    _roles.insert(role.name(), role);
    return true;
}

bool PermissionManager::removeRole(const QString &roleName)
{
    return _roles.remove(roleName) > 0;
}

Role PermissionManager::getRole(const QString &roleName) const
{
    return _roles.value(roleName);
}

bool PermissionManager::updateRole(const Role &role)
{
    if (!_roles.contains(role.name())) {
        return false;
    }

    _roles.insert(role.name(), role);
    return true;
}
