
execute pathogen#infect()
syntax on
filetype plugin indent on

set exrc
set secure

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" For using Vim as IDE
"
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

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
"set makeprg=make\ -C\ .\ -j9

nnoremap <F4> :make!<cr>
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


"""nmap <silent> <C-n> :NERDTreeToggle<CR>
nnoremap <silent> <F8> :NERDTreeToggle<cr>
let NERDTreeWinPos = "left"
