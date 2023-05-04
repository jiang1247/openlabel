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

#include "log.h"
#include "loghandler.h"
#include <QSharedPointer>
#include <QString>
#include <QVector>

namespace Log {

class Logger
{
  public:
    Logger(const QString &name);
    ~Logger();

    void setLevel(LogLevel level);
    LogLevel level() const;

    void registerHandler(QSharedPointer<LogHandler> handler);
    void unregisterHandler(QSharedPointer<LogHandler> handler);

    void debug(const QString &message);
    void info(const QString &message);
    void warning(const QString &message);
    void critical(const QString &message);

  private:
    void log(LogLevel level, const QString &message);

    QString _name;
    LogLevel _level;
    QVector<QSharedPointer<LogHandler>> _handlers;
};

} // namespace Log
