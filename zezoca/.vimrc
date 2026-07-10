" Example of caling llama in vim
let g:llama_config = {
\   'endpoint_fim': 'http://your__machine:8080/infill',
\   'show_info': 0,
\   'auto_fim': v:true
\}

call plug#begin()
Plug 'ggml-org/llama.vim'
:call plug#end()
