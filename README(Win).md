# Exec in cmd Manual for Windows

## .c .cpp
##### C :
       cd "{path}" & chcp 65001 & md {outputFolder} & cls & gcc "{filename}.c" -o "{filename}"
       cd "{path}\{outputFolder}" & "{filename}.exe"
##### C++ :
       cd "{path}" & chcp 65001 & md {outputFolder} & cls & g++ "{filename}.cpp" -o "{filename}"
       cd "{path}\{outputFolder}" & "{filename}.exe"

You can just compile without running (僅編譯不執行) by `Exec In Cmd:Advance` or `Shift+F12`

You need to install [`MINGW`](http://www.mingw.org/) and set environment variables.

* example/
   * out/ _(default output folder name)_
       * example.exe
   * example.c
   * example.cpp

----
## .go
##### Run :
`Exec In Cmd:Exec` or `F12`

       cd "{path}" & go run "{filename}.go"

##### Build :
`Exec In Cmd:Advance` or `Shift+F12`

       cd "{path}" & go build "{filename}.go"

You need to install [`GO`](https://golang.org/doc/install) and set environment varibales

such as `GOROOT` and `GOPATH`

* example/
   * bin/
   * pkg/
   * src/
       * example.go

----
## .java
__請將所有java檔放置在同一資料夾__，我們會將所有class檔放在適當的資料夾。我們利用 readPackage.exe 取得這個java檔的package名

Please __save all ".java" files in the same folder__. We will move ".class" to the folder which it should be. We use readPackage.exe to get the package name of this java file.


* example/
   * out/ _(default output folder name)_
       * p1/
           * a.class
       * b.class
       * c.class
   * a.java (use package p1)
   * b.java
   * c.java

##### 編譯：(Compile)

       cd "{path}" & md {outputFolder} & cls & javac -encoding UTF-8 -d {outputFolder} -classpath {outputFolder} {filename}.java

##### 取得package名：(Get package name)

       {exec-in-cmd-root}\lib\readPackage.exe -p "{path}"
##### 執行：(Run)

       // Use package
       cd "{path}\{outputFolder}" & java {package_name}.{filename}

       // Not use package
       cd "{path}\{outputFolder}" & java {filename}

You can just compile without running (僅編譯不執行) by `Exec In Cmd:Advance` or `Shift+F12`

You need to install [`JRE (Java Runtime Environment)`](https://www.oracle.com/technetwork/java/javase/downloads/index.html) and set environment variables.</BR>

----
## .js (Node.js)
       cd "{path}" & node "{filename}.js"
You need to install [`Node.js`](https://nodejs.org) and set environment variables.

----
## .php
 ##### For example :
 |                           |                                     |
 | ----------------------:   |:------------------------------------|
 | root_directory_of_PHP     | C:\MAMP\htdocs\                     |
 | URL_to access_your_PHP    | http://localhost:81/                |
 | PHP file you want to open | C:\MAMP\htdocs\myphp\index.php      |
 | We will open              | http://localhost:81/myphp/index.php |

       start "" "http://localhost:81/myphp/index.php"

You need some application which can make you run PHP in your computer, for example [__MAMP__]( https://www.mamp.info/ ).

----
## .rb
       cd "{path}"  & chcp 65001 & cls & ruby "{filename}.rb"
You need to install [`Ruby`](https://www.ruby-lang.org/) and set environment variables.

若有亂碼請試著在檔案開頭加入：

If you get garbled texts, try to insert following code in the opening of file.

        #!/usr/bin/ruby -w
        # -*- coding: UTF-8 -*-
        #coding=utf-8

## .py
##### Run :
`Exec In Cmd:Exec` or `F12`

       cd "{path}" & python "{filename}.py"

若有亂碼請試著在檔案開頭加入：

If you get garbled texts, try to insert following code in the opening of file.

      # -*- coding: utf-8 -*
##### Build : ( .py -> .exe )
`Exec In Cmd:Advance` or `Shift+F12`

       cd "{path}" &  pyinstaller -F  "{filename}.py"
You need to install [`python`](https://www.python.org/downloads/) and set environment variables.

如果你要使用 Build 功能，請先透過命令提示字元安裝 `pyinstaller`：<br>
If you want to use building feature, please insall `pyinstaller` by command line bellow :

     pip install pyinstaller

----
## .R
       cd "{path}" & chcp 65001 & cls & Rscript "{filename}.R"

You need to install [`R`](https://www.r-project.org/) and set environment variables.

----
## .html .htm .pdf .lnk
       start "" "{path}\{filename}{filename_extension}"
需安裝瀏覽器 (You need to install a web browser)

若HTML檔有亂碼請試試於&lt;head&gt; &lt;/head&gt;間加入

Get garbled texts in html file? Try to insert code between &lt;head&gt; &lt;/head&gt;:

       <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>

----
## Another Features
#### Open in command line:

Press `Ctrl+Shift+F12`

     start cmd /k "cd /d "{path}""


#### Advance Mode:

Press `Shift+F12`

##### .c .cpp .java
     0: Compile only  (僅編譯)
     1: Run old       (執行舊檔)
     2: Specify output folder and then compile and run
                      (指定輸出資料夾後編譯執行)

##### .go .py
     0: Run   (執行)
     1: Build (建立)

----
> `F12` : Normal
>
> `Shift + F12` : Advance
>
> `Ctrl + Shift +F12` : Open command line
----
## Hacking
First, the package catches the file's path, filename,  filename extension, and so on. Then, we deliver the arguments to `open.exe`(windows),a program that can detect the kind of file and choose the proper commands to work.</BR>

If you want to add or change the commands, please modify `lib\open.c` or`lib\advance.h` in the package.

* exec-in-cmd \
    * example \
    * lib \
        * exec.coffee
        * advance.h
        * function.h
        * open.c
        * open.exe
        * readPackage.go
        * readPackage.exe
