import pyowm

from config import APIKEY, LOCATION

owm = pyowm.OWM(APIKEY)


def get_weather():
    observation = owm.weather_at_place(LOCATION)
    weather = observation.get_weather()
    return weather._status
