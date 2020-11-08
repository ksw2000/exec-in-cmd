# Exec in cmd Manual for Mac OS
## Nothing happens ?

Please press `Control + F12` or type `Exec in cmd: init` in command-palette

It will run the following command in terminal:

```sh
chmod -R 755 {exec-in-cmd-root}/lib
```

Another way:

If you have already installed `gcc`, you can compile `/exec-in-cmd/lib/openDarwin.c` to `openDarwin`.

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

Need to install `gcc` and `g++`

* example/
   * out/ _(default output folder name)_
       * example.exe
   * example.c
   * example.cpp

----
## .dart
```sh
cd "{path}" ; dart "{filename}.dart"
```
Need to install [`dart`](https://dart.dev/get-dart).

----
## .go
```sh
cd "{path}" ; go run "{filename}.go"
```
Need to install [`GO`](https://golang.org/doc/install).

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
> Put ".java" in the folder whose name is as same as the package name

version <3.1.2
> Put all ".java" in the same folder

----
## .js (Node.js)

```sh
cd "{path}" ; node "{filename}.js"
```
Need to install [`Node.js`](https://nodejs.org).

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
open -a Terminal "http://localhost:80/index.php"
```

Need some applications that can run PHP on the computer (like a server).

----
## .rb
```sh
cd "{path}" ; ruby "{filename}.rb"
```
Need to install [`Ruby`](https://www.ruby-lang.org/).

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
Need to install [`Rust`](https://www.rust-lang.org/).

----

----
## .py
```sh
cd "{path}" ; python "{filename}.py"
```

If you get garbled texts, try to insert following code in the opening of file.

```py
# -*- coding: utf-8 -*
```

Need to install [`python`](https://www.python.org/downloads/).

----
## .R
```sh
cd "{path}" ; Rscript "{filename}.R"
```

Need to install [`R`](https://www.r-project.org/).

----
## .html .htm .pdf
```sh
open "{path}\{filename}{filename_extension}"
```

Get garbled texts in html file?

Try to insert code between &lt;head&gt; &lt;/head&gt;:

```html
<meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
```

----
## Hacking
First, the package gets the file's extension, and choose what action should we do in `exec.coffee`.

If this file needs to be compiled, it will be processed by `./openDarwin`, a program that can detect the kind of file and choose the proper commands to work.

If this file does not need to be compiled, but it needs to be run in a terminal, then `exec.coffee` will send proper commands to `openDarwin` because if you run these files through `exec.coffee` directly, they will exit (instead of pause) immediately.

If you want to add or change the commands, please modify `lib/openDarwin.c` or `lib/exec.coffee` in the package.

* exec-in-cmd /
    * example /
    * lib /
        * exec.coffee
        * openDarwin.c
        * openDarwin
