# Hành vi RazorVM

## Kiến trúc Word
Lưu trữ các bit theo thứ tự Litte Endian . Về mặt lý thuyết , không có Opcode nào nhận quá 2 tham số
```
	opcode dst src
	opcode dst imm
```
```
[ 8b opcode ][4b dst reg][ [4b src reg] 16 bit imm ]
```
Khi đó :
- 8 bit đầu LSB : Opcode
- 4 bit kế tiếp : index của thanh ghi đích
- và 20 bit còn lại tùy vào 2 trường hợp :
- 4 bit index của thanh ghi nguồn , 16 bit rỗng ( vì đạt đủ gới hạn )
- 20 bit imm

## Cách nạp lệnh
++ lên word tiếp theo và fetch

## Nhảy
Vì mọi thứ là nhãn ( kể cả hàm ) nên chỉ cần nhảy tuyệt đối

## Hàm
Bản chất là 1 khối có nhãn , khi thực thi xong nếu không nhảy lại về vị trí gọi thì nó sẽ bị trôi xuống
