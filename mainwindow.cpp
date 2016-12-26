#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bonus.h"
#include <QtGui>
#include "QMessageBox"
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(848,736);          // Задаем размеры окна
    this->setFixedSize(848,736);    // Фиксируем размеры виджета

    scene = new QGraphicsScene();   // Инициализируем графическую сцену
    hero = new Hero();              // Инициализируем треугольник

    ui->graphicsView->setScene(scene);                          // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scene->setSceneRect(-400,-300,800,600); /// Устанавливаем область графической сцены

    scene->addItem(hero);   // Добавляем на сцену треугольник
    hero->setPos(0,0);      // Устанавливаем треугольник в центр сцены


    timer = new QTimer();
    timer2 = new QTimer();
    connect(timer, &QTimer::timeout, hero, &Hero::slotGameTimer);
    connect(timer2, &QTimer::timeout, this, &MainWindow::slotEndSpeedup);
    timer->start(20);
    /* Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у Треугольника 20 раз в секунду.
     * Управляя скоростью отсчётов управляем скоростью
     * изменения состояния графической сцены
    * */

    timerCreateBonus = new QTimer();
    connect(timerCreateBonus, &QTimer::timeout, this, &MainWindow::slotCreateBonus);
    timerCreateBonus->start(6000);

    connect(hero, &Hero::signalCheckItem, this, &MainWindow::slotDeleteBonus);
    connect(hero, &Hero::signalRefreshHp, this, &MainWindow::slotRefreshHp);
    connect(hero, &Hero::signalRefreshLvl, this, &MainWindow::slotRefreshLvl);
    connect(hero, &Hero::signalRefreshXp, this, &MainWindow::slotRefreshXp);
    connect(hero, &Hero::signalEndGame, this, &MainWindow::slotEndGame);
    connect(this, &MainWindow::signalHPChanged, hero, &Hero::slotHPChanged);
    connect(this, &MainWindow::signalXPChanged, hero, &Hero::slotXPChanged);
    connect(this, &MainWindow::signalNickChanged, hero, &Hero::slotNickChanged);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("\test.db");
    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
    QSqlQuery *query = new QSqlQuery("CREATE TABLE results nick TEXT lvl INTEGER)", db);

    db.close();
    delete query;
}

void MainWindow::slotRefreshXp(int xp)
{
    ui->LevelProgress->setValue(xp);
}
void MainWindow::slotRefreshLvl(int lvl)
{
    ui->LevelProgress->setMaximum(lvl * 100);
    ui->LevelProgress->setValue(0);
    ui->LvCountL->setText(QString::number(lvl));
}
void MainWindow::slotRefreshHp(int hp)
{
    ui->HpCountL->setText(QString::number(hp));
}

void MainWindow::slotEndGame()
{
    QMessageBox msgBox(QMessageBox::Warning,
                       QString::fromUtf8("Конец игры"),
                       QString::fromUtf8("Вы умерли"),
                       0, this);
    msgBox.addButton(QString::fromUtf8("&Выход"),
                     QMessageBox::AcceptRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        exit(0);

}

void MainWindow::slotEndSpeedup()
{
    timer2->stop();
    timer->start(20);
}

void MainWindow::slotDeleteBonus(QGraphicsItem *item)
{
    foreach (Bonus *currentBonus, bonuses)
    {
        if((currentBonus->x() == item->x())&&(currentBonus->y() == item->y()))
        {
            // нашли нужный бонус в списке всех бонусов (покоординатно)
            int currentHp = ui->HpCountL->text().toInt(); // текущее хп
            int tmp;
            switch (currentBonus->getType())
            {
            case 1:
                // bomb
                currentHp -= 10 + qrand()%91;
                if (currentHp < 0)
                {
                    currentHp = 0;
                }
                emit signalHPChanged(currentHp);
                break;
            case 2:
                // heal
                currentHp+= 1 + rand() % 16;
                if (currentHp > 100)
                {
                    currentHp = 100;
                }
                emit signalHPChanged(currentHp);
                break;
            case 3:
                //xp
                tmp = ui->LevelProgress->value();
                tmp+=45;
                emit signalXPChanged(tmp);
                break;
            case 4:
                //speedup
                timer->start(10);
                timer2->start(5000);
                break;
            }

            scene->removeItem(currentBonus);
            bonuses.removeOne(currentBonus);
            delete currentBonus;
        }
    }
}

void MainWindow::slotCreateBonus()
{
    Bonus *bonus1 = new Bonus(); // Создаём
    scene->addItem(bonus1);      // Помещаем его в сцену со случайной позицией
    bonus1->setPos((qrand() % (251)) * ((qrand()%2 == 1)?1:-1), (qrand() % (251)) * ((qrand()%2 == 1)?1:-1));

    bonuses.append(bonus1);       // Добавляем в Список
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resButton_clicked()
{
    QWidget *widget = new QWidget();
    QPalette p(widget->palette());
    p.setColor(QPalette::Background, Qt::white);
    widget -> setPalette(p);
    QShortcut *shortcut =  new QShortcut(QKeySequence("Esc"), widget);
    connect(shortcut, SIGNAL(pressed()), widget, SLOT(close()));
    widget->show();
}

void MainWindow::on_okButton_clicked()
{
    ui->nickLine->setEnabled(false);

}
