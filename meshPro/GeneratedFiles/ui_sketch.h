/********************************************************************************
** Form generated from reading UI file 'sketch.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCH_H
#define UI_SKETCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_meshProClass
{
public:
    QWidget *centralWidget;
    QLabel *scale;
    QTextEdit *curv_scale;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *InputLayout;
    QPushButton *drawmode;
    QPushButton *dragmode;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *Linemode;
    QLabel *name;
    QPushButton *Bend;
    QPushButton *Contour;
    QPushButton *Flat;
    QPushButton *Sharp;
    QPushButton *Valley;
    QPushButton *openImg;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QPushButton *clearLines;

    void setupUi(QMainWindow *meshProClass)
    {
        if (meshProClass->objectName().isEmpty())
            meshProClass->setObjectName(QStringLiteral("meshProClass"));
        meshProClass->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(meshProClass->sizePolicy().hasHeightForWidth());
        meshProClass->setSizePolicy(sizePolicy);
        meshProClass->setMinimumSize(QSize(1024, 600));
        meshProClass->setMaximumSize(QSize(1366, 825));
        centralWidget = new QWidget(meshProClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setMaximumSize(QSize(1024, 111111));
        scale = new QLabel(centralWidget);
        scale->setObjectName(QStringLiteral("scale"));
        scale->setGeometry(QRect(40, 110, 91, 31));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        scale->setFont(font);
        curv_scale = new QTextEdit(centralWidget);
        curv_scale->setObjectName(QStringLiteral("curv_scale"));
        curv_scale->setGeometry(QRect(140, 110, 104, 31));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(440, 20, 254, 104));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        InputLayout = new QGridLayout();
        InputLayout->setSpacing(6);
        InputLayout->setObjectName(QStringLiteral("InputLayout"));
        InputLayout->setHorizontalSpacing(10);
        InputLayout->setContentsMargins(10, -1, 10, -1);
        drawmode = new QPushButton(verticalLayoutWidget);
        drawmode->setObjectName(QStringLiteral("drawmode"));
        drawmode->setMinimumSize(QSize(64, 64));
        drawmode->setMaximumSize(QSize(64, 64));
        drawmode->setCursor(QCursor(Qt::PointingHandCursor));
        drawmode->setToolTipDuration(1);
        drawmode->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/draw1.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon.addFile(QStringLiteral("Resources/draw2.png"), QSize(), QIcon::Selected, QIcon::On);
        drawmode->setIcon(icon);
        drawmode->setIconSize(QSize(64, 64));
        drawmode->setCheckable(true);

        InputLayout->addWidget(drawmode, 0, 1, 1, 1);

        dragmode = new QPushButton(verticalLayoutWidget);
        dragmode->setObjectName(QStringLiteral("dragmode"));
        dragmode->setEnabled(true);
        dragmode->setMinimumSize(QSize(64, 64));
        dragmode->setMaximumSize(QSize(64, 64));
        dragmode->setCursor(QCursor(Qt::PointingHandCursor));
        dragmode->setAcceptDrops(false);
        dragmode->setToolTipDuration(1);
        dragmode->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/drag1.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon1.addFile(QStringLiteral("Resources/drag2.png"), QSize(), QIcon::Selected, QIcon::On);
        dragmode->setIcon(icon1);
        dragmode->setIconSize(QSize(64, 64));
        dragmode->setCheckable(true);
        dragmode->setChecked(true);

        InputLayout->addWidget(dragmode, 0, 0, 1, 1);


        verticalLayout->addLayout(InputLayout);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(730, 20, 160, 171));
        Linemode = new QVBoxLayout(verticalLayoutWidget_2);
        Linemode->setSpacing(0);
        Linemode->setContentsMargins(11, 11, 11, 11);
        Linemode->setObjectName(QStringLiteral("Linemode"));
        Linemode->setContentsMargins(0, 0, 0, 0);
        name = new QLabel(verticalLayoutWidget_2);
        name->setObjectName(QStringLiteral("name"));
        name->setMinimumSize(QSize(0, 30));
        name->setMaximumSize(QSize(16777215, 30));
        name->setFont(font);

        Linemode->addWidget(name);

        Bend = new QPushButton(verticalLayoutWidget_2);
        Bend->setObjectName(QStringLiteral("Bend"));

        Linemode->addWidget(Bend);

        Contour = new QPushButton(verticalLayoutWidget_2);
        Contour->setObjectName(QStringLiteral("Contour"));

        Linemode->addWidget(Contour);

        Flat = new QPushButton(verticalLayoutWidget_2);
        Flat->setObjectName(QStringLiteral("Flat"));

        Linemode->addWidget(Flat);

        Sharp = new QPushButton(verticalLayoutWidget_2);
        Sharp->setObjectName(QStringLiteral("Sharp"));

        Linemode->addWidget(Sharp);

        Valley = new QPushButton(verticalLayoutWidget_2);
        Valley->setObjectName(QStringLiteral("Valley"));

        Linemode->addWidget(Valley);

        openImg = new QPushButton(centralWidget);
        openImg->setObjectName(QStringLiteral("openImg"));
        openImg->setEnabled(true);
        openImg->setGeometry(QRect(40, 29, 91, 61));
        openImg->setMinimumSize(QSize(0, 50));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setWeight(75);
        openImg->setFont(font2);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(150, 200, 741, 471));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(gridLayoutWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMouseTracking(false);

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        clearLines = new QPushButton(centralWidget);
        clearLines->setObjectName(QStringLiteral("clearLines"));
        clearLines->setGeometry(QRect(170, 30, 81, 61));
        clearLines->setMinimumSize(QSize(0, 50));
        clearLines->setMaximumSize(QSize(16777215, 16777215));
        clearLines->setFont(font);
        meshProClass->setCentralWidget(centralWidget);

        retranslateUi(meshProClass);
        QObject::connect(dragmode, SIGNAL(clicked()), meshProClass, SLOT(drag_clicked()));
        QObject::connect(drawmode, SIGNAL(clicked()), meshProClass, SLOT(draw_clicked()));

        QMetaObject::connectSlotsByName(meshProClass);
    } // setupUi

    void retranslateUi(QMainWindow *meshProClass)
    {
        meshProClass->setWindowTitle(QApplication::translate("meshProClass", "meshPro", 0));
        scale->setText(QApplication::translate("meshProClass", "curv scale", 0));
        label->setText(QApplication::translate("meshProClass", "Input Mode", 0));
#ifndef QT_NO_TOOLTIP
        drawmode->setToolTip(QApplication::translate("meshProClass", "\347\273\230\345\210\266", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        drawmode->setStatusTip(QApplication::translate("meshProClass", "\347\273\230\345\210\266", 0));
#endif // QT_NO_STATUSTIP
        drawmode->setText(QString());
#ifndef QT_NO_TOOLTIP
        dragmode->setToolTip(QApplication::translate("meshProClass", "\346\213\226\346\213\275", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        dragmode->setStatusTip(QApplication::translate("meshProClass", "\346\213\226\346\213\275", 0));
#endif // QT_NO_STATUSTIP
        dragmode->setText(QString());
        name->setText(QApplication::translate("meshProClass", "Line Mode", 0));
        Bend->setText(QApplication::translate("meshProClass", "Bend", 0));
        Contour->setText(QApplication::translate("meshProClass", "Contour", 0));
        Flat->setText(QApplication::translate("meshProClass", "Flat", 0));
        Sharp->setText(QApplication::translate("meshProClass", "Sharp feature", 0));
        Valley->setText(QApplication::translate("meshProClass", "Valley", 0));
        openImg->setText(QApplication::translate("meshProClass", "openImg", 0));
        clearLines->setText(QApplication::translate("meshProClass", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class meshProClass: public Ui_meshProClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKETCH_H
