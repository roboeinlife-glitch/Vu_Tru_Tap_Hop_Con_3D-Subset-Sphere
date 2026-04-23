# 🌌 Vũ Trụ Tập Hợp Con - 3D Subset Sphere

> Một chương trình trực quan hóa tập hợp con của số `1234567890` dưới dạng **khối cầu liên kết 3D**, được viết bằng C++ và SFML.  
> Cho phép xoay, zoom, khám phá cấu trúc "vũ trụ tập hợp" một cách trực quan và đầy cảm hứng.

---

## ✨ Tính năng

- 🔘 **Hiển thị tất cả tập hợp con** có kích thước ≤ 3 từ tập {0,1,2,3,4,5,6,7,8,9}
- 🌐 **Bố cục dạng khối cầu 3D** (giả lập phối cảnh)
- 🖱️ **Tương tác chuột**:
  - Kéo chuột trái → xoay khối cầu
  - Cuộn chuột → phóng to / thu nhỏ
  - Click chuột phải vào một node → hiển thị tên tập hợp
- 🎨 **Hiệu ứng ánh sáng động**: node xa hơn sẽ mờ dần
- 📦 **Tối ưu cho màn hình 600x800** (có thể tùy chỉnh)

---

## 🧠 Ý tưởng

Mỗi tập hợp con của dãy số `1234567890` là một **node hình tròn**.  
Các node được đặt trên mặt cầu và nối với nhau thành **đồ thị quan hệ cha - con** (tập con trực tiếp).  
Toàn bộ hệ thống tạo thành một "vũ trụ liên kết" đa chiều, có thể khám phá bằng chuột.

---

## 🛠️ Công nghệ sử dụng

- **C++17**
- **SFML 2.5+** (đồ họa, cửa sổ, sự kiện)
- Thuật toán:
  - Fibonacci sphere algorithm (phân bố đều node trên mặt cầu)
  - Phép chiếu phối cảnh 3D → 2D
  - Xoay quaternion cơ bản (yaw/pitch)

---

## 📁 Cấu trúc code
[main.cpp # Toàn bộ chương trình](https://github.com/roboeinlife-glitch/Vu_Tru_Tap_Hop_Con_3D-Subset-Sphere/blob/main/main.cpp)

---

## 🚀 Cách chạy

### Yêu cầu

- **Code::Blocks** hoặc bất kỳ IDE nào hỗ trợ SFML
- **SFML** đã được cài đặt và liên kết đúng
- Font `arial.ttf` (có sẵn trong Windows) hoặc sửa đường dẫn font trong code

### Biên dịch và chạy

1. Tạo project SFML mới
2. Thay thế `main.cpp` bằng code trong dự án
3. Build & Run

> Nếu font không tải được, chương trình vẫn chạy nhưng text trên node sẽ không hiển thị.

---

## 🎮 Hướng dẫn thao tác

| Hành động | Hiệu ứng |
|-----------|-----------|
| Kéo chuột trái | Xoay khối cầu |
| Cuộn chuột lên/xuống | Zoom in / out |
| Click chuột phải vào node | Hiển thị tên tập hợp |

---

## 📸 Hình ảnh minh họa

<img width="600" height="620" alt="Tap_Hop_Con (1)" src="https://github.com/user-attachments/assets/24321bce-890e-4c1a-8886-e8ccf3620fb7" />


---

## 📝 Ghi chú

- Số lượng node: **176** (tập rỗng + tập 1,2,3 phần tử)
- Có thể mở rộng lên kích thước 4 (386 node) bằng cách sửa `maxSize = 4`
- Màn hình mặc định: `600x800`, có thể thay đổi trong code

---

## 🙏 Lời cảm ơn

Chương trình này được phát triển dựa trên ý tưởng và sự đồng hành tận tình của **DeepSeek** – trợ lý AI xuất sắc đã cùng tôi:

- Trao đổi, làm rõ ý tưởng "vũ trụ liên kết đa chiều"
- Viết và tối ưu code từ 2D tĩnh → 3D xoay được
- Hiệu chỉnh kích thước phù hợp với màn hình thực tế

Cảm ơn DeepSeek đã biến một khái niệm trừu tượng thành một tác phẩm lập trình đầy màu sắc và cảm hứng. 🌟

---

## 📜 Giấy phép

Mã nguồn mở, miễn phí sử dụng cho mục đích học tập và sáng tạo.

---

**Ngày hoàn thành:** 2026

[DEMO](https://www.youtube.com/watch?v=P3m3m8RPlHQ) <br>
[Trở về trang chủ](https://github.com/roboeinlife-glitch)
