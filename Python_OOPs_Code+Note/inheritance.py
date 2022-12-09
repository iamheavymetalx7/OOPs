import csv

class Item:
    pay_rate = 0.8 

    all=[]

    def __init__(self,name : str,price: float, quantity = 0) -> None:    
        #Run validation to the received argument

        assert price>=0, f" price {price} is not greater than or equal to zero!!"
        assert quantity>=0, f" quantity {quantity} is not greater than or equal to zero!!"

        # Assign to the self object
        self.name = name
        self.price = price
        self.quantity=quantity

        # Actions to execute :
        Item.all.append(self)  

    def calc_total_price(self): 
        return self.price * self.quantity
    
    def apply_discount(self):
        self.price = self.price * self.pay_rate 

    @classmethod
    def instantiate_from_csv(cls):     #class Method : cls parameter is received --  when we call our class method, class object is passed as first argument
            with open("items.csv",'r') as f:
                reader = csv.DictReader(f) # this method reads our content as list of dictionaries
                items=list(reader)

            for item in items:
                #print(item)
                Item(
                name=item.get('name'),
                price=float(item.get('price')),
                quantity=int(item.get('quantity')),
                )      ##instantiating our instances
    
    @staticmethod       #--> static methods are not sending in the background the instance as the first argument, unlike the class methods.
    def is_integer(num):   # static method should be perceived as just a regular function
        # we will count the floats that are point zero : 10.0, 5.0
        if isinstance(num, float):     #--> built-in function
            #count the floats that are point zero
            return num.is_integer()
        elif isinstance(num, int):
            return True
        else:
            return False



    def __repr__(self) -> str:
        return f"{self.__class__.__name__}('{self.name}','{self.price}','{self.quantity})"


class Phone(Item):
    #all=[]
    def __init__(self,name : str,price: float, quantity = 0, broken_phones = 0) -> None:  
        # Call to super function to have access to all attributes/methodds

        super().__init__(
            name, price, quantity
        )

        #Run validation to the received argument
        assert broken_phones>=0
        # Assign to the self object

        self.broken_phones = broken_phones

        # Actions to execute :
        # Phone.all.append(self)  



phone1=Phone("nkPhonev10",500,5,1)
#phone1.broken_phones = 1

print(phone1.calc_total_price())

## SUPER allows us to have full access to all attributes of the parent class.


phone2=Phone('nkPhone20',700,3,1)
#phone1.broken_phones = 0 


# we will now create a separate class that will inherit the functionalities
# that the item class brings with it. And that is where we benefit from inheritance.

# Phone class will inherit all the method and all the atributes in the item class.

# Item is parent classes, Phone is a child class!!

item1 =Item("Laptop", 500, 3)


print(Item.all)
print(Phone.all)        ## both output the same, because we never implement the repr method inside the Phone class 
                        ## thats why we see the ungeneric result

## so we will use special methos: self.__class__.__name__ ----> generic way to access the name of class from instance



## now deleting the all from phone class and the method to execute step in Phone Class!!
