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

#include "scene.h"
#include <QObject>

namespace OpenLabel {

class Document : public QObject
{
    Q_OBJECT

  public:
    explicit Document(QObject *parent = nullptr);
    virtual ~Document();

    Scene *scene() const;

    bool load(const QString &filePath);
    bool save();
    bool saveAs(const QString &filePath);

    QString docPath() const;
    QString docName() const;

  private:
    Scene *_p_scene;

    QString _path;
};

}
