# DWM Build

**Patches**: tilegaps, hidevacanttags, alpha, pertag, noborder
 (for single window), titlecolor, scratchpad, attachbottom,
 movestack, statusallmons, leftlayout, autostart

**Unofficial Patches**: titlepos, statuspos,
remove gap on single, change/togglegaps

**Controls**: Mod Key = Mod4 (Windows key).

__Basics__:

Change to tag: Mod + [1-9]

Spawn terminal: Mod + Enter

Toggle scratchpad: Mod + `

Swap current slave with master: Mod + Shift + Enter

Quit window: Mod + Shift + q

Quit dwm: mod+ctrl+shift+q (I wanted this to be difficult to do to prevent
accidents)
<br></br>

__Patch Info__:

**Gaps**: Gap size between windows can be changed in the config.h with the gappx
variable. The gaps can also be changed on the fly with key bindings.

**Alpha**: Alpha value can be changed in config.h - it is a hex value from
0x000000 to 0xffffff

e.g.

```
static const unsigned int gappx = 8;
```
<br>

Other things can be changed in the config.h such as colours, fonts, tag names,
keybindings and a bunch of other things. Check it out :)

*Any changes to the config.h file will require a rebuild to take effect.*

*In the dwm directory*: ```sudo make clean install```
