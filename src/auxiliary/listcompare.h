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

#include <QList>

namespace Utils {

class ListCompare
{
  public:
    template<typename T> static bool allEqual(const QList<T> &list)
    {
        if (list.isEmpty()) {
            return true;
        }
        const T &first = list.first();
        for (int i = 1; i < list.size(); i++) {
            if (list.at(i) != first) {
                return false;
            }
        }
        return true;
    }
};

} // namespace Utils
