ReadMe.md
====

## 概要
DXライブラリを使用したRPGのサンプルです。  
ただし、dixqさんのhttp://dixq.net/sakuhin.html  
にあるサンプル  
`ゲーム名　：　RPGのサンプル`  
を丸々参考にさせていただいています。というかパクリというレベルです。  
Cで書かれているものをC++で説明(コメント)付で書かせていただきました。  
dxiqさんのホームページ http://dixq.net/

## 使い方
とりあえず動かしてみるのならダウンロード後  
`DxRpgProject/DxRpgProject/`にある  
`DxRpgProject.exe`をダブルクリックすると動きます。  

### 操作方法
矢印ボタン 移動  
Bボタンを押しながら移動 2倍速で移動  
Fボタンを押しながら移動 4倍速で移動  
Eボタンを押しながら移動 エンカウントしない  
Xボタン 決定  
Zボタン キャンセル  

## Visual Studioの設定について
Visual Studio Community 2013 推奨  
http://homepage2.nifty.com/natupaji/DxLib/use/dxuse_vc2013.html  
で説明されている手順でDXライブラリをインストールします。  
なお、DXライブラリのパスは  
`C:\Library\DxLib_VC\DxLibrary`  
としています。  
さらにシステム環境変数に  
`DX_LIB_VC_DIR`  
に上記パス(`C:\Library\DxLib_VC\DxLibrary`)を登録しています。  
このあたりはVisual Studioのプロジェクトの`プロパティ ページ`の  
`追加のインクルードディレクトリ`等を見ていただければわかります。  

## ソースの構成についての説明
プロジェクト以下の`source`フォルダにソースがあります。   
大きく`Sequence`, `Map`, `Battle`のフォルダとこの階層にいくつかファイルがあると思います。  
AppMain.cppのファイルが要はmainです。  
GameControllerクラスがFPSとキー入力の制御を行っています。  
ResourceLoaderクラスは画像と音楽のファイルを読込むクラスです。  
SharedCharacterStatusクラスはHPとかMPとかを持っているクラスです。  
Sequenceクラスがシーンの遷移を制御していてここのクラスの中の処理を   
ぐるぐる回って処理されています。  
最初はMapの画面からスタートして敵にエンカウントしたらバトルとなっています。  
Mapに入っているものはMapに関するキャラクターのデータとかが中心です。  
BattleにはいいているものはBattleに関するキャラクターのデータが中心です。  
ただし、Battleは処理が長いので一部こっちに処理を分割させているものがあります。  

## 処理の説明
もともと書いてあった説明をそのまま載せています。

### 戦闘突入時の処理について
バトルに突入する瞬間、画面を16分割してキャプチャし、その画像を中心から外へむけて座標移動して描画し(※1)、
一定の時間がたつと静止、ある程度静止したら加速度をもって落ちる(※2)ようにしてある。  
※1,2において、毎回同じ描画にならないよう、少々乱数の要素を持たせてある。
x方向y方向にあらかじめ乱数をセットし、その乱数を使って微妙にずらして描画する。


### ATBについて
ATB=アクティブタイムバトル。リアルタイムで戦闘が出来る戦闘システムの事
ATBカウンタ＝最大になるとレインボーになるあのメーターのカウンタ
カウンタは満タンでないときで、増加フラグが立っている時は毎回１増加する。
1秒で60増加し、デフォルトで4秒で満タンにさせるため240で満タンになるようになっている。


### 戦闘中のメニューについて
メニューは何を現在選択しているかという「選択状態」と選択しているｙ座標である「選択位置」から
諸々の計算を行う。
メニューは
「選択項目表示」->(決定を受ける)->「詳細選択項目表示」->(決定を受ける) =行動パターン決定
となっている。

選択状態は決定するごとに100かける。
つまり
「攻撃」の選択が1で有った時、この選択が決定されると選択状態は100になる。
選択状態が100～199の時は、攻撃に関する詳細選択項目を出せばいいことがわかる。
もっと言えば
「魔法」の選択が2で有った時、この選択が決定されると選択状態は200になる。
選択状態が200～299の時は、攻撃に関する詳細選択項目を出せばいいことがわかる。
各選択項目に最大100種類のパターンが持たせられる。

攻撃、を選択・決定し、通常攻撃、をさらに選択・決定した場合、選択状態は10000になる。
選択状態は10000以上なら全ての選択が終了した事がわかる。

0は何をかけても0なので、「選択状態」は最小で1でなければならないため、
最初表示されている

選択            |値   |
:---------------|----:|
攻撃            |1    |
魔法            |2    |
アビリティ      |3    |
アイテム        |4    |
逃げる          |5    |

で対応している。

選択                |値 |
:-------------------|--:|
攻撃                |1  |
-通常攻撃           |100|
-テクニカルアタック |101|

選択                |値 |
:-------------------|--:|
魔法                |2  |
-キュアI            |200|
-エアロ             |201|
-ファイア           |202|
-フリーザ           |203|
-サンダー           |204|

選択                |値 |
:-------------------|--:|
アビリティ          |3  |
-挑発               |300|
-ディフェンダー     |301|

選択                |値 |
:-------------------|--:|
アイテム            |4  |
-略                 |略 |

選択                |値 |
:-------------------|--:|
逃げる              |5  |
-略                 |略 |

つまりこのような対応であり、全てが決定されると詳細選択項目*100の値になる。

一方で選択位置は0から4で対応するので、初期で選択状態は選択位置より+1ということになる

選択位置|選択状態|
-------:|-------:|
0       |       1|
1       |       2|
2       |       3|
3       |       4|
4       |       5|
となるので注意。

### ダメージについて
ダメージは正規分布する乱数を用いて決定している。計算式は以下。  
```
ダメージ = レベル * 2 + ((自分の攻撃力 + 武器の攻撃力)
          - (相手の防御力 + 相手の装備防御力)) * 自分の力 * 乱数1 + 自分の力 * 乱数2
```  
だいたい自分の攻撃力が１あがったり相手の防御力が１下がると
ダメージはだいたい１変化する。
レベルを基本ダメージとして加算するのでレベルが上がるごとにダメージは底上げされる。

## ライセンス

ソースコードに関してはMITライセンス  
その他素材(画像・音楽)については出所が不明なため配布は禁止です。

## 著者

fa11enprince (http://fa11enprince.hatenablog.com/)
