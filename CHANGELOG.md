## 3.3.0
New Feature

* Add Dart

Fix bug

* Fix .js .php .R .ruby relative path problem

## 3.2.4
New Feature
+ You can choose which action to execute .php

    + run in browser

    + run in command line

+ You can choose what terminal you want to use in linux.

    + Gnome terminal

    + Konsole

## 3.2.3
Fix bug [d50c65b](https://github.com/Hadname/exec-in-cmd/commit/d50c65b43778847c878f602421f35145feb36b79) : java package mode error (only under Windows)

> There are a lot of bugs between 3.1.2 and 3.2.3 :roll_eyes: :pensive:

## 3.2.2
Fix bug [dc441d2](https://github.com/Hadname/exec-in-cmd/commit/dc441d27d7254003b0d40e8d07c85c72206188a1) : windwos extflag error (Cannot run .go .js .rb .py .R in windows)

## 3.2.1
Fix bug: [2ba5231](2ba52318a9b7547eb521084f2cb90cd29bc55e38) : windows advance mode error (Cannot use normal mode in windows)

## 3.2.0
+ Add "Rust"
+ Add "Assembly" for linux nasm

## 3.1.2
* Add feature: specify python interpreter

> python example.py
>
> or
>
> python3 example.py

* We use coffeescript instead of golang to detect package name (java). And we support java directory structure.

**New (ver >= 3.1.2)**
> * example/
    * out/ _(default output folder name)_
        * p1/
            * a.class
        * b.class
        * c.class
    * p1/
        * a.java    (use package p1)
    * b.java        (not using package)
    * c.java        (not using package)

**Old (ver < 3.1.2)**
> * example/
    * out/ _(default output folder name)_
        * p1/
            * a.class
        * b.class
        * c.class
    * a.java    (use package p1)
    * b.java        (not using package)
    * c.java        (not using package)

## 3.1.0
* We started to support macOS

## 3.0.2
* Add C# for windows
* Turn on optimization flags -O2 for C and C++
* Fix bug
    * We didn't support the file in the disk taht is different from exec.coffee. But now, we can do.
    * In the past, we didn't notice that `cd` can only change directory in the same disk.

## 3.0.1
* Fix bug in (exec.coffee)

## 3.0.0
* We started to support gnome based Linux

## 2.2.0
* Add "open directory in command line".
    * Press `Ctrl-Shift-F12`.
* Add PHP
    * By specifying the root of workspace and URL.
* Add "advance mode" for Python.
    * You can use `pyinstaller` to build .exe from .py
* Fixed bug: If filename contains "\&", open.exe can not work.
    * Update exec.coffee
* Replace some c code(open.c) by coffeescript code(exec.coffee).

## 2.1.5
* Add Node.js
* Add "advance mode" for GO, C, and C++.

## 2.1.4
* Fix bug: Get java package name (readPackage.go)
    * Rewrite the regexp

## 2.1.3
* Simplify open.c
* Rewrite README.md

## 2.1.2
* Add Ruby

## 2.0.0 - First Release
* First release
