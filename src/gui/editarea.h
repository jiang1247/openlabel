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

#include "openlabel/document.h"
#include "documentchangedevent.h"
#include "graphicsscene.h"
#include "graphicsview.h"
#include <QWidget>

namespace Gui {

class MouseProxy;

class EditArea : public QWidget
{
    Q_OBJECT

  public:
    explicit EditArea(QWidget *parent = nullptr);
    ~EditArea();

  public slots:
    void onDocumentChanged(const Gui::DocumentChangedEvent &event);

  private:
    GraphicsView *_p_graphicsView;
    GraphicsScene *_p_graphicsScene;
    MouseProxy *_p_mouseProxy;
};

} // namespace Gui
