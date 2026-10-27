#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

// Triển khai hàm thông báo lỗi chung
void err_msg(ErrCode code) {
    switch (code) {
        case ERR_SUCCESS:
            printf("Thao tac thanh cong.\n");
            break;
        case ERR_INVALID_KEY:
            printf("Loi: Khoa khong hop le.\n");
            break;
        case ERR_BLOCK_SIZE_MISMATCH:
            printf("Loi: Kich thuoc khoi BLOCK_SIZE khong chia het cho N.\n");
            break;
        default:
            printf("Loi khong xac dinh.\n");
            break;
    }
}

// Bản giả (stub) cho hàm mã hóa của Vương để chạy thử luồng tệp trước
int caesar_process(unsigned char *buf, int n, const Key *key, int offset, int op) {
    // Luôn viết hàm nội bộ gọn gàng (không quá 50 dòng theo quy ước)
    (void)buf; (void)n; (void)key; (void)offset; (void)op; // Tránh cảnh báo unused biến
    printf("[Stub] Da goi ham caesar_process thanh cong.\n");
    return 0;
}

int main(void) {
    // Kiểm tra quy ước kích thước khối N (Mặc định là 8 hoặc 16)
    int n_block = 8; 
    if (BLOCK_SIZE % n_block != 0) {
        err_msg(ERR_BLOCK_SIZE_MISMATCH);
        return EXIT_FAILURE;
    }

    // Khởi tạo dữ liệu giả lập để test
    Key my_key = {{0}, 0};
    unsigned char buffer[BLOCK_SIZE];

    // Bảng con trỏ hàm (Bảng tra thuật toán)
    // Giúp 5 người code song song ráp nối module cực kỳ dễ dàng
    algorithm_process_fn algorithm_table[] = {
        caesar_process,
        // Thêm các hàm của Huy, Tuấn... vào đây khi code xong
    };

    printf("--- Chay thu luong tep voi ban gia (stub) ---\n");
    // Gọi thử thuật toán đầu tiên (Caesar của Vương) qua bảng tra
    algorithm_table[0](buffer, n_block, &my_key, 0, 1);

    return EXIT_SUCCESS;
}
