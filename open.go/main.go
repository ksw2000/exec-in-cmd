package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path"
	"path/filepath"
	"runtime"
	"strings"
	"time"

	"github.com/fatih/color"
	"github.com/go-yaml/yaml"
)

var cd string

func run(arg ...string) time.Duration {
	cmd := exec.Command(arg[0], arg[1:]...)
	cmd.Dir = cd
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	start := time.Now()
	err := cmd.Run()
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s", err)
		return time.Duration(0)
	}
	return time.Since(start)
}

// ./open mode fullpath project-path output-path
func main() {
	defer func() {
		if err := recover(); err != nil {
			color.HiRed("%v", err) // 這已經是頂層的 UI 介面了，想以自己的方式呈現錯誤
		}
		fmt.Println("Press Enter to exit")
		fmt.Scanln()
	}()

	var mode, relative, project, out string
	flag.StringVar(&mode, "mode", "", "Command generator: c, cpp, go, java, ...")
	flag.StringVar(&relative, "file", "", "File path")
	flag.StringVar(&project, "project", "", "Project path")
	flag.StringVar(&out, "out", "./", "Output path")
	flag.Parse()

	// TODO: check flag

	// change dir
	cd = project

	// variable depend on OS
	var executable string
	if runtime.GOOS == "windows" {
		executable = ".exe"
	}

	paths := struct {
		absolute     string // /project/foo/bar.txt			%abs
		project      string // /project						%project
		relative     string // foo/bar.txt					%relative
		ext          string // txt							%ext
		base         string // bar							%base
		relativeBase string // foo/bar						%rbase
		relativeDir  string // foo							%rdir
	}{
		absolute:     path.Join(project, relative),
		project:      project,
		relative:     relative,
		ext:          strings.TrimPrefix(path.Ext(relative), "."),
		base:         strings.TrimSuffix(filepath.Base(relative), path.Ext(relative)),
		relativeBase: strings.TrimSuffix(relative, path.Ext(relative)),
		relativeDir:  filepath.Dir(relative),
	}

	config := "config.yaml"
	content, err := ioutil.ReadFile(config)
	if err != nil {
		panic("Read config error " + err.Error())
	}
	configure := map[string]interface{}{}
	yaml.UnmarshalStrict(content, configure)

	cmds, ok := configure[mode]
	if !ok {
		panic("mode not found")
	}

	steps := []string{"init", "compile", "transpile", "assemble", "link", "run"}
	timeMap := map[string]time.Duration{}
	commandText := map[string][]string{}
	for _, step := range steps {
		if cmd, ok := cmds.(map[interface{}]interface{})[step]; ok {
			rawCmdLayout := strings.TrimSuffix(cmd.(string), "\n")
			for _, line := range strings.Split(rawCmdLayout, "\n") {
				commandSlice := []string{}
				for _, v := range strings.Split(line, " ") {
					tmp := v
					tmp = strings.Replace(tmp, "%abs", paths.absolute, -1)
					tmp = strings.Replace(tmp, "%project", paths.project, -1)
					tmp = strings.Replace(tmp, "%ext", paths.ext, -1)
					tmp = strings.Replace(tmp, "%base", paths.base, -1)
					tmp = strings.Replace(tmp, "%relative", paths.relative, -1)
					tmp = strings.Replace(tmp, "%rbase", paths.relativeBase, -1)
					tmp = strings.Replace(tmp, "%rdir", paths.relativeDir, -1)
					tmp = strings.Replace(tmp, "%exe", executable, -1)
					commandSlice = append(commandSlice, tmp)
				}
				timeMap[step] += run(commandSlice...)
				commandText[step] = append(commandText[step], strings.Join(commandSlice, " "))
			}
		}
	}
	fmt.Println()
	fmt.Println()

	show := []string{"assemble", "link", "compile", "transpile", "run"}
	for _, v := range show {
		if timer, ok := timeMap[v]; ok {
			if timer.Seconds() == 0 {
				color.HiRed(" - %c%-10s\tFail", v[0]-'a'+'A', v[1:])
			} else {
				s := int(timer.Seconds())
				ms := float64(timer.Microseconds()) / 1000.0

				color.HiCyan(" - %c%-10s\t%ds %6.3fms", v[0]-'a'+'A', v[1:], s, ms)
			}
			color.White("  %s", strings.Join(commandText[v], " & "))
		}
	}

	fmt.Println()
}
