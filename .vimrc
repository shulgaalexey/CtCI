"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" For using Vim as IDE
"
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set number

set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

augroup project
	autocmd!
        autocmd BufRead,BufNewFile *.h,*.cpp,*.c set filetype=c.doxygen
augroup END

let &path.="src/include,/usr/include/AL,"

" For Java
"set includeexpr=substitute(v:fname,'\\.','/','g')

set makeprg=make\ -C\ ./build\ -j9

nnoremap <F4> :make!<cr>
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
