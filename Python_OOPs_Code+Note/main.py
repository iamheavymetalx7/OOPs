##main.py

item1= 'Phone' ##there are actually instances of some class --> this is instantiated from str class
item1_price = 2500 ## int class
item1_quantity = 4
item1_price_total = item1_price*item1_quantity


## now we can think what we need for our item data type: price, quantity

# lets create our first class

# creating an instance of a class or creating a object of a class is the same thing

class Item:
    def __init__(self) -> None:     ##magic methods
        print("I AM CREATED")

    def calc_total_price(self,x,y): ##self - python passes the object itself as first argument when we call these method everytime
        return x*y



item1=Item()        ##created an instance of item class

## same as random_str = str("4")

## now we will assign some atributes to the class

## achievable by using.dot

item1.name = "Phone"
item1.price = 100
item1.quantity = 5

print(item1.calc_total_price(item1.price, item1.quantity)) ##this action calls the method

##how we can create some method and execute them on our instances

## example: .upper() in string class or .lower() .... we do this inside our class

item2=Item()

##methods are the functions inside the class
item2.name = "Laptop"
item2.price = 1000
item2.quantity = 3

print(item2.calc_total_price(item2.price, item2.quantity)) ##this action calls the method


##in order to instiate an object succsefully : name price and quantity must be passed otherwise it would not create
## we can do this, by a special methos __init__ ---> constructor, unique method to use its features. 