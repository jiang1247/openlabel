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

#include "logger.h"

using namespace Log;

Logger::Logger(const QString &name)
    : _name(name)
    , _level(LogLevel::Debug)
{
}

Logger::~Logger() {}

void Logger::setLevel(LogLevel level)
{
    _level = level;
}

LogLevel Logger::level() const
{
    return _level;
}

void Logger::registerHandler(QSharedPointer<LogHandler> handler)
{
    if (!_handlers.contains(handler))
        _handlers.append(handler);
}

void Logger::unregisterHandler(QSharedPointer<LogHandler> handler)
{
    if (_handlers.contains(handler))
        _handlers.removeAll(handler);
}

void Logger::debug(const QString &message)
{
    log(LogLevel::Debug, message);
}

void Logger::info(const QString &message)
{
    log(LogLevel::Info, message);
}

void Logger::warning(const QString &message)
{
    log(LogLevel::Warning, message);
}

void Logger::critical(const QString &message)
{
    log(LogLevel::Critical, message);
}

void Logger::log(LogLevel level, const QString &message)
{
    if (level < _level)
        return;

    for (const auto &handler : qAsConst(_handlers)) {
        handler->handle(_name, level, message);
    }
}
