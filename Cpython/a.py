import filter

# 輸入字串並檢查是否有效
input_str = b'\x01\x00aaa'
result = filter.check_filter(input_str)

if result == 1:
    print("字串合法")
else:
    print("字串不合法，包含黑名單字符")
