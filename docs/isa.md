# REL ISA
Tài liệu này giới thiệu thiết kế Layout của lệnh và các hành vi của nó.
## Bố cục
```
[ opcode ] [  reg  ] [  imm   ]
[ 8 bit  ] [ 8 bit ] [ 16 bit ]
```
Bố cục này được thiết kế để nhét vừa vào một số nguyên 32 bit . Dạng chung của nó sẽ có 3 trường chính:
- `opcode` : Mã lệnh thực thi
- `reg` : trường của thanh ghi
- `imm` : giá trị tức thời  
Đối với trường `reg` thì nó sẽ bị chia thành 2 trường nhỏ hơn , có độ dài 4 bit:
```
[  dst  ] [  src  ]
[ 4 bit ] [ 4 bit ]
```
- `dst` : thanh ghi đích
- `src` : thanh ghi nguồn
Việc phân biệt 2 loại thanh ghi này theo tôi là một ý tưởng tốt vì bạn sẽ dễ hình dung hơn. nếu nhìn theo mô hình IPO thì `dst` là dữ liệu đầu ra , còn `src` là dữ liệu đầu vào.
