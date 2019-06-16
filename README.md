# 歡迎使用 (Welcome to Use) Exec-in-cmd
>Exec-in-cmd：以命令提示字元執行檔案 (Execute a file in command line)<BR>
>一鍵編譯執行檔案 (One click to compile and execute the file taht we support)<BR>
>點擊 F12 啟動 (Click F12 to start it).
>
  <img src="https://raw.githubusercontent.com/Hadname/exec-in-cmd/master/Screenshot.png" style="max-width:600px; width:100%;" alt="A screenshot of how Exec-in-cmd works"/>

# 目前支援的格示有 (Support Now)：
## .c
>       cd "{path}" & gcc "{filename}.c" -o "{filename}" & chcp 65001 & md out & cls
>       cd "{path}" & "{filename}.exe"
>需安裝mingw(http://www.mingw.org/) 並設定環境變數。
>
>You need to install mingw(http://www.mingw.org/) and set environment variables.
>
## .cpp
>       cd "{path}" & g++ "{filename}.cpp" -o "{filename}" & chcp 65001 & md out & cls
>       cd "{path}" & "{filename}.exe"
>需安裝mingw(http://www.mingw.org/) 並設定環境變數。
>
>You need to install mingw(http://www.mingw.org/) and set environment variables.
>
## .go
>       cd "{path}" & go run "{filename}.go"
>需安裝go(https://golang.org/doc/install) 並設定環境變數GOROOT GOPATH
>
>You need to install go(https://golang.org/doc/install) and set environment varibales
>such as GOROOT and GOPATH
>
## .java
#### 不使用 package： (Not using packages: )
>       cd "{path}" & md out & cls & javac -encoding UTF-8 -d out -classpath out {filename}.java
>       cd "{path}\out" & java {filename}
#### 使用 package： (Using packages ):
>請將所有java檔放置在同一資料夾，我們會將所有class檔放在適當的資料夾。我們利用 readPackage.exe 取得這個java檔的package名
>
>Please save all ".java" files in the same folder. We will move ".class" to the folder which it should be. We use readPackage.exe to get the package name of this java file.
>
>取得package名：(Get package name: )
>
>       {path_of_open.c}\readPackage.exe -p "{path}"
>執行：(Run .class: )
>
>       cd "{path}\out" & java {package_name}.{filename}
>需安裝jre 並設定環境變數。
>
>You need to install jre and set environment variables.</BR>
## .html .htm .pdf .lnk
>       cd "{path}" & start "" "{filename}{filename extension}"
>需安裝瀏覽器，若有亂碼請試試於&lt;head&gt; &lt;/head&gt;間加入
>
>You need to install a web browser.</BR>
>Get garbled texts? Try to insert code between &lt;head&gt; &lt;/head&gt;:
>
>       <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
>
## .rb
>       cd "{path}"  & chcp 65001 & cls & ruby "{filename}.rb"
>需安裝ruby 並設定環境變數.
>
>You need to install ruby and set environment variables.
>
>若有亂碼請試著在檔案開頭加入：
>
>If you get garbled texts, try to insert following code in the opening of file.
>
>        #!/usr/bin/ruby -w
>        # -*- coding: UTF-8 -*-
>        #coding=utf-8
>
## .py
>       cd "{path}" & python "{filename}.py"
>需安裝python 並設定環境變數
>
>You need to install python and set environment variables.
>
## .R
>       cd "{path}" & chcp 65001 & cls & Rscript "{filename}.R"
>需安裝R 並設定環境變數
>
>You need to install R and set environment variables.
>

# 原理 (How it works)：
>本外掛原理是透過抓取檔案位置、檔案名稱，及副檔名等參數傳送給 open.exe 偵測檔案類型丟給命令提示字元適合的程式碼進行工作。
>若要自行新增或更改方法，可修改本外掛 lib 資料夾內的 open.c 檔案並編譯成 open.exe</BR>
>
>The package catches the file's path, filename, and filename extension. We deliver the arguments to open.exe ,a program that can detect the kind of file and choose the proper commands to work.</BR>
>If you want to add or change the commands, please modify libs/open.c in our package.
>

# 注意 (Notice)
>使用時檔案建議以 UTF-8 進行編碼。
>
>We suggest that you use UTF-8 encoding.

<center>
Made by : Hadname Online (有名線上科技) <BR>
<a href="https://had.name/atom/">https://had.name/atom/</a>
</center>
