/***************************************************************************
                         qgscomposeritemgroup.h
                         ----------------------
    begin                : 2nd June 2008
    copyright            : (C) 2008 by Marco Hugentobler
    email                : marco dot hugentobler at karto dot baug dot ethz dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSCOMPOSERITEMGROUP_H
#define QGSCOMPOSERITEMGROUP_H

#include "qgis_core.h"
#include "qgscomposeritem.h"
#include <QSet>

/** \ingroup core
 * A container for grouping several QgsComposerItems
 */
class CORE_EXPORT QgsComposerItemGroup: public QgsComposerItem
{
    Q_OBJECT
  public:
    QgsComposerItemGroup( QgsComposition *c );
    ~QgsComposerItemGroup();

    //! Return correct graphics item type.
    virtual int type() const override { return ComposerItemGroup; }

    /** Adds an item to the group. All the group members are deleted
     if the group is deleted*/
    void addItem( QgsComposerItem *item ) override;
    //! Removes the items but does not delete them
    void removeItems() override;
    //! Draw stroke and ev. selection handles
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr ) override;

    /** Sets this items bound in scene coordinates such that 1 item size units
       corresponds to 1 scene size unit*/
    void setSceneRect( const QRectF &rectangle ) override;

    //overridden to also hide grouped items
    virtual void setVisibility( const bool visible ) override;

    /** Stores state in Dom node
       * @param elem is Dom element corresponding to 'Composer' tag
       * @param doc is the Dom document
       */
    bool writeXml( QDomElement &elem, QDomDocument &doc ) const override;

    /** Sets state from Dom document
       * @param itemElem is Dom node corresponding to item tag
       * @param doc is the Dom document
       */
    bool readXml( const QDomElement &itemElem, const QDomDocument &doc ) override;

    QSet<QgsComposerItem *> items() { return mItems; }

  signals:
    void childItemDeleted( QgsComposerItem *item );

  public slots:
    void itemDestroyed();

  protected:
    void drawFrame( QPainter *p ) override;

  private:
    QSet<QgsComposerItem *> mItems;
    QRectF mBoundingRectangle;
};

#endif
