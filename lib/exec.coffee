exec=require('child_process').exec
path=require('path')
os=require('os')
fs=require('fs')
system=os.platform()    # OS(win32,linux)

compatible =
    linux:
        C:
            description: 'Specify the folder name where C,C++,C# output <BR>`[ end with slash ]` `out/` , `output/c/` , `../out/` , `./` , `../`'
            default: 'out/'
        Java:
            description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with slash ]` `out/` , `output/java/` , `../out/` , `./` , `../`'
            default: 'out/'
        php:
            description: 'Specify the root directory of your PHP [ end with slash ]'
            default: '/var/www/'
    win:
        C:
            description: 'Specify the folder name where C,C++,C# output <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        Java:
            description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with backslash ]` `out\\` , `output\\java\\` , `..\\out\\` , `.\\` , `..\\`'
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
                    title: 'C, C++, C# output folder (relative)'
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
                    default: 'http://localhost/'
                    order: 2

    activate: ->
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:exec', => @exec_in_cmd(0)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:advance', => @exec_in_cmd(1)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:open_cmd', => @exec_in_cmd(2)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:init', => @exec_in_cmd(3)

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
                if system == 'win32'
                    phpFolder=atom.config.get('exec-in-cmd.php.phpFolder') ? 'C:\\MAMP\\htdoc\\';
                    openIn=atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost:81/';
                else if system =='linux'
                    phpFolder=atom.config.get('exec-in-cmd.php.phpFolder') ? '/var/www/';
                    openIn=atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost/';

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
                    if system == 'win32'
                        exec "start \"\" \"#{openUrl}\""
                    else if system =='linux'
                        exec "xdg-open \"#{openUrl}\""
            else if extname in ['.html','.htm','.lnk','.pdf']
                if system == 'win32'
                    exec "start \"\" \"#{dir_path}\\#{basename}#{extname}\""
                else if system =='linux'
                    exec "xdg-open \"#{dir_path}/#{basename}#{extname}\""
            else if extname in ['.c','.cpp','.cs','.go','.java','.js','.rb','.py','.R']
                _dir_path_ = "\"#{dir_path}\""
                _basename_ = "\"#{basename}\""
                _extname_  = "\"#{extname}\""
                _dirname_  = "\"#{__dirname}\""

                # For windows
                if system == 'win32'
                    outC     = atom.config.get('exec-in-cmd.outputfolder.C') ? 'out\\'
                    outJava  = atom.config.get('exec-in-cmd.outputfolder.Java') ? 'out\\'

                    command = "#{_dir_path_} #{_basename_} #{_extname_} #{_dirname_} #{advance}"
                    if extname in ['.c','.cpp','.cs']
                        command = "#{command} \"#{outC}\""
                    else if extname =='.java'
                        command = "#{command} \"#{outJava}\""
                    command = command.replace(/\\/g,'\\\\')

                    changeDisk = ""
                    i=0
                    while i< __dirname.length-1
                         if __dirname[i]==':' &&  __dirname[i+1]=='\\'
                             changeDisk = __dirname.slice(0,i)
                             changeDisk += ": & "
                             break
                         i++


                    command = "#{changeDisk}cd \"#{__dirname}\" & start \"Exec-in-cmd\" /WAIT open.exe " + command
                    exec command

                #For linux
                else if system == 'linux'
                    terminal = "gnome-terminal --window --title='Exec-in-cmd' -e"
                    outC     = atom.config.get('exec-in-cmd.outputfolder.C') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.outputfolder.Java') ? 'out/'
                    flag     = 0
                    _finalOutputC_ = "\"#{dir_path}/#{outC}\"\"#{basename}\""
                    switch extname
                        when '.c','.cpp','.cs'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dirname_}'\" \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outC}'\"\""
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
                else if system == 'darwin'
                    outC     = atom.config.get('exec-in-cmd.outputfolder.C') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.outputfolder.Java') ? 'out/'
                    flag = 0
                    switch extname
                        when '.c','.cpp','.cs'
                        then data = "#{extname}\n#{__dirname}\n#{dir_path}\n#{basename}\n#{outC}"
                        when '.go'
                        then data = "go run \"#{dir_path}/#{basename}.go\""
                        when '.java'
                        then data = "#{extname}\n#{__dirname}\n#{dir_path}\n#{basename}\n#{outJava}"
                        when '.js'
                        then data = "node \"#{dir_path}/#{basename}.js\""
                        when '.py'
                        then data = "python \"#{dir_path}/#{basename}.py\""
                        when '.R'
                        then data = "Rscript \"#{dir_path}/#{basename}.R\""
                        when '.rb'
                        then data = "ruby \"#{dir_path}/#{basename}.rb\""
                        else flag=1
                    data += "\n"
                    if !flag
                        fs.writeFile(__dirname+'/configTemp.tmp',data,(err)->{})
                        exec "open -a Terminal ./#{__dirname}/openDarwin"
                else
                    atom.notifications.addError('Invalid os',{
                        description :"`#{system}` is not supported."
                    })
            else
                atom.notifications.addError('Invalid file extension',{
                    description :"`#{extname}` is not supported."
                })
        else if advance == 2
            if system == 'win32'
                exec "start cmd /k \"cd /d \"#{dir_path}\"\""
            else if system == 'linux'
                exec "cd \"#{dir_path}\"; gnome-terminal --window"
            else if system == 'darwin'
                exec "open -a Terminal #{dir_path}"
            else
                atom.notifications.addError('Invalid os',{
                    description :"`#{system}` is not supported."
                })
        else if advance == 3
            if system =='linux'
                exec "gnome-terminal --title='Init for Exec-in-cmd' -e \"sudo chmod -R 777 \"'#{__dirname}'\"\""
            else if system =='darwin'
                exec "chmod -R 755 \"'#{__dirname}'\"\""
                atom.notifications.addSuccess('Initialization done',{
                    description :"You can press `F12` to run code"
                })
