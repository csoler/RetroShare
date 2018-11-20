/*******************************************************************************
 * retroshare-gui/src/gui/gxs/GxsIdTreeWidgetItem.h                            *
 *                                                                             *
 * Copyright 2012-2013 by Robert Fernie     <retroshare.project@gmail.com>     *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#ifndef _GXS_ID_TREEWIDGETITEM_H
#define _GXS_ID_TREEWIDGETITEM_H

#include <retroshare/rsidentity.h>

#include "gui/common/RSTreeWidgetItem.h"
#include "gui/gxs/GxsIdDetails.h"

/*****
 * NOTE: When the tree item is created within a thread you have to move the object
 * with "moveThreadTo()" QObject into the main thread.
 * The tick signal to fill the id cannot be processed when the thread is finished.
 ***/

class GxsIdRSTreeWidgetItem : public QObject, public RSTreeWidgetItem
{
	Q_OBJECT

public:
    GxsIdRSTreeWidgetItem(const RSTreeWidgetItemCompareRole *compareRole, uint32_t icon_mask,QTreeWidget *parent = NULL);

	void setId(const RsGxsId &id, int column, bool retryWhenFailed);
	bool getId(RsGxsId &id);

	int idColumn() const { return mColumn; }
    void processResult(bool success);
    uint32_t iconTypeMask() const { return mIconTypeMask ;}

	void setAvatar(const RsGxsImage &avatar);
	virtual QVariant data(int column, int role) const;
	void forceUpdate();
    
    	void setBannedState(bool b) { mBannedState = b; }	// does not actually change the state, but used instead by callbacks to leave a trace
    	void updateBannedState() ;				// checks reputation, and update is needed

private slots:
	void startProcess();

private:
	void init();

	RsGxsId mId;
	int mColumn;
	bool mIdFound;
    	bool mBannedState ;
	bool mRetryWhenFailed;
    RsReputations::ReputationLevel mReputationLevel ;
	uint32_t mIconTypeMask;
	RsGxsImage mAvatar;
};

#endif
