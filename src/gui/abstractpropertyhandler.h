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

#include <QObject>

#include "openlabel/property.h"

class QtAbstractPropertyBrowser;
class QtVariantEditorFactory;
class QtVariantPropertyManager;
class QtProperty;

namespace OpenLabel {
class Scene;
}

namespace Gui {

class AbstractPropertyHandler : public QObject
{
    Q_OBJECT
  public:
    explicit AbstractPropertyHandler();
    virtual ~AbstractPropertyHandler();

    void setSelectedIds(OpenLabel::Scene *scene, const QList<int> &ids);
    virtual void initProperies() = 0;

    virtual void setPropertyBrowser(QtAbstractPropertyBrowser *browser);

    QtProperty *findProperty(const QString &name) const;

    virtual void resetProperties() = 0;

    void updateProperty(int id, const OpenLabel::Property &property);
    virtual void setPropertyValue(QtProperty *property, const QVariant &val) = 0;

  public slots:
    void onValueChanged(QtProperty *property, const QVariant &val);

  protected:
    bool _updating;
    QtAbstractPropertyBrowser *_p_browser;
    QtVariantEditorFactory *_p_factory;
    QtVariantPropertyManager *_p_manager;
    OpenLabel::Scene *_p_scene;
    QList<int> _ids;
    QHash<int, QtProperty *> _qProperties;
};

} // namespace Gui
