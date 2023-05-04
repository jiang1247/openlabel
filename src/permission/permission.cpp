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

#include "permission.h"

using namespace Perm;

Permission::Permission(const QString &permissionId, const QString &description)
    : _permissionId(permissionId)
    , _description(description)
{
}

Permission::Permission(const Permission &other)
    : _permissionId(other._permissionId)
    , _description(other._description)
{
}

QString Permission::permissionId() const
{
    return _permissionId;
}

QString Permission::description() const
{
    return _description;
}

void Permission::setDescription(const QString &description)
{
    _description = description;
}

Permission &Permission::operator=(const Permission &other)
{
    if (this != &other) {
        _permissionId = other._permissionId;
        _description = other._description;
    }
    return (*this);
}

bool Permission::operator==(const Permission &other) const
{
    return (_permissionId == other._permissionId && _description == other._description);
}

bool Permission::operator!=(const Permission &other) const
{
    return !(*this == other);
}
