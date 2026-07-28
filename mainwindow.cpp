#include "mainwindow.h"
#include "license.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QPainter>
#include <QPen>

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

    QStringList countryList = {"Australia", "Belarus", "Belgium", "Brasil", "British", "Bulgaria", "California - US", "Canada", "China", "Colorado", "Croatia"
    "Cyprus", "Czech", "Columbia", "Denmark", "Delware - US", "Estonia", "Finland", "Florida - US", "France", "Georgia - US", "Germany", "Greece", "Haiti"
    "Hongkong", "Hungary", "Idaho - US", "Ireland", "Israel", "Italy", "Japan", "Kansas - US", "Kazakhstan", "Kentucky - US", "Latvia", "Lithunia", "Malaysia"
    "Mexico", "Netherland", "New zealand", "New Yourk - US", "Norway", "Panama", "Portugal", "Romania", "Russia", "Singapore", "Slovekia", "Spain", "Sweden"
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
                                  " Bulgaria", "California - US", "Canada", "Colorado - US", "Connecticut - US", "China", "Colorado", "Croatia", "Cyprus", "Czech", "Columbia", "Denmark"
                                  "Delware - US", "Estonia", "Finland", "Florida - US", "France", "Georgia - US", "Germany", "Greece", "Haiti", "Hawaii - US", "Hongkong", "Idaho - US"
                                  "Lowa - US", "Indiana - US", "lllionis - US", "Ireland", "Israel", "Italy", "Kansas - US", "Kentucky - US", "Louisiana - US", "Louisiana - US"
                                  "Japan", "Kazakhstan", "Latvia", "Lithuania", "Malaysia", "Massachusetts - US", "Maine - US", "Maryland - US", "Minnesota - US", "Mississippi - US"
                                  "Missouri - US", "Montana - US", "Mexico", "Michigan - US", "Netherland", "New zeeland", "Nebraska - US", "Nevada - US", "New Hampshire - US",
                                  "New Mexico - US", "New Jersey - US", "New Yourk - US", "North Carolina - US", "Norway", "Ohio - US", "Oklahoma - US", "Oregon - US", "Panama"
                                  "Pennsylvania - US", "Puerto Rico - US", "Portugal", "Rhode Island - US", "Romania", "Russia", "Singapore", "Slovekia", "South Carolina - US"
                                  "South Dakota - US", "Spain", "Sweden", "Taiwan", "Tennessee - US", "Texas - US", "Turkey", "UAE", "UK", "Utah - US", "Uzbekistan", "Vietnam"
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

void MainWindow::initPrtAndFr() {
    this->portrait_2 = new QLabel("Choose a portrait photo", this->deepfake);
    this->portrait_2->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top:20px;");


    this->browse_2 = new QPushButton("Browse", this->deepfake);
    this->browse_2->setStyleSheet("background-color: #404040; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 40px; max-width: 130px;"
                                  "border: 2px solid #fff; margin-left: 65px; margin-top: 25px;");
    btns.append(this->browse_2);

    this->frame_2_1 = new QLabel(this->deepfake);
    this->frame_2_1->setAlignment(Qt::AlignCenter);
    this->frame_2_1->setStyleSheet("max-width: 200px; min-height: 250px; max-height: 260px; margin-top: 30px; margin-left: 20px; border: 2px solid #555;");
    this->frame_2_1->setFrameShape(QFrame::StyledPanel);
    this->frame_2_1->setFrameShadow(QFrame::Sunken);


    this->layout2 = new QVBoxLayout;

    this->layout2->setAlignment(Qt::AlignTop);
    this->layout2->addWidget(this->portrait_2);  // Лейбл
    this->layout2->addWidget(this->browse_2);    // Кнопка "Browse"
    this->layout2->addWidget(this->frame_2_1);     // Рамка
}

void MainWindow::initKYCAndList() {
    this->layout2_1 = new QVBoxLayout;

    // Лейбл
    this->platform = new QLabel(this->deepfake);
    this->platform->setText("Choose platform KYC\n to create AI video");
    this->platform->setAlignment(Qt::AlignTop);
    this->platform->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top:20px;");

    // QListWidget для выбора платформы
    this->listWidget = new QListWidget(this->deepfake);
    this->listWidget->setStyleSheet("background-color: gray; color: #fff; font-size: 16px; font-weight: 500; max-width: 180px; min-height: 300px; max-height: 300px;"
                                    " border: 1px solid #fff; margin-top: 30px");

    // Добавляем элементы в QListWidget
    QStringList KYCList = {"CoinBase", "Go2bank", "Chime", "Paypal", "Webull", "Cashapp", "Venmo", "Payoneer", "Binance", "Bybit", "Coinlist", "Okx", "Gate.io",
                           "Huobi", "Revolut", "Stripe", "Primexbt", "Mexc", "Xmmarketglobal", "Mistplay", "AirBNB"};

    for (const auto& text : KYCList) {
        this->listWidget->addItem(text);
    }


    connect(this->listWidget, &QListWidget::itemClicked, this->errWindow, &ErrorWindow::show);

    // Создаем вертикальный layout
    this->layout2_1->addWidget(this->platform);  // Лейбл
    this->layout2_1->addWidget(this->listWidget);  // Список
    this->layout2_1->setSpacing(0);  // Убираем отступы между элементами
    this->layout2_1->addStretch(0);

    // Убираем addStretch и выравниваем элементы сверху
    this->layout2_1->setContentsMargins(150, 0, 0, 0);  // Отступ слева (по ширине)
    this->layout2_1->setAlignment(Qt::AlignTop);  // Выравнивание всех элементов сверху
}

void MainWindow::initModes() {
    this->layout2_2 = new QVBoxLayout;

    this->videoMode = new QLabel(this->deepfake);
    this->videoMode->setText("Mode Video");
    this->videoMode->setAlignment(Qt::AlignHCenter);
    this->videoMode->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top:20px; margin-right: 110px;");

    this->fastMode = new QCheckBox("Fast Mode", this->deepfake);
    this->fastMode->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-right: 30px;");

    this->proMode = new QCheckBox("Expert Mode", this->deepfake);
    this->proMode->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-right: 30px;");

    this->expertMode = new QCheckBox("Expert Mode", this->deepfake);
    this->expertMode->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-right: 30px;");

    this->videoModesLayout = new QHBoxLayout;
    this->videoModesLayout->addWidget(this->fastMode);
    this->videoModesLayout->addWidget(this->proMode);
    this->videoModesLayout->addWidget(this->expertMode);
    this->videoModesLayout->setAlignment(Qt::AlignTop);
    this->videoModesLayout->addStretch(0);
    this->videoModesLayout->setContentsMargins(0,20,0,0);

    this->qualityMode = new QLabel(this->deepfake);
    this->qualityMode->setText("Quality Video");
    this->qualityMode->setAlignment(Qt::AlignHCenter);
    this->qualityMode->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top:50px; margin-right: 100px;");

    this->sd = new QCheckBox("SD", this->deepfake);
    this->sd->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-right: 95px;");

    this->mp4 = new QCheckBox("MP4", this->deepfake);
    this->mp4->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-right: 90px;");

    this->hdMp4 = new QCheckBox("HD MP4", this->deepfake);
    this->hdMp4->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-right: 90px;");

    this->qualityModesLayout = new QHBoxLayout;
    this->qualityModesLayout->addWidget(this->sd);
    this->qualityModesLayout->addWidget(this->mp4);
    this->qualityModesLayout->addWidget(this->hdMp4);
    this->qualityModesLayout->setAlignment(Qt::AlignTop);
    this->qualityModesLayout->addStretch(0);
    this->qualityModesLayout->setContentsMargins(0,20,0,0);

    this->recomendation = new QLabel("Pro Mode or Expert Mode requires an advacned GPU\n(RTX 30+ is recommended), or the processing speed\nwill be really slow");
    this->recomendation->setStyleSheet("color: #fff; font-size: 16px; font-weight: 500; margin-top: 50px;");

    this->layout2_2->addWidget(this->videoMode);
    this->layout2_2->addLayout(this->videoModesLayout);
    this->layout2_2->addWidget(this->qualityMode);
    this->layout2_2->addLayout(this->qualityModesLayout);
    this->layout2_2->addWidget(this->recomendation);
    this->layout2_2->setSpacing(0);
    this->layout2_2->addStretch(0);
}

void MainWindow::initDeepfakePage() {
    this->initPrtAndFr();
    this->initKYCAndList();
    this->initModes();

    this->createVideo = new QPushButton("Create AI Video", this->deepfake);
    this->createVideo->setStyleSheet("background-color: #2667fd; color: #fff; font-weight: 600; font-size: 15px; min-height: 60px; max-height: 60px; min-width: 250px; "
                        "max-width: 250px; border: 2px solid #fff; margin-top: 80px");

    this->btns.append(this->createVideo);

    this->emptyBtn = new QPushButton("", this->deepfake);
    this->emptyBtn->setStyleSheet("background-color: #fff; color: #fff; font-weight: 600; font-size: 15px; min-height: 25px; max-height: 25px; min-width: 1100px; "
                               "max-width: 1100px; border: 2px solid #fff; margin-top: 50px");

    // Создаем горизонтальный лейаут для основного размещения
    this->mainLayout_2 = new QHBoxLayout;
    this->mainLayout_2->addLayout(this->layout2);  // Первый лейаут
    this->mainLayout_2->addLayout(this->layout2_1);  // Второй лейаут
    this->mainLayout_2->addLayout(this->layout2_2);  // Второй лейаут
    this->mainLayout_2->setAlignment(layout2, Qt::AlignTop | Qt::AlignLeft);  // Выравнивание по верхнему и левому краю
    this->mainLayout_2->setAlignment(layout2_1, Qt::AlignLeft | Qt::AlignTop);  // Выравнивание по верхнему и левому краю

    this->deepfakeLayout = new QVBoxLayout(this->deepfake);
    this->deepfakeLayout->addLayout(this->mainLayout_2);
    this->deepfakeLayout->addWidget(this->createVideo);
    this->deepfakeLayout->setAlignment(this->createVideo, Qt::AlignHCenter);
    this->deepfakeLayout->addWidget(this->emptyBtn);
    this->deepfakeLayout->setAlignment(this->emptyBtn, Qt::AlignHCenter);
    this->deepfakeLayout->addStretch(0);
    this->deepfakeLayout->setSpacing(0);

    this->deepfake->setLayout(this->deepfakeLayout);  // Применяем layout к главному виджету
}

void MainWindow::initDocumentAndKYC() {
    this->identDoc = new QLabel("Choose Identification Document", this->virtualCamera);
    this->identDoc->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500; margin-top: 100px; margin-left: 100px;");

    this->browseDoc = new QPushButton("Browse", this->virtualCamera);
    this->browseDoc->setStyleSheet("background-color: #404040; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px;  max-width: 150px;"
                                "border: 2px solid #fff; min-width: 150px; margin-left: 100px; margin-right: 30px; margin-top: 20px;");
    this->btns.append(this->browseDoc);

    this->inputDoc = new QTextEdit(this->virtualCamera);
    this->inputDoc->setStyleSheet("background-color: gray; min-height: 25px; margin-top: 20px; max-height: 25px; min-width: 700px; max-width: 700px; font-size: 15px; font-weight: 500");
    this->inputDoc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputDoc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputDoc->setReadOnly(true);

    this->docLayout = new QHBoxLayout;
    this->docLayout->addWidget(this->browseDoc);
    this->docLayout->addWidget(this->inputDoc);
    this->docLayout->addStretch(0);
    this->docLayout->setSpacing(0);

    this->videoKYC = new QLabel("Choose Video KYC", this->virtualCamera);
    this->videoKYC->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500; margin-top: 50px; margin-left: 100px;");

    this->browseKYC = new QPushButton("Browse", this->virtualCamera);
    this->browseKYC->setStyleSheet("background-color: #404040; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; max-width: 150px;"
                                   "border: 2px solid #fff; min-width: 150px; margin-left: 100px; margin-right: 30px; margin-top: 20px;");
    this->btns.append(this->browseKYC);

    this->inputKYC = new QTextEdit(this->virtualCamera);
    this->inputKYC->setStyleSheet("background-color: gray; min-height: 25px; max-height: 25px; margin-top: 20px; min-width: 700px; max-width: 700px; font-size: 15px; font-weight: 500");
    this->inputKYC->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputKYC->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputKYC->setReadOnly(true);

    this->KYCLayout = new QHBoxLayout;
    this->KYCLayout->addWidget(this->browseKYC);
    this->KYCLayout->addWidget(this->inputKYC);
    this->KYCLayout->addStretch(0);
    this->KYCLayout->setSpacing(0);

    this->layout3 = new QVBoxLayout;
    this->layout3->addWidget(this->identDoc);
    this->layout3->addLayout(this->docLayout);
    this->layout3->addWidget(this->videoKYC);
    this->layout3->addLayout(this->KYCLayout);
    this->layout3->setSpacing(0);
    this->layout3->addStretch(0);
}

void MainWindow::initButtons() {
    this->connectBr = new QPushButton("Connect Camera to Browser", this->virtualCamera);
    this->connectBr->setStyleSheet("background-color: #2667fd; color: #fff; font-weight: 600; font-size: 15px; min-height: 70px; max-height: 70px; max-width: 340px;"
                                   "border: 2px solid #fff; min-width: 340px; margin-left: 100px; margin-right: 220px; margin-top: 100px;");
    this->btns.append(this->connectBr);

    this->connectEm = new QPushButton("Connect Camera to Emulator", this->virtualCamera);
    this->connectEm->setStyleSheet("background-color: #296303; color: #fff; font-weight: 600; font-size: 15px; min-height: 70px; max-height: 70px; max-width: 340px;"
                                   "border: 2px solid #fff; min-width: 340px; margin-top: 100px;");
    this->btns.append(this->connectEm);

    this->connectLayout = new QHBoxLayout;
    this->connectLayout->addWidget(this->connectBr);
    this->connectLayout->addWidget(this->connectEm);
    this->connectLayout->setAlignment(Qt::AlignLeft);
}

void MainWindow::initVirtualCameraPage() {
    this->initDocumentAndKYC();
    this->initButtons();

    this->cameraLayout = new QVBoxLayout(this->virtualCamera);
    this->cameraLayout->addLayout(this->layout3);
    this->cameraLayout->addLayout(this->connectLayout);
    this->cameraLayout->setSpacing(0);
    this->cameraLayout->addStretch(0);

    this->virtualCamera->setLayout(this->cameraLayout);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , kycProcessor(new KYCProcessor(this))
{
    this->initIdentificationPage();
    this->initDeepfakePage();
    this->initVirtualCameraPage();

    this->tabWidget = new QTabWidget(this);
    setCentralWidget(this->tabWidget);
    this->tabWidget->addTab(identification, "Identification Creator");
    this->tabWidget->addTab(deepfake, "Deepfake AI Video Creator");
    this->tabWidget->addTab(virtualCamera, "Virtual Camera Connect");
    this->tabWidget->setStyleSheet("QTabBar::tab { height: 40px; width: 200px; font-weight: 600; font-size: 13px }");

    // Создание меню
    this->menu = menuBar()->addMenu(tr(""));

    for (auto i = 0; i < tabWidget->count(); ++i) {
        QAction *action = new QAction(tabWidget->tabText(i), this);  // Создаем действие с текстом вкладки
        this->menu->addAction(action);  // Добавляем это действие в меню

        // Связываем действия с переключением вкладок
        connect(action, &QAction::triggered, [this, i]() {
            this->tabWidget->setCurrentIndex(i);  // Переключаем на вкладку по индексу
        });
    }

    // Connect processor signals
    connect(kycProcessor, &KYCProcessor::processingStarted, this, [this] {
        this->editArea->append("Processing started...");
    });
    connect(kycProcessor, &KYCProcessor::processingProgress, this, [this](int p) {
        this->editArea->append(QString("Progress: %1%").arg(p));
    });
    connect(kycProcessor, &KYCProcessor::processingCompleted, this, [this](bool success) {
        this->editArea->append(success ? "Operation completed successfully!" : "Operation failed!");
    });
    connect(kycProcessor, &KYCProcessor::errorOccurred, this, [this](const QString& err) {
        QMessageBox::warning(this, "Error", err);
    });

    // Connect each button to its specific handler
    connect(this->browse, &QPushButton::clicked, this, &MainWindow::onBrowsePortrait);
    connect(this->browse_2, &QPushButton::clicked, this, &MainWindow::onBrowsePortrait2);
    connect(this->browseDoc, &QPushButton::clicked, this, &MainWindow::onBrowseDocument);
    connect(this->browseKYC, &QPushButton::clicked, this, &MainWindow::onBrowseKYCVideo);
    connect(this->run, &QPushButton::clicked, this, &MainWindow::onRunProcess);
    connect(this->effect, &QPushButton::clicked, this, &MainWindow::onApplyEffect);
    connect(this->save, &QPushButton::clicked, this, &MainWindow::onSaveIdentity);
    connect(this->getSmt, &QPushButton::clicked, this, &MainWindow::onGenerateIdentity);
    connect(this->createVideo, &QPushButton::clicked, this, &MainWindow::onCreateDeepfakeVideo);
    connect(this->connectBr, &QPushButton::clicked, this, &MainWindow::onConnectBrowser);
    connect(this->connectEm, &QPushButton::clicked, this, &MainWindow::onConnectEmulator);

    // List widget click
    connect(this->listWidget, &QListWidget::itemClicked, this->errWindow, &ErrorWindow::show);

    // this->setWindowIcon(QIcon("../../icons/logo.png"));
    setFixedSize(1200, 800);
}

MainWindow::~MainWindow() {
    delete kycProcessor;
}

void MainWindow::onBrowsePortrait()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose Portrait Photo", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!file.isEmpty()) {
        QPixmap pix(file);
        if (!pix.isNull()) {
            this->frame->setPixmap(pix.scaled(this->frame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void MainWindow::onBrowsePortrait2()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose Portrait Photo", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!file.isEmpty()) {
        QPixmap pix(file);
        if (!pix.isNull()) {
            this->frame_2_1->setPixmap(pix.scaled(this->frame_2_1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void MainWindow::onBrowseDocument()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose Identification Document", "", "Files (*.*)");
    if (!file.isEmpty()) this->inputDoc->setText(file);
}

void MainWindow::onBrowseKYCVideo()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose Video KYC", "", "Video Files (*.mp4 *.avi *.mov *.mkv)");
    if (!file.isEmpty()) this->inputKYC->setText(file);
}

void MainWindow::onRunProcess()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    QString country = this->countryComboBox->currentText();
    QString gender = this->menCheckBox->isChecked() ? "Men" : (this->womenCheckBox->isChecked() ? "Women" : "Unknown");
    QString passport = this->passportComboBox->currentText();
    
    bool success = kycProcessor->generateIdentity(country, gender, passport);
    if (success) {
        editArea->setText(kycProcessor->getGeneratedIdentityInfo());
        
        // Show generated identity preview in frame
        QPixmap preview(200, 250);
        preview.fill(Qt::transparent);
        QPainter painter(&preview);
        painter.setPen(QPen(Qt::white, 2));
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(preview.rect(), Qt::AlignCenter | Qt::TextWordWrap, 
            QString("IDENTITY GENERATED\n\nCountry: %1\nGender: %2\nPassport: %3\n\n[Preview]\nGenerated Identity\nReady for use")
            .arg(country).arg(this->menCheckBox->isChecked() ? "Men" : "Women").arg(this->passportComboBox->currentText()));
        this->frame->setPixmap(preview);
    }
}

void MainWindow::onApplyEffect()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    QString templatePath = this->frame->pixmap() ? "current" : "";
    
    bool success = kycProcessor->applyEffects(templatePath);
    if (success) {
        // Show effect applied preview in frame
        QPixmap preview(200, 250);
        preview.fill(Qt::transparent);
        QPainter painter(&preview);
        painter.setPen(QPen(QColor("#2667fd"), 3));
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(preview.rect(), Qt::AlignCenter | Qt::TextWordWrap, 
            "EFFECT APPLIED\n\n[Visual Effect]\nApplied to portrait\n\n[Preview]\nEffect overlay\nReady");
        this->frame->setPixmap(preview);
        
        QMessageBox::information(this, "Effect Applied", "Visual effect has been applied to the portrait!");
    }
}

void MainWindow::onSaveIdentity()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    kycProcessor->saveProject("project_data");
    this->editArea->append("Project saved successfully!");
}

void MainWindow::onGenerateIdentity()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    QString passport = this->passportComboBox->currentText();
    
    bool success = kycProcessor->generateIdentity("Auto", "Auto", passport);
    if (success) {
        editArea->setText(kycProcessor->getGeneratedIdentityInfo());
        
        // Show generated identity preview in frame
        QPixmap preview(200, 250);
        preview.fill(Qt::transparent);
        QPainter painter(&preview);
        painter.setPen(QPen(Qt::white, 2));
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(preview.rect(), Qt::AlignCenter | Qt::TextWordWrap, 
            "QUICK IDENTITY GENERATED\n\nPassport: " + this->passportComboBox->currentText() + "\n\n[Preview]\nQuick Identity\nGenerated & Ready");
        this->frame->setPixmap(preview);
    }
}

void MainWindow::onCreateDeepfakeVideo()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    if (this->listWidget->currentItem()) {
        QString platform = this->listWidget->currentItem()->text();
        kycProcessor->createVideo(platform);
        
        // Show video creation preview in frame_2_1
        QPixmap preview(200, 250);
        preview.fill(Qt::transparent);
        QPainter painter(&preview);
        painter.setPen(QPen(QColor("#2667fd"), 2));
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(preview.rect(), Qt::AlignCenter | Qt::TextWordWrap, 
            "DEEPFAKE VIDEO CREATED\n\nPlatform: " + this->listWidget->currentItem()->text() + 
            "\nMode: " + (this->fastMode->isChecked() ? "Fast" : (this->proMode->isChecked() ? "Pro" : "Expert")) +
            "\nQuality: " + (this->sd->isChecked() ? "SD" : (this->mp4->isChecked() ? "MP4" : "HD MP4")) +
            "\n\n[Preview]\nVideo Created\nReady for export");
        this->frame_2_1->setPixmap(preview);
        
        QMessageBox::information(this, "Video Created", "Deepfake video created successfully for " + this->listWidget->currentItem()->text() + "!");
    }
}

void MainWindow::onConnectBrowser()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    QString docPath = this->inputDoc->toPlainText();
    QString videoPath = this->inputKYC->toPlainText();
    if (!docPath.isEmpty() && !videoPath.isEmpty()) {
        kycProcessor->connectCamera(docPath, videoPath, "browser");
    } else {
        QMessageBox::warning(this, "Missing Files", "Please select both document and video KYC files first.");
    }
}

void MainWindow::onConnectEmulator()
{
    if (!LicenseManager::isActivated()) { errWindow->show(); return; }
    QString docPath = this->inputDoc->toPlainText();
    QString videoPath = this->inputKYC->toPlainText();
    if (!docPath.isEmpty() && !videoPath.isEmpty()) {
        kycProcessor->connectCamera(docPath, videoPath, "emulator");
    } else {
        QMessageBox::warning(this, "Missing Files", "Please select both document and video KYC files first.");
    }
}

void MainWindow::onProcessingProgress(int progress)
{
    editArea->setText(QString("Processing: %1%").arg(progress));
}

void MainWindow::onProcessingCompleted(bool success)
{
    if (success) {
        editArea->setText(editArea->toPlainText() + "\n\nProcessing completed successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Processing failed!");
    }
}

void MainWindow::onProcessingError(const QString& error)
{
    QMessageBox::critical(this, "Processing Error", error);
    editArea->setText("Error: " + error);
}