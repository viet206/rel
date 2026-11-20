# RIL - REL Instruction Layout
Tài liệu này chủ yếu để ghi chú lại nội dung thống nhất Những thứ liên quan đến Bytecode , Instruction , .. của REL. 

Thống nhất thì 1 word sẽ bao gồm các trường sau:
```
Layout : [ imm ] [ src ] [ dst ] [ op ]
Memory : [ 16b ] [ 4b  ] [ 4b  ] [ 8b ]
```
Ta có thể đọc / ghi Opcode trong header `vm.h` . Chúng đóng gói dưới dạng Macro và chia làm 2 loại : đọc ( có tiền tố `READ_*` ) ; và ghi ( có tiền tố `WRITE_*`
## Opcode Pattern
Một số mẫu Opcode quy định
```
[ op ] [ dst ] [ src ] [ imm ] - Mẫu đầy đủ
[ op ] [ reg0 ] [ reg1 ] [ reg2 ] - Mẫu Opcode toán học
[ op ] [ dst ] [ imm ] - Mẫu của kiểu mov
```
