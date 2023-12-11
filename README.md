# qaitool
AI tool implement by QT C++

## Language

[English](README.md) | [简体中文](readme_ch.md) | [繁體中文](readme_zh.md)

## Features

[x] QAITool Train Data Bundle

# QAITool Train Data Bundle

This project is a command-line application that helps you to generate a training data bundle for machine learning tasks. It reads images from a specified input directory, processes them according to the specified mode, and then saves them to a specified output directory.

## Build

To build this project, you need to have Qt installed on your machine. You can download it from the [official website](https://www.qt.io/download). After installing Qt, you can use the `qmake` tool to generate a Makefile, and then use `make` to build the project.

Here are the steps to build the project:

1. Open a terminal and navigate to the project directory.
2. Run `qmake` to generate a Makefile.
3. Run `make` to build the project.

```bash
cd /path/to/project
qmake
make
```

After building the project, you will get an executable file.

## Deployment

### Windows

After building the project, you can use the `windeployqt` tool to deploy the application on Windows. The `windeployqt` tool is included in your Qt installation and it will gather all the necessary DLLs and other files to run your application.

Here are the steps to deploy the application:

1. Open a terminal and navigate to the directory containing your built executable.
2. Run `windeployqt`.

```bash
cd /path/to/executable
windeployqt qaitool.exe
```

After running `windeployqt`, you will see a bunch of DLL files and other files in your directory. Now, you can distribute your application along with these files.

### Linux

On Linux, you can use the `linuxdeployqt` tool to deploy your application. This tool is not included in the Qt installation, but you can download it from the [GitHub repository](https://github.com/probonopd/linuxdeployqt).

Here are the steps to deploy the application:

1. Download `linuxdeployqt` from the GitHub repository and make it executable.
2. Open a terminal and navigate to the directory containing your built executable.
3. Run `linuxdeployqt`.

```bash
cd /path/to/executable
./linuxdeployqt qaitool
```

After running `linuxdeployqt`, you will get an AppImage file, which is a standalone executable file that includes all the necessary libraries and resources. You can distribute this AppImage file to your users.

## How to Use

The application accepts several command-line options:

- `-i <indir>`: Load images from `<indir>`.
- `-o <outdir>`: Save images to `<outdir>`.
- `-m <value>`: Set the mode of train data. The available modes are:
  - `Image_RGB8 = 0`
  - `Image_RGB888 = 1`
  - `Image_RGBA8888 = 2`
  - `Text = 3`
  - `Binary = 4`
- `-g <format>`: Generate train data archive file with format. The available formats are:
  - `TEXT = 0`
  - `NDT = 1`
  - `ALL = 3`
- `-C`: Display copyright information.

You can also use `-h` or `--help` to display the help information.

## Example

To load images from the directory `input`, process them in `Image_RGB8` mode, and save them to the directory `output` in `TEXT` format, you can use the following command:

```bash
./QAITool -i input -o output -m 0 -g 0
```

## Packaging File Formats

### Label.txt format

The i-th row represents the label with target value i

### TEXT Format

In the TEXT format, each training sample is saved as a line of text. The first number on each line is the target value, followed by the pixel values of the image. The pixel values are arranged in row-major order. Each number is separated by a space.

Here's an example of the TEXT format:

```
0 255 255 255 0 0 0 ...
1 0 0 0 255 255 255 ...
...
```

In this example, the first line represents a training sample with a target value of 0, and the pixel values of the image are 255, 255, 255, 0, 0, 0, etc. The second line represents a training sample with a target value of 1, and the pixel values of the image are 0, 0, 0, 255, 255, 255, etc.

### NDT Format

The NDT format is a binary format used for saving training data. It first writes a version number, then the number of inputs and outputs. Next, it writes the lengths and contents of the prefix and suffix. Then, it writes the number of images, as well as the number of rows and columns in each image. Next, it writes the pixel values of each image in row-major order. Finally, it writes the number of target values, as well as the number of rows and columns in each target value. For each target value, it writes a vector where the element at the index equal to the target value is 0.99, and all other elements are 0.01.

Here's an example of the NDT format (in bytes):

```
01 00 00 00 03 00 00 00 02 00 00 00 05 00 00 00 74 72 61 69 6E 03 00 00 00 6E 64 74 02 00 00 00 01 00 00 00 03 00 00 00 ...
```

In this example, the version number is 1, the number of inputs is 3, the number of outputs is 2, the prefix is "train", the suffix is "ndt", the number of images is 2, each image has 1 row and 3 columns, the pixel values are ..., the number of target values is ..., each target value has ... rows and ... columns, the vector values are ....


## License

This project is licensed under the GPLv3.

## Copyright

Copyright @2023 QAITool Developments.