gcat_opts=$(awk "
/option_list/ {
flag=1;
next;
}

/};/ {
flag=0;
}

flag {
a=index(\$0, \"{\")+2;
b=index(\$0, \",\")-1;
print \"-\"substr(\$0, a, b-a);
}

END {
print \"-help\";
}
" src/main.cpp)

# gcat_opts="-help -verbose -filters -topo -save-csv -save-dat"

_graphcat() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    COMPREPLY=( $(compgen -W "$gcat_opts" -- $cur) )
}

complete -o default -F _graphcat graphcat
complete -o default -F _graphcat gcat
