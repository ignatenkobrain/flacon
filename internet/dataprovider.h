/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Flacon - audio File Encoder
 * https://github.com/flacon/flacon
 *
 * Copyright: 2012-2013
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <QList>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "../tagset.h"

class Disk;
class QNetworkAccessManager;


class DataProvider : public QObject
{
    Q_OBJECT
public:
    explicit DataProvider(Disk *disk);
    virtual ~DataProvider();

    Disk *disk() const { return mDisk; }

    bool isFinished() const;

public slots:
    virtual void start() = 0;
    virtual void stop();


signals:
    void finished();

protected:
    void get(const QNetworkRequest &request);
    void error(const QString &message);
    virtual void dataReady(QNetworkReply *reply) = 0;

private slots:
    void replayFinished();

private:
    QNetworkAccessManager *networkAccessManager() const;
    Disk *mDisk;
    QList<QNetworkReply*> mReplies;

    void addReply(QNetworkReply* reply);
};


class FreeDbProvider: public DataProvider
{
public:
    explicit FreeDbProvider(Disk *disk);

    void start();
protected:
    void dataReady(QNetworkReply *reply);

private:
    void parse(QNetworkReply *reply);
    QList<TagSet> mResult;
};

#endif // DATAPROVIDER_H
