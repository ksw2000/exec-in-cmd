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
* Fixed bug: If filename contains "&", open.exe can not work.
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
