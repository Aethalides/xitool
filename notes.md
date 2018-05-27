## Runtime errors
### Segfaults
If these are occurring on calling X functions, then check to make sure that the resource being used hasn't been closed already. E.g. calling XIQueryDevice after closing the display will cause a segfault.

## Asorted noteds
   2 Virtual core pointer                          id=2    [master pointer  (3)]
   4 Virtual core XTEST pointer                id=4    [slave  pointer  (2)]
  10 Logitech G300s Optical Gaming Mouse       id=10   [slave  pointer  (2)]
  
  
  Virtual core keyboard                         id=3    [master keyboard (2)]
  
    ↳ Virtual core XTEST keyboard               id=5    [slave  keyboard (3)]
    ↳ Power Button                              id=6    [slave  keyboard (3)]
    ↳ Power Button                              id=7    [slave  keyboard (3)]
    ↳ Sleep Button                              id=8    [slave  keyboard (3)]
    ↳ AT Translated Set 2 keyboard              id=15   [slave  keyboard (3)]
    ↳ G11 Keyboard                              id=11   [slave  keyboard (3)]
    ↳ Gaming Keyboard                           id=12   [slave  keyboard (3)]
    ↳ Gaming Keyboard                           id=13   [slave  keyboard (3)]
    ↳ Logitech G300s Optical Gaming Mouse       id=9    [slave  keyboard (3)]
    ↳ Sycreader RFID Technology Co., Ltd SYC ID&IC USB Reader   id=14   [slave  keyboard (3)]

Master Keyboard and mice are always in pairs.

The master pointer device points to the master keyboard device, 
and the master keyboard device points to the master pointer device.

there could be devices not attached to any master

```
 id   type   class   ref   device name
------------------------------------------------
  2   master pointer   3    Virtual core pointer
  4   slave  pointer   2        Virtual core XTEST pointer
 10   slave  pointer   2        Logitech G300s Optical Gaming Mouse
  3   master keyboard  2    Virtual core keyboard
  5   slave  keyboard  3        Virtual core XTEST keyboard
  6   slave  keyboard  3        Power Button
```

[#] [T] [C] [R] [E] [N]
 2   M   P   3   Y   Virtual core pointer
 
How about using ANSI colours to highlight relationship.
For instance, matching id's will be printed in the same
colours. (just the id/m_id numbers).

We'll use indentation in the device names to show relationship between master
and slave devices also.


Obviously we'll turn off colours if device is not a tty
