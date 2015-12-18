# ConConRepeat（こんこんリピート）

A software to create endless-gif-loops from animation video files.

アニメの動画を与えると、自動でリピート動画を作ってくれるソフトウェア

# Samples

![](https://raw.githubusercontent.com/ledyba/ConConRepeat/master/sample/sample1.gif)

![](https://raw.githubusercontent.com/ledyba/ConConRepeat/master/sample/sample2.gif)

![](https://raw.githubusercontent.com/ledyba/ConConRepeat/master/sample/sample3.gif)

![](https://raw.githubusercontent.com/ledyba/ConConRepeat/master/sample/sample4.gif)

![](https://raw.githubusercontent.com/ledyba/ConConRepeat/master/sample/sample5.gif)


# How to run?

## Prerequisites

 - CMake
 - OpenCV
 - ImageMagick

```bash
sudo apt-get install libopencv-dev cmake imagemagick
```

## Build Instruction

```bash
cmake .
make
bash run.sh anime.mkv output-dir <skip-duration-in-sec>
```

# こんこんリピートって何？

　サンプルの最後の３つの動画は「[いなり、こんこん、恋いろは。](http://inarikonkon.jp/)」の限定OVAにだけ出てくるコンちゃん（顕現バージョン）です。つまり、そういうことです。
