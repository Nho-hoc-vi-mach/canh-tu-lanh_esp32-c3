# 🍦 IoT Smart Refrigerator Guard (ESP32-C3)

Hệ thống giám sát và chống quên đóng cửa tủ lạnh thông minh, tích hợp cảnh báo còi và gửi thông báo từ xa qua **Telegram Bot**.

## 🛠️ Linh kiện phần cứng cốt lõi
* **Vi điều khiển:** ESP32-C3 Super Mini
* **Cảm biến:** Cảm biến từ cửa MC-38
* **Cảnh báo:** Còi Buzzer 5V & Đèn LED tích hợp trên board
* **Kết nối:** WiFi (Băng tần 2.4GHz)

## 📌 Tính năng nổi bật
1. **Cảnh báo đa tầng:** 
   * Mở dưới 10s: Trạng thái bình thường.
   * Mở từ 10s - 20s: Bíp nhắc nhở định kỳ.
   * Mở quá 20s: Hú còi báo động gắt + Gửi tin nhắn cấp bách về **Telegram**.
2. **Chế độ Sắp xếp thực phẩm (Restock Mode):** Cho phép mở cửa tủ thoải mái trong khoảng thời gian nhất định mà không bị hú còi (tự động kích hoạt lại bảo vệ khi đóng cửa).
3. **Giám sát IoT từ xa:** Theo dõi trạng thái tủ lạnh mọi lúc mọi nơi qua điện thoại.

## 🔌 Sơ đồ nối dây nhanh
| Linh kiện | Chân trên linh kiện | Chân trên ESP32-C3 |
| :--- | :--- | :--- |
| **Cảm biến MC-38** | Dây 1 | GPIO 2 |
| **Cảm biến MC-38** | Dây 2 | GND (Mass chung) |
| **Còi Buzzer 5V** | Chân dài (+) | GPIO 3 |
| **Còi Buzzer 5V** | Chân ngắn (-) | GND |

## 🚀 Hướng dẫn sử dụng
1. Clone hoặc tải source code này về máy tính.
2. Mở bằng Arduino IDE, cài đặt các thư viện cần thiết (`WiFi.h`, `HTTPClient.h`).
3. Thay đổi thông tin WiFi, `BOT_TOKEN` và `CHAT_ID` của bạn ở phần `#define` đầu code.
4. Nạp code (Upload) vào mạch ESP32-C3 và trải nghiệm!