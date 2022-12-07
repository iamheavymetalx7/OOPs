## type is equivalent to class
from datetime import datetime
from pytz import timezone
from timezonefinder import TimezoneFinder
from sunnyday import Weather
from random import uniform
from folium import Marker   ##inheritance



class GeoPoint(Marker):

    latitude_range =(-90,90)    # class variable
    longitude_range=(-180,180)

    def __init__(self, latitude, longitude, popup=None):
        super().__init__(location =[latitude, longitude], popup =popup)
        self.latitude = latitude    # instance variable 
        self.longitude = longitude

    def closest_parallel(self):
        return round(self.latitude)

    def get_time(self):
        timezone_string = TimezoneFinder().timezone_at(lat=self.latitude, lng=self.longitude)
        time_now = datetime.now(timezone(timezone_string))
        return time_now

    def get_weather(self):
        weather = Weather(apikey="fe63b206610cd6bffc62de7c284c8ab0", lat=self.latitude, lon=self.longitude)
        return weather.next_12h_simplified


    @classmethod
    def random(cls):
        return cls(latitude = uniform(-90,90), longitude = uniform(-180,180) )