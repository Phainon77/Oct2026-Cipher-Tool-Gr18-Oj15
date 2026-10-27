#ifndef INTERFACE_H
#define INTERFACE_H

#include <stddef.h>

// --- 1. Bộ đệm & Cấu hình Khối ---
#define BLOCK_SIZE 65536 // Định mức bộ đệm, bắt buộc phải chia hết cho N

// --- 2. Khóa (Key Structure) ---
// Lưu dạng mảng byte kèm độ dài, Caesar nhận số nguyên 1-255
typedef struct {
    unsigned char key_data[256];
    size_t key_len;
} Key;

// --- 3. Chế độ (Flags) ---
// Chế độ chữ cái (chỉ dịch A-Z, a-z) là phần mở rộng, lưu trong flags của header
#define FLAG_BYTE_MODE 0x00     // Mặc định là byte mod 256
#define FLAG_ALPHA_MODE 0x01    // Chế độ chữ cái

typedef struct {
    unsigned char flags;
    // Các trường khác của header nếu có bổ sung ở đây
} Header;

// --- 4. Mã lỗi dùng chung ---
typedef enum {
    ERR_SUCCESS = 0,
    ERR_INVALID_KEY,
    ERR_BLOCK_SIZE_MISMATCH,
    ERR_OUT_OF_MEMORY,
    ERR_FILE_ERROR
} ErrCode;

// Hàm hiển thị thông báo lỗi chung
void err_msg(ErrCode code);

// --- 5. Chữ ký hàm & Bảng con trỏ hàm ---
// Mỗi thuật toán có dạng: xxx_process(buf, n, key, offset, op)
// Dùng 'const' cho tham số chỉ đọc (key) theo đúng quy ước code
typedef int (*algorithm_process_fn)(
    unsigned char *buf, 
    int n, 
    const Key *key, 
    int offset, 
    int op
);

// Ví dụ khai báo stub (bản giả) cho thuật toán của Vương
int caesar_process(unsigned char *buf, int n, const Key *key, int offset, int op);

#endif // INTERFACE_H
