# Wimads' keymap for 3x5+3 split boards 
This is my personal keymap, which is optimized for CAD and graphic usage on a 3x5+3 layout. It utilizes a ***lot of combos***, and ***no homerow mods***, and ***only 3 layers***. It also has a (combo based) ***"CAD mode" for one handed operation***. 

### Unique aspects of this keymap:
* Slightly modified QWERTY base layout
* Uses only 3 layers (or 4 if you count CAD mode as a layer)
    * Default layer (modified qwerty)
    * Numpad/symbol layer (left: symbols | right: numpad)
    * Miscelaneous layer (for media and rarely used keys)
* Makes heavy use of combos (which is why 3 layers was sufficient)
* No homerow mods, but a customized approach to oneshot-mods on thumbs
* CAD mode: unique combo-based approach for one handed operation

## 1 | Base layout
### Alphas (modified QWERTY):
![Default layer](<_DEF layer.png>)

The base layout for this keymap is QWERTY, with some slight modifications to the symbol/punctuation keys (adding some logic to it rather than the randomness of traditional QWERTY symbols).
The basic logic behind this modification was to make a clear distinction between *punctuation* and *symbols*. 

I have put all *punctuation* that commonly occurs in text on the default layer; and all *symbols* that are related to maths or programming (or occur in text relatively infrequently) are on a symbol layer. This means that `/`, `<` and `>` have moved to the numpad/symbol layer, and `!` has moved to the default layer; and since `< >` now leave two empty spots, there is room to keep both `; :` and `' "` on the default layer (one of which would otherwise have to be dropped on a 5 column layout).

And to keep some logic to it, I have put related punctuation together like so: `normal shifted` --> `, ;`  `. :`  `! ?`  `' "`. After some initial getting used to this now feels a lot more natural than the traditional QWERTY punctuation to me. And due to the clear logical distinction between punctuation and other symbols, there is now also no confusion for when to acces the symbol layer for a symbol or when to use shift.

### Modifiers:
A 36 key layout requires some rethinking of the approach to modifiers and other non-alpha keys. A lot of people opt for homerow mods (like Miryoku), but that is something I could not get used to. Timing issues were too common and hard to dial in, and hitting accidental modifiers can result in funky and sometimes even disastrous accidental hot key presses, so that is something I wanted to avoid. 

A second motivator to not put my modifiers on the homerow, is that I'm using this layout with a QMK trackball. I click with mousekeys on my left hand keyboard (combos), while operating the ball with the right hand. In graphic and CAD software, modifiers combined with mouse clicks are pretty common, which means that when clicking with my left hand fingers, and moving the trackball with my right hand, that only conveniently leaves the left thumb for the modifiers.

So I opted for keeping all my modifiers on the thumb (except the _NUM layer modifier), and the most important ones for CAD use on left thumb (`alt shift control`). Pressing combinations of modifiers (say `control+shift`) then becomes a challenge. I worked around this by using oneshot mods, so I just need to tap `control` and then hold `shift`, so I still only need to hold down one thumb key at a time for `control+shift` (or any other modifier combination). 

However, I do not like oneshot modifiers for other purposes (when accidentally pressing control, I do not want the following alpha key to trigger a hotkey). Hence I customized the oneshot behaviour to be cancelled for non-modifier keys. So my oneshot modifiers effectively only work as oneshot keys when stacking modifiers, but otherwise act as regular mods. (look in my keymap.c in process_record_user if you want to know how I solved that).

Lastly, I have made sure that the modifiers are in the same spot on every layer, so it is very straight forward to make any modifier combination, even if the key is on a layer.

### Non-alpha keys (combos):
Since my modifiers and `space` take up all the thumb keys, there is no room left on the thumbs for keys like `enter`, `backspace` and `tab` etc. , which might otherwise have been a logical place to put them.

My approach for basically all keys that didn't find a spot on a dedicated key, is ***combos***. This also allowed me to keep the layer count down, which was important to me, as I found that having too many layers became confusing, hard to remember, and hard to develop muscle memory for.

For combos it is important to consider whether they impact regular typing (similar to how homerow mods can be a challenge to dial in). To avoid problems, I basically avoid any combos with 2 adjacent keys on common rolls and bigrams (except in CAD mode, but that will be covered later on).

![Most important combos](<_DEF main combos.png>)

The image above shows the most important combos I use for the default layer. `escape` `tab` and `enter` are on the center 3 keys, which are very convenient to press in regular typing without much risk of misfires. `backspace` and `delete` are on the index columns, which also have become a pretty natural reflex in typing. I have kept these symmetrical (both left and right hand have them), which is convenient for one handed use (and lazy browsing).

The above image was just for clarity, but far from complete. Visualizing a lot of combos is a bit of a challenge, but below an attempt to show a more complete overview (and even more will follow down below):

![Default layer combos](<_DEF combos.png>)


### Accented characters (ãàáäâ):
Dutch uses some (infrequent) accented characters, ë being most common. On a traditional keyboard with Dutch language settings, these keys are accessed through dead keys, which I do not find convenient. Hence I've made my own method, modifying the standard dead key behaviour to my own needs. 

Basically, I've made it such that holding `e` and then tapping `.` results in `ë`; tap different keys for different diacritics. The same works for all vowels. The image below shows which keys to tap for which diacritics, taking `a` as an example:

![Accented characters](<_DEF accented.png>)

### Navigation keys (vertical combos):
I use vertical combos for arrow keys, which are also pretty convenient to have available on the default layer. Though, how convenient vertical combos are really depends on your keyboard and keycaps. I use a choc spaced board with Chicago Steno keycaps, which allows for reasonably conveniently pressing a vertical combo with a single finger between two keys.

![Mouse and navigation combos](<_DEF combos mouse nav.png>)

### Mouse buttons (combos):
Since I am using this keyboard in conjunction with my own QMK  trackball device (Look for TB3S in my github repos), I also added combos for mouse buttons on my keyboard. I very much enjoy operating the trackball with my right hand (finger ball), and clicking with my left hand on the keyboard. There is no mouse button combos on the right half, because my trackball device has it's own buttons.

## 2 | Numpad and symbols
![Numpad and symbols layer](<_NUM layer.png>)

### Numpad:
I have arranged my `_NUM` layer with a numpad layout on the right side, which also has the symbols that relate to math `= * / + - ^` as well as `%` because it kind of made sense to have that on `P` position. The numpad also has a special `DOTCOMM` key, which acts as `DOT` or `COMMA` depending on its state - double tapping swaps its state - which is convenient when swapping between Dutch notation (using comma for decimals) or US notation (dot for decimals). In either state, it results in opposite when shifted (so shift+dot becomes comma when its in US state).

The `TAB` and `ENTER` combos also work on the numlayer, but `ENTER` becomes `NUMPAD_ENTER` (some softwares have different functions for either enter key).

I also have a combo (`J` + `'"`) for locking only the right half of the numpad layer (so only the numpad, left hand is still qwerty, which is useful in CAD mode discussed down below).

![alt text](<_NUM combos.png>)

### Symbols:
On the left hand side I have put all the symbols that relate to programming. All brackets are conveniently together. And all other keys are positioned such that they link to a QWERTY key --> `@` is above `A`; `$` is above `S`; `&` (et) is on `E`; `|` (oR) is next to `&` (and/or) and also on `R`; `~` (tilde) is on `T`; `` ` `` (grave) is on `G`; and then just `_` and `#` are left on the remaining keys. And lastly there is some custom shifted characters: `\` is on `shift+/`; and `€` is on `shift+$`. In other words, basically all symbols are in a logical easy to remember place, which is especially useful for symbols that you don't use very frequently and thus don't develop muscle memory for very quickly either.

For convenience, I also added combos for `-` and `=` on `<>` and `>]` repsectively, so its convenient to type `->` and `<=` and the like (which would otherwise have been on left and right hand; and since I'm using `F` and `J` as `_NUM` layer mods, that'd mean having to twice activate and release the layer with each mod).

### F-keys (combos):
F-keys are actually accessible through the default layer via combos, but I'm mentioning them here since they are positioned according to the Numpad layout. Basically I use a combo of tucky thumb key `MO(_MISC)` on default layer, with a key corresponding to a number on the numpad. So combo `MO(_MISC)`+`J`=`F4` (J corresponds with 4 on the numpad layer). Same for all other F keys, and F10-F12 are on the pinky column. For convenience I have also mirrored these combos to the left hand side (combo with `LALT`), which is useful in one handed use (like in CAD with right hand on mouse/trackball).

![F-key combos](<_NUM combos F-keys.png>)

## 3 | Miscelaneous layer
![Miscelaneous layer](<_MISC layer.png>)

Not much to be said here, all keys that didn't fit on default or numpad layer, and didn't warrant a dedicated combo, are on the `_MISC` layer. That is keys like `printscreen` and `insert`, but also volume and screen brightness. 

## 4 | CAD mode
![CAD mode combos](<_CAD combos.png>)

CAD mode is technically an extra layer in my keymap file, although it is basically fully transparent (it only changes `shift` to a mod-tap of `shift` and `space`). However, the main trick about this layer is that it activates an additional set of combos that enables one handed operation. It makes nearly all keys accesible through the left hand via combos. This is useful for CAD usage, so you can keep your right hand on the mouse / trackball, while typing shortcuts, commands, numbers, etc. with the left hand. As you can imagine though, this requires a ***lot*** of combos, which would make regular typing unworkable. Hence, the CAD mode layer exists to activate/deactivate those combos on demand.

Why combos and not the QMK swap-hands feature? Well, I just find combos more convenient than holding down a modifier to swap hands; it allows for more flexibility, and it also allows for building muscle memory a lot better than a modifier. This approach was actually inspired by the TAIPO layout (a 10 key chording layout, google it if you don't know it yet, its pretty cool) - I did experiment with TAIPO for a bit, and I found the chording approach very effective for single handed use.
