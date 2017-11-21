import datetime

def get_day_of_new_year(x):
	for i in range(1, x + 1):
		print datetime.datetime(year=(2017 - i), month=1, day=1).weekday()

if __name__ == "__main__":
	get_day_of_new_year(3)
