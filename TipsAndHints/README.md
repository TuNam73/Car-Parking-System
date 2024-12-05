# Tips and Hints
Mọi người đều bắt đầu từ đâu đó, kể cả các chuyên gia. Bài viết này cung cấp một số mẹo và gợi ý dành cho những người mới bắt đầu lập trình với Arduino - phần mềm được thiết kế để giúp người mới làm quen với lập trình nhúng.

## Diễn đàn: Hãy đầu tư chút công sức
Trước khi nhờ sự trợ giúp từ người khác, hãy thể hiện rằng bạn đã nỗ lực tìm hiểu và thử giải quyết vấn đề thay vì chỉ đưa yêu cầu một cách hời hợt. Mọi người sẽ sẵn sàng giúp đỡ hơn nếu họ thấy bạn đã bỏ ra công sức với vấn đề đó.

## Bắt đầu từ những điều nhỏ nhặt
Đối với những bài toán lập trình lớn và phức tạp, nên chia chúng thành những phần nhỏ hoặc bắt đầu với các bài tập nhỏ, đơn giản. 
Ví dụ như bài nhấp nháy đèn LED, nó chứa đựng những kiến thức cơ bản trước khi làm việc phức tạp hơn.

## Tránh viết toàn bộ chương trình một lần
Không nên viết toàn bộ chương trình rồi mới kiểm tra, gỡ lỗi bởi những yêu cầu ở dự án có thể được thay đổi và vì việc gỡ lỗi đối với lập trình nhúng rất khó. Thay vào đó, hãy bắt đầu với những phần nhỏ, sử dụng khung cơ bản "basic shell".

## Khung cơ bản
Bắt đầu bằng cách viết một chương trình đơn giản với các hàm cơ bản setup() và loop(), có thể kiểm thử bằng Serial Monitor với lệnh "Hello" trong cả 2 hàm trên.

## Tiếp cận sơ khai
Dựa trên nền tảng của khung cơ bản, xây dựng thêm các hàm cho những chức năng phức tạp hơn. Ví dụ có thể tạo 1 hàm static void init_oled(); để in ra một câu lệnh.

## Sử dụng sơ đồ khối
Lập kế hoạch các nhiệm vụ và các mối quan hệ giữa chúng bằng sơ đồ khối đơn giản.

## Xử lý lỗi
Phát hiện lỗi dễ hơn bằng cách xây dựng ứng dụng theo từng phần nhỏ. Một số lỗi phổ biến là lỗi định dạng, thiếu stack space, vòng đời đối tượng.

## Quản lý lưu trữ:
Biết cách lưu trữ dữ liệu cục bộ (static) hoặc trên stack để tránh lỗi liên quan đến việc trỏ tới dữ liệu không còn tồn tại.

## Tận dụng phạm vi của biến
Hạn chế phạm vi của các biến để tránh việc chúng bị sử dụng sai nơi cần thiết. Các biến được khai báo toàn cục có thể tiện lợi trong dự án nhỏ, nhưng  sẽ gây khó khăn trong dự án lớn.

## Nghỉ ngơi
Hầu hết mọi người đều tiếp tục suy nghĩ về vấn đề ngay cả khi họ đã ngừng tư duy, có ý thức về nó. Dù ngủ yên hay trằn trọc, não bộ sẽ xử lý các sự kiện trong ngày và thử nghiệm mọi kịch bản có thể. Khi tỉnh dậy, bạn có thể có những ý tưởng mới. 

## Ghi chú
Lưu lại ý tưởng hoặc giải pháp để tra cứu sau này.

## Đặt câu hỏi hiệu quả
Cung cấp thông tin chi tiết và cụ thể khi yêu cầu trợ giúp trên diễn đàn.

## Chia nhỏ để dễ debug
Khi gặp lỗi, chương trình bị treo, nên chia nhỏ từng phần để kiểm tra và gỡ lỗi

## Viết mã kiểm tra
Để giải quyết một vấn đề gặp phải, thay vì tranh luận, cách tốt nhất là viết một chương trình nhỏ để kiểm tra giả thuyết

## Lệnh find
Khi kiểm tra mã nguồn mở, có thể tìm kiếm trực tuyến hoặc kiểm tra những gì đã cài đặt trên máy của mình. Việc xem mã đã cài đặt rất quan trọng khi tìm thấy lỗi trong thư viện mà bạn đang sử dụng.

## Cải tiến code
Một số lập trình viên ngừng cải tiến phần mềm sau khi nó "có vẻ hoạt động". Điều này có thể dẫn đến nhiều lỗi khi triển khai. Việc liên tục cải thiện và kiểm tra code sẽ tạo nên phần mềm tốt hơn. Hãy tự đặt đặt câu hỏi sau đó kiểm tra.

## Làm quen với thao tác Bit
Học cách xử lý các toán tử và thao tác bit trong C/C++ sẽ giúp bản thân làm chủ kỹ năng lập trình lâu dài, giúp kiểm soát code tốt hơn. Hãy dành thời gian học thứ tự ưu tiên toán tử và tránh các macro không cần thiết.

## Hiệu suất
Nhiều lập trình viên mới tập trung quá mức vào tối ưu hóa. Trước khi tối ưu, hãy tự hỏi liệu nó có thực sự cần thiết và liệu người dùng có nhận ra khác biệt không. Hãy ưu tiên sự dễ hiểu để cập nhật sau này.

## Tính thẩm mĩ của code
Code không chỉ quan trọng là hoạt động được, mà còn cần dễ đọc và dễ bảo trì. Quá nhiều hoặc quá ít chú thích đều không tốt. Nó là biểu hiện của sự chuyên nghiệp.

## Fritzing vs. Schematic Diagrams
Fritzing diagrams phù hợp cho người mới làm quen. Để tiến xa hơn, hãy học cách đọc và sử dụng sơ đồ nguyên lý (schematic diagrams). Đầu tư thời gian học sơ đồ nguyên lý sẽ giúp bản thân nắm bắt mạch điện tốt hơn là chỉ nhìn vào sơ đồ dây dẫn.

## Trả ngay hay trả sau
Sự nghiệp cần sự phát triển từng bước, bắt đầu từ các nhiệm vụ cơ bản và nâng dần theo thời gian và kinh nghiệm.
Đầu tư thời gian và công sức từ sớm sẽ mang lại lợi ích lâu dài.

## Tránh trở thành nhân viên không thể thay thế:
Đừng cố làm mình "không thể thay thế" bằng cách xây dựng các hệ thống khó hiểu và giữ lại thông tin cho riêng mình, không muốn chia sẻ với đồng nghiệp, vì sẽ gây mất thiện cảm với đồng nghiệp và quản lý.
Việc này cũng hạn chế cơ hội thăng tiến và đảm nhận thử thách mới. Hãy luôn sẵn sàng chuyển giao nhiệm vụ cũ và đón nhận trách nhiệm mới.

