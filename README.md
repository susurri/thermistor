# Arduino 用のサーミスタライブラリー

秋月電子通商で購入できる NTC サーミスタを Aruduino で利用するためのライブラリーです。
以下の型番をサポートしています。

* Murata NXFT15WF104FA2B
* Murata NXFT15WB473FA2B
* Semitec 103AT

NXFT15XH103FA2B は後述のフィッティングがきれいにできなかったので
サポートしていません。メーカーの提供している抵抗温度特性表が
間違っている可能性が高いと思われます。

## 使用方法

直列に抵抗を入れて抵抗分圧を測定する回路を想定しています。
直列に入れる抵抗は精度の良いものを使用してください。
抵抗とサーミスタにかける電圧を AREF に入れます。
ライブラリーの使用例は
[examples/thermistor/thermistor.ino](examples/thermistor/thermistor.ino)
にあります。抵抗値(K Ohm) とピン番号を引数にして Thermister_型番 クラスの
インスタンスを生成します。readTempC() メソッドで温度（摂氏）が返ります。

## 解説

### B 定数
 抵抗温度特性表から 
 B = log (r/r0) / (1/(t+k0) - 1/(t0 + k0)) の関係式より
 B 定数温度特性表を作成し、
 B 定数を温度の関数としてフィッテイングします。１次関数ではなく２次もしくは３次
関数を用いています。
bConstant() メソッドに絶対温度を引数として与えると B 定数の値が返ります。

### 温度
読み取った抵抗値 r から温度 t を求めるには
t  = 1 / (log (r/r0) / B(t) + 1/(t0 + k0) ) - k0
を解けば良いのですが、ここでは数値的な近似解を求めています。
readTempC() の中の iteration で、温度差が 0.01度より小さくなった時点で
打ち切りにしています。

## 参考

* [セッピーナの趣味の天文計算  B定数の近似式の作り方 - サーミスタ抵抗値温度変換計算の精度・誤差](http://seppina.cocolog-nifty.com/blog/2015/06/b---d8ec.html)
* [村田製作所 NTC サーミスタ NXF シリーズ](http://www.murata.com/ja-jp/products/thermistor/ntc/nxf)
* [SEMITEC AT サーミスタ](http://www.semitec.co.jp/products/thermo/thermistor/at/)
* [秋月電子通商　サーミスタ](http://akizukidenshi.com/catalog/goods/search.aspx?search=x&keyword=%83T%81%5B%83%7E%83X%83%5E&image=%8C%9F%8D%F5)
