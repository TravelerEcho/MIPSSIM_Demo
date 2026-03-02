MEMORY {
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 16M
	ROM (rx) : ORIGIN = 0xBFC00000, LENGTH = 2M
}

SECTIONS {
    .text : {
        *(.text)
    } > ROM
}