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

#include "mainwindow.h"
#include "addellipseaction.h"
#include "addstringaction.h"
#include "addtextaction.h"
#include "openlabel/document.h"
#include "openlabel/scene.h"
#include "datalistdockwidget.h"
#include "docnewaction.h"
#include "docopenaction.h"
#include "docsaveaction.h"
#include "editarea.h"
#include "graphicslistdockwidget.h"
#include "graphicspropertydockwidget.h"
#include "operationsdockwidget.h"
#include "removegraphicsaction.h"

#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QToolBar>

#include <QDebug>

using namespace Gui;

MainWindow *MainWindow::_p_instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _p_document(nullptr)
    , _p_mainToolBar(new QToolBar(this))
    , _p_menuBar(new QMenuBar(this))
    , _p_fileMenu(new QMenu(tr("File"), this))
    , _p_editMenu(new QMenu(tr("Edit"), this))
    , _p_viewMenu(new QMenu(tr("View"), this))
    , _p_helpMenu(new QMenu(tr("Help"), this))
    , _p_editArea(new EditArea(this))
{
    Q_ASSERT(!_p_instance);
    _p_instance = this;

    _actions[Doc_New] = new DocNewAction(this);
    _actions[Doc_Open] = new DocOpenAction(this);
    _actions[Doc_Save] = new DocSaveAction(this);

    _actions[Add_Ellipse] = new AddEllipseAction(this);
    _actions[Add_Text] = new AddTextAction(this);

    _actions[Add_String] = new AddStringAction(this);

    _actions[Edit_Remove] = new RemoveGraphicsAction(this);

    QAction *pUndoAct = new QAction(this);
    pUndoAct->setText(tr("Undo"));
    pUndoAct->setIcon(QIcon(":/icons/undo.png"));
    pUndoAct->setToolTip(tr("Undo"));
    connect(pUndoAct, &QAction::triggered, this, &MainWindow::doUndo);
    _actions[Edit_Undo] = pUndoAct;

    QAction *pRedoAct = new QAction(this);
    pRedoAct->setText(tr("Redo"));
    pRedoAct->setIcon(QIcon(":/icons/redo.png"));
    pRedoAct->setToolTip(tr("Redo"));
    connect(pRedoAct, &QAction::triggered, this, &MainWindow::doRedo);
    _actions[Edit_Redo] = pRedoAct;

    setCentralWidget(_p_editArea);

    _p_graphicsListDockWidget = new GraphicsListDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, _p_graphicsListDockWidget);
    connect(this, &MainWindow::documentChanged, _p_graphicsListDockWidget,
            &GraphicsListDockWidget::onDocumentChanged);

    _p_dataListDockWidget = new DataListDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, _p_dataListDockWidget);
    connect(this, &MainWindow::documentChanged, _p_dataListDockWidget,
            &DataListDockWidget::onDocumentChanged);

    _p_operationsDock = new OperationsDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea, _p_operationsDock);
    connect(this, &MainWindow::documentChanged, _p_operationsDock,
            &OperationsDockWidget::onDocumentChanged);

    _p_graphicsPropertyBrowser = new GraphicsPropertyDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, _p_graphicsPropertyBrowser);

    createMenus();
    createToolBars();

    connect(this, &MainWindow::documentChanged, _p_editArea, &EditArea::onDocumentChanged);

    QTimer::singleShot(100, this, [this]() { emit _actions[Doc_New]->triggered(); });

    setMinimumSize(1280, 800);
}

MainWindow::~MainWindow()
{
    unregisterDocument();

    Q_ASSERT(_p_instance == this);
    _p_instance = nullptr;
}

MainWindow &MainWindow::window()
{
    Q_ASSERT(_p_instance);
    return (*_p_instance);
}

OpenLabel::Document *MainWindow::document()
{
    return _p_document;
}

void MainWindow::registerDocument(OpenLabel::Document *document)
{
    if (!document) {
        return;
    }
    unregisterDocument();

    qDebug() << "document registered";
    _p_document = document;

    DocumentChangedEvent event(DocumentChangedEvent::DocumentOpened, _p_document);
    emit documentChanged(event);

    OpenLabel::Scene *scene = document->scene();
    connect(scene, SIGNAL(canUndoChanged(bool)), this, SLOT(onCanUndoChanged(bool)));
    connect(scene, SIGNAL(canRedoChanged(bool)), this, SLOT(onCanRedoChanged(bool)));

    _p_graphicsPropertyBrowser->setScene(scene);

    _actions[Edit_Undo]->setEnabled(false);
    _actions[Edit_Redo]->setEnabled(false);
}

void MainWindow::unregisterDocument()
{
    if (!_p_document) {
        return;
    }

    qDebug() << "document unregistered";
    OpenLabel::Scene *scene = _p_document->scene();
    disconnect(scene, SIGNAL(canUndoChanged(bool)), this, SLOT(onCanUndoChanged(bool)));
    disconnect(scene, SIGNAL(canRedoChanged(bool)), this, SLOT(onCanRedoChanged(bool)));

    _p_graphicsPropertyBrowser->setScene(nullptr);

    DocumentChangedEvent event(DocumentChangedEvent::DocumentClosed, _p_document);
    emit documentChanged(event);

    delete _p_document;
    _p_document = nullptr;

    _actions[Edit_Undo]->setEnabled(false);
    _actions[Edit_Redo]->setEnabled(false);
}

void MainWindow::onCanUndoChanged(bool enabled)
{
    _actions[Edit_Undo]->setEnabled(enabled);
}

void MainWindow::onCanRedoChanged(bool enabled)
{
    _actions[Edit_Redo]->setEnabled(enabled);
}

void MainWindow::doUndo()
{
    if (!_p_document) {
        return;
    }
    OpenLabel::Scene *scene = _p_document->scene();
    scene->undo();
}

void MainWindow::doRedo()
{
    if (!_p_document) {
        return;
    }
    OpenLabel::Scene *scene = _p_document->scene();
    scene->redo();
}

void MainWindow::createMenus()
{
    _p_menuBar->addMenu(_p_fileMenu);
    _p_menuBar->addMenu(_p_editMenu);
    _p_menuBar->addMenu(_p_viewMenu);
    _p_menuBar->addMenu(_p_helpMenu);

    _p_fileMenu->addAction(_actions[Doc_New]);
    _p_fileMenu->addAction(_actions[Doc_Open]);
    _p_fileMenu->addAction(_actions[Doc_Save]);

    _p_editMenu->addAction(_actions[Edit_Undo]);
    _p_editMenu->addAction(_actions[Edit_Redo]);
    _p_editMenu->addSeparator();
    _p_editMenu->addAction(_actions[Edit_Remove]);
    _p_editMenu->addSeparator();
    _p_editMenu->addAction(_actions[Add_Ellipse]);
    _p_editMenu->addAction(_actions[Add_Text]);
    _p_editMenu->addSeparator();
    _p_editMenu->addAction(_actions[Add_String]);
    setMenuBar(_p_menuBar);
}

void MainWindow::createToolBars()
{
    _p_mainToolBar->addAction(_actions[Doc_New]);
    _p_mainToolBar->addAction(_actions[Doc_Open]);
    _p_mainToolBar->addAction(_actions[Doc_Save]);
    _p_mainToolBar->addSeparator();
    _p_mainToolBar->addAction(_actions[Edit_Undo]);
    _p_mainToolBar->addAction(_actions[Edit_Redo]);
    _p_mainToolBar->addSeparator();
    _p_mainToolBar->addAction(_actions[Edit_Remove]);
    _p_mainToolBar->addSeparator();
    _p_mainToolBar->addAction(_actions[Add_Ellipse]);
    _p_mainToolBar->addAction(_actions[Add_Text]);
    _p_mainToolBar->addSeparator();
    _p_mainToolBar->addAction(_actions[Add_String]);

    addToolBar(_p_mainToolBar);
}
