#   IIT chennai coordinates : 12.992017471671709, 80.23373845207556

from folium import Map, Marker, Popup
from geopoint import GeoPoint


locations =[[41,-1],[40,2],[39,5],[12.990,80.223]]


mymap = Map(location=[12.990,80.223])


for loc in locations:
    geopoint = GeoPoint(latitude=loc[0], longitude=loc[1])

    forecast = geopoint.get_weather()

    popup_content= f"""
    {forecast[0][0][-8:-6]}h: {round(forecast[0][1])}°F <img src="http://openweathermap.org/img/wn/{forecast[0][-1]}@2x.png" width=35>
    <hr>
    {forecast[1][0][-8:-6]}h: {round(forecast[1][1])}°F <img src="http://openweathermap.org/img/wn/{forecast[1][-1]}@2x.png" width=35>
    <hr>
    {forecast[2][0][-8:-6]}h: {round(forecast[2][1])}°F <img src="http://openweathermap.org/img/wn/{forecast[2][-1]}@2x.png" width=35>
    """
    print(forecast)
    popup =Popup(popup_content, max_width=400)
    popup.add_to(geopoint)
    geopoint.add_to(mymap)

mymap.save("mymap.html")
