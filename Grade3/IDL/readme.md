# IDL二次开发作业

---

---

## 开发背景

在使用 Landsat 图像时，我们往往需要对图像进行预处理和波段运算等处理，而这种处理往往是批量的，这种批量的操作重复量大，逐个操作的话比较麻烦。为了使得使用 Landsat 的用户在进行相关处理时能节省精力，本项目使用 IDL 语言基于 ENVI 接口进行二次开发，实现了对 Landsat4-8 的 TM/ETM+/OLI 的图像预览、批量裁剪、批量快速大气校正、批量波段运算等实用功能。

更多细节请参考pdf文档[Landsat batch-批量流程工具使用说明 ](https://github.com/codeRimoe/homework/blob/master/Grade3/IDL/Landsat_batch_Introduction.pdf)

---

## 功能简介

1.添加图像、设置输出路径
a) 使用 Add Files... 按钮或 File 菜单中的 Add Files... 可以添加文件，允许批量添加，对于相同的文件不会重复添加，添加的文件会显示在 File List 列表中，并将参与批量操作。
b) 使用 Set Path... 按钮或 File 菜单中的 Set Path... 可以设置文件输出路径，设置的路径将在 Set Path 文本框中显示。
2.图像预览
双击 File List 中的文件，在界面右下方 Overview 会显示影像预览。影像预览经过直方图均衡化处理，以真彩色（R-G-B 波段）合成显示。
3.批处理模块
本工具所有模块只对 Landsat 的多波段图像进行处理，即不包括 TIR、Pan 等波段。
a) 裁剪（Clip）
点击 Set.. 设置裁剪区域，需要输入左上角和右下角两个点坐标，可以为地图坐标，也可以为经纬度，若为经纬度，需要勾选选项。确定后，在主界面会显示裁剪区域设置情况。
若无需裁剪，则不需设置，或全部输入为零清空之前的设置。
若设置了裁剪，可以选择需要保留的波段，但必须选择卫星（传感器）。
b) 大气校正（Atom Corr）
目前只支持快速大气校正（QUAC），若需要使用大气校正功能，勾选即可。
c) 波段运算（Band math）
输入波段运算公式，具体格式同 ENVI 内的 bandmath 工具，点击 OK 设置公式。
若无进行裁剪或裁剪时无筛选波段，按 Landsat 多波段图像顺序排列，波段代号为：
Landsat 4-5/7 - b1:B b2:G b3:R b4:NIR b5:SWIR1 b6:SWIR2
Landsat 8 - b1:Coast b2:B b3:G b4:R b5:NIR b6:SWIR1 b7:SWIR2
若进行裁剪并筛选波段，依据裁剪后波段顺序排序，波段代号在选项区上方有提示。
4.执行操作与退出
a) 点击 Proceed 按钮弹出 Confirm 对话框，提示将要执行的文件数以及任务。点击Confirm 对话框的 Proceed Now 按钮即开始一键执行操作，任务执行期间会提示目前操作状况。
b) 点击 File 菜单中的 Exit 按钮，将询问是否退出。

---

## 版权声明

Landsat Batch v0.5.4_release
This is a programe for pre-processing Landsat(Mul) Image, develop based on ENVI API.
Batch task is supoorted, which is convenient to study.
Now Landsat 4-5/7/8 is supported.
Author: Yue H.W. Luo, School of Geography and Planning, Sun-Yatsen University
Website: [http://rimoe.ml](http://rimoe.ml)
E-mail: yue.rimoe@gmail.com
License: Apache v2.0
TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
Copyright 2017 Yue H.W. Luo, yue.rimoe@gmail.com .
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
file except in compliance with the
License. You may obtain a copy of the License at
[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS"
BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific
language governing permissions and limitations under the License. 