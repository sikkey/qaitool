# algorithm

## CTrainDataBundle::Generate()

1. Query all folders under the parm.inputDir folder, sort them in lexicographic order of folder names, and save them to labels.

2. For each folder under the parm.inputDir folder, traverse all image files (including .png format and .jpg format). For each picture, add the last element of images, and add the last element of targets according to the vector index of the folder name in labels.

3. Generate a label.txt file in the parm.outputDir folder, and write labels elements in each line in order.

4. Generate an ltrain.txt file in the parm.outputDir folder, traverse targets, and save a training sample in each line: the first number is targets[i], leave one space blank, and then output the value of the red channel of images[i] , one space is free for every two values.


# 算法

## CTrainDataBundle::Generate()

1. 查詢parm.inputDir文件夾下所有的文件夾，按文件夾名的字典序排序，保存到labels 。 

2. 針對每一個parm.inputDir文件夾下的文件夾，遍歷所有圖片文件(包括.png格式和.jpg格式)。對於每張圖片，增加到images末尾元素，並根據文件夾名在labels中的vector index，增加targets的末尾元素。 

3. 在parm.outputDir文件夾下生成一個label.txt文件，按順序每行寫入labels元素。 

4. 在parm.outputDir文件夾下生成一個ltrain.txt文件，遍歷targets，每行保存一個訓練樣本：第一個數字是targets[i], 空一格，後面輸出images[i]紅色通道的值，每兩個數值閒空一格

