# ST Build

**Patches**: scrollback + mouse support, cursor blink (unofficial),
bold is not bright, clipboard

**Scrollback**: Alt [hold] + vim bindings (k = up, j = down, u = further up,
d = further down) OR Shift [hold] + mouse wheel

**Cursor Blink**: Cursor type can be set to blink in config.h. Frequency can
also be changed.

**Clipboard**: Copy = Ctrl [hold] + Alt [hold] + c OR just highlight a region,
Paste = Ctrl [hold] + Alt [hold] + v OR Shift [hold] + insert

**Transparency**: I don't use the aplpha patch anymore because you can just make
a compton rule for transparency. -> You can check my compton config for
reference.

<br>

Other things can be changed in config.h such as colours, key bindings, and cursor type.

*Any changes to the config.h file will require a rebuild to take effect.*

*In the st directory*:
```sudo make clean install```
