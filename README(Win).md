# Exec in cmd Manual for Windows

## .c .cpp

#### Compile (.c)

```sh
disk: & cd "{path}" & chcp 65001 & md "{output_dir}" & cls
gcc "{filename}.c" -O2 -o "{output_dir}{filename}"
```

#### Compile (.cpp)

```sh
disk: & cd "{path}" & chcp 65001 & md "{output_dir}" & cls
g++ "{filename}.cpp" -O2 -o "{output_dir}{filename}"
```

#### Run
```sh
cd "{path}\{output_dir}" & "{filename}.exe"
```

You can just compile without running by `Exec In Cmd:Advance` or `Shift+F12`

You need to install [`MINGW`](http://www.mingw.org/) and set environment variables.

* example/
   * out/ _(default output folder name)_
       * example.exe
   * example.c
   * example.cpp

----
## .go
**Run**

`Exec In Cmd:Exec` or `F12`

```sh
disk: & cd "{path}" & go run "{filename}.go"
```

**Build**

`Exec In Cmd:Advance` or `Shift+F12`
```sh
disk: & cd "{path}" & go build "{filename}.go"
```

You need to install [`GO`](https://golang.org/doc/install) and set environment varibales

such as `GOROOT` and `GOPATH`

* example/
   * bin/
   * pkg/
   * src/
       * example.go

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

You need to install [`JRE (Java Runtime Environment)`](https://www.oracle.com/technetwork/java/javase/downloads/index.html) and set environment variables.</BR>

----
## .js (Node.js)
```sh
disk: & cd "{path}" & node "{filename}.js"
```

You need to install [`Node.js`](https://nodejs.org) and set environment variables.

----
## .php
 ##### For example :
 | #                         | value                               |
 | ----------------------:   |:------------------------------------|
 | root_directory_of_PHP     | C:\MAMP\htdocs\                     |
 | URL_to access_your_PHP    | http://localhost:80/                |
 | PHP file you want to open | C:\MAMP\htdocs\myphp\index.php      |
 | We will open              | http://localhost:80/myphp/index.php |

```sh
start "" "http://localhost:80/myphp/index.php"
```

You need some application which can make you run PHP in your computer. **For example,** [__MAMP__]( https://www.mamp.info/ ).

----
## .rb
```sh
disk: & cd "{path}"  & chcp 65001 & cls & ruby "{filename}.rb"
```
You need to install [`Ruby`](https://www.ruby-lang.org/) and set environment variables.

If you get garbled texts, try to insert following code in the opening of file.

```ruby
#!/usr/bin/ruby -w
# -*- coding: UTF-8 -*-
#coding=utf-8
```

## .rs
#### Compile

```sh
disk: & cd "{path}" & rustc "{filename}.rs" --out-dir "{output_dir}"
```

#### Run

```sh
cd "{path}\{output_dir}" & "{filename}.exe"
```

You need to install [`Rust`](https://www.rust-lang.org/) and set environment variables.

## .py
#### Run
`Exec In Cmd:Exec` or `F12`

```sh
disk: & cd "{path}" & python "{filename}.py"
```

If you get garbled texts, try to insert following code in the opening of file.

```py
# -*- coding: utf-8 -*
```

You need to install [`python`](https://www.python.org/downloads/) and set environment variables.

#### Build ( .py -> .exe )

`Exec In Cmd:Advance` or `Shift+F12`

```sh
disk: & cd "{path}" &  pyinstaller -F  "{filename}.py"
```


If you want to use building feature, please insall `pyinstaller` by command line bellow :

```sh
pip install pyinstaller
```

----
## .R

```sh
disk: & cd "{path}" & chcp 65001 & cls & Rscript "{filename}.R"
```

You need to install [`R`](https://www.r-project.org/) and set environment variables.

----
## .html .htm .pdf .lnk

```sh
start "" "{path}\{filename}{filename_extension}"
```

Get garbled texts in html file? Try to insert code between &lt;head&gt; &lt;/head&gt;:

```html
<meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
```

----
## Another Features
#### Open in command line:

Press `Ctrl+Shift+F12`

```sh
start cmd /k "cd /d "{path}""
```

#### Advance Mode:

Press `Shift+F12`

##### .c .cpp
>
> 0: Compile only  (僅編譯)
>
> 1: Run old       (執行舊檔)
>
> 2: Specify output folder and then compile and run
> (指定輸出資料夾後編譯執行)
>

##### .go .py
>
> 0: Run   (執行)
> 1: Build (建立)
>

----
> `F12` : Normal
>
> `Shift + F12` : Advance
>
> `Ctrl + Shift +F12` : Open command line
----
## Hacking
First, the package catches the file's path, filename,  filename extension, and so on. Then, we deliver the arguments to `open.exe`, a program that can detect the kind of file and choose the proper commands to work.</BR>

If you want to add or change the commands, please modify `lib\open.c` or`lib\advance.h` in the package.

* exec-in-cmd \
    * example \
    * lib \
        * exec.coffee
        * advance.h
        * function.h
        * open.c
        * open.exe
