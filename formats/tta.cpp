/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Flacon - audio File Encoder
 * https://github.com/flacon/flacon
 *
 * Copyright: 2017
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


#include "tta.h"
#include <QDebug>

REGISTER_FORMAT(Format_Tta)


/************************************************
 *
 ************************************************/
QStringList Format_Tta::decoderArgs(const QString &fileName) const
{
    QStringList args;
    args << "-d";
    args << fileName;
    args << "-o" << "-";

    return args;
}


/************************************************
 *
 ************************************************/
QString Format_Tta::filterDecoderStderr(const QString &stdErr) const
{

    int pos = stdErr.indexOf("Error:");
    if (pos>-1)
        return stdErr.mid(pos + 6).trimmed();

    return "";
}
