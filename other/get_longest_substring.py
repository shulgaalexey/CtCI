# Assuming, that str is 2+ char length
my_str = "baileathacliath"

substrs = []
for _ in range(26):
    substrs.append({"from_idx": 0, "to_idx": 0})

for i in range(len(my_str)):
    c = my_str[i]
    idx = ord(c) - ord('a')
    cur_substr = substrs[idx]
    if cur_substr["from_idx"] == 0:
        cur_substr["from_idx"] = i
    else:
        cur_substr["to_idx"] = i

max_len = 0
max_substr = {"from_idx": 0, "to_idx": 0}
for substr in substrs:
    cur_len = substr["to_idx"] - substr["from_idx"]
    if cur_len > max_len:
        max_len = cur_len
        max_substr = substr

for i in range(max_substr["from_idx"], max_substr["to_idx"] + 1):
    print(my_str[i])

