# Trò chơi Hai Chú Vịt Né Chướng Ngại Vật (Duck FRDS).

## Lối chơi & Logic của Game

- Trò chơi gồm **2 nhân vật vịt**, có thể điều khiển bằng:
  - **Phím mũi tên** cho Người chơi 1.
  - **Phím WASD** cho Người chơi 2.
- Mục tiêu là **tránh né các chướng ngại vật** bay đến từ mọi hướng: **trên, dưới, trái, phải** màn hình.
- Góc **trái màn hình** hiển thị **thời gian**, góc **phải** hiển thị **điểm số**.
- Sau **mỗi 3 lần xuất hiện**, **chướng ngại vật tăng tốc** 1 lần.
- Người chơi **sống sót sau cùng** sẽ **chiến thắng**.
- Không có hệ thống độ khó, vì tốc độ chướng ngại vật **không giới hạn**.

## Chướng Ngại Vật

- Có **6 loại chướng ngại vật**: `RenderObstacle`, `RenderObstacle2`, ..., `RenderObstacle6`.
- `RenderObstacle3` và `RenderObstacle6` di chuyển **từ dưới lên trên**.
- Các chướng ngại vật còn lại có **quỹ đạo và tốc độ riêng biệt**.

## Trạng Thái Trò Chơi

- `MENU`: Người chơi bắt đầu trò chơi.
- `PLAYING`: Trạng thái chính, người chơi điều khiển nhân vật né chướng ngại vật.
- `GAME_OVER`: Hiển thị kết quả thắng/thua, cho phép **chơi lại** hoặc **thoát**.
- `PAUSE`: Dừng trò chơi bằng phím **ESC**, nhấn lại **ESC** để tiếp tục.

## Logic Thắng/Thua

- Va chạm với chướng ngại vật dẫn đến **thua**.
- Nếu **cả hai cùng va**, người va **trước** sẽ **thua**.
- Hiển thị hình ảnh chiến thắng tương ứng:
  - `player1_win.png`
  - `player2_win.png`

## Tăng Độ Khó

- Sau mỗi **3 lần sinh**, chướng ngại vật **tăng tốc**.
- Tốc độ **không giới hạn**, tăng độ thử thách theo thời gian.

## Âm Thanh

- **Nhạc nền**: `background_music.mp3`.
- **Âm thanh va chạm**: `crashed_sound.mp3`.
- **Nhạc kết thúc**: `game_over.mp3`.

## Hệ Thống Điểm

- Gồm **bộ đếm thời gian** và **điểm số**, phản ánh hiệu suất người chơi.

## Các Thành Phần Chính

- `RenderWindow`: Quản lý hiển thị cửa sổ và hình ảnh trò chơi.
- `RenderDuck`: Đại diện cho nhân vật người chơi, xử lý di chuyển & hiển thị.
- `RenderObstacle`: Đại diện cho các loại chướng ngại vật.
- `GameMenu`: Xử lý menu và chuyển đổi trạng thái trò chơi.
- `Timer` và `Point`: Quản lý thời gian và điểm số.

## Hành Vi Chướng Ngại Vật

- Khởi tạo **ngẫu nhiên vị trí và kích thước**.
- Tăng tốc sau mỗi **3 lần sinh**.
- Đặt lại vị trí khi **ra khỏi màn hình**.

## Kiểm Tra Va Chạm

- Dùng **logic giao nhau hình chữ nhật** để kiểm tra va chạm giữa người chơi và chướng ngại vật.

## Vòng Lặp Trò Chơi

- Xử lý sự kiện (nhập liệu, thoát).
- Cập nhật vị trí nhân vật & chướng ngại vật.
- Hiển thị tất cả trạng thái & đối tượng trong trò chơi.
- Quản lý chuyển đổi giữa các trạng thái như `PLAYING` và `GAME_OVER`.

## Công Cụ & Nguồn Tham Khảo

- **Công cụ sửa lỗi và học cơ chế game**: YouTube, GitHub Copilot.
- **Hình ảnh**: Vẽ tay bằng **Paint** và **Libresprite**.
- **Âm thanh**: Tải từ **YouTube**.
- **Logic game**: Tham khảo từ [phattrienphanmem123az.com](https://phattrienphanmem123az.com/) và YouTube.
