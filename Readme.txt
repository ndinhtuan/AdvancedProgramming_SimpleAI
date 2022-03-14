0. Vấn đề và tìm hiểu ban đầu:
* Đặt vấn đề
- Xây dựng chương trình chơi Hangman: Người chọn từ - Máy tính đoán.
- Hai vấn đề chính:
  + 1. Xây dựng giao diện tương tác người máy
  + 2. Cách/Phương pháp/Thuật toán để máy tính có thể đoán được.
  + Việc xây dựng giao diện (text-based) nói chung là làm được. 
    Câu hỏi khó hơn hiện giờ là phương pháp đoán word (từ) ?
    => Tập trung tìm hiểu vấn đề này trước. Sau khi có cách mới tìm cách cài đặt,
    cũng như làm các phần khác. (Bởi nếu không có thuật toán đoán từ thì không làm được
    chương trình)

* Một tiếp cận về phương pháp đoán từ
- Có thể có nhiều cách đoán. Một cách làm là xem con người (chúng ta) làm thế nào.
  Từ đó lấy ý tưởng để xây dựng (có thể bắt chước, nhưng phần nhiều là lấy cảm hứng
  để từ đó nghĩ ra cách làm trên máy tính).
- Một người có thể làm như sau:
 + B1: Chọn bất kỳ một kí tự trong a-z, nhưng không phải 
       là một trong các kí tự đã chọn rồi.
 + B2: Nếu đoán đúng thì sang bước 3 (thắng).
       Nếu hết số lần đoán sang bước 3 (thua).
       Nếu không quay lại B1.
 + B3: Kết thúc
- Cách chơi này may rủi, tỉ lệ thua cao. Nhưng nếu sử dụng, chúng ta vẫn 
  xây dựng được chương trình. Ưu điểm cách làm này là đơn giản, dễ cài đặt.
  Giả sử có 2 người xây dựng chương trình, khi đó có thể cài đặt nhanh thuật toán này,
  để người làm giao diện sử dụng làm phần của mình.
  Trong khi đó người làm thuật toán tiếp tục tìm hiểu để làm phần của mình.

- Sau khi chơi, và tìm hiểu, người đó có thể phát triển cách chơi như sau:
  + B0: Học thêm nhiều từ tiếng Anh
  + B1: Chọn một trong các nguyên âm a, e, i, o, u
  (Gợi ý chung, bởi từ nào cũng có nguyên âm, và số nguyên âm thì ít hơn phụ âm)
  + B2: Sau khi đoán (đúng được) một hay nhiều kí tự, tìm/nhớ xem liệu có các từ nào thoả mãn:
    - độ dài như từ phải đoán
    - có xuất hiện các kí tự đã tìm được tại đúng các vị trí đã được cho biết
    Nếu tìm/nhớ được thì chọn kí tự đó, nếu không chọn bất kỳ một kí tự cảm thấy có 
    khả năng xuất hiện (và không trùng với một kí tự nào đã đoán.)
 + B3: Nếu đoán đúng thì sang bước 4 (thắng).
       Nếu hết số lần đoán sang bước 4 (thua).
       Nếu không quay lại B2.
 + B4: Kết thúc
   
- Ý tưởng chỉnh:
  + Nhập vào knowledge base là danh sách từ vựng
  + Lọc lấy chỉ xem xét các từ thoả mãn điều kiện đang có (độ dài, kí tự và vị trí tương ứng)
  + Trong các từ xem xét, tìm kí tự xuất hiện nhiều nhất và chưa được chọn trước đó để chọn tiếp.

- Chương trình:
 + B0: Nạp danh sách từ vựng (vocabulary)
 + B1: Nhận vào số lần đoán tối đa N và độ dài từ phải đoán K. 
    Lọc danh sách từ vựng để chỉ chọn xem xét các từ có độ dài K.
    Danh sách các kí tự đã chọn ban đầu là rỗng.
 + B2: 
    Trong các từ đang xét, tìm kí tự xuất hiện nhiều nhất và không nằm trong các 
    kí tự đã chọn. Chọn kí tự này.
    Nhận vào kết quả trả đoán.
 + B3: 
    Nếu kết quả đoán đúng kí tự:
        Nếu đoán hết cả tử, sang B4 (thắng).
        Nếu chưa hết, lọc để giữ chỉ giữ lại xem xét từ vựng 
            với các từ có cả kí tự vừa đoán được tại vị trí được biêt; 
            Rồi quay lại B2. 
    Nếu đoán sai kí tự:
        Nếu hết số lần đoán, sang B4 (thua)
        Nếu chưa hết, tiếp tục đoán bằng cách quay lại B2
 + B4: Kết thúc


1. Tiền xử lý dữ liệu: data_processing.cpp (chạy một lần)
(Chú ý: Phần này có thể bỏ qua, bởi chương trình dùng chủ yếu tập từ vựng thứ 2
(và sau này, khi viết chương trình đánh giá thì cho kết quả tốt hơn)).

- Tạo/Tìm danh sách các từ. Vd nguồn:
    https://github.com/dwyl/english-words/blob/master/words.txt
    https://github.com/mrdziuban/Hangman/blob/master/dictionary.txt (better vocabulary)
    http://stackoverflow.com/questions/4456446/dictionary-text-file
    http://www.gwicks.net/dictionaries.htm
- Với nguồn đầu tiên: Trong đó có một số từ có ký tự không phải a-z hay số
  => tiền xử lý: viết chương trình loại bỏ các từ đó, ghi vào file mới
- File chương trình: data_processing.cpp (chạy một lần).
- Sử dụng tới: Ghi (write) file (và đọc file đã biết từ trước).
- (Nguồn thứ 2 lấy nguyên, chưa xử lý gì)

2. Phiên bản 1.0: Chương trình
- Cách viết:
  + Mỗi bước viết thành các hàm với tham số tương ứng. Lặp biểu diễn thành while
  + Khai báo các hàm cùng tham số lên trước.
  + Sau khi viết xong hàm main() thì cài đặt từng hàm. Trong quá trình đó sửa lại
    chi tiết hàm main() 
  + Viết hàm nào xong kiểm tra lại riêng và/hoặc chạy trong main() tới hết hàm đó.
- Kỹ thuật:
  + Mô tả tập các kí tự đã chọn (selectedChars - hàm main()) bằng set<char>
    (Chính từ tập đã gợi ý chuyển sang set)
  + Để dếm số lần xuất hiện mỗi kí tự, lưu tần số (occurrences - hàm findBestChar()) 
    bằng map<char, int>
    (do chỉ từ a-z, có thể biểu diễn hai kiểu dữ liệu trên bằng mảng kiểu như coungting sort)
  + Dùng iterator để duỵệt toàn bộ set (hàm findBestChar()) hay vector (hàm filterWordsByMask())
    Phải sử dụng con trỏ (pointer/*) để lấy giá trị.

    
* Note: Chương trình đang dùng từ vựng dictionary
(lý do: Tìm được sau, chuyên cho hangman. Hiện chủ yếu test trên tập từ vụng này)
- Bài tập: Với tập từ vựng đầu tiên, đếm xem mỗi chữ cái có bao nhiêu word. 
  In ra theo trật tự chữ cái.
- Bài tập: Với tập từ vựng đầu tiên, đếm xem mỗi chữ cái xuất hiện bao nhiều lần
  trong các từ của toàn bộ tập từ vựng. In ra theo trật tự số lượng tử giảm dần.
  (Dựa trên findBestChar())
- Bài tập: Kiểm tra responsedMask được nhập vào (về độ dài, so với đã nhập vào trước đó, ...)
- Bài tập: Nếu đoán sai kí tự, lọc lại tập từ vựng để loại đi những word KHÔNG chứa kí tự vừa đoán sai.
- Bài tập: Nếu một kí tự xuất hiện nhiều lần trong một từ, cũng chỉ đếm 1 lần (trong hàm countOccurrences()). 
- Bài tập: Nếu ko đoán được, hỏi đáp án. Nếu ko có trong từ điển thì thêm vào
  (webcam, internet ko có trong từ vựng hiện giờ)
- Bài tập: khi ko có trong từ điển thì đoán 'thông minh' hơn

3. Phiên bản v01_02
- Nếu đoán sai kí tự, lọc lại tập từ vựng để loại đi những word KHÔNG chứa kí tự vừa đoán sai.
  (xem bài tập ở trên) - giúp tăng tính chính xác khi đoán
- Trong khi đếm, kí tự xuất hiện nhiều lần trong một tử chỉ được đếm một lần
  (xem bài tập ở trên)
- Đưa hàm charNotInSet() ra util.*
- Đưa các hàm về đoán ra thành guesser.*. Chú ý:
  + Chỉ những (bốn) hàm dùng (chung/công cộng) trong main mới khai báo tại guesser.h
  + Còn những hàm chỉ dùng trong cài đặt 4 hàm trên, được khai báo ở đầu của guesser.cpp

Vấn đề:
- làm sao đánh giá được kết quả các cái tiến, của các tập từ vựng ?
Quan sát:
- Biến candidateWords chỉ dùng trong nội bộ 4 hàm trên (truyền vào, và được cập nhật)
- Biến selectedChars về cơ bản cũng thế (nếu như biến đổi để findBestChar cập nhật 
  luôn giá trị của selectedChars)

- Chương trình luôn đoán các nguyên âm trước, tương tự như các gợi ý trên Internet :)