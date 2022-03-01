#ifndef WORDDEEPENPROCOPERATOR_H
#define WORDDEEPENPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class WordDeepenProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit WordDeepenProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
    void getDeepenColor(int& r, int& g, int& b);
signals:

};

#endif // WORDDEEPENPROCOPERATOR_H
