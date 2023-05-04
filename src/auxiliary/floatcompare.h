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

#include <QPointF>
#include <QRectF>
#include <QSizeF>
#include <cmath>
#include <type_traits>

namespace Utils {

class FloatCompare
{
  public:
    template<typename T> static bool isEqual(const T &left, const T &right)
    {
        static_assert(std::is_floating_point<T>::value || std::is_same<T, QPointF>::value ||
                          std::is_same<T, QSizeF>::value || std::is_same<T, QRectF>::value,
                      "Type must be floating point or QPointF, QSizeF or QRectF.");
        return isEqualHelper(left, right, std::is_floating_point<T>());
    }

  private:
    template<typename T> static bool isEqualHelper(const T &left, const T &right, std::true_type)
    {
        return std::fabs(left - right) < std::numeric_limits<T>::epsilon();
    }

    static bool isEqualHelper(const QPointF &left, const QPointF &right, std::false_type)
    {
        return isEqual(left.x(), right.x()) && isEqual(left.y(), right.y());
    }

    static bool isEqualHelper(const QSizeF &left, const QSizeF &right, std::false_type)
    {
        return isEqual(left.width(), right.width()) && isEqual(left.height(), right.height());
    }

    static bool isEqualHelper(const QRectF &left, const QRectF &right, std::false_type)
    {
        return isEqual(left.topLeft(), right.topLeft()) && isEqual(left.size(), right.size());
    }
};

} // namespace Utils
