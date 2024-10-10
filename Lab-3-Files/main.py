from operator import itemgetter

def Show():
  departures = open("departures.csv", "r")

  departures_list = []

  for i in departures:
    departures_list.append(i.strip().split(sep=','))

  departures_list.sort(key = itemgetter(2))

  for d in departures_list:
    print(d[0], d[1], d[2])

  filter_by = input("Введите пункт назначения для фильтрации: ")
  print("\n", "Результат:")
  result_file = open("result.txt", "w")
  for d in departures_list:
    if d[1].lower() == filter_by.lower():
      print(d[0], d[2])
      result_file.write(d[0]+ "," + d[1] + "," + d[2] + "\n")
  
def AddEntry():
  departures = open("departures.csv", "a")
  index = int(input("Введите номер рейса: "))
  destination = input("Введите пункт назначения: ").capitalize()
  
  time = input("Введите время в формате \"чч:мм\": ").split(sep=":")
  hours = int(time[0])
  minutes = int(time[1])
  while hours >= 24 or minutes >= 60:
    time = input("Такого времени не бывает. Введите время в формате \"чч:мм\": ").split(sep=":")
    hours = int(time[0])
    minutes = int(time[1])
  while (len(time) > 4):
    time = input("Неверный формат времени, сликом много символов. Введите время в формате \"чч:мм\": ").split(sep=":")
    hours = int(time[0])
    minutes = int(time[1])
  if hours < 10:
    hours = "0" + str(hours)
  else:
    hours = str(hours)
  if minutes < 10:
    minutes = "0" + str(minutes)
  else:
    minutes = str(minutes)
    
  departures.write(str(index) + "," + destination + "," + str(hours) + ":" + str(minutes) + "\n")
  
while True:
  command = input("a — добавить элемент\nc — показать спиксок\np — показать предыдущий результат фильтрации\nx — выйти\n:")
  if command.lower() in ["a", "а", "ф", "f"]:
    AddEntry()
  if command.lower() in ["c", "с"]:
    Show()
  if command.lower() in ["x", "х", "ч", "["]:
    break
  if command.lower() in ["p", "р", "з", "h"]:
    previous_result = open("result.txt", "r")
    previous_result_list = []

    for i in previous_result:
      previous_result_list.append(i.strip().split(sep=','))
    for d in previous_result_list:
      print(d[0], d[1], d[2])
