#include "notatnik.h"
#include "ui_notatnik.h"
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include <QInputDialog>

Notatnik::Notatnik(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notatnik)
{
    ui->setupUi(this);
    //connect(ui->actionSave, &QAction::triggered, this, &Notatnik::saveFile);
}

Notatnik::~Notatnik()
{
    delete ui;
}

void Notatnik::on_actionNowy_triggered()
{
    QString fileName;
    QMessageBox message;
    message.setText("Czy zapisać plik?");
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Yes);
    int rep = message.exec();

    if(rep == QMessageBox::Yes)
    {
        //save file
        QString fileName;
        //QFile file;
        if(!biezacyPlik.isEmpty())
        {
            fileName = QFileDialog::getOpenFileName(this, "Zapisz plik...");
            biezacyPlik = fileName;
        }
        else {
            fileName = biezacyPlik;
        }

        QFile file(fileName);

        if(file.open(QIODevice::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"warning","Nie mozna zapisać pliku..." + file.errorString());
        }
        setWindowTitle(fileName);
        QTextStream str(&file);
        QString tekst = ui->textEdit->toPlainText();
        str << tekst;
        file.close();
    }
    else if(rep==QMessageBox::No){
        ui->textEdit->clear();
    }
    else if(rep==QMessageBox::Cancel)
        return;

}

void Notatnik::on_actionOtworz_triggered()
{
        //open .txt files
    QString fileName = QFileDialog::getOpenFileName(this,"Otwórz plik...");
    QFile file(fileName);   //utworz plik o nazwie fileName
    biezacyPlik = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","Nie można otworzyć pliku!" + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString tekst = in.readAll();       //pobierz tekst
    ui->textEdit->setText(tekst);   //wczytaj do pola tekstowego
    file.close();   //zamknij plik
}

void Notatnik::on_actionSave_triggered()
{
    QString fileName;
    //utworzenie nowego pliku

    if(biezacyPlik.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Zapisz plik...");
        biezacyPlik = fileName;
    }
    else {
        fileName = biezacyPlik;
    }
    QFile file(fileName);       //utworz plik o nazwie fileName

    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "warning", "Nie można zapisać pliku!" + file.errorString());      //spróbuj zapisać albo wywal error
        return;
    }
    setWindowTitle(fileName);
    //text stream i zapis do pliku
    QTextStream out(&file);
    QString tekst = ui->textEdit->toPlainText();
    out << tekst; //pobierz do "wyjścia" tekst z TextEditor'a
    file.close(); //zamknij plik
}

void Notatnik::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz plik jako...");
    QFile file(fileName); //stwórz plik

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","Nie można zapisać pliku!" + file.errorString());
        return;
    }
    //pobieranie tekstu do wyjscia
    biezacyPlik = fileName;
    QString tekst;
    QTextStream out(&file);
    tekst = ui->textEdit->toPlainText();
    out << tekst;
    //zamykanie
    file.close();
}

void Notatnik::on_actionQuit_triggered()
{
    close();
}

void Notatnik::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);

     if(printDialog.exec()==QDialog::Rejected)
         return;

     ui->textEdit->print(&printer);
}

void Notatnik::on_actionCopy_triggered()
{
    ui->textEdit->copy();       //kopiuj
}

void Notatnik::on_actionCut_triggered()
{
    ui->textEdit->cut();    //wytnij
}

void Notatnik::on_actionUndo_triggered()
{
    ui->textEdit->undo();       //cofnij
}

void Notatnik::on_actionPaste_triggered()
{
    ui->textEdit->paste();      //wklej
}

void Notatnik::on_actionRemove_triggered()
{
    ui->textEdit->clear();       //usun
}

void Notatnik::on_actionSetFont_triggered()
{
    bool fontSelect;
    QFont font = QFontDialog::getFont(&fontSelect,this);    //pobierz czcionke z dialogu
    if(fontSelect)  //jeśli wybrano to taka ustaw w txtEditor
        ui->textEdit->setFont(font);
}

void Notatnik::on_actionWrap_triggered()
{
    bool wprapped;
   // ui->textEdit->setLineWrapMode(QTextEdit::WordWrap);
}

void Notatnik::on_actionSelectAllText_triggered()
{
    ui->textEdit->selectAll();  //zaznacz wszystko
}

void Notatnik::on_actionFind_triggered()
{
    QString findword = QInputDialog::getText(this,"Znajdź","Znajdź słowo...");
    QString tekst_biezacy = ui->textEdit->toPlainText();
    QList<QString> tekst;
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();
    int len = ui->textEdit->toPlainText().length();

    for (int i=0;i<len;++i) {
        QString biezacy = ui->textEdit->toPlainText().at(i);
        tekst.append(biezacy);

    }
    for(int i=0; i<len; ++i)
    {
        if(tekst.at(i) == findword){
            tekst.at(i).isUpper();
        }
        else
           return;
    }
}
