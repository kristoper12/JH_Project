from numpy import loadtxt
import os
import csv
import sys

def Result(check_flag, header, customer_list, key) :
    if (check_flag == 1) :
        # 삽입 이상현상 : 만약 Child 가 없는 Person 이 들어올 경우 Child 값이 NULL 이 되어 아노말리 발생
        # 삭제 이상현상 : 만약 Person에 있는 Codd 를 지워야 할 경우 Person 값이 NULL 이 되어 아노말리 발생
        # 따라서 Key 인 Person 을 토대로 테이블을 나누어 주어야 함
        if (key == 0) :
            print(header[0] + "\t\t" + header[1] + "\n" + header[0] + "\t\t" + header[2])
            for i in range(0, 6) :
                print(customer_list[i][0] + "\t\t" + customer_list[i][1] + "\n" + customer_list[i][0] + "\t\t" + customer_list[i][2])
        elif (key == 1) :
            print(header[1] + "\t\t" + header[0] + "\t\t\t\t\t\t" + header[1] + "\t\t" + header[2])
        elif (key == 2) :
            print(header[2] + "\t\t" + header[0] + "\t\t\t\t\t\t" + header[2] + "\t\t" + header[1])

        print("\n", end = "")


    elif (check_flag == 2) :
        return
    elif (check_flag == 3) :
        return
    elif (check_flag == 4) :
        return

line_counter = 0
header = []
customer_list = []

with open('Table.csv') as fp:
    while 1:
        data = fp.readline().replace("\n", "")
        if not data: break
        if line_counter == 0:
            header = data.split(",")
        else:
            customer_list.append(data.split(","))
        line_counter = line_counter + 1

for i in range(0, 3):
    print(header[i] + "\t", end="\t")

print("\n", end = "")
for i in range(0, 6):
    for j in range(0, 3):
        print(customer_list[i][j] + "\t", end="\t")
    print("\n", end="")
print("\n", end = "")
# 제 1 정규형에 위배 되는지 검사
# 한 행이 중복되면 안됨
# 각 속성은 하나의 도메인을 가지고 있어야 함
# 각 셀은 하나의 값만 갖는다.
check_flag = 0
num_flag = 0

# 중복 행 찾기
for i in range(0, 5):
    Person = customer_list[i][0]

    if (Person == customer_list[i + 1]):
        Child = customer_list[i][1]

        if (Child == customer_list[i + 1]):
            Salary = customer_list[i][2]

            if (Salary == customer_list[i + 1]):
                check_flag = 1

# 각 속성이 하나의 도메인을 갖는가
if (check_flag != 1):
    for i in range(0, 3):
        if (customer_list[0][i][0] < '0' or customer_list[0][i][0] > '9'):
            num_flag = 0
        else:
            num_flag = 1
        for j in range(1, 6):
            if (num_flag == 1):
                if (customer_list[j][i][0] < '0' or customer_list[j][i][0] > '9'):
                    check_flag = 2
            elif (num_flag == 0):
                if (customer_list[j][i][0] >= '0' and customer_list[j][i][0] <= '9'):
                    check_flag = 2

# 각 셀이 하나의 값을 갖는가
if (check_flag != 1 and check_flag != 2):
    for i in range(0, 6):
        for j in range(0, 3):
            for k in range(0, len(customer_list[i][j])) :
                if (customer_list[i][j][k] == ' ') :
                    check_flag = 3

if (check_flag == 1):
    print("중복된 행이 있습니다. 제 1 정규형에 위배됩니다.")
    sys.exit(1)
elif (check_flag == 2):
    print("두 개 이상의 도메인을 가지고 있습니다. 제 1 정규형에 위배됩니다.")
    sys.exit(1)
elif (check_flag == 3):
    print("두 개 이상의 셀 값을 가지고 있습니다. 제 1 정규형에 위배됩니다.")
    sys.exit(1)
elif (check_flag == 0):
    print("제 1 정규형에 위배되지 않습니다. Key를 찾겠습니다.")

# Key 찾기
check_flag = 0
find_key = -1
double_key = []
temp1, temp2 = "", ""
# Key 가 속성이 하나인 경우
for i in range (0, 3) :
    for j in range (0, 5) :
        Person = customer_list[j][i]
        for k in range(1 + j, 6) :
            if (Person == customer_list[k][i]) :
                check_flag = 1
                break
    if (check_flag == 0) :
        find_key = i
        check_flag = 1
        break
    else :
        check_flag = 0

# Key 가 속성이 둘인 경우
if (find_key == -1) :
    for i in range (0, 2) :
        for j in range (1 + i, 3) :
            for x in range (0, 5) :
                temp1 = customer_list[x][i]
                temp2 = customer_list[x][j]
                for y in range (1 + x, 6) :
                    if (temp1 == customer_list[y][i] and temp2 == customer_list[y][j]) :
                        check_flag = 1
                        break
            if (check_flag == 0) :
                double_key = [i, j]
                check_flag = 2
                break
        if (check_flag == 2) :
            find_key = 1
            break

# Key 가 속성이 셋인 경우
if (find_key == -1) :
    check_flag = 3

if (check_flag == 1) :
    for i in range(0, 6) :
        print(customer_list[i][find_key])

elif (check_flag == 2) :
    for i in range(0, 6) :
        print(customer_list[i][double_key[0]] + "\t\t" + customer_list[i][double_key[1]])

elif (check_flag == 3) :
    for i in range(0, 6) :
        for j in range(0, 3) :
            print(customer_list[i][j] + "\t", end = "\t")
        print("\n", end = "")

print("%d개의 속성을 가진 키를 찾았습니다." %check_flag)

if (check_flag == 1) :
    print("Partial Key 가 존재하지 않습니다. 제 2 정규형에 위배됩니다.")
    print("다음 테이블은 제 1 정규형 입니다.")
    Result(1, header, customer_list, find_key)
    sys.exit(1)

print("Partial Key 가 존재합니다. 제 2 정규형을 하겠습니다.")
#
# if (check_flag == 2) :
#     for i in range (1, 6) :
