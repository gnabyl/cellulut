#ifndef BSLIDER_H
#define BSLIDER_H

#include <QSlider>
#include <QStyleOptionSlider>
#include <QToolTip>

class BSlider : public QSlider {
    Q_OBJECT
  public:
    explicit BSlider(QWidget* parent = 0);
    explicit BSlider(Qt::Orientation orientation, QWidget* parent = 0);

  protected:
    virtual void sliderChange(SliderChange change);
};

#endif // BSLIDER_H
