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

#include "usermanager.h"

using namespace Perm;

UserManager &UserManager::instance()
{
    static UserManager instance;
    return instance;
}

bool UserManager::login(const QString &username, const QString &password)
{
    User user = _users.value(username);
    if (user.username().isEmpty() || user.password() != password) {
        return false;
    }

    _currentUser = user;
    return true;
}

void UserManager::logout()
{
    _currentUser = User();
}

User UserManager::currentUser() const
{
    return _currentUser;
}

bool UserManager::isLogin()
{
    return _users.values().contains(_currentUser);
}

bool UserManager::addUser(const User &user)
{
    if (_users.contains(user.username())) {
        return false;
    }

    _users.insert(user.username(), user);
    return true;
}

bool UserManager::removeUser(const QString &username)
{
    return _users.remove(username) > 0;
}

User UserManager::getUser(const QString &username) const
{
    return _users.value(username);
}

bool UserManager::updateUser(const User &user)
{
    if (!_users.contains(user.username())) {
        return false;
    }

    _users.insert(user.username(), user);
    return true;
}
