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

#include "gui/mainwindow.h"
#include "logger/consoleloghandler.h"
#include "logger/logmanager.h"
#include <QApplication>

void loggerOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)
    auto logger = Log::LogManager::instance().getLogger("global");
    QString logMsg(msg);
#if 1
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    QString detailStr = QString(" (%1:%2, %3)").arg(file).arg(context.line).arg(function);
    logMsg.append(detailStr);
#endif
    switch (type) {
    case QtDebugMsg:
        logger->debug(logMsg);
        break;
    case QtInfoMsg:
        logger->info(logMsg);
        break;
    case QtWarningMsg:
        logger->warning(logMsg);
        break;
    case QtCriticalMsg:
        logger->critical(logMsg);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    auto logger = Log::LogManager::instance().getLogger("global");
    auto consoleHandler = QSharedPointer<Log::ConsoleLogHandler>(new Log::ConsoleLogHandler);
    logger->registerHandler(consoleHandler);

    qInstallMessageHandler(loggerOutput);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    Gui::MainWindow *pWindow = new Gui::MainWindow;
    pWindow->show();

    int result = app.exec();

    delete pWindow;

    logger->unregisterHandler(consoleHandler);

    return result;
}
