system = require('os').platform()

compatible =
    linux_and_darwin:
        C:
            description: 'Specify the folder name where C,C++,C# output <BR>`[ end with slash ]` `out/` , `output/c/` , `../out/` , `./` , `../`'
            default: 'out/'
        Java:
            description: 'Specify the folder name where Java output (Do not include whitespace character.) <BR>`[ end with slash ]` `out/` , `output/java/` , `../out/` , `./` , `../`'
            default: 'out/'
        php:
            description: 'Specify the root directory of your PHP [ end with slash ] <BR> If you choose to running in cmd(terminal) instead of opening in browser, you can skip this column.'
            default: '/var/www/'
        Rust:
            description: 'Specify the folder name where Rust output <BR>`[ end with slash ]` `out/` , `output/` , `../out/` , `./` , `../`'
            default: 'out/'
        asm:
            type: 'object'
            title: 'About assembly'
            order: 6
            properties:
                out:
                    type: 'string'
                    title: 'Assembly output folder (relative)'
                    description: 'Specify the folder name where assembly output <BR>`[ end with slash ]` `out/` , `output/asm/` , `../out/` , `./` , `../`'
                    default: 'out/'
                    order: 1
                flag:
                    type: 'string'
                    title: 'Specify flag'
                    description: 'elf64 for x64, elf for x86'
                    default: 'elf64'
                    enum: ['elf64','elf']
                    order: 2
    win:
        C:
            description: 'Specify the folder name where C,C++,C# output <BR>`[ end with backslash ]` `out\\` , `output\\c\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        Java:
            description: 'Specify the folder name where Java, Kotlin output (Do not include whitespace character.) <BR>`[ end with backslash ]` `out\\` , `output\\java\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        php:
            description: 'Specify the root directory of your PHP [ end with backslash ]'
            default: 'C:\\MAMP\\htdoc\\'
        Rust:
            description: 'Specify the folder name where Rust output <BR>`[ end with backslash ]` `out\\` , `output\\rust\\` , `..\\out\\` , `.\\` , `..\\`'
            default: 'out\\'
        asm:
            type: 'object'
            title: 'About assembly'
            order: 6
            properties:
                out:
                    type: 'string'
                    title: 'Assembly output folder (relative)'
                    description: 'Specify the folder name where assembly output <BR>`[ end with backslash ]` `out\\` , `output\\asm\\` , `..\\out\\` , `.\\` , `..\\`'
                    default: 'out/'
                    order: 1

compatible = if(system == 'win32') then compatible.win else compatible.linux_and_darwin

cfg =
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
            phpAction:
                type: 'string'
                title: 'How to process .php'
                description: 'Open in browser or run php in cmd(terminal)?'
                default: 'Open in browser'
                enum: ['Open in browser', 'Run in cmd']
                order: 1
            phpFolder:
                type: 'string'
                title: 'Root directory'
                description: compatible.php.description
                default: compatible.php.default
                order: 2
            openIn:
                type: 'string'
                title: 'Go to:'
                description: 'Specify the URL to access your PHP.'
                default: 'http://localhost/'
                order: 3
    python:
        type: 'object'
        title: 'About Python'
        order: 4
        properties:
            interpreter:
                type: 'string'
                title: 'About Python'
                description: 'Type an interpreter to run python. Ex: `python`, `python3`, ...'
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
    asm: compatible.asm

if system == 'linux'
    cfg.terminal =
        type: 'string'
        title: 'Linux terminal'
        default: 'gnome-terminal'
        enum: ['gnome-terminal', 'konsole']
        order: 0

module.exports = cfg
