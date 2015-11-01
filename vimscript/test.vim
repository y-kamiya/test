echon 'Hello'
let num1 = 1
let num2 = 2
echo num1 + num2

let str1 = 'aaa'
let str2 = 'bbb'
let join = join([str1, str2, 'ccc'], '/')
echo join
echo join[3]
echo join[2:3]

let dict = {
\   'a': 1,
\   'b': 2,
\ }
echo dict
echo keys(dict)
echo values(dict)

echo [1,2] == [1,2]
let val = 1
echo val is 1

function! Multi(n1, n2)
    return a:n1 * a:n2
endfunction
echo Multi(num1, num2)

function! s:sum(n,...)
    let num = 0 "a:n
    for i in a:000
        let num += i
    endfor
    echo a:1
    return num
endfunction
echo s:sum(1,2,3,4,5)

for line in readfile('read')
    echo line
endfor

call writefile(['aa','bb','cc'], 'write')

let list = [1,'a',2,[1,3,5]]
for i in list
    echo i
    unlet i
endfor

echo expand("<cfile>")
echo expand("<cword>")
echo expand("<cWORD>")
echo line(".")
echo col(".")

function! s:movingCursor()
    let cursorPos = getpos(".")
    echo cursorPos
    call cursor(10,10)
    call setpos(".", cursorPos)
endfunction
call s:movingCursor()

function! s:displayRange() range
    echo a:firstline
    echo a:lastline
endfunction
10,20call s:displayRange()
