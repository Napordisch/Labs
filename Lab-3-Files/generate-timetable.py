import random
from operator import itemgetter
def GenerateTime():
  minutes = random.randint(0, 59)
  hours = random.randint(0, 23)
  str_minutes = str(minutes)
  str_hours = str(hours)
  if minutes < 10:
    str_minutes = "0" + str(minutes)
  if hours < 10:
    str_hours = "0" + str(hours)
  return str_hours + ":" + str_minutes

destinations = ["Нью-йорк", "Париж", "Сан-франциско", "Лондон", "Токио"]

timetable = open("departures.csv", "a", newline="\n")

destination = random.choice(destinations)

number = random.randint(0, 10000)

timetable.write(str(number) + "," + random.choice(destinations) + "," + GenerateTime() + "\n")