exec=require('child_process').exec
path=require('path')
os=require('os')
system=os.platform()    #使用系統 OS(win32,linux)

compatible =
    linux:
        C:
            description: 'Specify the folder name where C,C++ output <BR>`[ end with slash ]` `out/` , `output/c/` , `../out/` , `./` , `../`'
            default: 'out/'
        Java:
            description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with slash ]` `out/` , `output/c/` , `../out/` , `./` , `../`'
            default: 'out/'
        php:
            description: 'Specify the root directory of your PHP [ end with slash ]'
            default: 'home/user/'
    win:
        C:
            description: 'Specify the folder name where C,C++ output <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        Java:
            description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        php:
            description: 'Specify the root directory of your PHP [ end with blackslash ]'
            default: 'C:\\MAMP\\htdoc\\'

compatible = if(system=='win32') then compatible.win else compatible.linux

module.exports =
    config:
        outputfolder:
            type: 'object'
            title: 'Output Folder'
            order: 2
            properties:
                C:
                    type: 'string'
                    title: 'C, C++ output folder (relative)'
                    description: compatible.C.description
                    default: compatible.C.default
                    order: 1
                Java:
                    type: 'string'
                    title: 'Java output folder (relative)'
                    description: compatible.Java.description
                    default: compatible.Java.default
                    order: 2
        php:
            type: 'object'
            title: 'About PHP'
            order: 4
            properties:
                phpFolder:
                    type: 'string'
                    title: 'PHP Setting'
                    description: compatible.php.description
                    default: compatible.php.default
                    order: 1
                openIn:
                    type: 'string'
                    title: 'index URL'
                    description: 'Specify the URL to access your PHP.'
                    default: 'http://localhost:81/'
                    order: 2

    activate: ->
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:exec', => @exec_in_cmd(0)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:advance', => @exec_in_cmd(1)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:open_cmd', => @exec_in_cmd(2)

    deactivate: ->
        @subscriptions.dispose()
    exec_in_cmd: (advance) ->
        select_file=atom.workspace.getActivePaneItem()?.buffer?.file?.path #complete filepath

        ###
            dir_path: 檔案位罝(結尾不含斜線或反斜線) file path (not including slash or backslash)
            extname : 副檔名(含點) filename extension (including point)
            basename: 檔名(不含副檔名) filename (not including extension)
        ###

        dir_path = path.dirname(select_file)
        extname  = path.extname(select_file)
        basename = path.basename(select_file).replace(extname,"")
        complete_file_path = "#{dir_path}\\#{basename}#{extname}"

        if advance < 2
            if extname == '.php'
                phpFolder=atom.config.get('exec-in-cmd.php.phpFolder') ? 'C:\\MAMP\\htdoc\\';
                openIn=atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost:81/';
                if complete_file_path.indexOf(phpFolder) == -1
                    option=
                        description :
                            """
                            #### The root directory of your PHP:
                            `#{phpFolder}`
                            #### The path of this php file:
                            `#{complete_file_path}`
                            """
                        dismissable : true
                    atom.notifications.addError('Invalid directory',option)
                else
                    openUrl=openIn + complete_file_path.replace("#{phpFolder}",'').replace("\\","/")
                    exec "start \"\" \"#{openUrl}\""
            else if extname in ['.html','.htm','.lnk','.pdf']
                if system == 'win32'
                    exec "start \"\" \"#{dir_path}\\#{basename}#{extname}\""
                else if system =='linux'
                    exec "xdg-open \"#{dir_path}/#{basename}#{extname}\""
            else if extname in ['.c','.cpp','.go','.java','.js','.rb','.py','.R']
                _dir_path_ = "\"#{dir_path}\""
                _basename_ = "\"#{basename}\""
                _extname_  = "\"#{extname}\""
                _dirname_  = "\"#{__dirname}\""

                # For windows
                if system == 'win32'
                    outC     = atom.config.get('exec-in-cmd.outputfolder.C').replace(/\\$/,"\\\\") ? 'out'
                    outJava  = atom.config.get('exec-in-cmd.outputfolder.Java').replace(/\\$/,"\\\\") ? 'out'
                    command  = "start \"Exec-in-cmd\" /WAIT \"#{__dirname}\\open.exe\" #{_dir_path_} #{_basename_} #{_extname_} #{_dirname_} #{advance}"
                    if extname == '.c' or extname=='.cpp'
                        command = "#{command} \"#{outC}\""
                    else if extname =='.java'
                        command = "#{command} \"#{outJava}\""
                    exec command
                #For linux
                else if system == 'linux'
                    terminal = "gnome-terminal --window --title='Exec-in-cmd' -e"
                    outC     = atom.config.get('exec-in-cmd.outputfolder.C') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.outputfolder.Java') ? 'out/'
                    flag     = 0
                    _finalOutputC_ = "\"#{dir_path}/#{outC}\"\"#{basename}\""
                    switch extname
                        when '.c','.cpp'
                        # then command = "cd #{_dir_path_}; mkdir -p \"#{outC}\"; #{if(extname == '.c') then "gcc" else "g++"} \"#{basename}#{extname}\" -o \"#{outC}#{basename}\"; cd #{_dirname_}; #{terminal} \"./openLinux '\"'#{_finalOutputC_}'\"'\""
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dirname_}'\" \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outC}'\"\""
                        #then command = "cd #{_dir_path_}; mkdir -p \"#{outC}\"; #{if(extname == '.c') then "gcc" else "g++"} \"#{basename}#{extname}\" -o \"#{outC}#{basename}\"; cd #{_dirname_}; #{terminal} \"./openLinux '\"'#{_finalOutputC_}'\"'\""
                        when '.go'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'go run \"'#{_dir_path_}/#{_basename_}.go'\"'\""
                        when '.java'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dirname_}'\" \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outJava}'\"\""
                        when '.js'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'node \"'#{_dir_path_}/#{_basename_}.js'\"'\""
                        when '.py'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'python \"'#{_dir_path_}/#{_basename_}.py'\"'\""
                        when '.R'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'Rscript \"'#{_dir_path_}/#{_basename_}.R'\"'\""
                        when '.rb'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'ruby \"'#{_dir_path_}/#{_basename_}.rb'\"'\""
                        else flag=1
                    if !flag
                        exec command
                else
                    # Not support
            else
                atom.notifications.addError('Invalid file extension',{
                    description :"`#{extname}` is not supported."
                })
        else
            if system == 'win32'
                exec "start cmd /k \"cd /d \"#{dir_path}\"\""
            else if system == 'linux'
                exec "cd \"#{dir_path}\"; gnome-terminal --window"
