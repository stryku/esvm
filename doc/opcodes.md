# Opcodes

## mov
* `mov ra , rb`- moves value from `rb` to `ra`
* `mov ra , [<memory cell>]`- moves value from memory cell to `ra`
* `mov [<memory cell>] , ra`- moves value from `ra` to memory cell

## add
* `add ra , rb`- adds value from `rb` to `ra`
* `add ra , [<memory cell>]`- adds value from memory cell to `ra`
* `add [<memory cell>] , ra`- adds value from `ra` to memory cell

## sub
* `sub ra , rb`- subtracts value from `rb` to `ra`
* `sub ra , [<memory cell>]`- subtracts value from memory cell to `ra`
* `sub [<memory cell>] , ra`- subtracts value from `ra` to memory cell

## mul
* `mul ra , rb`- multiplies value of `ra` by value from `rb`
* `mul ra , [<memory cell>]`- multiplies value of `ra` by value from `<memory cell>`
* `mul [<memory cell>] , ra`- multiplies value of `<memory cell>` by value from `ra`

## div
* `div ra , rb`- divides `ra`'s value by value from `rb`. Stores reminder in `rrem`.
* `div ra , [<memory cell>]`- divides `ra`'s value by value from `<memory cell>`. Stores reminder in `rrem`.
* `div [<memory cell>] , ra`- divides `<memory cell>`'s value by value from `ra`. Stores reminder in `rrem`.

## inc
* `inc ra`- increments `ra`'s value
* `inc [<memory cell>]`- increments `<memory cell>`'s value

## dec
* `dec ra`- decrements `ra`'s value
* `dec [<memory cell>]`- decrements `<memory cell>`'s value

## cmp
* `cmp ra , rb`- compares value from `rb` to `ra`. Stores results in flags.
* `cmp ra , [<memory cell>]`- compares value from memory cell to `ra`. Stores results in flags.
* `cmp [<memory cell>] , ra`- compares value from `ra` to memory cell. Stores results in flags.

## jmp
* `jmp <ip>` - moves `<ip>` to `rip`.

## je
* `je <ip>` - jumps to `<ip>` only when equal flag is set.

## jl
* `jl <ip>` - jumps to `<ip>` only when less flag is set.

## jg
* `jg <ip>` - jumps to `<ip>` only when greater flag is set.

