/*
 * Copyright (c) 2001-2024 Territorium Online Srl / TOL GmbH. All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code as defined in and that are
 * subject to the Territorium Online License Version 1.0. You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at http://www.tol.info/license/
 * and read it before using this file.
 *
 * The Original Code and all software distributed under the License are distributed on an 'AS IS'
 * basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND TERRITORIUM ONLINE HEREBY
 * DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see the License for
 * the specific language governing rights and limitations under the License.
 */
#include "testimageprovider.h"

#include <QTimer>

QQuickImageResponse * TestImageProvider::requestImageResponse(const QString & requestData, const QSize & requestedSize)
{
    return new AsyncUrlImageResponse(QColor(requestData), requestedSize);
}

AsyncUrlImageResponse::AsyncUrlImageResponse(const QColor & color, const QSize & requestedSize)
{
    QTimer::singleShot(500, this, [this, color, requestedSize] {
        _image = QImage(requestedSize, QImage::Format_RGB32);
        _image.fill(color);
        emit finished();
    });
}

QQuickTextureFactory * AsyncUrlImageResponse::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(_image);
}
