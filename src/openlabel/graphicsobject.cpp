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

#include "graphicsobject.h"
#include "auxiliary/utils.h"
#include "factory.h"
#include "global.h"

#include <QDebug>

using namespace OpenLabel;

PropertyId GraphicsObject::NamePropertyId = objectPropertyRegister("Name");
PropertyId GraphicsObject::SelectedPropertyId = objectPropertyRegister("Selected");
PropertyId GraphicsObject::PositionPropertyId = objectPropertyRegister("Position");
PropertyId GraphicsObject::SizePropertyId = objectPropertyRegister("Size");
PropertyId GraphicsObject::TransformPropertyId = objectPropertyRegister("Transform");

GraphicsObject::GraphicsObject(int id, Scene *scene)
    : _p_scene(scene)
    , _graphicsId(id)
    , _selected(false)
    , _position(0.0, 0.0)
    , _size(200.0, 200.0)
{
    qDebug() << "graphics object is created, id " << _graphicsId;
}

GraphicsObject::~GraphicsObject()
{
    qDebug() << "graphics object is destroyed, id " << _graphicsId;
}

bool GraphicsObject::operator==(const GraphicsObject &other) const
{
    return _graphicsId == other._graphicsId;
}

bool GraphicsObject::operator!=(const GraphicsObject &other) const
{
    return !(*this == other);
}

QSharedPointer<GraphicsObject> GraphicsObject::clone() const
{
    auto cloned = Factory::createGraphics((GraphicsTypeId)this->graphicsType(),
                                              this->graphicsId(), this->_p_scene);
    cloned->_properties = this->_properties;
    cloned->_position = this->_position;
    cloned->_size = this->_size;
    cloned->_transform = this->_transform;
    cloned->_selected = this->_selected;

    return cloned;
}

QString GraphicsObject::objectName() const
{
    return QStringLiteral("GraphicsObject");
}

int GraphicsObject::objectType() const
{
    return GraphicsObjectType;
}

void GraphicsObject::initializeProperties()
{
    _size = initialSize();
    _name = globalTr("GraphicsObject", "Graphics");
}

QVariant GraphicsObject::propertyValue(int id) const
{
    if (id == NamePropertyId) {
        return name();
    } else if (id == SelectedPropertyId) {
        return isSelected();
    } else if (id == PositionPropertyId) {
        return position();
    } else if (id == SizePropertyId) {
        return size();
    } else if (id == TransformPropertyId) {
        return QVariant::fromValue(transform());
    }
    return BaseObject::propertyValue(id);
}

void GraphicsObject::setProperty(const Property &property)
{
    if (property.id == NamePropertyId) {
        if (property.value.canConvert<QString>()) {
            QString nm = property.value.toString();
            qDebug() << "graphics object set property, set name" << nm;
            setName(nm);
        }
    } else if (property.id == SelectedPropertyId) {
        if (property.value.canConvert<bool>()) {
            bool selected = property.value.toBool();
            qDebug() << "graphics object set property, set selected" << selected;
            setSelected(selected);
        }
    } else if (property.id == PositionPropertyId) {
        if (property.value.canConvert<QPointF>()) {
            QPointF pos = property.value.toPointF();
            qDebug() << "graphics object set property, set position" << pos;
            setPosition(pos);
        }
    } else if (property.id == SizePropertyId) {
        if (property.value.canConvert<QSizeF>()) {
            QSizeF size = property.value.toSizeF();
            qDebug() << "graphics object set property, set size" << size;
            setSize(size);
        }
    } else if (property.id == TransformPropertyId) {
        if (property.value.canConvert<QTransform>()) {
            QTransform transform = property.value.value<QTransform>();
            qDebug() << "graphics object set property, set transfor";
            setTransform(transform);
        }
    } else {
        BaseObject::setProperty(property);
    }
}

Properties GraphicsObject::properties() const
{
    Properties properties = BaseObject::properties();
    properties.append(Property(NamePropertyId, name()));
    properties.append(Property(SelectedPropertyId, isSelected()));
    properties.append(Property(PositionPropertyId, position()));
    properties.append(Property(SizePropertyId, size()));
    properties.append(Property(TransformPropertyId, size()));
    return properties;
}

void GraphicsObject::onSceneEvent(SceneEvent *event)
{
    Q_UNUSED(event)
}

QSizeF GraphicsObject::initialSize()
{
    return QSizeF(200.0, 200.0);
}

void GraphicsObject::updateSize()
{
    _size = _transform.mapRect(QRectF(QPointF(0, 0), initialSize())).size();
}

QRectF GraphicsObject::boundingRect() const
{
    return QRectF(_position, _size);
}

QPointF GraphicsObject::position() const
{
    return _position;
}

void GraphicsObject::setPosition(const QPointF &pos)
{
    if (!floatCompare(_position, pos)) {
        _position = pos;
    }
}

QSizeF GraphicsObject::size() const
{
    return _size;
}

void GraphicsObject::setSize(const QSizeF &size)
{
    if (!floatCompare(_size, size)) {
        qreal scaleX = size.width() / _size.width();
        qreal scaleY = size.height() / _size.height();
        _size = size;
        _transform.scale(scaleX, scaleY);
    }
}

int GraphicsObject::graphicsId() const
{
    return _graphicsId;
}

bool GraphicsObject::isSelected() const
{
    return _selected;
}

void GraphicsObject::setSelected(bool on)
{
    if (_selected != on) {
        _selected = on;
    }
}

const QTransform &GraphicsObject::transform() const
{
    return _transform;
}

void GraphicsObject::setTransform(const QTransform &transform)
{
    _transform = transform;
    updateSize();
}

Scene *GraphicsObject::scene()
{
    return _p_scene;
}

void GraphicsObject::setScene(Scene *scene)
{
    if (scene) {
        _p_scene = scene;
    }
}

QString GraphicsObject::name() const
{
    return _name;
}

void GraphicsObject::setName(const QString &name)
{
    if (_name != name) {
        _name = name;
    }
}
