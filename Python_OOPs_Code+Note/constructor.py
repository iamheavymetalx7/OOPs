##main.py

item1= 'Phone' ##there are actually instances of some class --> this is instantiated from str class
item1_price = 2500 ## int class
item1_quantity = 4
item1_price_total = item1_price*item1_quantity



## i can dynamically assign an attribute to an instance by this __init__ method
class Item:
    pay_rate = 0.8  ##pay rate after 20% discount

    all=[]

    def __init__(self,name : str,price: float, quantity = 0) -> None:     ##setting default to zero
        #Run validation to the received argument

        assert price>=0, f" price {price} is not greater than or equal to zero!!"
        assert quantity>=0, f" quantity {quantity} is not greater than or equal to zero!!"

        # Assign to the self object
        self.name = name
        self.price = price
        self.quantity=quantity

        # Actions to execute :
        Item.all.append(self)   ## for each instance that is created, this list is going to be filled with instances

    def calc_total_price(self): 
        return self.price * self.quantity
    
    def apply_discount(self):
        self.price = self.price * self.pay_rate  ##over writing the prev value

#        self.price = self.price * Item.pay_rate  ##over writing the prev value

        ## can not directly access here using pay_rate since we know that we can access it at class level or instance level only

    def __repr__(self) -> str:
        return f"Item('{self.name}','{self.price}','{self.quantity})"


item1=Item("Phone",100,1)

item2=Item("Laptop",1000,3)

## now if we dont pass quantity here, it will be set to zero.
print(item1.name)

'''
print(item1.name)
print(item2.name)


print(item1.price)
print(item2.price)

print(item1.quantity)
print(item2.quantity)
'''
## always take care of the attributes that you want to assign to an object
## inside the __init__  method.

#item3=Item("Clock",30)
#print(item3.quantity) ##--> 0


## one can assign attributes to specific instances individually!!

item2.has_numpad = False

## print("item 1 total price: {}".format(item1.calc_total_price( )))
## print("item 2 total price: {}".format(item2.calc_total_price( )))


## A class attribute  is an attribute that is going to belong to the class itself
## But however you can also access this attribute from the instance level as well.

'''
print(Item.pay_rate)

print(item1.pay_rate) # accessible from instance level
print(item2.pay_rate) # attributes bought from class level

'''

##print(Item.__dict__)    ## all attributes for class level
##print()
##print(item1.__dict__)   ## all attributes for instance level
item1.apply_discount()
#print(item1.price)



## now suppose we want to have different discount for different items


## say for laptop we want to discount 30%.


item2.pay_rate = 0.7
## here, for item 2 it will find the attribute of pay_rate in the instance level, so it doesnt have
## to go to class level. Like we discussed earlier, at first it finds it in the instance level


item2.apply_discount()
#print(item2.price)      ## outputs 800 : this is because of the "self.price = self.price * Item.pay_rate" Item.pay_rate
## so best practice is use to change it to self!! 



item3 = Item("Cube",10,5)
item4 = Item("Keyboard",50,5)
item5 = Item ("Mouse", 40, 7)


#print(Item.all)

#for instance in Item.all:
#    print (instance.name)


print(Item.all)