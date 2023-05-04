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

#include "openlabel/graphicsevent.h"
#include "openlabel/graphicsobject.h"
#include "openlabel/scene.h"
#include "openlabel/sceneeventlistener.h"
#include "qtpropertybrowser.h"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include <QDockWidget>
#include <QMap>

namespace Gui {

class GraphicsPropertyBrowser : public QDockWidget, public OpenLabel::SceneEventListener
{
    Q_OBJECT
  public:
    explicit GraphicsPropertyBrowser(QWidget *parent = nullptr);

    void registerScene(OpenLabel::Scene *scene);
    void unregisterScene();

  protected:
    void showEvent(QShowEvent *event) override;
    void onSceneEvent(OpenLabel::SceneEvent *event) override;

  private slots:
    void updateProperty(QtProperty *property, const QVariant &value);
    void updateProperty(const QString &propertyName, const QVariant &value);

  private:
    void setObjects(const QList<int> &graphicsObjectIds);
    void addProperty(QtVariantProperty *property, const QString &id);
    void updateProperties();

    QtTreePropertyBrowser *_p_propertyBrowser;
    QMap<QString, QtVariantProperty *> _propertyToId;
    QMap<QtProperty *, QString> _idToProperty;

    OpenLabel::Scene *_p_scene;
    QList<int> _currentGraphicsIds;
};

} // namespace Gui
