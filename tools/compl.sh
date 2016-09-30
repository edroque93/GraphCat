gcat_opts="-help -verbose -filters -topo -save-csv -save-dat"

_graphcat() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    COMPREPLY=( $(compgen -W "$gcat_opts" -- $cur) )
}

complete -o default -F _graphcat graphcat
complete -o default -F _graphcat gcat
