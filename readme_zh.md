# qaitool
使用QT C++實作的AI工具
(中文 readme 由 AI 自動生成，如有錯誤歡迎指出)

## 語言

[繁體中文](readme_ch.md) |  [簡體中文](readme_ch.md) | [英文](README.md)

## 工作流程：打包待訓練的AI圖片

1. 在編譯的qaitool同級目錄下新建`./input/`和`./output/`兩個資料夾。
2. 在`input/`中按圖片分類 label 建立資料夾，每個資料夾名字為對應的 `<label>/`
3. 將所有圖片匯入到對應的`input/<label>`資料夾下
4. 執行`./QAITool -i input -o output -m 0 -g 2`在`output/`資料夾下產生所有打包文件
5. 將打包檔案匯入AI軟體進行學習、訓練和測試

## 功能


- [x]  QAITool Train Data Bundle  打包AI訓練數據


# QAITool Train Data Bundle 打包AI訓練數據

這個專案是一個命令列應用程序，它可以幫助你產生用於機器學習任務的訓練資料包。 它從指定的輸入目錄讀取影像，根據指定的模式處理它們，然後將它們儲存到指定的輸出目錄。

## 建構

要建置此項目，你需要在你的機器上安裝Qt。 你可以從[官方網站](https://www.qt.io/download)下載。 安裝Qt後，你可以使用`qmake`工具產生Makefile，然後使用`make`來建置專案。

以下是建置專案的步驟：

1. 開啟終端並導航至專案目錄。
2. 執行`qmake`產生Makefile。
3. 運行`make`建置專案。

```bash
cd /path/to/project
qmake
make
```

建置專案後，你將得到一個可執行檔。

## 部署

### Windows

建置專案後，你可以使用`windeployqt`工具在Windows上部署應用程式。 `windeployqt`工具包含在你的Qt安裝中，它將收集執行你的應用程式所需的所有DLL和其他檔案。

以下是部署應用程式的步驟：

1. 開啟終端並導覽到包含你的建置執行檔的目錄。
2. 執行`windeployqt`。

```bash
cd /path/to/executable
windeployqt qaitool.exe
```

執行`windeployqt`後，你將在你的目錄中看到一堆DLL檔案和其他檔案。 現在，你可以將你的應用程式連同這些檔案一起分發。

### Linux

在Linux上，你可以使用`linuxdeployqt`工具部署你的應用程式。 這個工具不包含在Qt安裝中，但你可以從[GitHub倉庫](https://github.com/probonopd/linuxdeployqt)下載。

以下是部署應用程式的步驟：

1. 從GitHub倉庫下載`linuxdeployqt`並使其可執行。
2. 開啟終端並導覽到包含你的建置執行檔的目錄。
3. 執行`linuxdeployqt`。

```bash
cd /path/to/executable
./linuxdeployqt qaitool
```

執行`linuxdeployqt`後，你將會得到一個AppImage文件，這是一個包含所有必要函式庫和資源的獨立執行檔。 你可以將這個AppImage檔案分發給你的用戶。

## 如何使用

該應用程式接受幾個命令列選項：

- `-i <indir>`：從`<indir>`載入映像。
- `-o <outdir>`：將影像儲存到`<outdir>`。
- `-m <value>`：設定訓練資料的模式。 可用的模式有：
   - `Image_RGB8 = 0`
   - `Image_RGB888 = 1`
   - `Image_RGBA8888 = 2`
   - `Text = 3`
   - `Binary = 4`
- `-g <format>`：以格式產生訓練資料存檔檔案。 可用的格式有：
   - `TEXT = 0`
   - `NDT = 1`
   - `ALL = 3`
- `-C`：顯示版權資訊。

你也可以使用`-h`或`--help`顯示幫助資訊。

## 範例

要從`input`目錄載入圖像，以`Image_RGB8`模式處理它們，並將它們以`TEXT`格式儲存到`output`目錄，你可以使用以下命令：

```bash
./QAITool -i input -o output -m 0 -g 0
```

## 打包文件格式

### Label.txt 格式

第i行代表目標值i的label

### TEXT 格式

在TEXT格式中，每個訓練樣本都被儲存為一行文字。 每行的第一個數字是目標值，後面的數字是影像的像素值。 像素值是按照影像的行優先順序排列的。 每個數字之間以空格分隔。

以下是TEXT格式的範例：

```
0 255 255 255 0 0 0 ...
1 0 0 0 255 255 255 ...
…
```

在這個例子中，第一行表示目標值為0的訓練樣本，其影像的像素值為255, 255, 255, 0, 0, 0等。 第二行表示目標值為1的訓練樣本，其影像的像素值為0, 0, 0, 255, 255, 255等。

### NDT 格式

NDT格式是一種二進位格式，用於儲存訓練資料。 它首先寫入一個版本號，然後寫入輸入和輸出的數量。 接下來，它寫入前綴和後綴的長度和內容。 然後，它寫入圖像的數量，以及每個圖像的行數和列數。 接下來，它會按行優先順序寫入每個影像的像素值。 最後，它寫入目標值的數量，以及每個目標值的行數和列數。 對於每個目標值，它寫入一個向量，該向量的長度等於標籤的數量，如果索引等於目標值，則向量的元素值為0.99，否則為0.01。

以下是NDT格式的範例（以位元組為單位）：

```
01 00 00 00 03 00 00 00 02 00 00 00 05 00 00 00 74 72 61 69 6E 03 00 00 00 6E 64 74 0200 03 0000 00 0001
```

在這個例子中，版本號為1，輸入數量為3，輸出數量為2，前綴為"train"，後綴為"ndt"，圖像數量為2，每個圖像的行數為1，列數為3 ，像素值為...，目標值的數量為...，每個目標值的行數為...，列數為...，向量值為...。

## 許可證

GPLv3

## 版權

Copyright @2023 QAITool Developments.