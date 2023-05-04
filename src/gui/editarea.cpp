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

#include "editarea.h"
#include "mouseproxy.h"
#include <QVBoxLayout>

using namespace Gui;

EditArea::EditArea(QWidget *parent)
    : QWidget(parent)
    , _p_graphicsView(nullptr)
    , _p_graphicsScene(nullptr)
    , _p_mouseProxy(nullptr)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(5);
    setLayout(layout);
}

EditArea::~EditArea() {}

void EditArea::onDocumentChanged(const DocumentChangedEvent &event)
{
    if (_p_mouseProxy) {
        delete _p_mouseProxy;
        _p_mouseProxy = nullptr;
    }

    if (_p_graphicsView) {
        layout()->removeWidget(_p_graphicsView);
        delete _p_graphicsView;
        _p_graphicsView = nullptr;
    }

    if (_p_graphicsScene) {
        delete _p_graphicsScene;
        _p_graphicsScene = nullptr;
    }

    if (event.changeType() == DocumentChangedEvent::DocumentOpened) {
        _p_graphicsView = new GraphicsView(this);

        _p_graphicsScene = new GraphicsScene(this);
        _p_graphicsView->setScene(_p_graphicsScene);

        layout()->addWidget(_p_graphicsView);

        _p_graphicsScene->registerScene(event.document()->scene());
        _p_graphicsView->centerOn(0.0, 0.0);

        _p_mouseProxy = new MouseProxy(_p_graphicsView, this);
    }
}
