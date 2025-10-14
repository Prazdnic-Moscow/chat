#pragma once
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

class LoadingOverlay : public QWidget
{
    Q_OBJECT
    public:
        explicit LoadingOverlay(QWidget *parent = nullptr)
            : QWidget(parent)
        {
            setAttribute(Qt::WA_NoSystemBackground);
            setAttribute(Qt::WA_TransparentForMouseEvents, false);
            setStyleSheet("background-color: rgba(0, 0, 0, 128);"); // полупрозрачный фон
            setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

            QVBoxLayout *layout = new QVBoxLayout(this);
            layout->setAlignment(Qt::AlignCenter);

            QLabel *spinner = new QLabel(this);
            QMovie *movie = new QMovie(":/spinner.gif"); // добавь spinner.gif в ресурсы Qt (resources.qrc)
            spinner->setMovie(movie);
            movie->start();

            QLabel *label = new QLabel("Проверка устройства...", this);
            label->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");
            label->setAlignment(Qt::AlignCenter);

            layout->addWidget(spinner);
            layout->addSpacing(10);
            layout->addWidget(label);
        }

    protected:
        void resizeEvent(QResizeEvent *) override {
            if (parentWidget())
                resize(parentWidget()->size());
        }
};
