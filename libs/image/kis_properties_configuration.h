/*
 *  Copyright (c) 2006 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef _KIS_PROPERTIES_CONFIGURATION_H_
#define _KIS_PROPERTIES_CONFIGURATION_H_

#include <QString>
#include <QMap>
#include <QVariant>
#include <kis_debug.h>
#include <kis_cubic_curve.h>
#include <KoColor.h>

class QDomElement;
class QDomDocument;

#include "kis_serializable_configuration.h"
#include "kritaimage_export.h"
#include "kis_types.h"


/**
 * KisPropertiesConfiguration is a map-based properties class that can
 * be serialized and deserialized.
 *
 * It differs from the base class KisSerializableConfiguration in that
 * it provides a number of convenience methods to get at the data and
 */
class KRITAIMAGE_EXPORT KisPropertiesConfiguration : public KisSerializableConfiguration
{

public:

    /**
     * Create a new properties  config.
     */
    KisPropertiesConfiguration();
    virtual ~KisPropertiesConfiguration();

    /**
     * Deep copy the properties  configFile
     */
    KisPropertiesConfiguration(const KisPropertiesConfiguration& rhs);

public:


    /**
     * Fill the properties  configuration object from the XML encoded representation in s.
     * This function use the "Legacy" style XML of the 1.x .kra file format.
     * @param xml the string that will be parsed as xml
     * @param clear if true, the properties map will be emptied.
     * @return true is the xml document could be parsed
     */
    virtual bool fromXML(const QString& xml, bool clear = true);

    /**
     * Fill the properties  configuration object from the XML encoded representation in s.
     * This function use the "Legacy" style XML  of the 1.x .kra file format.
     *
     * Note: the existing properties will not be cleared
     */
    virtual void fromXML(const QDomElement&);

    /**
     * Create a serialized version of this properties  config
     * This function use the "Legacy" style XML  of the 1.x .kra file format.
     */
    virtual void toXML(QDomDocument&, QDomElement&) const;

    /**
     * Create a serialized version of this properties  config
     * This function use the "Legacy" style XML  of the 1.x .kra file format.
     */
    virtual QString toXML() const;

    /**
     * @return true if the map contains a property with the specified name
     */
    bool hasProperty(const QString& name) const;

    /**
     * Set the property with name to value.
     */
    virtual void setProperty(const QString & name, const QVariant & value);

    /**
     * Set value to the value associated with property name
     *
     * XXX: API alert: a setter that is prefixed with get?
     *
     * @return false if the specified property did not exist.
     */
    virtual bool getProperty(const QString & name, QVariant & value) const;

    virtual QVariant getProperty(const QString & name) const;

    template <typename T>
        T getPropertyLazy(const QString & name, const T &defaultValue) const {
        QVariant value = getProperty(name);
        return value.isValid() ? value.value<T>() : defaultValue;
    }

    int getInt(const QString & name, int def = 0) const;

    double getDouble(const QString & name, double def = 0.0) const;

    float getFloat(const QString& name, float def = 0.0) const;

    bool getBool(const QString & name, bool def = false) const;

    QString getString(const QString & name, const QString & def = QString()) const;

    KisCubicCurve getCubicCurve(const QString & name, const KisCubicCurve & curve = KisCubicCurve()) const;

    KoColor getColor(const QString& name, const KoColor& color = KoColor()) const;

    QMap<QString, QVariant> getProperties() const;

    /// Clear the map of properties
    void clearProperties();

    ///Marks a property that should not be saved by toXML
    void setPropertyNotSaved(const QString & name);

    void removeProperty(const QString & name);

public:

    void dump() const;

private:

    struct Private;
    Private* const d;
};

class KRITAIMAGE_EXPORT KisPropertiesConfigurationFactory : public KisSerializableConfigurationFactory
{
public:
    KisPropertiesConfigurationFactory();
    virtual ~KisPropertiesConfigurationFactory();
    virtual KisSerializableConfigurationSP createDefault();
    virtual KisSerializableConfigurationSP create(const QDomElement& e);
private:
    struct Private;
    Private* const d;
};

#endif
