# Exec in cmd

![](https://img.shields.io/apm/dm/exec-in-cmd)

Make it more convenient for running code in Atom. Instead of command line or other IDEs, you just need to press `F12` to run your code.


![preview](https://raw.githubusercontent.com/Hadname/exec-in-cmd/master/Screenshot.png)

# Notice for Linux & MacOS
Please type `Exec in cmd: init` in command-palette for __Linux__ user and __macOS__ user when the first time use to avoid `permission denied`.

Or, you can type these in terminal:

```sh
cd {root of atom}/packages/exec-in-cmd/lib
sudo chmod -R 4777 ./
sudo chown -R root ./
sudo chmod -R u+s ./
```

# Manual
+ Windows : <br>https://github.com/Hadname/exec-in-cmd/blob/master/README(Win).md

+ Linux: <br>https://github.com/Hadname/exec-in-cmd/blob/master/README(Linux).md<br>
We support `Gnome-terminal` and `Konsole`

+ macOS : <br>https://github.com/Hadname/exec-in-cmd/blob/master/README(Mac).md

# Hot Key
`F12` Normal ( Run code )

`Ctrl + Shift +F12` Open command line in windows or open terminal in linux or macOS

`Shift + F12` Advance Mode ( For __windows__ user now )

`Ctrl + F12` Initialize ( for __Linux__ user and __macOS__ user when the first time use )

![permission_denied](https://raw.githubusercontent.com/Hadname/exec-in-cmd/master/Screenshot_linux_permission.png)
If you get __Permission denied__ , please press `Ctrl + F12`

# Support
| Language | Windows x64        | Linux x86_64       | MacOS              |
| -------- | ------------------ | ------------------ | ------------------ |
| Assembly | NASM               | NASM + ld          |                    |
| C        | gcc                | gcc                | gcc                |
| C++      | g++                | g++                | g++                |
| dart     | dart               | dart               | dart               |
| go       | `go run` / `gofmt` | `go run`           | `go run`           |
| java     | java / javac       | java / javac       | java / javac       |
| js       | node               | node               | node               |
| coffee   | coffeescript       | coffeescript       |                    |
| ts       | tsc                | tsc                |                    |
| php      | browser / `php -f` | browser / `php -f` | browser / `php -f` |
| rb       | ruby               | ruby               | ruby               |
| rs       | rustc              | rustc              | rustc              |
| py       | python / python3   | python / python3   | python / python3   |
| R        | Rscript            | Rscript            | Rscript            |
| sh       |                    | terminal           |                    |
| bat      | command line       |                    |                    |


----

Made by [Hadname Online](https://had.name)
