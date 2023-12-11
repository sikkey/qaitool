# qaitool
使用QT C++實作的AI工具
(中文 readme 由 AI 自動生成，如有錯誤歡迎指出)

## 語言

[繁體中文](readme_ch.md) |  [簡體中文](readme_ch.md) | [英文](README.md)

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

## 許可證

GPLv3

## 版權

Copyright @2023 QAITool Developments.