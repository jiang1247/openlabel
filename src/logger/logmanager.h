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

#include "logger.h"
#include "loghandler.h"
#include <QMap>
#include <QMutex>
#include <QSharedPointer>
#include <QString>

namespace Log {

class LogManager
{
  public:
    static LogManager &instance();

    QSharedPointer<Logger> getLogger(const QString &name);

  private:
    LogManager() = default;
    ~LogManager() = default;

    LogManager(const LogManager &) = delete;
    LogManager &operator=(const LogManager &) = delete;

    QMap<QString, QSharedPointer<Logger>> _loggers;
    QMutex _mutex;
};

} // namespace Log
