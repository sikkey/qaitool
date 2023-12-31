# qaitool
使用QT C++实现的AI工具
(中文 readme 由 AI 自动生成，如有错误欢迎指出)

## 语言

[简体中文](readme_ch.md) | [繁體中文](readme_ch.md) |  [英文](README.md)

## 工作流程：打包待训练的AI图片

1. 在编译出的qaitool同级目录下新建`./input/`和`./output/`两个文件夹。
2. 在`input/`中按图片分类 label 建立文件夹，每个文件夹名字为对应的 `<label>/`
3. 将所有图片导入到对应的`input/<label>`文件夹下
4. 运行`./QAITool -i input -o output -m 0 -g 2`在`output/`文件夹下生成所有打包文件
5. 将打包文件导入到AI软件中进行学习、训练和测试

## 功能

[x] QAITool Train Data Bundle 打包AI训练数据

# QAITool Train Data Bundle 打包AI训练数据

这个项目是一个命令行应用程序，它可以帮助你生成用于机器学习任务的训练数据包。它从指定的输入目录读取图像，根据指定的模式处理它们，然后将它们保存到指定的输出目录。

## 构建

要构建此项目，你需要在你的机器上安装Qt。你可以从[官方网站](https://www.qt.io/download)下载。安装Qt后，你可以使用`qmake`工具生成Makefile，然后使用`make`来构建项目。

以下是构建项目的步骤：

1. 打开终端并导航到项目目录。
2. 运行`qmake`生成Makefile。
3. 运行`make`构建项目。

```bash
cd /path/to/project
qmake
make
```

构建项目后，你将得到一个可执行文件。

## 部署

### Windows

构建项目后，你可以使用`windeployqt`工具在Windows上部署应用程序。`windeployqt`工具包含在你的Qt安装中，它将收集运行你的应用程序所需的所有DLL和其他文件。

以下是部署应用程序的步骤：

1. 打开终端并导航到包含你的构建可执行文件的目录。
2. 运行`windeployqt`。

```bash
cd /path/to/executable
windeployqt qaitool.exe
```

运行`windeployqt`后，你将在你的目录中看到一堆DLL文件和其他文件。现在，你可以将你的应用程序连同这些文件一起分发。

### Linux

在Linux上，你可以使用`linuxdeployqt`工具部署你的应用程序。这个工具不包含在Qt安装中，但你可以从[GitHub仓库](https://github.com/probonopd/linuxdeployqt)下载。

以下是部署应用程序的步骤：

1. 从GitHub仓库下载`linuxdeployqt`并使其可执行。
2. 打开终端并导航到包含你的构建可执行文件的目录。
3. 运行`linuxdeployqt`。

```bash
cd /path/to/executable
./linuxdeployqt qaitool
```

运行`linuxdeployqt`后，你将得到一个AppImage文件，这是一个包含所有必要库和资源的独立可执行文件。你可以将这个AppImage文件分发给你的用户。

## 如何使用

该应用程序接受几个命令行选项：

- `-i <indir>`：从`<indir>`加载图像。
- `-o <outdir>`：将图像保存到`<outdir>`。
- `-m <value>`：设置训练数据的模式。可用的模式有：
  - `Image_RGB8 = 0`
  - `Image_RGB888 = 1`
  - `Image_RGBA8888 = 2`
  - `Text = 3`
  - `Binary = 4`
- `-g <format>`：以格式生成训练数据存档文件。可用的格式有：
  - `TEXT = 0`
  - `NDT = 1`
  - `ALL = 3`
- `-C`：显示版权信息。

你也可以使用`-h`或`--help`显示帮助信息。

## 示例

要从`input`目录加载图像，以`Image_RGB8`模式处理它们，并将它们以`TEXT`格式保存到`output`目录，你可以使用以下命令：

```bash
./QAITool -i input -o output -m 0 -g 0
```

## 打包文件格式

### Label.txt 格式

第i行代表目標值為i的label

### TEXT 格式

在TEXT格式中，每个训练样本都被保存为一行文本。每行的第一个数字是目标值，后面的数字是图像的像素值。像素值是按照图像的行优先顺序排列的。每个数字之间用空格分隔。

以下是TEXT格式的示例：

```
0 255 255 255 0 0 0 ...
1 0 0 0 255 255 255 ...
...
```

在这个例子中，第一行表示目标值为0的训练样本，其图像的像素值为255, 255, 255, 0, 0, 0等。第二行表示目标值为1的训练样本，其图像的像素值为0, 0, 0, 255, 255, 255等。

### NDT 格式

NDT格式是一种二进制格式，用于保存训练数据。它首先写入一个版本号，然后写入输入和输出的数量。接下来，它写入前缀和后缀的长度和内容。然后，它写入图像的数量，以及每个图像的行数和列数。接下来，它按行优先顺序写入每个图像的像素值。最后，它写入目标值的数量，以及每个目标值的行数和列数。对于每个目标值，它写入一个向量，该向量的长度等于标签的数量，如果索引等于目标值，则向量的元素值为0.99，否则为0.01。

以下是NDT格式的示例（以字节为单位）：

```
01 00 00 00 03 00 00 00 02 00 00 00 05 00 00 00 74 72 61 69 6E 03 00 00 00 6E 64 74 02 00 00 00 01 00 00 00 03 00 00 00 ...
```

在这个例子中，版本号为1，输入数量为3，输出数量为2，前缀为"train"，后缀为"ndt"，图像数量为2，每个图像的行数为1，列数为3，像素值为...，目标值的数量为...，每个目标值的行数为...，列数为...，向量值为...。

## 许可证

GPLv3

## 版权

Copyright @2023 QAITool Developments.