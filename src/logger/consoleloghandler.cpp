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

#include "consoleloghandler.h"
#include <QTime>
#include <iostream>

using namespace Log;

ConsoleLogHandler::ConsoleLogHandler()
    : LogHandler()
{
}

void ConsoleLogHandler::handle(const QString &name, LogLevel level, const QString &message)
{
    QString levelName;
    switch (level) {
    case LogLevel::Debug:
        levelName = "debug";
        break;
    case LogLevel::Info:
        levelName = "info";
        break;
    case LogLevel::Warning:
        levelName = "warning";
        break;
    case LogLevel::Critical:
        levelName = "error";
        break;
    default:
        break;
    }
    if (levelName.isEmpty()) {
        return;
    }

    QString formattedMessage =
        QString("[%1 %2] %3: %4")
            .arg(name, levelName, QTime::currentTime().toString("hh:mm:ss"), message);
    std::cout << formattedMessage.toStdString() << std::endl;
}
