from folium import Map
from geopoint import GeoPoint

tokyo = GeoPoint(latitude=35.7, longitude=139.7)

print(tokyo.get_time()) ## this is local time in geopoint location
print(tokyo.get_weather())  ## this is time of user, that is me!!


point = GeoPoint.random()
print(point.latitude, point.longitude)
print(point)