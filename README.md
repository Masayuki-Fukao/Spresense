# Spresense_学生証認識システム
# はじめに

このコードは大学の講義で作成したものである．学生証認識システムはカードをカメラで撮影することで学生証であるかと判断するシステムである．ハードウェアにSPRESENSEを用い，組み込みを想定した作品となっている．

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

1. SDcardに「detect_card.ino」，「get_student_card.ino」をコピーする

2. マッチングする画像を撮影する．(「get_student_card.ino」を実行し，画像を撮影する．）

3. 撮影した画像からピクセル値を取得する．（外部ライブラリを用いて学生証のピクセル値を取得する）

4. 取得したピクセル値で学生証を切り取りSDcard直下に保存する．


## 学生証認識

1. 「detect_card.ino」のコードの画像読み込み部分の画像名を事前準備で取得した画像名に変更する．

2. 「detect_card.ino」を実行し，学生証の認識を行う．


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
