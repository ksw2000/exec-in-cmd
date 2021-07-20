package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path"
	"path/filepath"
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

type Program struct {
	FullPath    string
	ProjectRoot string
	ProjectName string
	Ext         string
	File        string
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

	var mode, full, project, out string
	flag.StringVar(&mode, "mode", "", "Command generator: c, cpp, go, java, ...")
	flag.StringVar(&full, "full", "", "Full path")
	flag.StringVar(&project, "project", "", "Project path")
	flag.StringVar(&out, "out", "./", "Output path")
	flag.Parse()

	// TODO: check flag

	// change dir
	cd = project

	// if runtime.GOOS == "windows" {
	// } else {

	// }

	ext := strings.TrimPrefix(path.Ext(full), ".")
	file := strings.TrimSuffix(filepath.Base(full), fmt.Sprintf(".%s", ext))

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

	steps := []string{"init", "compile", "assemble", "link", "run"}
	timeMap := map[string]time.Duration{}
	commandText := map[string][]string{}
	for _, step := range steps {
		if cmd, ok := cmds.(map[interface{}]interface{})[step]; ok {
			rawCmdLayout := strings.TrimSuffix(cmd.(string), "\n")
			for _, line := range strings.Split(rawCmdLayout, "\n") {
				commandSlice := []string{}
				for _, v := range strings.Split(line, " ") {
					tmp := v
					tmp = strings.Replace(tmp, "%ext", ext, -1)
					tmp = strings.Replace(tmp, "%file", file, -1)
					tmp = strings.Replace(tmp, "%out", out, -1)
					commandSlice = append(commandSlice, tmp)
				}
				timeMap[step] += run(commandSlice...)
				commandText[step] = append(commandText[step], strings.Join(commandSlice, " "))
			}
		}
	}
	fmt.Println()
	fmt.Println()
	if timer, ok := timeMap["assemble"]; ok {
		if timer.Seconds() == 0 {
			color.HiRed(" - Assemble: \tFail")
		} else {
			color.HiCyan(" - Assemble: \t%fs", timer.Seconds())
		}
		color.White("  %s", strings.Join(commandText["assemble"], " & "))
	}
	if timer, ok := timeMap["link"]; ok {
		if timer.Seconds() == 0 {
			color.HiRed(" - Link:     \tFail")
		} else {
			color.HiCyan(" - Link:     \t%fs", timer.Seconds())
		}
		color.White("  %s", strings.Join(commandText["link"], " & "))
	}
	if timer, ok := timeMap["compile"]; ok {
		if timer.Seconds() == 0 {
			color.HiRed(" - Compile:  \tFail")
		} else {
			color.HiCyan(" - Compile:  \t%fs", timer.Seconds())
		}
		color.White("  %s", strings.Join(commandText["compile"], " & "))
	}
	if timer, ok := timeMap["run"]; ok {
		if timer.Seconds() == 0 {
			color.HiRed(" - Run:      \tFail")
		} else {
			color.HiCyan(" - Run:      \t%fs", timer.Seconds())
		}
		color.White("  %s", strings.Join(commandText["run"], " & "))
	}
	fmt.Println()
	fmt.Println()

}
