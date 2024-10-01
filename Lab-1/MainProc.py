import subprocess

def CheckForInt(num_list):
  for var in num_list:
    try:
      int(var)
    except ValueError:
      return False

while True:
  numbers = input("Введите числа, разделённые пробелом: ")
  while CheckForInt(numbers.split()) == False:
    numbers = input("Вы ввели не число, введите числа, разделённые пробелом, ещё раз: ")

  sorting_method = "0"
  
  while sorting_method != "1" or sorting_method != "2":
    sorting_method = input("Выберите метод сортировки\n" \
                         + "1 - Сортировка слиянием;\n" \
                         + "2 - Быстрая сортировка.\n");
    
    if sorting_method == "1" or sorting_method == "2":
      break

  result = subprocess.run(['./Sort', numbers, sorting_method], \
                          capture_output = True, text = True)
  print("Result:", result.stdout)

  command = input("q — выйти, любые другие символы — продолжить: ")
  if command == "q":
    break