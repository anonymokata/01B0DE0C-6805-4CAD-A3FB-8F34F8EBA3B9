set exrc
set secure
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
set colorcolumn=110
highlight ColorColumn ctermbg=darkgray
augroup project
	autocmd!
	autocmd BufRead,BunNewFile *.h,*.c set filetype=c.doxygen
augroup END
lst &path.="src/include,test/include"
