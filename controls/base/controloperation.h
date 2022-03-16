#ifndef CONTROLOPERATION_H
#define CONTROLOPERATION_H

#include <QObject>
enum ControlOperation
{
    //添加对象
    OP_ADD_OBJECT,
    //正在添加对象
    OP_ADDING_OBJECT,
    OP_SELECT,
    OP_DELETE_OBJECT,
    OP_PASTE_SELECT_OBJECTS,
    OP_SET_CENTER_POINT,
    OP_SET_ORIGIN_POINT,
    ///没有任何操作
    OP_NONE
};

#endif // CONTROLOPERATION_H
