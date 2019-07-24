exec=require('child_process').exec
path=require('path')

module.exports=
    activate: ->
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:start', => @open_in_cmd(0)
        atom.commands.add 'atom-workspace', 'Exec-in-cmd:advance', => @open_in_cmd(1)
    deactivate: ->
        @subscriptions.dispose()
    open_in_cmd: (advance) ->
        select_file=atom.workspace.getActivePaneItem()?.buffer?.file?.getPath()

        dir_path=path.dirname(select_file)  #檔案位罝(結尾不含反斜線) file path (not including \)
        extname=path.extname(select_file)   #檔名不含副檔名 filename (not including extension)
        basename=path.basename(select_file) #檔名含副檔名 filename extension (including point)
        basename=basename.replace(extname,"")
        dir_name=__dirname;

        dir_path=if dir_path.indexOf(" ")==-1 then dir_path else "\"#{dir_path}\""
        basename=if basename.indexOf(" ")==1 then basename else "\"#{basename}\""
        extname=if extname.indexOf(" ")==-1 then extname else "\"#{extname}\""
        dir_name=if dir_name.indexOf(" ")==-1 then dir_name else "\"#{dir_name}\""

        exec "start #{dir_name}\\open.exe #{dir_path} #{basename} #{extname} #{dir_name} #{advance}"
