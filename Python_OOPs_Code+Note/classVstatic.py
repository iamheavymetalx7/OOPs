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
        return f"Item('{self.name}','{self.price}','{self.quantity})"


#Item.instantiate_from_csv()
#
# print(Item.all)

print(Item.is_integer(7.0))
