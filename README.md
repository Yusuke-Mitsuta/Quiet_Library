# quiet

このライブラリは**C++** において**堅牢性**、**柔軟性**、**簡素性**の３つを高水準で実現した[Array][Array]、[Tuple][Tuple]、[Function][Function]を提供し、型が**複数の要素から構成**されていると捉えられる様になります。

[ライブラリ詳細へ][quiet]
***
## quietを利用するメリット
`クラス`、`関数`の引数が、構成される要素と互換性がある値を、受け取れる様になり、オーバーロード、キャストの手間を削減出来ます。

[詳細の解説へ](Reference/Explanation/merit_0_0.md)    

***
### 環境
|項目|値|
|:-|:-|
ライブラリ種別|ヘッダーオンリー
バージョン|C++ 20
コンパイラ|MSVC 2022
IDE|Visual Studio Community 2022 (ver 17.9.2)

### 備考
コンパイラ**Clang**については、現在**仮対応**になります。
一部コードにて、動作には影響が無い警告が発生しております。

※**Clang** ver 17.0.3にて確認実施

&#13;&#10;

## 連絡先について
#### Disecord: [Quiet_Library_コミュニティー](https://discord.gg/zgcU33nu3x) 
#### mail: ohs15028@gmail.com

&#13;&#10;  
&#13;&#10;  

## ライセンスについて
現在、このライブラリ、及びリファレンスにはライセンスが適用されていません。

このライブラリを評価する目的に限り、**複製**、**改変**が可能です。

***

&#13;&#10;

&#13;&#10;
ライブラリ、及びリファレンスは著作権法に基づき保護されています。    

(C) 2024 Mitsuta Yusuke

[quiet]:Reference/quiet.md
[Array]:Reference/Array/Array.md
[Tuple]:Reference/Tuple/Tuple.md
[Function]:Reference/Function/Function.md   
[Apply]:Reference/Tuple/N_Tuple/Apply.md
