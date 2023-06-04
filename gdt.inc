gdt_start:
   DD 0
   DD 0

gdt_code:
   DW 0FFFFh
   DW 0
   DB 0
   DB 10011010b
   DB 11001111b
   DB 0

gdt_data:
   DW 0FFFFh
   DW 0
   DB 0
   DB 10010010b
   DB 11001111b
   DB 0
end_of_gdt:

gdtr:
   DW end_of_gdt - gdt_start - 1
   DD gdt_start

   CODE_SEG equ gdt_code - gdt_start
   DATA_SEG equ gdt_data - gdt_start
