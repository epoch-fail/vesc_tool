/*
    Copyright 2016 - 2017 Benjamin Vedder	benjamin@vedder.se

    This file is part of VESC Tool.

    VESC Tool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    VESC Tool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#include "pageappskidaddle.h"
#include "ui_pageappskidaddle.h"
#include "utility.h"

PageAppSkidaddle::PageAppSkidaddle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAppSkidaddle)
{
    ui->setupUi(this);
    layout()->setContentsMargins(0, 0, 0, 0);
    mVesc = nullptr;
    ui->display->setDual(true);

//    ui->throttlePlot->addGraph();
//    ui->throttlePlot->graph()->setName("Throttle Curve");
//    ui->throttlePlot->xAxis->setLabel("Throttle Value");
//    ui->throttlePlot->yAxis->setLabel("Output Value");
//    ui->throttlePlot->legend->setVisible(true);
//    ui->throttlePlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
}

PageAppSkidaddle::~PageAppSkidaddle()
{
    delete ui;
}

VescInterface *PageAppSkidaddle::vesc() const
{
    return mVesc;
}

void PageAppSkidaddle::setVesc(VescInterface *vesc)
{
    mVesc = vesc;

    if (mVesc) {
        ui->nrfPair->setVesc(mVesc);
        reloadParams();

        //connect(mVesc->commands(), SIGNAL(decodedChukReceived(double)),
        //        this, SLOT(decodedChukReceived(double)));

        connect(mVesc->appConfig(), SIGNAL(paramChangedDouble(QObject*,QString,double)),
                this, SLOT(paramChangedDouble(QObject*,QString,double)));
        connect(mVesc->appConfig(), SIGNAL(paramChangedInt(QObject*,QString,int)),
                this, SLOT(paramChangedInt(QObject*,QString,int)));
        connect(mVesc->appConfig(), SIGNAL(paramChangedEnum(QObject*,QString,int)),
                this, SLOT(paramChangedEnum(QObject*,QString,int)));

        paramChangedEnum(nullptr, "app_skidaddle_conf.ski_mode", 0);
    }
}

void PageAppSkidaddle::reloadParams()
{
    if (mVesc) {
        ui->generalTab->clearParams();
        //ui->throttleCurveTab->clearParams();

        ui->generalTab->addParamSubgroup(mVesc->appConfig(), "skidaddle", "general");
        //ui->throttleCurveTab->addParamSubgroup(mVesc->appConfig(), "vesc remote", "throttle curve");
    }
}

//void PageAppSkidaddle::decodedChukReceived(double value)
//{
//    double p = value * 100.0;
//    ui->display->setValue(p);
//    ui->display->setText(tr("%1 %").
//                         arg(p, 0, 'f', 1));
//}

void PageAppSkidaddle::paramChangedDouble(QObject *src, QString name, double newParam)
{
    (void)src;
    (void)newParam;

    if (name == "app_skidaddle_conf.continuous_mode_cycle_peak" || name == "app_skidaddle_conf.continuous_mode_cycle_trough") {
        int mode = mVesc->appConfig()->getParamEnum("app_skidaddle_conf.ski_mode");
        float val_peak = mVesc->appConfig()->getParamDouble("app_skidaddle_conf.continuous_mode_cycle_peak");
        float val_trough = mVesc->appConfig()->getParamDouble("app_skidaddle_conf.continuous_mode_cycle_trough");

        //QVector<double> x;
        //QVector<double> y;
        //for (float i = -1.0;i < 1.0001;i += 0.002) {
        //    x.append(i);
        //    double val = Utility::throttle_curve(i, val_acc, val_brake, mode);
        //    y.append(val);
        //}
        //ui->throttlePlot->graph()->setData(x, y);
        //ui->throttlePlot->rescaleAxes();
        //ui->throttlePlot->replot();
    }
}

void PageAppSkidaddle::paramChangedInt(QObject *src, QString name, int newParam)
{
    (void)src;
    (void)newParam;

    if (name == "app_skidaddle_conf.continuous_mode_cycle_time_ms") {
        paramChangedDouble(nullptr, "app_skidaddle_conf.continuous_mode_cycle_time_ms", 0.0);
    }
}

void PageAppSkidaddle::paramChangedEnum(QObject *src, QString name, int newParam)
{
    (void)src;
    (void)newParam;

    if (name == "app_skidaddle_conf.ski_mode") {
        paramChangedDouble(nullptr, "app_skidaddle_conf.ski_mode", 0.0);
    }
}

