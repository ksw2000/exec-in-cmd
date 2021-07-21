exec = require('child_process').exec
path = require('path')
fs   = require('fs')
sys  = require('os').platform()

MODE =
    EXEC:    0
    OPEN:    1
    INIT:    2

config =
    autosave:
        type: 'boolean'
        title: 'Need to autosave?'
        default: false
        order: 1
        enum: [true, false]

if sys == 'linux'
    config.terminal =
        type: 'string'
        title: 'Linux terminal'
        default: 'gnome-terminal'
        enum: ['gnome-terminal', 'konsole']
        order: 0
else if sys == 'win32'
    config.terminal =
        type: 'string'
        title: 'Windows terminal'
        default: 'command-line'
        enum: ['command-line', 'windows-terminal']

module.exports =
    config: config
    activate: ->
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:exec',     => @exec_in_cmd MODE.EXEC
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:open_cmd', => @exec_in_cmd MODE.OPEN
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:init',     => @exec_in_cmd MODE.INIT
        #atom.window.document.querySelector('.status-bar .status-bar-right').append(execBtn)

    consumeStatusBar: (statusBar) ->
        execBtn = document.createElement('div')
        execBtn.classList.add("inline-block")
        execBtn.classList.add("icon")
        # https://github.com/atom/atom/blob/master/static/icons/octicons.less
        execBtn.classList.add("icon-triangle-right")
        execBtn.style.color = 'green'
        @statusBarTile = statusBar.addRightTile(item: execBtn, priority: 0)

    deactivate: ->
        @statusBarTile?.destroy()
        @statusBarTile = null

    exec_in_cmd: (mode) ->
        # atom.workspace https://flight-manual.atom.io/api/v1.57.0/Workspace/
        if atom.workspace.getActivePaneItem()?.selectedPath?
            abs = atom.workspace.getActivePaneItem()?.selectedPath
        else if atom.workspace.getActivePaneItem()?.getURI()?
            abs = atom.workspace.getActivePaneItem()?.getURI()
        else
            return

        file =
            # /path/file.ext
            abs:  abs
            # /path
            dir:  path.dirname(abs)
            # .ext
            ext:  path.extname(abs)
            # file.ext
            base: path.basename(abs)
            # file
            realbase: path.basename(abs, path.basename(abs))
            # atom project dir
            # [0]: project path
            # [1]: relative file path
            project: atom.project.relativizePath(abs)

        console.log file

        terminal =  atom.config.get('exec-in-cmd.terminal')

        if mode == MODE.OPEN
            if sys == 'win32'
                if terminal == 'windows-terminal'
                    exec "wt", {cwd: file.dir}
                else
                    exec "start cmd /k", {cwd: file.dir}
            else if sys == 'linux'
                if terminal == 'konsole'
                    exec "konsole", {cwd: file.dir}
                else
                    exec "gnome-terminal --window", {cwd: file.dir}
            else if sys == 'darwin'
                exec "open -a Terminal #{file.dir}"
            else
                atom.notifications.addError('Invalid os',{
                    description :"`#{sys}` is not supported."
                })

        if mode == MODE.EXEC
            validExtension = false

            if atom.config.get('exec-in-cmd.autosave')
                atom.workspace.getActivePaneItem()?.save()

            if file.ext in ['.html', '.htm', '.lnk', '.pdf', '.cmd', '.bat']
                switch sys
                    when 'win32'
                    then exec "start \"\" \"#{file.base}\"", {
                        cwd: file.dir
                    }
                    when 'linux'
                    then exec "xdg-open \"#{file.base}\"", {
                        cwd: file.dir
                    }
                    when 'darwin'
                    then exec "open \"#{file.base}\"", {
                        cwd: file.dir
                    }
            else
                # get project directory

                supportMode =
                    '.asm':     if sys == 'win32' then 'nasm_win' else 'nasm_unix'
                    '.bat':     'cmd'
                    '.cmd':     'cmd'
                    '.c':       if sys == 'win32' then 'c_win' else 'c_unix'
                    '.cpp':     if sys == 'win32' then 'cpp_win' else 'cpp_unix'
                    '.cs':      'csharp'
                    '.dart':    'dart'
                    '.go':      'go'
                    '.java':    'java'
                    '.js':      'node'
                    '.kt':      'kotlin'
                    '.php':     'php'
                    '.py':      if sys == 'win32' then 'python' else 'python3'
                    '.R':       'rscript'
                    '.rb':      'ruby'
                    '.rs':      'rust'
                    '.coffee':  'coffee'
                    '.ts':      'typescript'
                    '.wasm':    'wasm'

                mode = supportMode[file.ext]
                validExtension = file.ext in supportMode

                if !validExtension
                    if sys == 'win32'
                        if terminal == 'windows-terminal'
                            exec "wt ../open.go/main --mode #{mode} --file \"#{file.project[1]}\" --project \"#{file.project[0]}\"", {
                                cwd: path.join(__dirname, "../open.go/")
                            }
                        else
                            exec "start \"Exec-in-cmd\" /WAIT ../open.go/main.exe --mode #{mode} --file \"#{file.project[1]}\" --project \"#{file.project[0]}\"", {
                                cwd: path.join(__dirname, "../open.go/")
                            }
                    else if sys == 'linux'
                        exec "#{terminal} \"../open.go/main --mode #{mode} --file \"#{file.project[1]}\" --project \"#{file.project[0]}\"", {
                            cwd: path.join(__dirname, "../open.go/")
                        }
                    # TODO darwin
                else
                    atom.notifications.addError 'Invalid file extension', {
                        description :"`#{file.ext}` is not supported."
                    }

        else if mode == MODE.INIT
            console.log "TODO"
            # if sys =='linux'
            #     atom.notifications.addInfo('Try below in terminal:', {
            #         description : "1. `cd \"#{__dirname}\"`<br>2. `sudo chmod -R 4777 ./ & sudo chown -R root ./`<br> 3. `sudo chmod -R u+s ./`"
            #     })
            #
            # else if sys =='darwin'
            #     exec "chmod -R 755 '#{__dirname}'"
            #     atom.notifications.addSuccess('Initialization done',{
            #         description :"Now, you can press `F12` to run code!"
            #     })
