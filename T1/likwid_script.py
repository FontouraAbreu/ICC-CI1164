file_path = "likwid.out"



group = "FLOPS_DP"
flops_avx = "AVX"
flops_dp = "DP"
metric = "Metric    "
found_specific_text = False
found_group = False
found_metric1 = False
found_metric2 = False
found_avx = False
found_dp = False
line_count = 0
count = 0

with open(file_path, "r") as file:
    lines = file.readlines()

for line in lines:
    if line_count < 12:  # Check if you've read fewer than 11 lines
        print(line, end="")
        line_count += 1
    else:
        break

lines_to_print = [39, 40, 41, 46, 47, 48, 52, 54, 55, 56, 61, 62, 63, 67, 69, 96, 97, 98, 104, 110]

with open(file_path, "r") as file:
    for line_number, line in enumerate(file, start=1):
        if line_number in lines_to_print:
            print(line, end="")

# for line in lines:
#     if group in line:
#         print(line, end="")
#         found_group = True
#     if found_group and metric in line:
#         print(previous_line, end="")
#         print(line, end="")
#         found_metric1 = True
#     if found_metric1 and metric not in line:
#         print(line, end="")
#         found_metric2 = True
#         found_metric1 = False
#     if found_metric2 and flops_avx in line:
#         print(line, end="")
#     if found_metric2 and flops_dp in line and flops_avx not in line:
#         print(line, end="")
#         found_dp = True
    # if found_dp:
    #     count+=1
    #     if count == 1:
    #         print(line, end="")
    #         found_dp = False
    #         count = 0

    previous_line = line

