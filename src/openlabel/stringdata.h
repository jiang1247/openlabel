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

#include "datasource.h"

namespace OpenLabel {

class StringData : public DataSource
{
    static const PropertyId StringPropertyId;

  public:
    explicit StringData(int id, Scene *scene = nullptr);
    virtual ~StringData() = default;

    QSharedPointer<DataSource> clone() const override;

    virtual QVariant propertyValue(int id) const override;
    virtual void setProperty(const Property &property) override;
    virtual Properties properties() const override;

    virtual int dataSourceType() const override;
    virtual QString dataSourceName() const override;

    virtual QVariant data() const override;

    QString string() const;
    void setString(const QString &string);

  private:
    QString _string;
};

}
