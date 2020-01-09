## 3.0.2
* Add C#
* Turn on optimization flags -O2 for C and C++
* Fix bug
    * We didn't support the file in the disk taht is different from exec.coffee. But now, we can.
    * In the past, we didn't notice that `cd` can only change directory in the same disk.

## 3.0.1
* Fix bug in ( exec.coffee )

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
