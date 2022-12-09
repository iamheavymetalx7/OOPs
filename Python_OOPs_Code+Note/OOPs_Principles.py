from item import Item
from phone import Phone
from keyboard import Keyboard

item1= Item("MyItem",750) 


#print(item1.__name) #AttributeError: 'Item' object has no attribute '__name'



#print(item1.price)
#Encapsulation --  read only attributes, restricting the users to overwrite the attributes after initilisation of instances


## Encapsulation - refers to a mechanism of restricting the direct access to some of  
## our attributes in a program.

item1.apply_discount()

item1.apply_inc(0.2)

#print(item1.price)


## Abstraction : shows the only necessary attributes and hides the unnecesaary information
## 

#item2 = Item("Myitem",750,6)
#item2.send_email() ##--> doesnt exist!!

##item2.connect()         ## this is accessible, which we should hide from users!!
## we apply abstraction!!

## so we add __




## Inheritance : mechanism that allows you to re-use code across our classes.
## More classes that are child classes of item class, where each child class represents an kind of item.

item1 =Phone("nkV10",1000,2)     ## implemented in the parent class: uses all method and attributes

#print(item1.name)

item1.apply_discount() ## ---> this is also polymorphism in action, because apply discount is a 
## method is accesible from all the kinds of objects.

item1.send_email() ## designed in the parent class (Item) but we can use here!!


item1.apply_inc(0.3)

#print(item1.price)


## Polymorphism: refers to use of a single type of entity to represent different type in different scenarios
## refers to many forms
## ability to have different scenario, when we call the exact same entity.

'''
name = "Jim" # str
print(len(name)) #--> total amount of characters

some_list = ["some","name"] # list
print(len(some_list)) #--> receives amount of elts inside the list
'''
# That's polymorphism in action, a single function does now
# how to handle different kinds of objects as expected!

item3 = Keyboard("nkkeyboard",100,3)

item3.apply_discount()

print(item3.price)



## The end