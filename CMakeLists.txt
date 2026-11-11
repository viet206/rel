cmake_minimum_required(VERSION 3.20)
project(Razor-lang C ASM)

# Cấu hình chuẩn C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Cho phép người dùng tùy chọn kiến trúc/target (mặc định là x64 dựa trên cấu trúc thư mục)
set(ARCH "x64" CACHE STRING "Target architecture suffix (e.g., x64, arm64)")

# --- CỜ BIÊN DỊCH FREESTANDING ---
# Loại bỏ hoàn toàn standard library, runtime và built-ins không cần thiết,
# chỉ giữ lại startup file và code thuần túy.
set(FREESTANDING_C_FLAGS
    -ffreestanding
    -fno-builtin
    -fno-exceptions
    -fno-stack-protector
    -fno-pie
    -fno-pic
)

# Áp dụng cờ biên dịch cho mã nguồn C (Không áp dụng -ffreestanding trực tiếp cho ASM để tránh lỗi trình biên dịch)
foreach(flag ${FREESTANDING_C_FLAGS})
    add_compile_options($<$<COMPILE_LANGUAGE:C>:${flag}>)
endforeach()

# --- DANH SÁCH TỆP NGUỒN ---
# Tự động nạp các tệp nguồn của VM, loader và tệp startup Assembly tương ứng
set(RAZOR_SOURCES
    src/vm/rzvm.c
    src/vm/${ARCH}/ld.c
    src/vm/${ARCH}/startup.s
)

# --- TẠO TỆP NHỊ PHÂN ---
add_executable(rzld ${RAZOR_SOURCES})

# Thêm đường dẫn include cho các header file
target_include_directories(rzld PRIVATE
    src/vm
)

# --- CỜ LINKER (LIÊN KẾT) ---
# Đảm bảo quá trình linking không tự động chèn libc, crt0 mặc định của hệ thống
set(FREESTANDING_LINK_FLAGS
    -nostdlib
    -nodefaultlibs
    -static
    # Gợi ý: Nếu bạn có Linker Script riêng cho từng target, hãy bỏ chú thích dòng dưới:
    # "-T${CMAKE_CURRENT_SOURCE_DIR}/src/vm/linker_${RAZOR_ARCH}.ld"
)

target_link_options(rzld PRIVATE ${FREESTANDING_LINK_FLAGS})

# (Tùy chọn) In thông báo cấu hình thành công
message(STATUS "Configuring Razor-lang for target architecture: ${RAZOR_ARCH}")
