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
#ifndef TESTIMAGEPROVIDER_H
#define TESTIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>

class AsyncUrlImageResponse : public QQuickImageResponse
{
public:
    AsyncUrlImageResponse(const QColor &color, const QSize & requestedSize);
    QQuickTextureFactory * textureFactory() const override;

private:
    QImage _image;
};

class TestImageProvider : public QQuickAsyncImageProvider
{
public:
    TestImageProvider() = default;
    QQuickImageResponse * requestImageResponse(const QString & requestData, const QSize & requestedSize) override;
};

#endif // TESTIMAGEPROVIDER_H
