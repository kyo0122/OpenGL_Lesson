# このプロジェクトについて
- 開発環境
  - MacOS X El Capitan (10.11.4)
  - Xcode7.3
  - [Homebrew](https://brew.sh/index_ja.html)
  - 使用する(もしくは予定がある)ライブラリ
    - [assimp](http://assimp.org)
      - 3Dファイルを色々読み込むことができる。  
        ライセンスは三条項BSD。
    - [glfw3](http://www.glfw.org)
      - OpenGLを簡単に扱えるようにする。  
        ライセンスはzlib/libpng。
    - [glew](http://glew.sourceforge.net)
      - OpneGLを拡張してくれる。  
        ライセンスは[ちょっと特殊](http://glew.sourceforge.net/glew.txt)。
    - [glm](https://www.opengl.org/sdk/libs/GLM/)
      - 行列計算などを楽にしてくれる。
        ライセンスは[これ](https://github.com/g-truc/glm/blob/master/manual.md#section0)。
    - [libpng](http://libpng.org/pub/png/libpng.html)
      - png画像を読み込める。
        ライセンスはlibpng。
    - [ImGui](https://github.com/ocornut/imgui)
      - OpneGLでUIを簡単に用意できる。
        ライセンスはMIT。

Homebrewは、ターミナルを起動して  
`/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`  
と打ち込むことによってインストールできます。  
詳細は公式サイトに載っていますので、そちらを確認してください。  

使用する各ライブラリは、  
`brew install assimp glfw glew glm libpng`  
と入力することでインストールできます。  

## 機能ごとのリポジトリ確認方法

![いい感じに画像が表示されているはず！](/images/how_to_switch01.png)  
左上の **Branch: develop▼** を選択して

![でもこの文字が表示されてるってことは…](/images/how_to_switch02.png)  
**Tags** を選択すると、大体の機能実装毎にタグをつけています。

選択すると、機能が実装された直後のリポジトリに変わります。  
元のブランチ戻す時も、同じ要領で **Tag: hogehoge▼** を選択して、
**Branches** から **develop** を選択してください。

好きなブランチ(又はタグ)を選択できたら、  
![ダメだったってことだよね…](/images/how_to_clone01.png)  
右上の緑のボタンをクリックして、**Download ZIP** をクリック。  
プロジェクトフォルダごとダウンロードできます。


## ソースコードが汚い！ フォルダ分けがなってない！...etc.

新しい技術知識に加えて、汚れたソースコードを読む…心中お察しします。  
是非ともプルリクエストを送ってください。  
バグも結構あると思うので、手をあげる or Classroom or issue で気軽にお知らせください。  
Gitの練習だと思ってガンガン送ってくださって結構です:thumbsup:  
