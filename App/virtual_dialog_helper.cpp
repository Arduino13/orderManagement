#include "virtual_dialog_helper.h"

virtual_dialog_helper::virtual_dialog_helper(QWidget *parent) : QMainWindow(parent)
{

}

void virtual_dialog_helper::onClose_support(){
    onClose(this);
}

virtual_dialog_helper::~virtual_dialog_helper(){

}
