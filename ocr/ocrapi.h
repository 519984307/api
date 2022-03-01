#ifndef OCRAPI_H
#define OCRAPI_H

#include <QObject>
#include <QWidget>

#include <QThread>
#include <QScreen>
#include <QPixmap>
#include <QApplication>
#include "tesseract/baseapi.h"

QString getOcrText(QPixmap& pix);

QString getOcrText(tesseract::TessBaseAPI* api, QPixmap& pix);
#endif // OCRAPI_H
