/****************************************************************
 * Copyright @2023 qAITool Developments.
 * License: GPLv3.
 * Author: Seven Mersenne <7mersenne@gmail.com>
 ***************************************************************/

#include "TrainDataBundle.h"
using namespace QAITool;

#include <QDir>
#include <QTextStream>


#include <fstream>
#include <iostream>


CTrainDataBundle::CTrainDataBundle(const FTrainDataParam &&config)
    :param(config)
{
    images.reserve(__DEFAULT_TRAIN_CAP__);
    labels.reserve(__DEFAULT_TRAIN_CAP__);
}

CTrainDataBundle::CTrainDataBundle(FTrainDataParam &config)
    :param(config)
{
    images.reserve(__DEFAULT_TRAIN_CAP__);
    labels.reserve(__DEFAULT_TRAIN_CAP__);
}

CTrainDataBundle::~CTrainDataBundle()
{
}

double CTrainDataBundle::ConvertElementData(const QColor &element)
{
    return ((double)element.red() / 255.0 * 0.99) + 0.01;
}

void CTrainDataBundle::SaveTXT(const QString &filename)
{
    if (!param.outputdir.endsWith('/')) {
        param.outputdir += '/';
    }
    QFile trainFile(param.outputdir + filename + ".txt");
    if (trainFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&trainFile);
        for (int i = 0; i < targets.size(); ++i) {
            out << targets[i] << " ";
            QImage img = images[i];
            for (int y = 0; y < img.height(); ++y) {
                for (int x = 0; x < img.width(); ++x) {
                    QRgb pixel = img.pixel(x, y);
                    out << qRed(pixel) << " ";
                }
            }
            out << "\n";
        }
        trainFile.close();
    }
}

void CTrainDataBundle::SaveNDT(const QString &filename)
{
    if (!param.outputdir.endsWith('/')) {
        param.outputdir += '/';
    }

    QString _fname = param.outputdir + filename + ".ndt";

    //===

    if(images.size() <=0) return;

    std::ofstream ofs(_fname.toStdString(), std::ios::binary);
    if (!ofs.is_open()) {
        std::cerr << "Error: can not open file " << _fname.toStdString() << std::endl;
        return;
    }

    ofs.unsetf(std::ios::skipws);

    int version = 1;

    ofs.write((char*)&version, sizeof(int));


    size_t in_cnt = images[0].width() * images[0].height();
    size_t out_cnt = labels.size();

    ofs.write((char*)&in_cnt, sizeof(size_t));
    ofs.write((char*)&out_cnt, sizeof(size_t));

    std::string prefixFilename = "train";
    std::string suffixFilename = "ndt";

    size_t length = prefixFilename.size();
    ofs.write((char*)&length, sizeof(size_t));
    ofs.write(prefixFilename.data(), length);

    length = suffixFilename.size();
    ofs.write((char*)&length, sizeof(size_t));
    ofs.write(suffixFilename.data(), length);

    length = images.size();
    ofs.write((char*)&length, sizeof(size_t));

    size_t m = 1;
    size_t n = images[0].width() * images[0].height();

    ofs.write((char*)&m, sizeof(size_t));
    ofs.write((char*)&n, sizeof(size_t));

    for(size_t t=0, imax = (size_t)images.size();t<imax;++t)
    {
        for(int i=0;i<images[t].width();++i)
        {
            for(int j=0;j<images[t].height();++j)
            {
                double v = ConvertElementData(images[t].pixelColor(i,j));
                ofs.write((char*)&v, sizeof(double));
            }
        }
    }

    length = targets.size();
    ofs.write((char*)&length, sizeof(size_t));

    m = 1;
    n = labels.size();

    ofs.write((char*)&m, sizeof(size_t));
    ofs.write((char*)&n, sizeof(size_t));

    double not_target = 0.01;
    double is_target = 0.99;

    for(size_t t=0, imax = (size_t)targets.size();t<imax;++t)
    {
        for(size_t i=0;i<m;++i)
        {
            for(size_t j=0;j<n;++j)
            {
                if(j != targets[j])
                {
                    ofs.write((char*)&not_target, sizeof(double));
                }else{
                    ofs.write((char*)&is_target, sizeof(double));
                }
            }
        }
    }

    ofs.close();
}

void CTrainDataBundle::Generate()
{
    QDir inputDir(param.inputDir);
    QStringList dirList = inputDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    for (const QString& dirName : dirList) {
        labels.append(dirName);
        QDir subDir(inputDir.absoluteFilePath(dirName));
        QStringList filters;
        filters << "*.png" << "*.jpg";
        QStringList imgList = subDir.entryList(filters, QDir::Files | QDir::NoDotAndDotDot, QDir::Name);

        auto target_id = labels.size() - 1;

        for (const QString& imgName : imgList) {
            QImage img(subDir.absoluteFilePath(imgName));
            images.append(img);
            targets.append(target_id);
        }
    }

    QString _dir = param.outputdir;

    if (!_dir.endsWith('/')) {
        _dir += '/';
    }

    QFile file(_dir + param.labelFName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString& label : labels) {
            out << label << "\n";
        }
        file.close();
    }

    switch (param.format) {
    case ETrainFileFormat::TEXT:
        SaveTXT(param.TrainFName);
        break;
    case ETrainFileFormat::NDT:
        SaveNDT(param.TrainFName);
        break;
    default://ETrainFileFormat::ALL
        SaveTXT(param.TrainFName);
        SaveNDT(param.TrainFName);
        break;
    }

}
