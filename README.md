# 歡迎使用 (Welcome to Use) Exec-in-cmd
>Exec-in-cmd：以命令提示字元執行檔案 (Execute a file in command line)<BR>
>一鍵編譯執行檔案 (One click to compile and execute the file taht we support)<BR>
>點擊 F12 啟動 (Click F12 to start it).
>
  <img src="https://user-images.githubusercontent.com/50315688/57392898-8b079680-71f4-11e9-96d9-f36b5c9ab264.gif" style="max-width:600px; width:100%;" alt="A screenshot of how Exec-in-cmd works"/>

# 目前支援的格示有 (Support Now)：
## .c
>cd "{path}" & gcc "{filename}.c" -o "{filename}" & chcp 65001 & md out & cls</BR>
>cd "{path}" & "{filename}.exe"</BR>
>需安裝mingw(http://www.mingw.org/) 並設定環境變數。</BR>
>You need to install mingw(http://www.mingw.org/) and set environment variables.
>
## .cpp
>cd "{path}" & g++ "{filename}.cpp" -o "{filename}" & chcp 65001 & md out & cls</BR>
>cd "{path}" & "{filename}.exe"</BR>
>需安裝mingw(http://www.mingw.org/) 並設定環境變數。</BR>
>You need to install mingw(http://www.mingw.org/) and set environment variables.
>
## .go
>cd "{path}" & go run "{filename}.go"</BR>
>需安裝go(https://golang.org/doc/install) 並設定環境變數GOROOT GOPATH
>You need to install go(https://golang.org/doc/install) and set environment varibales
>such as GOROOT and GOPATH

## .java
>cd "{path}" & md out & cls & javac {filename}.java -encoding UTF-8 -d out</BR>
>cd "{path}\\out" & java {filename}</BR>
>需安裝jre 並設定環境變數。</BR>
>You need to install jre and set environment variables.
>
## .html .htm .pdf
>cd "{path}" & start "" "{filename}{filename extension}"</BR>
>需安裝瀏覽器，若有亂碼請試試於&lt;head&gt; &lt;/head&gt;間加入
>
>       <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
>
>You need to install a web browser.</BR>
>Get garbled texts? Try to insert code between &lt;head&gt; &lt;/head&gt;:
>
>       <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
>
>
## .py
>cd "{path}" & python "{filename}.py"</BR>
>需安裝python 並設定環境變數</BR>
>You need to install python and set environment variables.
>
## .R
>cd "{path}" & chcp 65001 & cls & Rscript "{filename}.R"</BR>
>需安裝R 並設定環境變數</BR>
>You need to install R and set environment variables.
>

# 原理 (How it works)：
>本外掛原理是透過抓取檔案位置、檔案名稱，及副檔名等參數傳送給 open.exe 偵測檔案類型丟給命令提示字元適合的程式碼進行工作。</BR>
>若要自行新增或更改方法，可修改本外掛 lib 資料夾內的 open.c 檔案並編譯成 open.exe</BR>
>The package catches the file's path, filename, and filename extension. We deliver the arguments to open.exe ,a program that can detect the kind of file and choose the proper commands to work.</BR>
>If you want to add or change the commands, please modify the file open.c in file libs/ in our package.
>

# 注意 (Notice)
>使用時檔案建議以 UTF-8 進行編碼。</BR>
>We suggest that you use UTF-8 encoding.

# 關於我們 (About)
>來自有名線上科技 (From Hadname Online Technology)
>https://had.name/atom/
>
