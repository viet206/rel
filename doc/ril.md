# RIL - REL Instruction Layout
Tài liệu này chủ yếu để ghi chú lại nội dung thống nhất Bố cục 1 lệnh trong REL , giúp cho VM và các công cụ đọc , ghi Bytecode có thể thao tác 1 cách chính xác.  

Thống nhất thì 1 word sẽ bao gồm các trường sau:
```
Layout : [ imm ] [ src ] [ dst ] [ op ]
Memory : [ 16b ] [ 4b  ] [ 4b  ] [ 8b ]
```
