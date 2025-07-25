ENTRY(Start)

gNumMusicPlayers = 4;
gMaxLines = 0;
gInitialMainCB2 = CB2_TestRunner;

MEMORY
{
    EWRAM            (rwx) : ORIGIN = 0x2000000, LENGTH = 256K
    IWRAM            (rwx) : ORIGIN = 0x3000000, LENGTH = 0x7F00
    IWRAM_PERSISTENT (rwx) : ORIGIN = 0x3007F00, LENGTH = 0x100
    ROM               (rx) : ORIGIN = 0x8000000, LENGTH = 32M
}

SECTIONS {

    .ewram ORIGIN(EWRAM) : AT (__ewram_lma)
    ALIGN(4)
    {
        __ewram_start = .;
        *(.ewram*)
        __ewram_end = .;
    } > EWRAM

    .ewram.sbss (NOLOAD) :
    ALIGN(4)
    {
        src/*.o(.sbss);
        test/*.o(.sbss);
        . = ALIGN(4);
    } > EWRAM

    .iwram ORIGIN(IWRAM) : AT (__iwram_lma)
    ALIGN(4)
    {
        __iwram_start = .;
        *(.iwram*);
        . = ALIGN(4);
        __iwram_end = .;
    } > IWRAM

    .iwram.bss (NOLOAD) :
    ALIGN(4)
    {
        src/*.o(.bss);
        data/*.o(.bss);
        test/*.o(.bss);
        *libc.a:*.o(.bss*);
        *libgcc.a:*.o(.bss*);
        *libnosys.a:*.o(.bss*);

        src/m4a.o(.bss.code);

        src/*.o(common_data);
        src/*.o(COMMON);
        data/*.o(COMMON);
        test/*.o(COMMON);
        *libc.a:sbrkr.o(COMMON);
    } > IWRAM

    /* .persistent starts at 0x3007F00 */
    /* WARNING: This is the end of the IRQ stack, if there's too
     * much data it WILL be overwritten. */
    .iwram.persistent (NOLOAD) :
    ALIGN(4)
    {
        test/*.o(.persistent);
    } > IWRAM_PERSISTENT

    /* BEGIN ROM DATA */
    . = 0x8000000;

    .text :
    ALIGN(4)
    {
        src/rom_header.o(.text);
        src/rom_header_gf.o(.text.*);
        src/rom_header_rhh.o(.text.*);
        src/*.o(.text);
    } > ROM =0

    script_data :
    ALIGN(4)
    {
    data/*.o(script_data);
    } > ROM =0

    lib_text :
    ALIGN(4)
    {
        *libagbsyscall.a:*.o(.text*);
        *libgcc.a:*.o(.text*);
        *libc.a:*.o(.text*);
        *libnosys.a:*.o(.text*);
    } > ROM =0

    .rodata :
    ALIGN(4)
    {
        src/*.o(.rodata*);
        data/*.o(.rodata*);
    } > ROM =0

    song_data :
    ALIGN(4)
    {
        sound/songs/*.o(.rodata);
    } > ROM =0

    lib_rodata :
    SUBALIGN(4)
    {
        *libgcc.a:*.o(.rodata*);
        *libc.a:*.o(.rodata*);
        *libc.a:*.o(.data*);
        src/libisagbprn.o(.rodata);
    } > ROM =0

    .data.iwram :
    ALIGN(8)
    {
        __iwram_lma = .;
        . = . + (__iwram_end - __iwram_start);
    } > ROM = 0

    .data.ewram :
    ALIGN(4)
    {
        __ewram_lma = .;
        . = . + (__ewram_end - __ewram_start);
    } > ROM = 0

    tests :
    ALIGN(4)
    {
        __start_tests = .;
        test/test_test_runner.o(.tests); /* Sanity checks first. */
        test/*.o(.tests);
        __stop_tests = .;
        test/*.o(.text);
        test/*.o(.rodata*);
    } > ROM =0

    __rom_end = .;

    dacs 0x9FFC000 :
    ALIGN(4)
    {
        test/*.o(.dacs);
    } > ROM =0

    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0.  */

    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }

    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }

    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }

    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }

    /* Discard everything not specifically mentioned above. */
    /DISCARD/ :
    {
        *(*);
    }
}
