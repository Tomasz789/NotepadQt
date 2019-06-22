#ifndef NOTATNIK_H
#define NOTATNIK_H

#include <QMainWindow>

namespace Ui {
class Notatnik;
}

class Notatnik : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notatnik(QWidget *parent = nullptr);
    ~Notatnik();

private slots:
    //void openFile();

    void on_actionNowy_triggered();

    void on_actionOtworz_triggered();



    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionQuit_triggered();

    void on_actionPrint_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionPaste_triggered();

    void on_actionRemove_triggered();

    void on_actionSetFont_triggered();

    void on_actionWrap_triggered();

    void on_actionSelectAllText_triggered();

    void on_actionFind_triggered();

private:
    Ui::Notatnik *ui;
    QString biezacyPlik;
};

#endif // NOTATNIK_H
