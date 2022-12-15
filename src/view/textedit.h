#ifndef MTEXTEDIT_H
#define MTEXTEDIT_H

#include <QTextEdit>

class MTextEdit : public QTextEdit {
    Q_OBJECT
    public:
        MTextEdit() : QTextEdit() {
            // setUndoRedoEnabled(false);
        }
        MTextEdit(QWidget*&qw) : QTextEdit(qw) {}
        // ~MTextEdit() = default;
    private:
        void keyPressEvent(QKeyEvent *event);
    signals:
        void enterP();
};

#endif
