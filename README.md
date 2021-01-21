# Spresense_学生証認識システム
# はじめに

このコードは大学の講義で作成したものである．本システムはカードをカメラで撮影することで学生証であるかと判断するシステムである．ハードウェアにSPRESENSEを用い組み込みを想定した作品となっている．

<div align="center">
<img src= "/images_readme/外観図.jpg" width= "320pix">
</div>


# 機能

・テンプレートマッチングによる学生証の認識


# 工夫点

・テンプレートマッチングの弱点であるピクセルズレによるマッチングミスをハードウェアから自作することで抑制した
・また光源によるマッチングミスは，光源を固定することや，光源に左右されないZNCC(Zero-means Normalized Cross-Correlation)手法を用いて精度向上をはかった

# 実装方法

## 事前準備

テンプレートマッチングであるためあらかじめ画像を取得しておく．


# SysMLモデル

## コンテキスト図

<div align="center">
<img src= "/images_readme/コンテキスト図.png" width= "640pix">
</div>


## 要求図

<div align="center">
<img src= "/images_readme/要求図.png" width= "640pix">
</div>

## アクティビティ図

<div align="center">
<img src= "/images_readme/アクティビティ図.png" width= "640pix">
</div>


## ブロック図

<div align="center">
<img src= "/images_readme/ブロック図.png" width= "640pix">
</div>


## ユースケース図

<div align="center">
<img src= "/images_readme/ユースケース図.png" width= "640pix">
</div>


# LICENSE

MIT
