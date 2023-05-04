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

#include <QMainWindow>

#include "documentchangedevent.h"

namespace OpenLabel {
class Document;
}

namespace Gui {

class EditArea;
class GraphicsListDockWidget;
class DataListDockWidget;
class OperationsDockWidget;
class GraphicsPropertyDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    enum ActionId {
        Doc_New,
        Doc_Open,
        Doc_Save,

        Add_Ellipse,
        Add_Text,

        Add_String,

        Edit_Undo,
        Edit_Redo,
        Edit_Remove,

    };
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow &window();

    OpenLabel::Document *document();
    void registerDocument(OpenLabel::Document *document);
    void unregisterDocument();

  signals:
    void documentChanged(const Gui::DocumentChangedEvent &event);

  private slots:
    void onCanUndoChanged(bool enabled);
    void onCanRedoChanged(bool enabled);

    void doUndo();
    void doRedo();

  private:
    void createMenus();
    void createToolBars();

    static MainWindow *_p_instance;
    OpenLabel::Document *_p_document;

    QToolBar *_p_mainToolBar;
    QMenuBar *_p_menuBar;

    QMenu *_p_fileMenu;
    QMenu *_p_editMenu;
    QMenu *_p_viewMenu;
    QMenu *_p_helpMenu;

    EditArea *_p_editArea;

    QHash<ActionId, QAction *> _actions;

    GraphicsListDockWidget *_p_graphicsListDockWidget;
    DataListDockWidget *_p_dataListDockWidget;
    OperationsDockWidget *_p_operationsDock;
    GraphicsPropertyDockWidget *_p_graphicsPropertyBrowser;
};

} // namespace Gui
