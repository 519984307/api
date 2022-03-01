#ifndef LUNAR_H
#define LUNAR_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <QString>



extern int LunarCalendarX(int, int, int, int&, int&, int&);
extern QString GetLunarStringX(int, int, int, int&, int&, int&);
QString getLunarDay(int y, int m, int d);
#endif // LUNAR_H
