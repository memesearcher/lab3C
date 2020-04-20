#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   ui->setupUi(this);
    ui->displayPanel->clear();
    operatorClicked = false;
    hasStoredNumber = false;
    ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(numberGroup_clicked(QAbstractButton*)));
        ui->actionGroup->connect(ui->actionGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(actionGroup_clicked(QAbstractButton*)));
    this->setFixedSize(QSize(300, 320));
}
MainWindow::~MainWindow()
{delete ui;}
// Регистрация нажатия цифр
void MainWindow::numberGroup_clicked(QAbstractButton* button)
{
    QString displayLabel = ui->displayPanel->text();
    if (operatorClicked) {
        displayLabel.clear();
        operatorClicked = false;
    }
    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }
    //Объединение строк и знака
    displayLabel.append(button->text());
    //Вывод объединенных строк
    ui->displayPanel->setText(displayLabel);
}
// Регистрация нажатия операций
void MainWindow::actionGroup_clicked(QAbstractButton* button)
{
    if (operatorClicked) {
        storedOperator = button->text().at(0);
    }
    else {
        if (hasStoredNumber) {
            calculate_result();
        }
        else {
            hasStoredNumber = true;
            //Get string from display
            QString displayLabel = ui->displayPanel->text();
            //Convert string to double and save
            storedNumber = displayLabel.toDouble();
        }
        //Флаг, что был нажата операция
        operatorClicked = true;
        //Запоминание оператора
        storedOperator = button->text().at(0);
    }
}

void MainWindow::on_actionDel_clicked()
{
    QString displayLabel = ui->displayPanel->text();
    //Проверка на пустоту
    if (displayLabel.length() == 0) {
        return;
    }
    //Удаление последней цифры
    displayLabel.QString::chop(1);
    //Возврат обновленного значения числа
    ui->displayPanel->setText(displayLabel);
}
//Нажатие =
void MainWindow::on_actionCalc_clicked()
{
    QString displayLabel = ui->displayPanel->text();

    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        return;
    }
    //Вычисление и вывод
    calculate_result();
    hasStoredNumber = false;
}
//Знак запятой
void MainWindow::on_comma_clicked()
{
    QString displayLabel = ui->displayPanel->text();
    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }
    //Если на экране пусто, добавить 0, а потом запятую
    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }
    //Объединение числа и нуля
    displayLabel.append('.');
    ui->displayPanel->setText(displayLabel);
}
void MainWindow::on_actionClear_clicked()
{
    //Очистка экрана
    ui->displayPanel->clear();
    operatorClicked = false;
    hasStoredNumber = false;
}
void MainWindow::on_actionPercent_clicked()
{
    QString displayLabel = ui->displayPanel->text();
    double percentage = displayLabel.toDouble();
    percentage *= 0.01;
    //Тут возможно переполнение
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    ui->displayPanel->setText(displayLabel);
}
void MainWindow::on_actionSign_clicked()
//изменение знака числа
    QString displayLabel = ui->displayPanel->text();
    double percentage = displayLabel.toDouble();
    percentage *= -1;
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    ui->displayPanel->setText(displayLabel);
}
void MainWindow::calculate_result() {
    //Вычисление результата
    QString displayLabel = ui->displayPanel->text();
    //откидываем запятую, если число на нее заканчивается
     if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
         displayLabel.QString::chop(1);
     }
     if (storedOperator == '+') {
         storedNumber += displayLabel.toDouble();
     }
     else if (storedOperator == '-') {
         storedNumber -= displayLabel.toDouble();
     }
     else if (storedOperator == 'x') {
         storedNumber *= displayLabel.toDouble();
     }
     else if (storedOperator == '/') {
         storedNumber /= displayLabel.toDouble();
     }
     //Переполнение 
     displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);
     ui->displayPanel->setText(displayLabel);
}
//Регистрация нажатий клавиш
void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        //Numbers
        case Qt::Key_1:
            numberGroup_clicked(ui->num1);
            break;
        case Qt::Key_2:
            numberGroup_clicked(ui->num2);
            break;
        case Qt::Key_3:
            numberGroup_clicked(ui->num3);
            break;
        case Qt::Key_4:
            numberGroup_clicked(ui->num4);
            break;
        case Qt::Key_5:
            numberGroup_clicked(ui->num5);
            break;
        case Qt::Key_6:
            numberGroup_clicked(ui->num6);
            break;
        case Qt::Key_7:
            numberGroup_clicked(ui->num7);
            break;
        case Qt::Key_8:
            numberGroup_clicked(ui->num8);
            break;
        case Qt::Key_9:
            numberGroup_clicked(ui->num9);
            break;
        case Qt::Key_0:
            numberGroup_clicked(ui->num0);
            break;
        case Qt::Key_Plus:
            actionGroup_clicked(ui->actionPlus);
            break;
        case Qt::Key_Minus:
            actionGroup_clicked(ui->actionMinus);
            break;
        case Qt::Key_Asterisk:
            actionGroup_clicked(ui->actionMul);
            break;
        case Qt::Key_Slash:
            actionGroup_clicked(ui->actionDiv);
            break;
        //запятая
        case Qt::Key_Period:
            on_comma_clicked();
            break;
        //Энтер
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_actionCalc_clicked();
            break;
        //Backspace и delete
        case Qt::Key_Backspace:
            on_actionDel_clicked();
            break;
        case Qt::Key_Delete:
            on_actionClear_clicked();
            break;
        //Проценты
        case Qt::Key_Percent:
            on_actionPercent_clicked();
            break;
    }
}