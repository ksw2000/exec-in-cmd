# Exec in cmd Manual for Linux (gnome-based)
## Get "permission denied" ?
![permission_denied](https://raw.githubusercontent.com/Hadname/exec-in-cmd/master/Screenshot_linux_permission.png)

Please press `Ctrl + F12` or type `Exec in cmd: init` in command-palette

It will run the following command in terminal:

    sudo chmod -R 777 {atom_packages}/exec-in-cmd/lib

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
* example/
    * out/ _(default output folder name)_
        * p1/
            * a.class
        * b.class
        * c.class
    * p1/
        * a.java    (use package p1)
    * b.java        (not using package)
    * c.java        (not using package)

> Put ".java" in proper folder (version >= 3.1.2)
>
> Put all ".java" in the same folder (version <3.1.2)

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
 | URL_to access_your_PHP    | http://localhost:80/                   |
 | PHP file you want to open | /var/www/test.com/index.php         |
 | We will open              | http://localhostl:80/index.php          |

    xdg-open "http://localhost:80/index.php"

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
    xdg-open "{path}\{filename}{filename_extension}"

Get garbled texts in html file? Try to insert code between &lt;head&gt; &lt;/head&gt;:

    <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>

----
## Hacking
First, the package gets the file's extension, and choose what action should we do in `exec.coffee`.

If this file needs to be compiled, it will be processed by `openLinux`, a program that can detect the kind of file and choose the proper commands to work.

If this file does not need to be compiled, but it needs to be run in terminal, then `exec.coffee` will send proper commands to `openLinux` because if you run these files through `exec.coffee` directly, they will exit (instead of pause) immediately.

If you want to add or change the commands, please modify `lib/openLinux.c` or `lib/exec.coffee` in the package.

* exec-in-cmd /
    * example /
    * lib /
        * exec.coffee
        * openLinux.c
        * openLinux
