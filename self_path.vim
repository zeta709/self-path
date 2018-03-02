" https://stackoverflow.com/questions/4976776/how-to-get-path-to-the-current-vimscript-being-executed
let s:path=fnamemodify(resolve(expand("<sfile>:p")), ":h")
