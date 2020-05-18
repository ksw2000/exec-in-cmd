exec=require('child_process').exec
path=require('path')
os=require('os')
fs=require('fs')
readPackage=require("./readPackage.coffee");

system=os.platform()    # OS(win32,linux)

compatible =
    linux_and_darwin:
        C:
            description: 'Specify the folder name where C,C++,C# output <BR>`[ end with slash ]` `out/` , `output/c/` , `../out/` , `./` , `../`'
            default: 'out/'
        Java:
            description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with slash ]` `out/` , `output/java/` , `../out/` , `./` , `../`'
            default: 'out/'
        php:
            description: 'Specify the root directory of your PHP [ end with slash ]'
            default: '/var/www/'
        Rust:
            description: 'Specify the folder name where Rust output <BR>`[ end with slash ]` `out/` , `output/` , `../out/` , `./` , `../`'
            default: 'out/'
    win:
        C:
            description: 'Specify the folder name where C,C++,C# output <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        Java:
            description: 'Specify the folder name where Java,Kotlin output (Do not include whitespace character.) <BR>`[ end with backslash ]` `out\\` , `output\\java\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        php:
            description: 'Specify the root directory of your PHP [ end with backslash ]'
            default: 'C:\\MAMP\\htdoc\\'
        Rust:
            description: 'Specify the folder name where Rust output <BR>`[ end with backslash ]` `out\\` , `output\\rust\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'


compatible = if(system=='win32') then compatible.win else compatible.linux_and_darwin

module.exports =
    config:
        c:
            type: 'object'
            title: 'About C, C++, C#'
            order: 1
            properties:
                out:
                    type: 'string'
                    title: 'C, C++, C# output folder (relative)'
                    description: compatible.C.description
                    default: compatible.C.default
        java:
            type: 'object'
            title: 'About Java'
            order: 2
            properties:
                out:
                    type: 'string'
                    title: 'Java output folder (relative)'
                    description: compatible.Java.description
                    default: compatible.Java.default
        php:
            type: 'object'
            title: 'About PHP'
            order: 3
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
        python:
            type: 'object'
            title: 'About Python'
            order: 4
            properties:
                interpreter:
                    type: 'string'
                    title: 'About Python'
                    description: 'Type an interpreter to run python. Ex: python, python3, ...'
                    default: 'python'
                    #enum: ['python','python3']
        rust:
            type: 'object'
            title: 'About Rust'
            order: 5
            properties:
                out:
                    type: 'string'
                    title: 'Rust output folder (relative)'
                    description: compatible.Rust.description
                    default: compatible.Rust.default
        asm:
            type: 'object'
            title: 'About assembly (Only for linux)'
            order: 6
            properties:
                out:
                    type: 'string'
                    title: 'Assembly output folder (relative)'
                    description: 'Specify the folder name where assembly output <BR>`[ end with slash ]` `out/` , `output/c/` , `../out/` , `./` , `../`'
                    default: 'out/'
                    order: 1
                flag:
                    type: 'string'
                    title: 'Specify flag'
                    description: 'elf64 for x64, elf for x86'
                    default: 'elf64'
                    enum: ['elf64','elf']
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

        if advance < 2
            if extname == '.php'
                if system == 'win32'
                    phpFolder=atom.config.get('exec-in-cmd.php.phpFolder') ? 'C:\\MAMP\\htdoc\\';
                    openIn=atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost:81/';
                else if system =='linux' || system=='darwin'
                    phpFolder=atom.config.get('exec-in-cmd.php.phpFolder') ? '/var/www/';
                    openIn=atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost/';

                if select_file.indexOf(phpFolder) == -1
                    option=
                        description :
                            """
                            #### The root directory of your PHP:
                            `#{phpFolder}`
                            #### The path of this php file:
                            `#{select_file}`
                            """
                        dismissable : true
                    atom.notifications.addError('Invalid directory',option)
                else
                    openUrl=openIn + select_file.replace("#{phpFolder}",'').replace("\\","/")
                    switch system
                        when 'win32'
                        then exec "start \"\" \"#{openUrl}\""
                        when 'linux'
                        then exec "xdg-open \"#{openUrl}\""
                        when 'darwin'
                        then exec "open \"#{openUrl}\""

            else if extname in ['.html','.htm','.lnk','.pdf']
                switch system
                    when 'win32'
                    then exec "start \"\" \"#{dir_path}\\#{basename}#{extname}\""
                    when 'linux'
                    then exec "xdg-open \"#{dir_path}/#{basename}#{extname}\""
                    when 'darwin'
                    then exec "open \"#{dir_path}/#{basename}#{extname}\""

            else if extname in ['.asm','.c','.cpp','.cs','.go','.java','.js','.rb','.py','.R','.kt','.rs']
                _dir_path_   = "\"#{dir_path}\""
                _basename_   = "\"#{basename}\""
                _extname_    = "\"#{extname}\""
                _dirname_    = "\"#{__dirname}\""
                pythonInter  = atom.config.get('exec-in-cmd.python.interpreter') ? 'python'

                # Get Package Name of java file
                packageName = '0'
                if extname == '.java'
                    data = null
                    try
                        data = readPackage(select_file)
                    catch err
                        console.log(err)

                    if data != null
                        packageName = data[1]

                # For windows
                if system == 'win32'
                    outC     = atom.config.get('exec-in-cmd.c.out') ? 'out\\'
                    outJava  = atom.config.get('exec-in-cmd.java.out') ? 'out\\'
                    outRust  = atom.config.get('exec-in-cmd.rust.out') ? 'out\\'

                    command = "#{_dir_path_} #{_basename_} #{_extname_} #{_dirname_} #{advance}"
                    if extname in ['.c','.cpp','.cs']
                        command = "#{command} \"#{outC}\""
                    else if extname == '.java'
                        command = "#{command} \"#{outJava}\" \"#{packageName}\""
                    else if extname == '.kt'
                        command = "#{command} \"#{outJava}\""
                    else if extname == '.py'
                        command = "#{command} \"#{pythonInter}\""
                    else if extname == '.rs'
                        command = "#{command} \"#{outRust}\""
                    command = command.replace(/\\/g,'\\\\')

                    # Beside change directory, also need to notice to change disk if user works under D:\ or anotehr disk
                    i=0
                    changeDisk=""

                    while i< __dirname.length-1
                        if __dirname[i]==':' &&  __dirname[i+1]=='\\'
                            changeDisk = __dirname.slice(0,i)
                            changeDisk = "#{changeDisk}: & "
                            break
                        i++

                    command = "#{changeDisk}cd \"#{__dirname}\" & start \"Exec-in-cmd\" /WAIT open.exe #{command}"
                    exec command

                #For linux
                else if system == 'linux'
                    terminal = "gnome-terminal --window --title='Exec-in-cmd' -e"
                    outA     = atom.config.get('exec_in_cmd.asm.out') ? 'out/'
                    nasmFlag = atom.config.get('exec_in_cmd.asm.flag') ? 'elf64'
                    outC     = atom.config.get('exec-in-cmd.c.out') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.java.out') ? 'out/'
                    outRust  = atom.config.get('exec-in-cmd.rust.out') ? 'out/'
                    flag     = 0

                    switch extname
                        when '.asm'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"#{nasmFlag}\" \"#{outA}\"\""
                        when '.c','.cpp','.cs'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outC}'\"\""
                        when '.go'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'cd \"'#{_dir_path_}'\"; go run \"'#{_dir_path_}/#{_basename_}.go'\"'\""
                        when '.java'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dirname_}'\" \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outJava}'\" \"'#{packageName}'\"\""
                        when '.js'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'cd \"'#{_dir_path_}'\"; node \"'#{_dir_path_}/#{_basename_}.js'\"'\""
                        when '.py'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'cd \"'#{_dir_path_}'\"; #{pythonInter} \"'#{_dir_path_}/#{_basename_}.py'\"'\""
                        when '.R'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'cd \"'#{_dir_path_}'\"; Rscript \"'#{_dir_path_}/#{_basename_}.R'\"'\""
                        when '.rb'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux 'cd \"'#{_dir_path_}'\"; ruby \"'#{_dir_path_}/#{_basename_}.rb'\"'\""
                        when '.rs'
                        then command = "cd #{_dirname_}; #{terminal} \"./openLinux #{extname} \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outRust}'\"\""
                        else flag=1
                    if !flag
                        exec command

                #For mac os
                else if system == 'darwin'
                    outC     = atom.config.get('exec-in-cmd.c.out') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.java.out') ? 'out/'
                    flag = 0
                    switch extname
                        when '.c','.cpp','.cs'
                        then data = "#{extname}\n#{__dirname}\n#{dir_path}\n#{basename}\n#{outC}"
                        when '.go'
                        then data = "cd \"'#{_dir_path_}'\"; go run \"#{dir_path}/#{basename}.go\""
                        when '.java'
                        then data = "#{extname}\n#{__dirname}\n#{dir_path}\n#{basename}\n#{outJava}\n#{packageName}"
                        when '.js'
                        then data = "cd \"'#{_dir_path_}'\"; node \"#{dir_path}/#{basename}.js\""
                        when '.py'
                        then data = "cd \"'#{_dir_path_}'\"; #{pythonInter} \"#{dir_path}/#{basename}.py\""
                        when '.R'
                        then data = "cd \"'#{_dir_path_}'\"; Rscript \"#{dir_path}/#{basename}.R\""
                        when '.rb'
                        then data = "cd \"'#{_dir_path_}'\"; ruby \"#{dir_path}/#{basename}.rb\""
                        else flag=1
                    data = "#{data}\n"
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

        # advace2: Open cmd in windows or terminal in linux or mac os
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

        # advance3: Initialize for linux users and mac os users
        else if advance == 3
            if system =='linux'
                exec "gnome-terminal --title='Init for Exec-in-cmd' -e \"sudo chmod -R 777 \"'#{__dirname}'\"\""
            else if system =='darwin'
                exec "chmod -R 755 '#{__dirname}'"
                atom.notifications.addSuccess('Initialization done',{
                    description :"Now, you can press `F12` to run code!"
                })
