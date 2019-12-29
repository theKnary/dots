#
# ~/.bashrc
#

# bash settings
# vi mode
set -o vi
# single tab completion
bind 'set show-all-if-ambiguous on'
# cycle through autocompletion
bind TAB:menu-complete

# lang
#export LANG=en_CA.UTF-8
#export LANGUAGE=en_CA.UTF-8
#export LC_ALL=en_CA.UTF-8

export GOPATH=$HOME/.cstmpkgs/gospace/

## Added path variables
export PATH=$PATH:/opt/android-studio/bin/
export PATH=$PATH:/opt/VSCode-linux-x64/bin/
export PATH=$PATH:/home/knary/.scripts/
export PATH=$PATH:$GOPATH/bin/

### nnn
export NNN_OPENER=xdg-open
export NNN_USE_EDITOR=1
export NNN_SCRIPT=/home/knary/.scripts
# nnn temp var and cd on exit function (must run with 'n')
export NNN_TMPFILE="/tmp/nnn"
n(){
	nnn "$@"
    if [ -f $NNN_TMPFILE ]; then
		. $NNN_TMPFILE
		 rm -f $NNN_TMPFILE > /dev/null
	fi
}

[[ $- != *i* ]] && return

# import custom git bash status
source ~/.bash_git

	# user						# machine						# dir
# default uncoloured user and machine names:
#PS1='[\u@\h \W]\$ '

# coloured user, machine, and current directory:
#PS1='\[\e[4m\e[1m\e[3m\e[32m\u@\e[23m\e[37m\e[21m\e[23m\h\e[24m \e[34m\W \]\e[0m> '

# git prompt, without user and machine name, coloured dir, '>' as symbol
PS1='\[\[$(git_prompt)\]'
PS1+=' \[\e[1m\e[34m\]\W \[\e[39m>\]\[\e[0m\] \]'

# aliases
alias o="xdg-open"
alias p="sudo pacman"
alias ls="ls -hN --color=auto --group-directories-first"
alias grep="grep --color=auto"
alias weather="curl wttr.in/?Toronto"
alias sys="sudo systemctl"
alias kronycle="cd ~/dev/kronycle"
alias trash="mv $@ -t ~/.trash/"

alias zathura="~/.scripts/tzathura"
alias surf="~/.scripts/tsurf"
