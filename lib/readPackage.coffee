fs = require('fs')

getPackageName = (path) ->
    try
        fs.readFileSync(path,'utf-8').toString().match(/^\s?package\b\s+([a-zA-Z_$]+[a-zA-Z0-9._$]{0,});/m)
    catch err
        throw err

module.exports = getPackageName
