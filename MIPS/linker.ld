ENTRY(__start)

MEMORY {
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 16M
	ROM (rx) : ORIGIN = 0xBFC00000, LENGTH = 1M
}

SECTIONS {
	.text.loader 0xBFC00000 : {
		*(.text.loader)
	} > ROM

	.text.except.tlbrefill 0x80000000 : AT(0xBFC00200) {
		*(.text.except.tlbrefill)
	} > RAM

	.text.except.xtlbrefill 0x80000080 : AT(0xBFC00280) {
		*(.text.except.xtlbrefill)
	} > RAM

	.text.except.cacheerror 0x80000100 : AT(0xBFC00300) {
		*(.text.except.cacheerror)
	} > RAM

	.text.except.others 0x80000180 : AT(0xBFC00380) {
		*(.text.except.others)
	} > RAM

	.text 0x80000600 : AT(0xBFC00800) {
		*(.text)
		*(.text.*)
	} > RAM

	.rodata : {
		*(.rodata)
		FILL(0x00);
		. = 0x8000;
	} > RAM
}
