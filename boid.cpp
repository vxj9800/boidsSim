#include "boid.h"

boid::boid(QObject *parent) : QObject(parent)
{
    connect(this,&boid::nBoidsChanged,this,&boid::initBoids);
    connect(&dt,&QTimer::timeout,this,&boid::updateBoids);
    dt.start(1000/30.0);
}

void boid::initBoids()
{
    xPos.resize(nBoids); yPos.resize(nBoids);
    xVel.resize(nBoids); yVel.resize(nBoids);
    rot.resize(nBoids);
    for(int i = 0; i < nBoids; ++i)
    {
        xPos[i] = QRandomGenerator::global()->generate()/float(UINT32_MAX);
        yPos[i] = QRandomGenerator::global()->generate()/float(UINT32_MAX);
        xVel[i] = (QRandomGenerator::global()->generate()/float(UINT32_MAX) - 0.5)*0.1;
        yVel[i] = (QRandomGenerator::global()->generate()/float(UINT32_MAX) - 0.5)*0.1;
//        xVel[i] = 0; yVel[i] = 0;
        rot[i] = atan2f(yVel[i],xVel[i]);
    }
}

void boid::updateBoids()
{
    // Sum all the positions for use in cFactor calculation
    float xSum = 0, ySum = 0;
    for (int j = 0; j < nBoids; ++j)
    {
        xSum += xPos[j]; ySum += yPos[j];
    }

    for (int i = 0; i < nBoids; ++i)
    {
        // Compute Coherence
        float cx = 0, cy = 0;
        cx = xSum - xPos[i], cy = ySum - yPos[i];
        cx /= (nBoids - 1); cy /= (nBoids - 1);
        xVel[i] += (cx - xPos[i]) * cFactor;
        yVel[i] += (cy - yPos[i]) * cFactor;

        // Compute Separation and Alignment
        float ax = 0, ay = 0;
        for (int j = 0; j < nBoids; ++j)
            if (j != i)
            {
                if (j > i && sqrt(powf(xPos[j] - xPos[i],2.0) + powf(yPos[j] - yPos[i],2.0)) < sFactor)
                {
                    xVel[i] -= (xPos[j] - xPos[i]);
                    yVel[i] -= (yPos[j] - yPos[i]);
                    xVel[j] += (xPos[j] - xPos[i]);
                    yVel[j] += (yPos[j] - yPos[i]);
                }
                ax += xVel[j]*aFactor; ay += yVel[j]*aFactor;
            }

        ax /= (nBoids - 1); ay /= (nBoids - 1);
        ax = (ax - xVel[i])/100.0; ay = (ay - yVel[i])/100.0;
        xVel[i] += ax; yVel[i] += ay;

        // Compute position bound
        float Xmin = 0, Xmax = 1, Ymin = 0, Ymax = 1;
        if (xPos[i] < Xmin)
            xVel[i] += 0.01;
        else if (xPos[i] > Xmax)
            xVel[i] -= 0.01;
        if (yPos[i] < Ymin)
            yVel[i] += 0.01;
        else if (yPos[i] > Ymax)
            yVel[i] -= 0.01;

        // Add up all the velocity changes
//        xVel[i] += cx + sx + ax + bx; yVel[i] += cy + sy + ay + by;

        // Limit the velocity magnitude
        float vMag = 0.02;
        if (sqrt(powf(xVel[i],2) + powf(yVel[i],2)) > vMag)
        {
            xVel[i] = xVel[i] / sqrt(powf(xVel[i],2) + powf(yVel[i],2)) * vMag;
            yVel[i] = yVel[i] / sqrt(powf(xVel[i],2) + powf(yVel[i],2)) * vMag;
        }

        xPos[i] += xVel[i]; yPos[i] += yVel[i];
        rot[i] = atan2f(yVel[i],xVel[i]);
        emit xPosChanged(); emit yPosChanged();
        emit rotChanged();
    }
}
