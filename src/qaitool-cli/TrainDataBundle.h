/****************************************************************
 * Copyright @2023 qAITool Developments.
 * License: GPLv3.
 * Author: Seven Mersenne <7mersenne@gmail.com>
 ***************************************************************/

#pragma once

#ifndef CTRAINDATABUNDLE_H
#define CTRAINDATABUNDLE_H

#define __DEFAULT_TRAIN_CAP__ 2048

#include <QImage>
#include <QString>
#include <QDir>

namespace QAITool{

/**
 * @brief The ETrainDataMode enum
 * [-] Image_RGB8
 * [ ] Image_RGB888
 * [ ] Image_RGBA8888
 * [ ] Text
 * [ ] Binary
 */
enum ETrainDataMode
{
    Image_RGB8 = 0,
    Image_RGB888 = 1,
    Image_RGBA8888 = 2,
    Text = 3,
    Binary = 4
};

/**
 * @brief The ETrainFileFormat enum
 * [ ] TEXT
 * [ ] NDT
 * [ ] ALL
 */
enum ETrainFileFormat
{
    TEXT = 0,
    NDT = 1,
    ALL
};

struct FTrainDataParam
{
    ETrainDataMode mode;
    QString inputDir;
    QString outputdir;
    ETrainFileFormat format;
    QString labelFName;
    QString TrainFName;

    FTrainDataParam()
        : mode(ETrainDataMode::Image_RGB8)
        , inputDir("./data/input/")
        , outputdir("./data/ouput/")
        , format(ETrainFileFormat::TEXT)
        , labelFName("label.txt")
        , TrainFName("train")
    {
    }
};

class CTrainDataBundle
{
public:
    explicit CTrainDataBundle(const FTrainDataParam&&config = FTrainDataParam());
    explicit CTrainDataBundle(FTrainDataParam&config);
    virtual ~CTrainDataBundle();

    double ConvertElementData(const QColor& element);

    void SaveTXT(const QString& filename = "train");
    void SaveNDT(const QString& filename = "train");

    /**
     * @brief Generate will genrate 2 files in output dir.
     * train data files:     train.txt / train.ndt
     * train label file:    label.txt
     * the label file show the label which means the targets of train data file.
     * target id = the line of label in label.txt
     */
    void Generate();

protected:
    FTrainDataParam param;
    QVector<QImage> images;
    QVector<QString> labels;
    QVector<size_t> targets;
};

}//namespace QAITool

#endif // CTRAINDATABUNDLE_H
