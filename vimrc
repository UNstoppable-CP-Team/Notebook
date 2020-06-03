syntax on
set number
set noerrorbells
set tabstop=4 softtabstop=4
set shiftwidth=4
set autoindent
set smartindent
set cindent
noremap <F5> :w <bar> !g++ -o -std=c++14 -static -Wall -Who-unused-result -02 %:r.cpp -o %:r<CR>
noremap <F6> :%y+<CR>
noremap <F8> :<C-U> !./%:r <in
noremap <F9> :<C-U> !./%:r<CR>
"Alternative"
autocmd filetype cpp nnoremap <F5> :w <bar> !g++ -std=c++14 % -o %:r -Wl,--stack,268435456<CR>
autocmd filetype cpp nnoremap <F6> :%y+<CR>
autocmd filetype cpp nnoremap <F10> :!%r <in
autocmd filetype cpp nnoremap <F9> :!%:r<CR>
