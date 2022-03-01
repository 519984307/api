#include "ocrapi.h"





QString getOcrText(QPixmap& pix)
{
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    api->Init(nullptr, "chi_sim");
    api->Clear();
    QImage img = pix.toImage();
    uchar* data = img.bits();

    api->SetImage(data, img.width(), img.height(), 3, img.bytesPerLine());
    api->SetSourceResolution(96);
    QString ret = api->GetUTF8Text();
    api->End();
    delete api;
    return ret;
}

QString getOcrText(tesseract::TessBaseAPI* api, QPixmap& pix)
{


    api->Clear();
    QImage img = pix.toImage();

    uchar* data = img.bits();

    api->SetImage(data, img.width(), img.height(), 3, img.bytesPerLine());
    api->SetSourceResolution(96);
    std::string str;
    char* s = api->GetUTF8Text();
    str = s;
    //
    delete [] s;


    QString ret = QString::fromStdString(str);
    // qDebug() << QString::fromStdString(str);
    return ret;
}
