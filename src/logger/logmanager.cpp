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

#include "logmanager.h"

using namespace Log;

LogManager &LogManager::instance()
{
    static LogManager manager;
    return manager;
}

QSharedPointer<Logger> LogManager::getLogger(const QString &name)
{
    QMutexLocker locker(&_mutex);

    if (!_loggers.contains(name))
        _loggers[name] = QSharedPointer<Logger>::create(name);

    return _loggers[name];
}
