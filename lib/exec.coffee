exec = require('child_process').exec
path = require('path')
fs   = require('fs')
rp   = require('./readPackage.coffee')
cfg  = require('./config.coffee')
sys  = require('os').platform()

module.exports =
    config : cfg

    activate: ->
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:exec', => @exec_in_cmd(0)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:advance', => @exec_in_cmd(1)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:open_cmd', => @exec_in_cmd(2)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:init', => @exec_in_cmd(3)

    deactivate: ->
        @subscriptions.dispose()
    exec_in_cmd: (advance) ->
        #complete filepath
        select_file = atom.workspace.getActivePaneItem()?.buffer?.file?.path
        ###
            dir_path: 檔案位罝(結尾不含斜線或反斜線) file path (not including slash or backslash)
            extname : 副檔名(含點) filename extension (including point)
            basename: 檔名(不含副檔名) filename (not including extension)
        ###

        dir_path = path.dirname(select_file)
        extname  = path.extname(select_file)
        basename = path.basename(select_file).replace(extname, '')

        terminal = atom.config.get('exec-in-cmd.terminal')

        if advance < 2
            if extname == '.php'
                openIn = atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost/';

                if sys == 'win32'
                    phpFolder = atom.config.get('exec-in-cmd.php.phpFolder') ? 'C:\\MAMP\\htdoc\\';
                else if sys == 'linux' || sys == 'darwin'
                    phpFolder = atom.config.get('exec-in-cmd.php.phpFolder') ? '/var/www/';

                if select_file.indexOf(phpFolder) == -1
                    option =
                        description :
                            """
                            #### The root directory of your PHP:
                            `#{phpFolder}`
                            #### The path of this php file:
                            `#{select_file}`
                            """
                        dismissable : true
                    atom.notifications.addError('Invalid directory', option)
                else
                    openUrl = openIn + select_file.replace("#{phpFolder}", '').replace("\\","/")
                    switch sys
                        when 'win32'
                        then exec "start \"\" \"#{openUrl}\""
                        when 'linux'
                        then exec "xdg-open \"#{openUrl}\""
                        when 'darwin'
                        then exec "open \"#{openUrl}\""

            else if extname in ['.html', '.htm', '.lnk', '.pdf']
                switch sys
                    when 'win32'
                    then exec "start \"\" \"#{dir_path}\\#{basename}#{extname}\""
                    when 'linux'
                    then exec "xdg-open \"#{dir_path}/#{basename}#{extname}\""
                    when 'darwin'
                    then exec "open \"#{dir_path}/#{basename}#{extname}\""

            else if extname in ['.asm', '.c', '.cpp', '.cs', '.go', '.java', '.js', '.rb', '.py', '.R',
                                '.kt', '.rs']
                _dir_path_  = "\"#{dir_path}\""
                _basename_  = "\"#{basename}\""
                _extname_   = "\"#{extname}\""
                _dirname_   = "\"#{__dirname}\""
                pythonInter = atom.config.get('exec-in-cmd.python.interpreter') ? 'python'
                extFlag     = 0

                # Get Package Name of java file
                packageName = '0'
                if extname == '.java'
                    data = null
                    try
                        data = rp(select_file)
                    catch err
                        console.log(err)

                    if data != null
                        packageName = data[1]

                # For windows
                if sys == 'win32'
                    outA    = atom.config.get('exec_in_cmd.asm.out') ? 'out/'
                    outC    = atom.config.get('exec-in-cmd.c.out') ? 'out\\'
                    outJava = atom.config.get('exec-in-cmd.java.out') ? 'out\\'
                    outRust = atom.config.get('exec-in-cmd.rust.out') ? 'out\\'
                    args    = "#{_dir_path_} #{_basename_} #{_extname_} #{_dirname_} #{advance}"

                    switch extname
                        when '.asm'
                        then args = "#{args} \"#{outA}\""
                        when '.c', '.cpp', '.cs'
                        then args = "#{args} \"#{outC}\""
                        when '.java'
                        then args = "#{args} \"#{outJava}\" \"#{packageName}\""
                        when '.kt'
                        then args = "#{args} \"#{outJava}\""
                        when '.py'
                        then args = "#{args} \"#{pythonInter}\""
                        when '.rs'
                        then args = "#{args} \"#{outRust}\""

                    args = args.replace(/\\/g,'\\\\')

                    # Beside change directory, also need to notice to change disk if user
                    # works under D:\ or anotehr disk

                    i = 0
                    changeDisk = ''

                    while i< __dirname.length-1
                        if __dirname[i] == ':' &&  __dirname[i+1] == '\\'
                            changeDisk = __dirname.slice(0,i)
                            changeDisk = "#{changeDisk}: & "
                            break
                        i++

                    exec "#{changeDisk}cd \"#{__dirname}\" & start \"Exec-in-cmd\" /WAIT open.exe #{args}"

                #For linux
                else if sys == 'linux'
                    if terminal == 'gnome-terminal'
                        terminal = "gnome-terminal --window --title='Exec-in-cmd' -e"
                    else if terminal == 'konsole'
                        terminal = 'konsole -e'

                    outA     = atom.config.get('exec_in_cmd.asm.out') ? 'out/'
                    nasmFlag = atom.config.get('exec_in_cmd.asm.flag') ? 'elf64'
                    outC     = atom.config.get('exec-in-cmd.c.out') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.java.out') ? 'out/'
                    outRust  = atom.config.get('exec-in-cmd.rust.out') ? 'out/'

                    command = "cd #{_dirname_}; #{terminal}"

                    switch extname
                        when '.asm'
                        then command += "\"./openLinux #{extname} \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"#{nasmFlag}\" \"#{outA}\"\""
                        when '.c','.cpp','.cs'
                        then command += "\"./openLinux #{extname} \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outC}'\"\""
                        when '.go'
                        then command += "\"./openLinux 'cd \"'#{_dir_path_}'\"; go run \"'#{_dir_path_}/#{_basename_}.go'\"'\""
                        when '.java'
                        then command += "\"./openLinux #{extname} \"'#{_dirname_}'\" \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outJava}'\" \"'#{packageName}'\"\""
                        when '.js'
                        then command += "\"./openLinux 'cd \"'#{_dir_path_}'\"; node \"'#{_dir_path_}/#{_basename_}.js'\"'\""
                        when '.py'
                        then command += "\"./openLinux 'cd \"'#{_dir_path_}'\"; #{pythonInter} \"'#{_dir_path_}/#{_basename_}.py'\"'\""
                        when '.R'
                        then command += "\"./openLinux 'cd \"'#{_dir_path_}'\"; Rscript \"'#{_dir_path_}/#{_basename_}.R'\"'\""
                        when '.rb'
                        then command += "\"./openLinux 'cd \"'#{_dir_path_}'\"; ruby \"'#{_dir_path_}/#{_basename_}.rb'\"'\""
                        when '.rs'
                        then command += "\"./openLinux #{extname} \"'#{_dir_path_}'\" \"'#{_basename_}'\" \"'#{outRust}'\"\""
                        else extFlag = 1
                    if !extFlag
                        exec command

                #For mac os
                else if sys == 'darwin'
                    outC     = atom.config.get('exec-in-cmd.c.out') ? 'out/'
                    outJava  = atom.config.get('exec-in-cmd.java.out') ? 'out/'
                    outRust  = atom.config.get('exec-in-cmd.rust.out') ? 'out/'

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
                        when '.rs'
                        then data = "#{extname}\n#{__dirname}\n#{dir_path}\n#{basename}\n#{outRust}"
                        else extFlag = 1
                    data = "#{data}\n"
                    if !extFlag
                        fs.writeFile(__dirname+'/configTemp.tmp',data,(err)->{})
                        exec "open -a Terminal ./#{__dirname}/openDarwin"
                else
                    atom.notifications.addError('Invalid os',{
                        description :"`#{sys}` is not supported."
                    })
            else
                atom.notifications.addError('Invalid file extension',{
                    description :"`#{extname}` is not supported."
                })

        # advace2: Open cmd in windows or terminal in linux or mac os
        else if advance == 2
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

        # advance3: Initialize for linux users and mac os users
        else if advance == 3
            if sys =='linux'
                if terminal == 'gnome-terminal'
                    exec "gnome-terminal --title='Init for Exec-in-cmd' -e \"sudo chmod -R 777 \"'#{__dirname}'\"\""
                else if terminal == 'konsole'
                    exec "konsole -e \"sudo chmod -R 777 \"'#{__dirname}'\"\""

            else if sys =='darwin'
                exec "chmod -R 755 '#{__dirname}'"
                atom.notifications.addSuccess('Initialization done',{
                    description :"Now, you can press `F12` to run code!"
                })
