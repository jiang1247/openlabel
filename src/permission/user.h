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

#include "role.h"
#include <QMetaType>
#include <QString>

namespace Perm {

class User
{
  public:
    User() = default;
    User(const QString &username, const QString &password, const Role &role);
    User(const User &other);

    User &operator=(const User &other);
    bool operator==(const User &other) const;
    bool operator!=(const User &other) const;

    QString username() const;
    QString password() const;
    void setPassword(const QString &password);

    Role role() const;
    void setRole(const Role &role);

  private:
    QString _username;
    QString _password;
    Role _role;
};

} // namespace Perm

Q_DECLARE_METATYPE(Perm::User)
