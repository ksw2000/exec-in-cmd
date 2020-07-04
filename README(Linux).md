# Exec in cmd Manual for Linux

We support `gnome-terminal` and `konsole`(v3.2.4)

## Get "permission denied" ?
![permission_denied](https://raw.githubusercontent.com/Hadname/exec-in-cmd/master/Screenshot_linux_permission.png)

Please press `Ctrl + F12` or type `Exec in cmd: init` in command-palette

It will run the following command in terminal:

```sh
sudo chmod -R 777 {atom_packages}/exec-in-cmd/lib
```

---
## .asm
#### Assembling (nasm)
flag : `elf` or `elf64`
```sh
cd "{path}"; mkdir -p "{output_dir}"; nasm -f {flag} "{filename}.asm" -o "{output_dir}/{filename}.o"
```

#### Link (binutils)
```sh
cd "{path}/{output_dir}"; ld -s -o "{filename}" "{filename}.o"
```

#### Run
```sh
cd "{path}/{output_dir}"; "./{filename}"
```

#### Install
```sh
# install nasm
sudo apt-get install nasm

# install binutils
sudo apt-get install binutils
```

---
## .c .cpp

#### Compile (.c)

```sh
cd "{path}"; mkdir -p "{output_dir}";
gcc "{filename}.c" -lm -O2 -o "{output_dir}/{filename}"
```
#### Compile (.cpp)

```sh
cd "{path}"; mkdir -p "{output_dir}";
g++ "{filename}.cpp" -lm -O2 -o "{output_dir}/{filename}"
```

#### Run

```sh
cd "{path}/{output_dir}"; "./{filename}"
```

You need to install `gcc` and `g++`

* example/
   * out/ _(default output folder name)_
       * example
   * example.c
   * example.cpp

----
## .cs

#### Compile
```sh
cd "{path}"; mkdir -p "{output_dir}"; mcs -out:"{filename}.exe"
```

#### Run
```sh
cd "{path}/{output_dir}" ; mono "{filename}.exe"
```

You need to install [`mono`](https://www.mono-project.com/)

* example/
   * out/ _(default output folder name)_
       * example.exe
   * example.cs

----
## .go
```sh
cd "{path}" ; go run "{filename}.go"
```
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

version >= 3.1.2
> Put ".java" in the folder which is same as package name

version <3.1.2
> Put all ".java" in the same folder

----
## .js (Node.js)

```sh
cd "{path}" ; node "{filename}.js"
```
You need to install [`Node.js`](https://nodejs.org).

----
## .php
 ##### For example :
 | #                         | value                               |
 | ----------------------:   |:------------------------------------|
 | root_directory_of_PHP     | /var/www/test.com/                  |
 | URL_to access_your_PHP    | http://localhost:80/                |
 | PHP file you want to open | /var/www/test.com/index.php         |
 | We will open              | http://localhostl:80/index.php      |

```sh
xdg-open "http://localhost:80/index.php"
```

You need some application which can make you run PHP in your computer (server).

----
## .rb
```sh
cd "{path}" ; ruby "{filename}.rb"
```
You need to install [`Ruby`](https://www.ruby-lang.org/).

If you get garbled texts, try to insert following code in the opening of file.

```ruby
#!/usr/bin/ruby -w
# -*- coding: UTF-8 -*-
#coding=utf-8
```

----
## .rs

#### Compile
```sh
cd "{path}"; rustc "{filename}.rs" --out-dir "{output_dir}"
```

#### Run
```sh
cd "{path}/{output_dir}" ; "./{filename}"
```
You need to install [`Rust`](https://www.rust-lang.org/).

----
## .py
```sh
cd "{path}" ; python "{filename}.py"
```

If you get garbled texts, try to insert following code in the opening of file.

```py
# -*- coding: utf-8 -*
```

Yout need to install [`python`](https://www.python.org/downloads/).

----
## .R
```sh
cd "{path}" ; Rscript "{filename}.R"
```

You need to install [`R`](https://www.r-project.org/).

----
## .html .htm .pdf

```sh
xdg-open "{path}\{filename}{filename_extension}"
```

Get garbled texts in html file? Try to insert code between &lt;head&gt; &lt;/head&gt;:

```html
<meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
```

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
