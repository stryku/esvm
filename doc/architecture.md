# Architecture

## Registers

There are 16 general purpose and three dedicated registers named:
* r0 .. r15
* rret
* rip
* rrem

### r0 .. r15
General purpose registers. Just use it as you want.

### rret
Supposed to hold function return value.

### rip
An instruction pointer register.

### rrem
Stores division result reminder.

## Flags
Flags are set by cmp operation.

There are three of them:
* fe - is set only if last cmp arguments were equal
* fl - is set only if last cmp first argument was less that the second one
* fg - is set only if last cmp first argument was greater that the second one

