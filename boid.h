#ifndef BOID_H
#define BOID_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QTimer>

class boid : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int nBoids MEMBER nBoids NOTIFY nBoidsChanged)
    Q_PROPERTY(QVector<float> xPos MEMBER xPos NOTIFY xPosChanged)
    Q_PROPERTY(QVector<float> yPos MEMBER yPos NOTIFY yPosChanged)
    Q_PROPERTY(QVector<float> rot MEMBER rot NOTIFY rotChanged)
    Q_PROPERTY(float cFactor MEMBER cFactor NOTIFY cFactorChanged)
    Q_PROPERTY(float aFactor MEMBER aFactor NOTIFY aFactorChanged)
    Q_PROPERTY(float sFactor MEMBER sFactor NOTIFY sFactorChanged)

    int nBoids = 1;
    QVector<float> xPos, yPos;
    QVector<float> xVel, yVel;
    QVector<float> rot;
    QTimer dt;
    float cFactor, aFactor, sFactor;

public:
    explicit boid(QObject *parent = nullptr);

signals:
    void nBoidsChanged();
    void xPosChanged();
    void yPosChanged();
    void rotChanged();
    void cFactorChanged();
    void aFactorChanged();
    void sFactorChanged();

public slots:
    void initBoids();
    void updateBoids();
};

#endif // BOID_H
