## Compile errors/warnings
### function may be candidate for attribute 'noreturn'
The error often lies not in the function being flagged, but in one of the functions it calls.

#### Example

```C
static table_column list_table[]={
	{(char*)"test",4,XDEVCLASS,ALIGN_LEFT,ALIGN_CENTER},
	{NULL,-1,-1,-1}
};

static size_t getLineLength(void) {

	size_t out=0;
	
	table_column *cols=list_table;
	
	while(cols->name!=NULL) {
		
		out+=cols->width;
	}
	
	return out+1;
}

char* sprintTableHeader(void) {
	
	size_t memneeded=sizeof(char)*getLineLength();
	
	char *out=malloc(memneeded);
	
	if(out==NULL)
		die_with_error("Unable to allocate %d byte(s) for table row");
	
	memset(out,0,memneeded);
	
	return out;
}
```

```bash
table.c:38:7: error: function might be candidate for attribute ‘noreturn’ [-Werror=suggest-attribute=noreturn]
 char* sprintTableHeader(void) {
```

In case you haven't noticed it yet, the bug is actualy in the `getLineLength` function. The compiler has spotted that the while loop never exits because we forgot to increment the pointer at the end of each iteration of the loop.

## Runtime errors
### Segfaults
If these are occurring on calling X functions, then check to make sure that the resource being used hasn't been closed 
already. E.g. calling XIQueryDevice after closing the display will cause a segfault.

## Asorted notes
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

field types via enum to reference `XIDeviceInfo` struct members

```
 XDEVID-> deviceid
 XDEVNAME -> name
 XDEVTYPE -> use (type)
 XDEVCLASS -> use (class)
 XDEVSTATE -> enabled
 
enum align
 ALIGN_NONE
 ALIGN_LEFT
 ALIGN_RIGHT
 ALIGN_CENTER

char *name,
size_t length,
int type (via enum),
int h_align (via enum),
int align (via enum)

{"id",4,XDEVID,ALIGN_CENTER,ALIGN_RIGHT},
```

```
 id   type    class   master    device name
------------------------------------------------
  2   master pointer    3     Virtual core pointer
  4   slave  pointer    2         Virtual core XTEST pointer
 10   slave  pointer    2         Logitech G300s Optical Gaming Mouse
  3   master keyboard  2     Virtual core keyboard
  5   slave  keyboard  3         Virtual core XTEST keyboard
  6   slave  keyboard  3         Power Button
```

[#] [T] [C] [R] [E] [N]
 2   M   P   3   Y   Virtual core pointer
 
How about using ANSI colours to highlight relationship.
For instance, matching id's will be printed in the same
colours. (just the id/m_id numbers).

We'll use indentation in the device names to show relationship between master
and slave devices also.


Obviously we'll turn off colours if device is not a tty
