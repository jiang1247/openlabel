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

#include "user.h"

using namespace Perm;

User::User(const QString &username, const QString &password, const Role &role)
    : _username(username)
    , _password(password)
    , _role(role)
{
}

User::User(const User &other)
    : _username(other._username)
    , _password(other._password)
    , _role(other._role)
{
}

User &User::operator=(const User &other)
{
    if (this != &other) {
        _username = other._username;
        _password = other._password;
        _role = other._role;
    }
    return *this;
}

bool User::operator==(const User &other) const
{
    return (_username == other._username && _password == other._password &&
            _role == other._role);
}

bool User::operator!=(const User &other) const
{
    return !(*this == other);
}

QString User::username() const
{
    return _username;
}

QString User::password() const
{
    return _password;
}

void User::setPassword(const QString &password)
{
    _password = password;
}

Role User::role() const
{
    return _role;
}

void User::setRole(const Role &role)
{
    _role = role;
}
