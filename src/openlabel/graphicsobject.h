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

#include "baseobject.h"
#include "propertyiddispatcher.h"
#include "sceneeventlistener.h"

#include <QPointF>
#include <QSizeF>
#include <QTransform>

namespace OpenLabel {

class Scene;

class GraphicsObject : public BaseObject, public SceneEventListener
{
    static const PropertyId NamePropertyId;
    static const PropertyId SelectedPropertyId;
    static const PropertyId PositionPropertyId;
    static const PropertyId SizePropertyId;
    static const PropertyId TransformPropertyId;

  public:
    GraphicsObject(int id, Scene *scene = nullptr);
    GraphicsObject(const GraphicsObject &other) = delete;
    virtual ~GraphicsObject();

    GraphicsObject &operator=(const GraphicsObject &other) = delete;
    bool operator==(const GraphicsObject &other) const;
    bool operator!=(const GraphicsObject &other) const;

    virtual QSharedPointer<GraphicsObject> clone() const;

    virtual QString objectName() const override;
    virtual int objectType() const override;

    virtual void initializeProperties();

    virtual QVariant propertyValue(int id) const override;
    virtual void setProperty(const Property &property) override;
    virtual Properties properties() const override;

    virtual void onSceneEvent(SceneEvent *event) override;

    virtual QSizeF initialSize();
    virtual void updateSize();

    virtual QRectF boundingRect() const;

    QPointF position() const;
    void setPosition(const QPointF &pos);

    QSizeF size() const;
    void setSize(const QSizeF &size);

    virtual int graphicsType() const = 0;
    virtual QString graphicsName() const = 0;

    int graphicsId() const;

    bool isSelected() const;
    void setSelected(bool on);

    const QTransform &transform() const;
    void setTransform(const QTransform &transform);

    Scene *scene();

    QString name() const;
    void setName(const QString &name);

  protected:
    void setScene(Scene *scene);
    Scene *_p_scene;

    QString _name;
    QTransform _transform;
    int _graphicsId;
    bool _selected;
    QPointF _position;
    QSizeF _size;

    friend class Scene;
};

using GraphicsObjects = QList<QSharedPointer<GraphicsObject>>;

} 
