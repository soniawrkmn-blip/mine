#include "mainwindow.h"
#include "license.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QFont>

void MainWindow::initPortraitAndIdentity()
{
    this->identification = new QWidget(this);
    this->identification->setStyleSheet("background-color: #101A28");
    this->deepfake = new QWidget(this);
    this->deepfake->setStyleSheet("background-color: #101A28");
    this->virtualCamera = new QWidget(this);
    this->virtualCamera->setStyleSheet("background-color: #101A28");

    // Настройка widget1 (например, кнопка)
    this->portrait = new QLabel("Choose a portrait photo", this->identification);
    this->portrait->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top:20px;");

    this->browse = new QPushButton("Browse", this->identification);
    this->browse->setStyleSheet("background-color: #404040; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 40px; max-width: 200px;"
                          "border: 2px solid #fff; margin-left: 20px; margin-top: 25px;");
    btns.append(this->browse);

    this->frame = new QLabel(this->identification);
    this->frame->setStyleSheet("min-width: 200px; max-width: 200px; min-height: 250px; max-height: 260px; margin-top: 30px; margin-left: 20px; border: 2px solid #555;");
    this->frame->setAlignment(Qt::AlignCenter);
    this->frame->setFrameShape(QFrame::StyledPanel);
    this->frame->setFrameShadow(QFrame::Sunken);

    this->identitiy = new QLabel("Get Generated Identity", this->identification);
    this->identitiy->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin: 150px, 0px, 0, 0;");

    this->countryComboBox = new QComboBox(this);

    this->countryComboBox->setStyleSheet(
        "QComboBox {"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "    padding: 2px 5px;"
        "    max-width: 200px;"
        "    min-height: 25px;"
        "    background-color: white;"  // Белый фон для поля ввода
        "    font-size: 14px;"
        "    font-weight: 600;"
        "}"
        "QComboBox::down-arrow {"
        "    border: none;"  // Убираем фон за стрелочкой
        "    background-color: transparent;"
        "    image: url(../../icons/down-arrow.png);"  // Замените на ваше изображение стрелочки
        "}"
        "QComboBox::drop-down {"
        "    border: 1px solid #ccc;"  // Рамка для выпадающего списка
        "    background-color: white !important;"  // Белый фон для выпадающего списка (с !important)
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"  // Белый фон для элементов в выпадающем списке
        "    selection-background-color: #0095ff;"  // Цвет фона выбранного элемента
        "    min-height: 450px;"
        "    max-height: 500px;"
        "}"
        );

    QStringList countryList = {"Australia", "Belarus", "Belgium", "Brasil", "British", "Bulgaria", "California - US", "Canada", "China", "Colorado", "Croatia",
    "Cyprus", "Czech", "Columbia", "Denmark", "Delware - US", "Estonia", "Finland", "Florida - US", "France", "Georgia - US", "Germany", "Greece", "Haiti",
    "Hongkong", "Hungary", "Idaho - US", "Ireland", "Israel", "Italy", "Japan", "Kansas - US", "Kazakhstan", "Kentucky - US", "Latvia", "Lithunia", "Malaysia",
    "Mexico", "Netherland", "New zealand", "New Yourk - US", "Norway", "Panama", "Portugal", "Romania", "Russia", "Singapore", "Slovekia", "Spain", "Sweden",
    "Taiwan", "Texas - US", "Turkey", "UAE", "UK", "Utah", "Uzbekistan", "Vietnam"};

    for (const auto& text : countryList)
    {
        this->countryComboBox->addItem(text.trimmed());
    }

    this->menCheckBox = new QCheckBox("Men", this);
    this->menCheckBox->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500;");

    this->womenCheckBox = new QCheckBox("Women", this);
    this->womenCheckBox->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500;");

    this->checkBoxsLayout = new QHBoxLayout;
    this->checkBoxsLayout->addWidget(this->menCheckBox);
    this->checkBoxsLayout->addWidget(this->womenCheckBox);
    this->checkBoxsLayout->addStretch(0);

    this->identityLayout = new QVBoxLayout;
    this->identityLayout->addWidget(identitiy);
    this->identityLayout->addWidget(this->countryComboBox);
    this->identityLayout->addLayout(this->checkBoxsLayout);
    this->identityLayout->setContentsMargins(20,10,0,0);

    // Создаем layout и добавляем элементы
    this->layout1 = new QVBoxLayout;

    this->layout1->setAlignment(Qt::AlignTop);
    this->layout1->addWidget(this->portrait);  // Лейбл
    this->layout1->addWidget(this->browse);    // Кнопка "Browse"
    this->layout1->addWidget(this->frame);     // Рамка
    this->layout1->addLayout(this->identityLayout);
    this->layout1->setContentsMargins(80, 0, 0, 0);  // Отступы для сдвига влево
}

void MainWindow::initPassTemplate() {
    this->passTemp = new QLabel("Choose a passport template", this->identification);
    this->passTemp->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top:20px; margin-bottom: 25px;");

    this->passportComboBox = new QComboBox(this);

    this->passportComboBox->setStyleSheet(
        "QComboBox {"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "    min-width: 320px;"
        "    max-width: 320px;"
        "    min-height: 25px;"
        "    background-color: white;"  // Белый фон для поля ввода
        "    font-size: 14px;"
        "    font-weight: 600;"
        "}"
        "QComboBox::down-arrow {"
        "    border: none;"  // Убираем фон за стрелочкой
        "    background-color: transparent;"
        "    image: url(../../icons/down-arrow.png);"  // Замените на ваше изображение стрелочки
        "}"
        "QComboBox::drop-down {"
        "    border: 1px solid #ccc;"  // Рамка для выпадающего списка
        "    background-color: white !important;"  // Белый фон для выпадающего списка (с !important)
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"  // Белый фон для элементов в выпадающем списке
        "    selection-background-color: #0095ff;"  // Цвет фона выбранного элемента
        "    min-height: 450px;"
        "    max-height: 500px;"
        "    min-width: 320px;"  // Ограничение ширины выпадающего списка
        "    max-width: 320px;"  // Ограничение ширины выпадающего списка
        "}"
        );

    QStringList passportString = {"Alaska - US", "Alabama - US", "Arizona - US", "Arkansas - US", "Australia", "Belarus", "Belgium", "Brasil", "British",
                                  " Bulgaria", "California - US", "Canada", "Colorado - US", "Connecticut - US", "China", "Colorado", "Croatia", "Cyprus", "Czech", "Columbia", "Denmark",
                                  "Delware - US", "Estonia", "Finland", "Florida - US", "France", "Georgia - US", "Germany", "Greece", "Haiti", "Hawaii - US", "Hongkong", "Idaho - US",
                                  "Lowa - US", "Indiana - US", "lllionis - US", "Ireland", "Israel", "Italy", "Kansas - US", "Kentucky - US", "Louisiana - US", "Louisiana - US",
                                  "Japan", "Kazakhstan", "Latvia", "Lithuania", "Malaysia", "Massachusetts - US", "Maine - US", "Maryland - US", "Minnesota - US", "Mississippi - US",
                                  "Missouri - US", "Montana - US", "Mexico", "Michigan - US", "Netherland", "New zeeland", "Nebraska - US", "Nevada - US", "New Hampshire - US",
                                  "New Mexico - US", "New Jersey - US", "New Yourk - US", "North Carolina - US", "Norway", "Ohio - US", "Oklahoma - US", "Oregon - US", "Panama",
                                  "Pennsylvania - US", "Puerto Rico - US", "Portugal", "Rhode Island - US", "Romania", "Russia", "Singapore", "Slovekia", "South Carolina - US",
                                  "South Dakota - US", "Spain", "Sweden", "Taiwan", "Tennessee - US", "Texas - US", "Turkey", "UAE", "UK", "Utah - US", "Uzbekistan", "Vietnam",
                                  "Virginia - US", "Washington - US", "West Virginia - US", "Wisconsin - US"};

    for (const auto& text : passportString) {
        this->passportComboBox->addItem(text.trimmed());
    }


    this->frame_1 = new QLabel(this->identification);
    this->frame_1->setAlignment(Qt::AlignCenter);
    this->frame_1->setStyleSheet("min-width: 320px; max-width: 321px; min-height: 400px; max-height: 401px; margin-top: 45px; margin-left: 10px; border: 1px solid #555;");
    this->passportComboBox->setFixedSize(320, 25);
    this->frame_1->setFixedSize(320, 650);

    this->getSmt = new QPushButton("GET", this->identification);
    this->getSmt->setStyleSheet("background-color: #800000; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 40px; min-width: 200px; max-width: 201px;"
                                  "border: 2px solid #fff; margin-top: 45px;");
    this->btns.append(this->getSmt);

    this->layout1_2 = new QVBoxLayout;

    this->layout1_2->setAlignment(Qt::AlignTop);
    this->layout1_2->addWidget(this->passTemp);
    this->layout1_2->addWidget(this->passportComboBox);
    this->layout1_2->addWidget(this->frame_1);
    this->layout1_2->addWidget(this->getSmt);
    this->layout1_2->setSpacing(0);
    this->layout1_2->setContentsMargins(30, 0, 0, 0);  // Отступы для сдвига влево

    // connect browse button
    connect(this->browse, &QPushButton::clicked, this, &MainWindow::onBrowsePortrait);
}

void MainWindow::initBtnsAndFrame() {
    this->run = new QPushButton("RUN", this->identification);
    this->run->setStyleSheet("background-color: #2667fd; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; min-width: 100px; max-width: 100px;"
                       "border: 2px solid #fff; margin-top: 45px;");
    btns.append(this->run);

    this->effect = new QPushButton("EFFECT", this->identification);
    this->effect->setStyleSheet("background-color: #296303; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; min-width: 200px; max-width: 200px;"
                          "border: 2px solid #fff; margin-top: 45px;");
    btns.append(this->effect);

    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->addWidget(run);
    this->btnsLayout->addWidget(this->effect);
    this->btnsLayout->addStretch(0);

    this->none = new QPushButton("", this->identification);
    this->none->setStyleSheet("background-color: #fff; min-height: 20px; max-height: 20px; min-width: 312px; max-width: 312px;"
                        "border: 2px solid #fff; margin-top: 5px;");

    this->frame_2 = new QFrame(this->identification);
    this->frame_2->setFrameShape(QFrame::StyledPanel);  // Устанавливаем рамку
    this->frame_2->setFrameShadow(QFrame::Sunken);
    this->frame_2->setStyleSheet("min-width: 313px; max-width: 313px; min-height: 400px; max-height: 401px;");
    this->frame_2->setFixedSize(313, 650);

    this->editArea = new QTextEdit(this->identification);
    this->editArea->setStyleSheet("max-height: 90px; min-height: 90px; min-width: 313px; max-width: 313px; background-color: #fff; font-size: 15px; font-weight: 600");

    this->layout1_3 = new QVBoxLayout;
    this->layout1_3->setAlignment(Qt::AlignTop);
    this->layout1_3->addLayout(this->btnsLayout);
    this->layout1_3->addWidget(this->none);
    this->layout1_3->addWidget(this->frame_2);
    this->layout1_3->addWidget(this->editArea);
    this->layout1_3->setContentsMargins(30,20,0,0);
}

void MainWindow::initIdentificationPage() {
    
    this->initPortraitAndIdentity();
    this->initPassTemplate();
    this->initBtnsAndFrame();

    this->save = new QPushButton("SAVE", this->identification);
    this->save->setStyleSheet("background-color: #030863; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; min-width: 100px; max-width: 100px;"
                        "border: 2px solid #fff; margin-left: 20px");

    btns.append(this->save);

    this->mainLayout = new QHBoxLayout;
    this->mainLayout->addLayout(this->layout1);
    this->mainLayout->addLayout(this->layout1_2);
    this->mainLayout->addLayout(this->layout1_3);
    this->mainLayout->addWidget(this->save);
    this->mainLayout->addStretch(0);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);  // Отступы для сдвига влево

    this->errWindow = new ErrorWindow(this);

    this->identification->setLayout(this->mainLayout);
}

// ... rest of file unchanged
