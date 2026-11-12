# Hành vi Relc và RelVM

## Rel Codegen ( rcgen )
là 1 header nhỏ trong thư mục của Relc . được viết như 1 Assembler nhỏ được thiết kế trên nền của ngôn ngữ C để tự động hóa việc viết mã Bytecode an toàn và chính xác hơn:
```c
#include "rcgen.h"

    rc_init(16);

    // Thân đoạn mã Assembler
    MOV(0,16);
    MOV(1,16);
    ADD(0,1);
    EXIT();

    rc_exec(result);
```
## RelVM

### Layout Word
```
	[ 16 bit imm ][ 4 bit src ][ 4 bit src ][ 8 bit opcode ]
```
Thiết kế ngược đời , nhưng nó giúp giảm 1 phần chi phí ALU trên VM do về mặt lý thuyết thì chỉ cần sử dụng 1 toán tử bit cho trường opcode , và imm.

Đối với VM , cách Decode :
- opcode : ( word & 0xFF )
- thanh ghi đích : ( word >> 8 ) & 0xF
- thanh ghi nguồn : ( word >> 12 ) & 0xF
- giá trị tức thời : ( word >> 16 )

Vì Layout đã ngược , kết hợp với LE khiến chúng lại ngược nhau nữa . Nên khi dump từ trong RAM ra ngoài , ta hoàn toàn có thể đọc word thô bằng mắt người với Layout:
```
    [ 8 bit op ] [ 4 bit dst ] [ 4 bit src ] [ 16 bit imm ]
```
Ví dụ:
```
    lúc viết : 0x78000000
    RAM hiểu : 0x00007800
    CPU hiểu : 0x78000000

    Opcode : 00 ( mov )
    dst reg : 0
    src reg : 0
    imm : 0x7800
```
### Cách nạp lệnh
++ lên word tiếp theo và fetch

### Nhảy
Vì mọi thứ là nhãn ( kể cả hàm ) nên chỉ cần nhảy tuyệt đối

### Hàm
Bản chất là 1 khối có nhãn , khi thực thi xong nếu không nhảy lại về vị trí gọi thì nó sẽ bị trôi xuống
