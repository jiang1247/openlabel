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

#include "graphicspropertybrowser.h"
#include "openlabel/modifygraphicsoperation.h"
#include "mainwindow.h"

using namespace Gui;

GraphicsPropertyBrowser::GraphicsPropertyBrowser(QWidget *parent)
    : QDockWidget(parent)
    , _p_scene(nullptr)
{
    _p_propertyBrowser = new QtTreePropertyBrowser(this);
    setWidget(_p_propertyBrowser);

    QtVariantPropertyManager *variantManager = new QtVariantPropertyManager(this);
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    _p_propertyBrowser->setFactoryForManager(variantManager, variantFactory);

    connect(variantManager, &QtVariantPropertyManager::valueChanged, this,
            [=](QtProperty *property, const QVariant &value) {
                this->updateProperty(property, value);
            });

    // Add properties here, for example:
    addProperty(variantManager->addProperty(QVariant::String, "Name"), "Name");
    addProperty(variantManager->addProperty(QVariant::PointF, "Position"), "Position");
    addProperty(variantManager->addProperty(QVariant::SizeF, "Size"), "Size");
}

void GraphicsPropertyBrowser::setObjects(const QList<int> &graphicsObjectIds)
{
    _currentGraphicsIds = graphicsObjectIds;
    updateProperties();
}

void GraphicsPropertyBrowser::updateProperty(QtProperty *property, const QVariant &value)
{
    if (_currentGraphicsIds.isEmpty())
        return;
    const QString id = _idToProperty.value(property, QString());
    if (id.isEmpty())
        return;

    updateProperty(id, value);
}

void GraphicsPropertyBrowser::updateProperty(const QString &propertyName, const QVariant &value)
{
    if (_currentGraphicsIds.isEmpty())
        return;

    int propertyId = OpenLabel::PropertyIdDispatcher::instance().propertyId(propertyName);
    if (propertyId == 0)
        return;

    OpenLabel::Properties properties;
    properties.append(OpenLabel::Property(propertyId, value));

    auto operation =
        new OpenLabel::ModifyGraphicsOperation(_currentGraphicsIds.first(), properties, _p_scene);
    _p_scene->pushOperation(operation);
}

void GraphicsPropertyBrowser::addProperty(QtVariantProperty *property, const QString &id)
{
    _propertyToId[id] = property;
    _idToProperty[property] = id;
    _p_propertyBrowser->addProperty(property);
}

void GraphicsPropertyBrowser::updateProperties()
{
    if (_currentGraphicsIds.isEmpty()) {
        _propertyToId["Position"]->setValue(QPointF());
        _propertyToId["Size"]->setValue(QSizeF());
        return;
    }

    QRectF boundingRect;
    bool first = true;

    for (int id : _currentGraphicsIds) {
        auto graphicsObject = _p_scene->findGraphicsById(id);
        if (!graphicsObject)
            continue;

        if (first) {
            boundingRect = graphicsObject->boundingRect();
            first = false;
        } else {
            boundingRect |= graphicsObject->boundingRect();
        }
    }

    _propertyToId["Position"]->setValue(boundingRect.topLeft());
    _propertyToId["Size"]->setValue(boundingRect.size());
}

void GraphicsPropertyBrowser::registerScene(OpenLabel::Scene *scene)
{
    if (scene) {
        _p_scene = scene;
        scene->addSceneEventListener(this);
    }
}

void GraphicsPropertyBrowser::unregisterScene()
{
    if (_p_scene) {
        _p_scene->removeSceneEventListener(this);
        _p_scene = nullptr;
    }
}

void GraphicsPropertyBrowser::showEvent(QShowEvent *event)
{
    this->adjustSize();

    QPoint pos(MainWindow::window().centralWidget()->size().width(), 0);
    pos = MainWindow::window().centralWidget()->mapToGlobal(pos);
    int x = pos.x() - this->width() - 20;
    int y = pos.y() + 1;
    this->move(x, y);

    QDockWidget::showEvent(event);
}

void GraphicsPropertyBrowser::onSceneEvent(OpenLabel::SceneEvent *event)
{
    if (!_p_scene) {
        return;
    }
    setObjects(_p_scene->selectedGraphicsIds());
    if (_p_scene->hasSelected()) {
        show();
    } else {
        hide();
    }
}
