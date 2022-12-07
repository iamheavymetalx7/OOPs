#   IIT chennai coordinates : 12.992017471671709, 80.23373845207556

from folium import Map

latitude = float("12.99")
longtitude = float("80.233")

antipode_latitude =  latitude.__mul__(int("-1")) #  ---> method


if longtitude.__le__(float("0")):
    antipode_longitude = longtitude.__add__(float("180"))
elif longtitude.__gt__(float("180")):
    antipode_longitude = str("Invalid Longitude !!")
else:
    antipode_longitude = longtitude.__sub__(float("180"))

location = list((antipode_latitude, antipode_longitude))
mymap = Map(location)

print(antipode_latitude, antipode_longitude)       #--> functions

print(mymap) ## prints the object

mymap.save(str("antipode_loc.html"))


"""
1. Object Types
2. Methods and Functions
3. New Object Types (Building)
4. Decision Making
"""


##dir(__builtins_) -> gives all the builtins in python

'''
1. Objects - 
2. Identifiers - names we assign to objects
3. Keywords - from, import, else, if
4. Delimiters - " ", . , ()
5. Blank lines
6. White space
7. Indentation
8. Comments
9. Operators


'''