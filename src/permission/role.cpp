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

#include "role.h"

using namespace Perm;

Role::Role(const QString &name)
    : _name(name)
{
}

Role::Role(const Role &other)
    : _name(other._name)
    , _permissions(other._permissions)
{
}

Role &Role::operator=(const Role &other)
{
    if (this != &other) {
        _name = other._name;
        _permissions = other._permissions;
    }
    return *this;
}

bool Role::operator==(const Role &other) const
{
    return (_name == other._name && _permissions == other._permissions);
}

bool Role::operator!=(const Role &other) const
{
    return !(*this == other);
}

QString Role::name() const
{
    return _name;
}

bool Role::hasPermission(const Permission &permission) const
{
    return _permissions.contains(permission);
}

void Role::addPermission(const Permission &permission)
{
    _permissions.append(permission);
}

void Role::removePermission(const Permission &permission)
{
    _permissions.removeAll(permission);
}
