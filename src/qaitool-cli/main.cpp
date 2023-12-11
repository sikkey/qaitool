/****************************************************************
 * Copyright @2023 qAITool Developments.
 * License: GPLv3.
 * Author: Seven Mersenne <7mersenne@gmail.com>
 ***************************************************************/

#include <QCoreApplication>
//#include <QGuiApplication>
#include <QtCore>

#include <iostream>
using namespace std;

#include "TrainDataBundle.h"
using namespace QAITool;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    /*
    QCommandLineOption inputOpt("i");
    QCommandLineOption outputOpt("o");
    QCommandLineOption helpOpt("h");
    QList<QCommandLineOption> optList;

    inputOpt.setValueName("value");
    outputOpt.setValueName("value");

    // -i --input
    optList.append(inputOpt);
    // -o --output
    optList.append(outputOpt);
    // -h --help
    optList.append(helpOpt);
    optList[0].setValueName("value");
    parser.addOptions(optList);
*/

    parser.addOption({{"i", "input"}, "-i <indir> Load images from <indir>.", "indir"});
    parser.addOption({{"o", "output"}, "-o <outdir> Save images to <outdir>.", "outdir"});
    parser.addOption({{"m", "mode"}, "-m <value> set mode of train data.\n"
                                     "=======================\n"
                                     "Image_RGB8 = 0\n"
                                     "Image_RGB888 = 1\n"
                                     "Image_RGBA8888 = 2\n"
                                     "Text = 3\n"
                                     "Binary = 4\n"
                                     "=======================\n", "value"});
    parser.addOption({{"g", "gen"}, "-g <format> generate train data archive file with format\n"
                                    "=======================\n"
                                    "TEXT = 0\n"
                                    "NDT = 1\n"
                                    "ALL = 3\n"
                                    "=======================\n", "format"});
    parser.addOption({{"C", "copyright"}, "Copyright @2023 qAITool Developments."}); // no value

    parser.addHelpOption();

    parser.process(app);

    if(parser.isSet("C"))
    {
        qInfo()<<R"(
  ___      _    ___ _____           _
 / _ \    / \  |_ _|_   _|__   ___ | |
| | | |  / _ \  | |  | |/ _ \ / _ \| |
| |_| | / ___ \ | |  | | (_) | (_) | |
 \__\_\/_/   \_\___| |_|\___/ \___/|_|
        )";
        qInfo()<<"Copyright @2023 QAITool Developments.";
        qInfo()<<"License: GPLv3.";
        return 0;
    }

    FTrainDataParam param;
    //CTrainDataBundle trainDataBundle(param);

    //qInfo()<<"Please use -i for input <indir>, -o for output <outdir>";
    if(parser.isSet("i"))
    {
        param.inputDir = parser.value("i");
    }

    if(parser.isSet("o"))
    {
        param.outputdir = parser.value("o");
    }

    qInfo()<<param.inputDir<<"<= in Working_Dir out =>"<<param.outputdir;

    {
        //generate archive train file to output dir.
        if(parser.isSet("m"))
        {
            bool ok =false;
            param.mode = (ETrainDataMode)parser.value("m").toInt(&ok);
            qDebug()<<parser.value("m")<<" mode="<< param.mode <<" ok="<<ok;
        }

        if(parser.isSet("g"))
        {
            bool ok =false;
            param.format = (ETrainFileFormat)parser.value("g").toInt(&ok);
            qDebug()<<parser.value("g")<<" gen="<< param.format <<" ok="<<ok;
        }
#if 0 \
    // todo: convolution
            if(parser.isSet("c"))
            {
                bool ok =false;
                auto convolution_file = parser.value("c").toStdWString();
                qDebug()<<parser.value("c")<<" convolution matrix file ="<<convolution_file;
            }
#endif
    }

    while(1){
        // work
#if 0
            if(parser.isSet("new workmode?"))
            {
                // do something
                break;
            }
#endif

        // default : package train data into a bundle file for training.

        CTrainDataBundle bundler(param);

        bundler.Generate();

        break;
    }


    //return app.exec();

    //system("pause");
    return 0;
}
