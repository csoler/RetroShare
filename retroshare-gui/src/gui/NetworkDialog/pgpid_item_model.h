#ifndef KEY_ITEM_MODEL_H
#define KEY_ITEM_MODEL_H

#include <QAbstractItemModel>
#include <retroshare/rspeers.h>
#include <QColor>

#define IMAGE_AUTHED         ":/images/accepted16.png"
#define IMAGE_DENIED         ":/images/denied16.png"
#define IMAGE_TRUSTED        ":/images/rs-2.png"


#define COLUMN_CHECK 0
#define COLUMN_PEERNAME    1
#define COLUMN_I_AUTH_PEER 2
#define COLUMN_PEER_AUTH_ME 3
#define COLUMN_PEERID      4
#define COLUMN_LAST_USED   5
#define COLUMN_COUNT 6

struct bg_colors {
    bg_colors (QColor _mBackgroundColorSelf, QColor _mBackgroundColorOwnSign, QColor _mBackgroundColorAcceptConnection,
               QColor _mBackgroundColorHasSignedMe, QColor _mBackgroundColorDenied) :
        mBackgroundColorSelf(_mBackgroundColorSelf), mBackgroundColorOwnSign(_mBackgroundColorOwnSign), mBackgroundColorAcceptConnection(_mBackgroundColorAcceptConnection),
        mBackgroundColorHasSignedMe(_mBackgroundColorHasSignedMe), mBackgroundColorDenied(_mBackgroundColorDenied)
    {}
    QColor &mBackgroundColorSelf;
    QColor &mBackgroundColorOwnSign;
    QColor &mBackgroundColorAcceptConnection;
    QColor &mBackgroundColorHasSignedMe;
    QColor &mBackgroundColorDenied;
};


class pgpid_item_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit pgpid_item_model(std::list<RsPgpId> &neighs, float &font_height, bg_colors &__bg_colors, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void data_updated(std::list<RsPgpId> &new_neighs);

private:
    std::list<RsPgpId> &neighs;
    float &font_height;
    bg_colors _bg_colors;
};

#endif // KEY_ITEM_MODEL_H
