d = 4
di = 4 - 1
test_list = [[0.0, 0.1, 0.2, 0.3], [1.0, 1.1, 1.2, 1.3], [2.0, 2.1, 2.2, 2.3], [3.0, 3.1, 3.2, 3.3]]
test_list2 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

for i in range(0, int(d/2)):
    for j in range(i, int(d-1-i)):
        d1 = d - 1 - i
        d2 = d - 1 -j
        a0 = test_list[i][j]
        a90 = test_list[j][d1]
        a180 = test_list[d1][d2]
        a270 = test_list[d2][i]

        test_list[i][j] = a270
        test_list[j][d1] = a0
        test_list[d1][d2] = a90
        test_list[d2][i] = a180
        
print(test_list)
