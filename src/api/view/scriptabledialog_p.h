#pragma once

#include "dialog.h"
#include <QDialog>
#include <QDialogButtonBox>

namespace api {
namespace view {
class Column;

class Dialog::ScriptableDialog : public QDialog {
    Q_OBJECT
    friend class Dialog;

   public:
    explicit ScriptableDialog(QWidget* parent = 0) : QDialog(parent) {}
    ~ScriptableDialog() {}

   private:
    Column* _col;
    QDialogButtonBox* _btnBox;
};

}  // namespace view
}  // namespace api