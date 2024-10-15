# Reimplementation of UNIX list directory (`ls`)

## Description
_ls_ implements limited functionality of UNIX command _ls_. For full documentation of `ls`, see `man ls` on an UNIX machine, or an [online manual](https://linux.die.net/man/1/ls).

## Prerequisites
`gcc` and `make` on a supporting system.

## Usage
Clone and run `make` in the cloned directory. Other commands (or _rules_) for _make_ can be found in the Makefile. For explanation of _make_ concepts, _make_ documentation is available [here (one page HTML)](https://www.gnu.org/software/make/manual/make.html).

Invocation: `./ft_ls [OPTION]... [FILE]...`

_ft_ls_ accepts only short style options, i.e. single character options. Allowed options are:
- `-l` - long listing format
- `-R` - recursive listing
- `-a` - include files starting with . ("hidden" files)
- `-r` - reverse order while sorting
- `-t` - sort by time, newest first

These options correspond directly with the UNIX _ls_ version.

## Notes
This is a learning project and not intended for use.
