A program that runs in the background to provide a different way to execute shortcuts. This program utilises key press sequences, following a master key \`ind, to execute different shell commands. This is meant for shortcuts and not key binds, such as volume up.


# Usage


## Create Configuration

Create the a config file, default location `$XDG_CONFIG_HOME/key_mapper/key_map` or `$HOME/.config/key_mapper/key_map` if `$XDG_CONFIG_HOME` is not set.

The file must contain a `Master` key binding. This key binding must be pressed before the program starts listening to key strings. Must be in a separate line. Key modifiers, like <kbd> Ctrl </kbd>, can be used. The list of currently supported key modifiers are as follows:

-   `C`: <kbd> Ctrl </kbd>
-   `M`: <kbd> Alt </kbd>
-   `S`: <kbd> Super </kbd>

The format for the `Master` key bind is as such: \((Mod-)^{+}^{}Key\). Where \(Mod\) is any modifier specified above and key is any single character key. An example would be `C-S-k` which is `Control+Super+k` which is the default in case it failed to recognise a master key bind.

Here you can also create key strings. The format of which is as such: \((key)^{+}^{}\ cmd\) where \(key\) is any single character key and \(cmd\) is the command to be executed. The key string has to be at least one character long and the command is any shell command.

Conflicting key string will be reported in the system log. Only the first conflicting key string will be registered.


# Installation


## Arch Linux

Install `shortcut-mapper-git` from AUR


## Git

1.  Clone this repo, `git clone ... DIR`
2.  `cd` into the directory
3.  Run `cmake . -B BUILD-DIR`
4.  Run `cmake --build BUILD-DIR`
5.  Run `cmake --install BUILD-DIR` with sudo privileges


# Future features

-   [ ] Show a dialogue box when activated

    To show the current shortcut string

-   [ ] Support input masks for shortcut strings

    Masks like <kbd> Ctrl </kbd> or <kbd> Alt </kbd>.

-   [ ] Support using shift
