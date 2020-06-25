" Vim (~/.vimrc) / Neovim (~/.config/nvim/init.vim) Configuration 
" vim: set tw=0 et ts=8 sw=3 sts=3 smarttab fenc=utf-8 fdm=marker :

" SANE DEFAULTS: {{{1
" Neovim is probably by default set to `no compatible`.
" Shortest of short messages.
"
set nocompatible
set shortmess+=astcTWAIF
syntax on

" COMPLETIONS: {{{1
" This deals with filename completion (<TAB>) and <Ctrl-P>/<Ctrl-N>
" Tab completion & show possiblities in ‘menu’.
" The <CR> mapping simply inserts the current selection.
" TODO: Sort out `path`.
"
set path=.,,**
set wildmenu " completeopt=longest,menuone
set wildmode=longest,list,full
set complete-=i
set complete+=kspell
set completeopt=menuone,longest
set showmatch
inoremap <expr> <CR> pumvisible() ? "\<C-y>" : "\<C-g>u\<CR>"
inoremap <expr> <C-n> pumvisible() ? '<C-n>' :
  \ '<C-n><C-r>=pumvisible() ? "\<lt>Down>" : ""<CR>'
set foldcolumn=1 nofoldenable foldmethod=marker

" BELLS AND FLASHES: {{{1
" No noises or flashes, please.
"
set novisualbell noerrorbells visualbell t_vb=
au GUIEnter * set visualbell t_vb=

" LINE NUMBERS: {{{1
" Set relative line numbering.
"
set number
set relativenumber

" INDENTATION: {{{1
"
set expandtab tabstop=8 shiftwidth=3 softtabstop=3 smarttab
set smartindent autoindent nocindent
set laststatus=0
set showtabline=1
set noshowmode

" BUFFERS: {{{1
" Allow switching away from unsaved buffers without prompts.
" Auto-reload externally changed buffers.
"
set hidden
set autoread
au FocusGained,BufEnter * checktime

" BACKUPS AND SWAP FILES: {{{1
" No backups, no swap files.
" In case ‘swap files’ gets enabled, write them in `~/.local/nvim/`.
" Set persistent undo files in `~/.local/nvim/undo/`.
"
set nobackup
set nowritebackup
set noswapfile
set directory=~/.local/nvim/swap/
set undofile
set undodir=~/.local/nvim/undo/

if has('syntax') && has('eval')
  packadd! matchit
endif

" FILE TYPE SPECIFICS: {{{1
augroup Behaviour
   au!
   " this is optional and debatable, for some it will work:
   " au BufEnter * silent! lcd %:p:h | silent! set nohls
   " au BufReadPost * silent! lcd %:p:h | silent! set nohls
   au BufReadPost *
      \ if line("'\"") >= 1 && line("'\"") <= line("$") &&
      \    &ft !~# 'commit'
      \ |  try | exe "normal! g`\"zvzz" | catch | endtry
      \ | endif
   au BufReadPost *.{c,cpp,h,hpp,java,perl,js,php}
      \ setl nocindent ai
   au BufReadPost Makefile
      \ setl noexpandtab ts=4 sw=4
augroup END


" COLORS: {{{1
" We assume at least 256 colours everywhere. Accept errors otherwise.
" Override some highlight items like `Comment` and `Normal`. Slate is a
" standard colorscheme, so we use that (with customisations).
"
" We create a `TrailSpace` highlight item, which we style. That includes
" special colours for optional-hyphen and emdash.
"
augroup WhiteSpace
   au!
   au! WinEnter,BufRead,BufNew,InsertLeave,InsertEnter,BufWinEnter *
      \ :match TrailSpace /\s\+$\| \+\ze\t/ |
      \ :match UnicodeDashes /­\|—\|␣\|‗ /
   au! BufWinLeave * call clearmatches()
augroup END

augroup Appearance
   func! CSO_all()
      "hi clear CursorLine
      hi Cursor guibg=#00FF00 guifg=#000000
      hi Comment ctermfg=248 cterm=italic guifg=#998F77 gui=italic
      hi default TrailSpace guifg=#445566 guibg=#161616 ctermbg=8
      hi default UnicodeDashes gui=bold guifg=#FF00FF guibg=NONE ctermfg=11
   endfu
   au! ColorScheme * call CSO_all()
   func! CSO_slate()
      hi clear Normal
      "hi Normal ctermbg=236 guibg=#17191c guifg=#B7B7B7
      hi Normal ctermbg=236 guibg=NONE guifg=#B7B7B7
      hi clear ToDo
      hi ToDo ctermbg=240 guifg=#AA9944
      hi Cursor guibg=#99FF99 guifg=#000000
      hi CursorLine guibg=black
      hi CursorLineNr guibg=#121212 guifg=#BBBB00
      hi CursorColumn guibg=black
      hi PreProc ctermbg=NONE ctermfg=93 guibg=NONE guifg=#d7aa48
      hi Include ctermbg=NONE ctermfg=92 guibg=NONE guifg=#f7aa48
      hi Visual ctermfg=NONE ctermbg=white guifg=black guibg=#999999
      hi NonText guifg=#8c39cc guibg=NONE
      hi clear Statement | hi Statement guifg=#6F94D2
      hi clear Type | hi Type guifg=#229c55
      hi Pmenu guifg=NONE guibg=black
      hi PmenuSel guifg=yellow guibg=#000077
      hi String guifg=#009CBE
      hi Operator guifg=#CC4400
      hi Search gui=bold guibg=black guifg=#FFFFFF
      hi IncSearch gui=bold guibg=black guifg=#FFFF00
      hi TabLine gui=none guibg=#333333
      hi TabLineFill gui=none guibg=#333333
      hi TabLineSel gui=bold guibg=NONE guifg=#FFFFFF
      hi ColorColumn guibg=#222222
      hi StatusLine guibg=#334455 guifg=#ccccaa
      hi StatusLineNC gui=none guibg=#25272f guifg=#888800
      hi clear LineNr | hi LineNr guifg=grey50
      hi clear SignColumn
   endfu
   au! ColorScheme {slate,torte} call CSO_slate()
augroup END

set termguicolors
set background=dark
colorscheme slate

" MARKDOWN: {{{1
func! MDFoldExpr(lnum)
   if getline(a:lnum) =~? '\v^[^#]|^\s*$'
      return '1'
   endif
   return '>1'
endfu

augroup MySyntax
   func! WrappedText()
      setlocal linebreak wrap textwidth=0 colorcolumn= foldignore=
      setlocal nonumber norelativenumber
      set cursorline
      setlocal virtualedit=block,insert,onemore spell
      if &filetype == "markdown"
         setl fdm=expr fde=MDFoldExpr(v:lnum)
      endif
      nnoremap <buffer> $ g$
      nnoremap <buffer> g$ g_
      nnoremap <buffer> 0 g0
      nnoremap <buffer> g0 _zh
      nnoremap <buffer> j gj
      nnoremap <buffer> k gk
      nnoremap <buffer> gj j
      nnoremap <buffer> gk k
      xnoremap <buffer> $ g$
      xnoremap <buffer> g$ g_
      xnoremap <buffer> 0  g0
      xnoremap <buffer> g0 _
      xnoremap <buffer> j gj
      xnoremap <buffer> k gk
      xnoremap <buffer> gj j
      xnoremap <buffer> gk k
   endfu
   au! FileType markdown
      \ call WrappedText()
   au! BufReadPost,BufNewFile *.{md,md.txt}
      \ set filetype=markdown | call CSO_all()
augroup END

" KEYBOARD MAPPINGS: {{{1
" The following works best when lines are wrapped, as in markdown. It 
" maybe should only be enabled when ‘wrapping’ is on. Enabling globally,
" might not be a good idea.
"
nnoremap zl 40zl
nnoremap zh 40zh

" fast-typing `;;` == ESC, but leaves cursor on current character.
inoremap ;; <ESC>`^
xnoremap ;; <ESC>
nnoremap ;; <ESC>:
cnoremap ;; <ESC>

" Let Ctrl-L toggle highlightsearch and resync syntax highlighting.
nnoremap <silent> <C-L> :set hls!<CR>:syn sync fromstart<CR><C-L>
nnoremap / :set hls<CR>:let @/=''<CR>/

nmap Y y$

" PERSONAL: {{{1
" These timings should be adjusted to taste.
set ttyfast ttimeout ttimeoutlen=100
set lazyredraw updatetime=300 timeoutlen=500

" Toggle `cursorline` on enter/leave insert mode.
autocmd! InsertEnter * set nocursorline | set cursorcolumn
autocmd! InsertLeave * set cursorline | set nocursorcolumn

" NETRW: {{{1
" Make it easier to use.
"
let g:netrw_banner=0       | let g:netrw_menu=0      | let g:netrw_keepdir=0
let g:netrw_browse_split=0 | let g:netrw_liststyle=3 | let g:netrw_silent=1 
let g:netrw_list_hide=
   \'.*\.exe\*$,.*\.com\*$,.*\.obj$,.*\.jpg$,.*\.dll$.*\.bmp$,'.
   \'.*\.png$,.*\.jpeg$,.*\.pyc$,.*\.luac$,.*\.DS_Store.*$,.*'.
   \'\.aux$,.*\.out$,.*\.toc$'

" SEARCHING: {{{1
"
set ignorecase smartcase
set incsearch nohlsearch

" OTHERS: {{{1
" 
set scrolloff=2 sidescrolloff=2
set nofoldenable "rather do it manually"
set encoding=utf-8 fileencoding=utf-8
set fileformats=unix,dos,mac
set pumheight=10
set mouse=a
set splitbelow splitright
set conceallevel=0
set formatoptions-=cro
set clipboard+=unnamedplus
set modeline
set modelines=20
set nowrap
set virtualedit=block,onemore
set backspace=eol,indent,start

set whichwrap=<,>,b,h,l
set selection=exclusive
set colorcolumn=+1,81,73
set textwidth=0

" make n always search forward and N backward
nnoremap <expr> n 'Nn'[v:searchforward]
nnoremap <expr> N 'nN'[v:searchforward]

" make ; always "find" forward and , backward
nnoremap <expr> ; getcharsearch().forward ? ';' : ','
nnoremap <expr> , getcharsearch().forward ? ',' : ';'

nnoremap <silent> <C-V> "+P:set nopaste<CR><C-O>`.
inoremap <silent> <C-V> <C-O>"+P<C-O>:set nopaste<CR><C-O>`.
cnoremap <C-V> <C-R>+
cnoremap <C-A> <Home>
cnoremap <C-E> <End>
cnoremap <C-P> <Up>
cnoremap <C-N> <Down>

let g:mapleader      = '\'
let g:maplocalleader = ' '

nnoremap <leader>e :set virtualedit=all<CR>
nnoremap <leader>E :set virtualedit=block,onemore<CR>
nnoremap <silent> <leader>cd :lcd %:p:h<CR>

nnoremap ' `
nnoremap ` '

" Start new line from any cursor position in insert-mode
" This require terminal remappings: https://stackoverflow.com/a/42461580
" Maybe rather use: https://github.com/tpope/vim-unimpaired
inoremap <S-Return> <C-o>o

" FZF INTEGRATION: {{{1
" https://github.com/junegunn/fzf/blob/master/README-VIM.md
" If installed using Homebrew
set rtp+=/usr/local/opt/fzf
" If installed using git
"set rtp+=~/.fzf
"nnoremap <leader>f :FZF .<CR>

set clipboard=unnamed
if has("unnamedplus") " X11 support
    set clipboard+=unnamedplus
endif

" FROM VIM: {{{1
" From Vim's `defaults.vim`
set display=truncate   " Show @@@ in the last line if it is truncated.
set nrformats-=octal
" let `Q` execute last macro. Also popular: `map Q gq`.
map Q @@
inoremap <C-U> <C-G>u<C-U>

silent! dig -. 8230 "add diggraph: U+2026=… HORIZONTAL ELLIPSIS
set spelllang=en_gb
if (has('unix') || has('winunix')) && !has('nvim')
   set spellfile=$XDG_CONFIG_HOME/vim/spell/en.utf-8.add
elseif has('nvim')
   set spellfile=$XDG_CONFIG_HOME/nvim/spell/en.utf-8.add
else
   set spellfile=$VIM/.vim/spell/en.utf-8.add
endif

function! BufDel(arg)
   if !buflisted(a:arg) || a:arg =~ 'scratch'
      exec ':bwipe! ' . a:arg
   else
      exec ':bdelete ' . a:arg
   endif
endfunction

function! ScratchEdit()
   if bufexists('scratch') | sbuffer scratch | return | endif
   exec ':$tabnew'
   setlocal noswapfile buftype=nofile hidden nobuflisted filetype=markdown
   file scratch
   lcd ~
endfunction

function! ScratchClose()
   if bufexists('scratch') | bwipe! scratch | return | endif
endfunction

command! BZ call BufDelEmpty()
func! BufDelEmpty()
   let [i, n; empty] = [1, bufnr('$')]
   while i <= n
      if bufexists(i) && bufname(i) == ''
         call add(empty, i)
      endif
      let i += 1
   endwhile
   try
      if len(empty) > 0
         exe 'bdelete' join(empty)
      endif
   catch
   endtry
endfu

" TABS: {{{1
" Lots of opinionated mappings for handling tabs.
"
set switchbuf=useopen,usetab,newtab
nnoremap <C-C> :call BufDel(@%)<CR>
nnoremap <silent> <TAB> gt
nnoremap <silent> <S-TAB> gT
nnoremap <silent> <leader>ta :tab ball<CR>
nnoremap <silent> <leader>tc :tabclose<CR>
nnoremap <silent> <leader>tn :$tabnew<CR>
"nnoremap <silent> <leader>to :tabonly<CR>
nnoremap <leader>to :$tabnew<space>
nnoremap <leader>te :$tabedit <C-r>=expand("%:p:h")<cr>/
"nnoremap <leader>te :tabedit<space>
nnoremap <leader>th :$tab help<space>
nnoremap <leader>tf :$tabfind<space>
nnoremap <leader>tm :tabmove<space>
nnoremap <silent> <leader>bn :sbnext<CR>
nnoremap <silent> <leader>bp :sbprev<CR>
nnoremap <leader>/ :sbuffer<space>
nnoremap <silent> <leader>ss :call ScratchEdit()<CR>
nnoremap <silent> <leader>sx :call ScratchClose()<CR>
nnoremap <silent> <C-N> :sbnext<CR>
nnoremap <silent> <C-P> :sbprev<CR>
nnoremap <leader>f. :FZF .<CR>
nnoremap <leader>nn :set invrelativenumber<CR>
nnoremap <leader>nu :setlocal number relativenumber<CR>
nnoremap <leader>no :setlocal nonumber norelativenumber<CR>
" <leader>'tt' toggles between last two visited tabs.
let g:lasttab = 1
nmap <Leader>tt :exe "tabn ".g:lasttab<CR>
au TabLeave * let g:lasttab = tabpagenr()
vmap < <gv
vmap > >gv
" sudo save file when not loaded with sudo. here are two options. select one.
cmap w!! w !sudo tee > /dev/null %
"cnoremap w!! execute 'silent! write !sudo tee % >/dev/null' <bar> edit!
nnoremap <leader>w :w<CR>
nnoremap <leader>W :wall<CR>
nnoremap <leader>Q :qall!<CR>
nnoremap <leader>Z :xall<CR>
nnoremap <leader>sl :set laststatus=2 noruler<CR>:<CR>
nnoremap <leader>so :set laststatus=0 ruler<CR>:<CR>

" Changes are saved to the ‘black hole’ register.
nnoremap c "_c
set signcolumn=yes:1
set laststatus=2

" STATUS LINE {{{1
"
" These settings are all related to the information displayed, and the
" colours used for the status line at the bottom of the Vim screen.
"
func! QFixBufNr()
   for l:n in range(1, bufnr('$'))
      if buflisted(l:n) && getbufvar(l:n, '&buftype') == 'quickfix'
         return l:n
      endif
   endfor
   return 0
endfu

func! QFixWinNr()
   let l:bn = QFixBufNr()
   let l:wn = 0
   try | if l:bn
         let l:wn = getbufinfo(l:bn)[0]['windows'][0]
         let l:wn = getwininfo(l:wn)[0]['winnr']
      endif
   catch | endtry
   return l:wn
endfu

func! QFixTitle()
   return getwinvar(QFixWinNr(), 'quickfix_title') 
endfu

func! QFixIsOpen()
   let l:n = QFixBufNr()
   if l:n && !empty(win_findbuf(l:n))
      return l:n
   endif
   return 0
endfu

hi! SLColor guifg=#000000 guibg=#33BBCC
   \ ctermbg=lightgreen ctermfg=black

func! SLSetColor(mode)
   if a:mode =~ 'leave'
      hi! link SLColor StatusLineNC
      hi! link SLInfo StatusLineNC
      return ''
   endif
   if &readonly
      hi! SLColor guifg=#000000 guibg=#33EE66
         \ ctermbg=lightgreen ctermfg=black
   elseif &modified
      hi! SLColor guifg=#000000 guibg=#FF663C
         \ ctermbg=lightred ctermfg=white
   elseif &buftype =~ 'quickfix' || &buftype =~ 'help'
      hi! SLColor guifg=#000000 guibg=#33BB33
         \ ctermbg=lightgreen ctermfg=black
   elseif mode() =~# '\v(n|no)'
      hi! SLColor guifg=#000000 guibg=#44BBFF
         \ ctermbg=lightcyan ctermfg=black
   elseif mode() =~# '\v(v|V|)'
      hi! SLColor guifg=#000000 guibg=#CC66CC
         \ ctermbg=lightmagenta ctermfg=black
   elseif mode() =~# '\vi'
      hi! SLColor guifg=#000000 guibg=#CCAA33
         \ ctermbg=14 ctermfg=black
   else
      hi! SLColor guifg=#000000 guibg=#33BB33
         \ ctermfg=15 ctermbg=8
   endif
   hi! SLInfo gui=NONE guifg=#000000 guibg=#AAAA00
         \ ctermbg=lightgreen ctermfg=black
   return ''
endfu

func! SLChelper(mode)
   let l:sl = ""
   if &buftype =~ "quickfix"
      if !empty(QFixTitle()) | let l:sl.= QFixTitle() | endif
   elseif &buftype =~ "help"
      return "HELP"
   else
      let l:sl.= fnamemodify(getcwd(), ':~')
"      let l:sl.= &modified ? " ϟ" : "  "
   endif
   return l:sl
endfu

func! SLCmode()
   let l:mode = ' '
   if &buftype !~ 'quickfix' && &buftype !~ 'help'
      let l:mode = toupper(mode())
      if l:mode =~ '' | let l:mode = 'V' | endif
   endif
   return l:mode
endfu

func! SLCreate(mode)
   let l:sl = "%{SLSetColor('".a:mode."')}"
   let l:sl.= "%#SLColor#  %{SLCmode()}  %*"
   let l:sl.= " %{SLChelper('".a:mode."')}"
   let l:sl.= " %* %R %=%h%w"
   if &filetype =~ 'help'
      let l:sl.= " %-3P "
   else
      "let l:sl.= " %{&ft} %#SLInfo# %{&encoding}"
      let l:sl.= &modified ? "ϟ" : " "
      let l:sl.= " %{&ft}›%{&encoding}"
      let l:sl.= "›%{&fileformat} %#SLInfo# %3v⋮%3P "
   endif
   return l:sl
endfu

augroup StatusLine
   au!
   au WinEnter * setl statusline=%!SLCreate('enter')
   au WinLeave * setl statusline=%!SLCreate('leave')
   au BufEnter * call SLSetColor('enter')
   au InsertEnter * call SLSetColor('enter')
   au InsertLeave * call SLSetColor('leave')
augroup END

set statusline=%!SLCreate('Enter')
set showtabline=3
set guioptions-=e

set foldcolumn=0 nofoldenable foldmethod=marker
autocmd BufLeave term://* stopinsert
set shell=/usr/local/bin/zsh

" Prevent x from overriding what's in the clipboard.
" noremap x "_x
" noremap X "_x

" Prevent selecting and pasting from overwriting what you originally copied.
xnoremap p pgvy
xnoremap P Pgvy

" Keep cursor at the bottom of the visual selection after you yank it.
vmap y ygv<Esc>
"set listchars=nbsp:␣,tab:│\ ,trail:⋅,extends:▓,precedes:▒
"set listchars=nbsp:‗,tab:┊\ ,trail:⋅,extends:▓,precedes:▒
set listchars=nbsp:‗,tab:┊⋅,trail:⋅,extends:▓,precedes:▒
set list

if has('nvim')
   set inccommand=split
   set scrollback=5000
   set wildoptions=
endif

command! -nargs=1 -bang GrepBuffer
   \ :execute printf('Capture: global%s/%s/print',
   \    expand('<bang>'),
   \    <q-args>)

" set statusline=%<%F\ %m%r%h%w%y%{'['.(&fenc!=''?&fenc:&enc).']['.&fileformat.']'}%=%l/%L,%c%V%8P
" Avoiding getting <NUL> from <C-Space>.
map <NUL> <C-Space>
map! <NUL> <C-Space>

" Adding blank lines.
nnoremap <silent><expr> <CR> &buftype ==# 'quickfix' ? '<CR>' : ':<C-U>call append(".", repeat([""], v:count1))<CR>'
nnoremap <silent> <Leader>O :<C-U>call append(line('.') - 1, repeat([''], v:count1))<CR>

"let &showbreak='⤷ '
"let &showbreak='╲ '
"let &showbreak='▌'
let &showbreak='┆'
set breakindent

" RIPGREP:
" Running make and jumping to errors {{{1
let [s:grep_prg, s:grep_format] = ['%s -SF --vimgrep', '%f:%l:%c:%m']
if executable('rg')
    let &grepprg = printf(s:grep_prg, 'rg')
    let &grepformat = s:grep_format
endif
unlet! s:grep_prg s:grep_format


" TERMINAL TITLE: {{{1
" set title titlestring=%<%t%=
" auto BufEnter * let &titlestring = expand("%:t")

" RULER: {{{1
"
" hi RulerFormat ctermbg=1 guibg=#334455
" set ruler
" set rulerformat=%220(%#RulerFormat#%=%t\ %)
" augroup RulerFormat
"    autocmd!
"    autocmd WinEnter,BufEnter vimrc call matchadd('RulerFormat', 'rulerformat=\zs.\+', -1)
" augroup END

" RANDOM: {{{1
set cmdheight=2
" set laststatus=1

set shiftround
set tildeop
set nostartofline

augroup term_settings
   autocmd!
   " Do not use number and relative number for terminal inside nvim
   autocmd TermOpen * setlocal norelativenumber nonumber
   " Go to insert mode by default to start typing command
   autocmd TermOpen * startinsert
augroup END

augroup RestoreCursorShapeOnExit
   autocmd!
   autocmd VimLeave * set guicursor=a:ver33
augroup END

