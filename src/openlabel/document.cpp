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

#include "document.h"
#include <QFileInfo>

#include <QDebug>

using namespace OpenLabel;

Document::Document(QObject *parent)
    : QObject(parent)
    , _p_scene(new Scene)
{
    qDebug() << "document is created";
}

Document::~Document()
{
    qDebug() << "document is destroyed";
    delete _p_scene;
}

Scene *Document::scene() const
{
    return _p_scene;
}

bool Document::load(const QString &filePath)
{
    _path = filePath;
    return true;
}

bool Document::save()
{
    if (_path.isEmpty()) {
        return false;
    }

    return true;
}

bool Document::saveAs(const QString &filePath)
{
    _path = filePath;
    return save();
}

QString Document::docPath() const
{
    return _path;
}

QString Document::docName() const
{
    return QFileInfo(_path).fileName();
}
