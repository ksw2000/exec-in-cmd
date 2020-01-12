# Exec in cmd Manual for Mac OS
## Nothing happens ?

Please press `Control + F12` or type `Exec in cmd: init` in command-palette

It will run the following command in terminal:

    chmod -R 755 {exec-in-cmd-root}/lib

---
## .c .cpp
##### C :
    cd "{path}"; mkdir -p "{outputFolder}" ; gcc "{filename}.c" -lm -O2 -o "{outputFolder}/{filename}"
    cd "{path}/{outputFolder}" ; "./{filename}"
##### C++ :
    cd "{path}"; mkdir -p "{outputFolder}" ; g++ "{filename}.cpp" -lm -O2 -o "{outputFolder}/{filename}"
    cd "{path}/{outputFolder}" ; "./{filename}"

You need to install `gcc` and `g++`

* example/
   * out/ _(default output folder name)_
       * example.exe
   * example.c
   * example.cpp

----
## .go
    cd "{path}" ; go run "{filename}.go"

You need to install [`GO`](https://golang.org/doc/install).

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

    cd "{path}" ; mkdir -p {outputFolder} ; javac -encoding UTF-8 -d {outputFolder} -classpath {outputFolder} {filename}.java

##### 取得package名：(Get package name)

    {exec-in-cmd-root}/lib/readPackageDarwin.exe -p "{path}"

##### 執行：(Run)

    // Use package
    cd "{path}/{outputFolder}" ; java {package_name}.{filename}

    // Not use package
    cd "{path}/{outputFolder}" ; java {filename}

You need to install `javac` and `java`.

----
## .js (Node.js)
    cd "{path}" ; node "{filename}.js"
You need to install [`Node.js`](https://nodejs.org).

----
## .php
 ##### For example :
 |                           |                                     |
 | ----------------------:   |:------------------------------------|
 | root_directory_of_PHP     | /var/www/test.com/                  |
 | URL_to access_your_PHP    | http://localhost/                   |
 | PHP file you want to open | /var/www/test.com/index.php         |
 | We will open              | http://localhost/index.php          |

    open -a Terminal "http://localhost/index.php"

You need some application which can make you run PHP in your computer.

----
## .rb
       cd "{path}" ; ruby "{filename}.rb"
You need to install [`Ruby`](https://www.ruby-lang.org/).

If you get garbled texts, try to insert following code in the opening of file.

        #!/usr/bin/ruby -w
        # -*- coding: UTF-8 -*-
        #coding=utf-8

----
## .py
    cd "{path}" ; python "{filename}.py"

If you get garbled texts, try to insert following code in the opening of file.

    # -*- coding: utf-8 -*

Yout need to install [`python`](https://www.python.org/downloads/).

----
## .R
    cd "{path}" ; Rscript "{filename}.R"

You need to install [`R`](https://www.r-project.org/).

----
## .html .htm .pdf
    open "{path}\{filename}{filename_extension}"

Get garbled texts in html file? Try to insert code between &lt;head&gt; &lt;/head&gt;:

    <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>

----
## Hacking
First, the package gets the file's extension, and choose what action should we do in `exec.coffee`.

If this file needs to be compiled, it will be processed by `./openDarwin`, a program that can detect the kind of file and choose the proper commands to work.

If this file does not need to be compiled, but it needs to be run in terminal, then `exec.coffee` will send proper commands to `openLinux` because if you run these files through `exec.coffee` directly, they will exit (instead of pause) immediately.

If you want to add or change the commands, please modify `lib/openLinux.c` or `lib/exec.coffee` in the package.

* exec-in-cmd /
    * example /
    * lib /
        * exec.coffee
        * openDarwin.c
        * openDarwin
        * readPackage.go
        * readPackageDarwin
