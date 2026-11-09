# Syntax cho Razor

## Syntax chung
Tất cả đều theo chung : `[opcode][dst][src][imm]`

đối với mov :
```
mov reg , imm
mov reg , reg
```

Đối với các Opcode toán học ( bao gồm + , - , * , / , % )
```
math reg , reg
math reg , imm
```

Comment sẽ sử dụng dấu `-` làm dấu comment 1 dòng , và
cũng là comment duy nhất
