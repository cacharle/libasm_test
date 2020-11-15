# libasm\_test

Test for the libasm project of school 42.

![example\_screenshot](./screenshot.png)

## Usage

The default path to your libasm is `../libasm`. You can modify it in the Makefile.

```sh
$ make
```

## Bonus

```sh
$ make bonus
```

Or:

Set the environment variable `LIBASM_TEST_BONUS` to `yes`.
```sh
$ echo 'export LIBASM_TEST_BONUS=yes' >> ~/.zshrc
```

## Common issues

### ft\_write and ft\_read crash

<https://stackoverflow.com/c/42network/questions/1494>

### Compilation on linux with gcc

To fix the `relocation R_X86_64_PC32 against symbol` error you can add inside your
libasm source code `wrt ..plt` after a call to a libc function, like example below:

```asm
    ...
    call __errno_location wrt ..plt
    ...
```

Now you should be able to compile with `gcc`
