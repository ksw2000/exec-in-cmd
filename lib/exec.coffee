exec=require('child_process').exec
path=require('path')
os=require('os')

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
                    description: 'Specify the folder name where C,C++ output <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
                    default: 'out\\'
                    order: 1
                Java:
                    type: 'string'
                    title: 'Java output folder (relative)'
                    description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
                    default: 'out\\'
                    order: 2
        php:
            type: 'object'
            title: 'About PHP'
            order: 4
            properties:
                phpFolder:
                    type: 'string'
                    title: 'PHP Setting'
                    description: 'Specify the root directory of your PHP (including the end of backslash)'
                    default: 'C:\\MAMP\\htdoc\\'
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

        dir_path=path.dirname(select_file)      #檔案位罝(結尾不含反斜線) file path (not including backslash)
        extname=path.extname(select_file)       #副檔名(含點) filename extension (including point)
        basename=path.basename(select_file)
        basename=basename.replace(extname,"")   #檔名(不含副檔名) filename (not including extension)
        complete_file_path="#{dir_path}\\#{basename}#{extname}"

        if advance < 2
            if extname == '.php'
                phpFolder=atom.config.get('exec-in-cmd.php.phpFolder') ? 'C:\\MAMP\\htdoc\\';
                openIn=atom.config.get('exec-in-cmd.php.openIn') ? 'http://localhost:81/';
                if complete_file_path.indexOf(phpFolder)==-1
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
                exec "start \"\" \"#{dir_path}\\#{basename}#{extname}\""
            else if extname in ['.c','.cpp','.go','.java','.js','.rb','.py','.R']
                if os.platform() == 'win32'
                    dir_path = "\"#{dir_path}\""
                    basename = "\"#{basename}\""
                    extname  = "\"#{extname}\""
                    dirname  = "\"#{__dirname}\""
                    outC = atom.config.get('exec-in-cmd.outputfolder.C').replace(/\\$/,"\\\\") ? 'out'
                    outJava = atom.config.get('exec-in-cmd.outputfolder.Java').replace(/\\$/,"\\\\") ? 'out'
                    command = "start \"Exec-in-cmd\" /MAX /WAIT \"#{__dirname}\\open.exe\" #{dir_path} #{basename} #{extname} #{dirname} #{advance}"
                    if extname == '".c"' or extname=='".cpp"'
                        command = "#{command} \"#{outC}\""
                    else if extname =='".java"'
                        command = "#{command} \"#{outJava}\""
                    exec command
                else
                    # Linux
            else
                atom.notifications.addError('Invalid file extension',{
                    description :"`#{extname}` is not supported."
                })
        else
            exec "start cmd /k \"cd /d \"#{dir_path}\"\""
