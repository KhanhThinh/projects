import sys
N = 4  # Số file cần tạo
ClusterSize = 8192
# Theo thẻ SD của tui thì cái này là 1 cluster = 16*512 bytes
for x in range(0, N):
    num_temp = str(x)
    file_name = "E:\\F" + num_temp + ".dat"
    file = open(file_name, "w")
    file_size = 0

    if x % 2 == 0:
        file_size = ClusterSize * 2
    else:
        file_size = ClusterSize

    #  size_num = sys.getsizeof(num_temp) # = 1
    #  size_enter = sys.getsizeof('\n') # = 2
    while file_size != 0:
        file.write(num_temp)
        file_size -= 1
        if file_size < (2 + 1):
            break
        else:
            file.write('\n')
            file_size -= 2
    file.close()
