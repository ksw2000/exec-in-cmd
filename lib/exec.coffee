exec = require('child_process').exec
path = require('path')
fs   = require('fs')
rp   = require('./readPackage.coffee')
cfg  = require('./config.coffee')
sys  = require('os').platform()

MODE =
    EXEC:    0
    ADVANCE: 1
    OPEN:    2
    INIT:    3

module.exports =
    config : cfg

    activate: ->
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:exec',     => @exec_in_cmd MODE.EXEC
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:advance',  => @exec_in_cmd MODE.ADVANCE
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:open_cmd', => @exec_in_cmd MODE.OPEN
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:init',     => @exec_in_cmd MODE.INIT
        div = document.createElement('div')
        div.classList.add("inline-block")
        div.classList.add("icon")
        # https://github.com/atom/atom/blob/master/static/icons/octicons.less
        div.classList.add("icon-triangle-right")
        atom.window.document.querySelector('.status-bar .status-bar-right').append(div)

    deactivate: ->
        @subscriptions.dispose()

    exec_in_cmd: (mode) ->
        if atom.workspace.getActivePaneItem()?.buffer?.file?.path?
            # /path/file.ext
            select_file = atom.workspace.getActivePaneItem()?.buffer?.file?.path
            dir_path = path.dirname(select_file)                         # /path
            extname  = path.extname(select_file)                         # .ext
            basename = path.basename(select_file).replace(extname, '')   # file
        else if mode == MODE.OPEN && atom.workspace.getActivePaneItem()?.selectedPath?
            dir_path = atom.workspace.getActivePaneItem()?.selectedPath
        else
            return

        if mode == MODE.EXEC or mode == MODE.ADVANCE
            validExtension = false
            
            #atom.workspace.save()
            if extname in ['.html', '.htm', '.lnk', '.pdf']
                switch sys
                    when 'win32'
                    then exec "start \"\" \"#{dir_path}\\#{basename}#{extname}\""
                    when 'linux'
                    then exec "xdg-open \"#{select_file}\""
                    when 'darwin'
                    then exec "open \"#{dir_path}/#{basename}#{extname}\""
            else
                openGoMode = 
                    '.asm':     sys == 'win32' ? 'nasm_win' : 'nasm_unix' 
                    '.bat':     'cmd'
                    '.cmd':     'cmd'
                    '.c':       sys == 'win32' ? 'c_win' : 'c_unix'
                    '.cpp':     sys == 'win32' ? 'cpp_win' : 'cpp_unix'
                    '.cs':      'csharp'
                    '.dart':    'dart'
                    '.go':      'go'
                    '.java':    'java'
                    '.js':      'node'
                    '.kt':      'kotlin'
                    '.php':     'php'
                    '.py':      sys == 'win32' ? 'python' : 'python3'
                    '.R':       'rscript'
                    '.rb':      'ruby'
                    '.rs':      'rust'
                    '.coffee':  'coffee'
                    '.ts':      'typescript'
                    '.wasm':    'wasm'

                mode = openGoMode[extname]
                validExtension = extname in mode
                
                if !validExtension
                    if sys == 'win32'
                        exec "start \"Exec-in-cmd\" /WAIT ../open.go/main.exe --mode #{mode} --full \"#{select_file}\" --project \"#{dir_path}\"", {cwd: path.join(__dirname, "../open.go/")}
                    else if sys == 'linux'
                        exec "#{terminal} \"../open.go/main --mode #{mode} --full \"#{select_file}\" --project \"#{dir_path}\"", {cwd: path.join(__dirname, "../open.go/")}
                    # TODO darwin
                else
                    atom.notifications.addError 'Invalid file extension', {
                        description :"`#{extname}` is not supported."
                    }

        else if mode == MODE.OPEN
            if sys == 'win32'
                exec "start cmd /k \"cd /d \"#{dir_path}\"\""
            else if sys == 'linux'
                if terminal == 'gnome-terminal'
                    exec "cd \"#{dir_path}\"; gnome-terminal --window"
                else if terminal == 'konsole'
                    exec "cd \"#{dir_path}\"; konsole"
            else if sys == 'darwin'
                exec "open -a Terminal #{dir_path}"
            else
                atom.notifications.addError('Invalid os',{
                    description :"`#{sys}` is not supported."
                })

        else if mode == MODE.INIT
            if sys =='linux'
                atom.notifications.addInfo('Try below in terminal:', {
                    description : "1. `cd \"#{__dirname}\"`<br>2. `sudo chmod -R 4777 ./ & sudo chown -R root ./`<br> 3. `sudo chmod -R u+s ./`"
                })

            else if sys =='darwin'
                exec "chmod -R 755 '#{__dirname}'"
                atom.notifications.addSuccess('Initialization done',{
                    description :"Now, you can press `F12` to run code!"
                })
