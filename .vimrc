" VIMRC - knary

" -- Basics --

" turn off all error bells
set noerrorbells visualbell t_vb=

" detect filetype and load syntax
filetype plugin on
filetype indent on
set nocompatible
syntax on

" -- Settings --

" status line
set laststatus=2
set statusline=
set statusline+=%#ColorColumn# " colour
set statusline+=\ %R\          " readonly flag
set statusline+=\ %M\          " modified [+] flag
set statusline+=\ %F\          " full path
set statusline+=%=             " right align
set statusline+=\ %Y\          " file type
set statusline+=\ %3l:%-2c\    " line + column
set statusline+=\ %3p%%\       " scroll percentage

" highlight all matching searches
set encoding=utf-8
set number
set relativenumber
set splitbelow
set splitright
set wildmode=longest,list,full
set wildmenu

" vim file browser
let g:netrw_liststyle=3
let g:netrw_banner=0
let g:netrw_browse_split=3
let g:netrw_winsize=20

" spacing
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
" tabbing, trailing spaces etc.
set listchars=tab:\|\ ,extends:›,precedes:‹,nbsp:·,trail:·
" text width
set tw=80

" colours and highlight col 81 and 121 (80, 120 col wrapping standards)
colors peachpuff
set colorcolumn=81,121,122
hi ColorColumn ctermbg=8
"line numbers
hi LineNr ctermfg=8
hi CursorLineNr ctermfg=white

" vert split colours
hi VertSplit ctermfg=8
hi VertSplit ctermbg=8

" -- Mappings --

" functions

" ide mode (by making 2 vertical splits, resizing and returning to middle) - ~120 column size
" open terminal and tree
let s:ide = 0
function! ToggleIde()
	if s:ide
		call feedkeys("\<Esc>\<C-w>h:q\<CR>\<C-w>l:q\<CR>\<C-w>jexit\<CR>")
		let s:ide = 0
	else
		call feedkeys("\<Esc>:Vexplore\<CR>\<C-w>w:rightb vs tmp\<CR>\<C-w>h\<C-w>46>:term\<CR>\<C-w>15-\<C-w>k")
		let s:ide = 1
	endif
endfunction
" toggle ide mode with ctrl i (same as tab)
noremap <C-i> :call ToggleIde()<CR>

" general
noremap <F1> :set list!<CR>
noremap <F2> :Vexplore<CR>
noremap <F6> :setlocal spell! spelllang=en_ca<CR>

" insert brackets etc.
inoremap ( ()<Esc>F(a
inoremap { {}<Esc>F{a
inoremap [ []<Esc>F[a
inoremap "" ""<Esc>F"a

" lazy nav
inoremap jj <Esc>
inoremap ,, <Esc>la

" tabs
noremap <C-t> :tabnew 
noremap <C-l> :tabn<CR>
noremap <C-h> :tabp<CR>

" filegroups
let code = "php,java,c,cpp,h,cs,css,js,json,html,py,pyw,sh,bib"
let web = "php,html,js,css"

" programming files
execute "autocmd Filetype ".code." inoremap {<CR> {<CR>}<Esc>O"
execute "autocmd Filetype ".code." inoremap {; {<CR>};<Esc>O"
execute "autocmd Filetype ".code." inoremap ;; <Esc>$a;"
execute "autocmd Filetype ".web." inoremap ;' </<C-X><C-O><C-X><Esc>F<i"
execute "autocmd Filetype ".web." inoremap < <><Esc>F<a"
autocmd FileType cpp map <F5> :w<CR> :!clear && g++ *.cpp && ./a.out<CR>

" latex files
autocmd BufRead,BufNewFile *.tex set filetype=tex
autocmd Filetype tex inoremap " ``''<Esc>F`a
autocmd Filetype tex map <F5> :w<CR>:!pdflatex %<CR><CR>:!biber %:r<CR><CR>:!pdflatex %<CR><CR>
autocmd Filetype tex map <F3> <F5>:!clear && pdftotext %:r.pdf - \| wc -w<CR>

" groff files
autocmd BufRead,BufNewFile *.me,*.ms set filetype=groff
autocmd Filetype groff map <F5> :w<CR>:!groff -%:e % -T pdf > %:r.pdf<CR><CR>
autocmd Filetype groff map <F3> <F5>:!clear && pdftotext %:r.pdf - \| wc -w<CR>

" fountain files
autocmd BufRead,BufNewFile *.fountain set filetype=fountain
autocmd Filetype fountain noremap <F5> :w<CR>:!textplay < % > %:r.html && wkhtmltopdf -q -s Letter -R 2cm -B 2cm -L 2cm -T 2cm %:r.html %:r.pdf 2> /dev/null && rm %:r.html<CR><CR>
