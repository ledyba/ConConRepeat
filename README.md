# ConConRepeat（こんこんリピート）

A software to create gif-movie from animation video files.

アニメの動画を与えると、自動でリピート動画を作ってくれるソフトウェア

# Samples

![]()

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
bash run.sh anime.mkv
./ConConRepeat anime.mkv output-dir <skip-duration-in-ms>
```

# こんこんリピートって何？

　サンプルの最後の３つの動画は「[いなり、こんこん、恋いろは。](http://inarikonkon.jp/)」の限定OVAにだけ出てくるコンちゃん（顕現バージョン）です。つまり、そういうことです。
