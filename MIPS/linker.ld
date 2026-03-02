MEMORY {
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 16M
	ROM (rx) : ORIGIN = 0xBFC00000, LENGTH = 2M
}

SECTIONS {
	.text.except_tlbrefill 0x80000000 : AT(0xBFC00000){
		*(.text.except_tlbrefill)
	} > RAM

	.text.except_others 0x80000180 : AT(0xBFC00180){
		*(.text.except_others)
	} > RAM

	.text 0x80005000 : AT(0xBFC00600){
		*(.text)
	} > RAM
}
