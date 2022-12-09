import csv
class Item:
    pay_rate = 0.8 # The pay rate after 20% discount
    all = []
    def __init__(self, name: str, price: float, quantity=0):
        # Run validations to the received arguments
        assert price >= 0, f"Price {price} is not greater than or equal to zero!"
        assert quantity >= 0, f"Quantity {quantity} is not greater or equal to zero!"

        # Assign to self object
        self.__name = name
        self.__price = price
        self.quantity = quantity

        # Actions to execute
        Item.all.append(self)

    @property
    def price(self):
        return self.__price

    @property
    # Property Decorator = Read-Only Attribute
    def name(self):
        #print("acccessing the name huh?")
        return self.__name


    def apply_discount(self):
        self.__price = self.__price * self.pay_rate 

    def apply_inc(self, inc_val):
        self.__price = self.__price + self.__price * inc_val

    @name.setter        #decorator
    def name(self, value):
        #print("You are trying to set")
        if len(value) > 10:
            raise Exception("The name is too long!")
        else:
            self.__name = value
    def calc_total_price(self): 
        return self.__price * self.quantity
    

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
    
    def __connect(self, smpt_server):
        pass

    def __prepare_body(self):
        return f"""
        Hello, Someone.
        We have {self.name} {self.quantity} times.

        Regards,
        Nitish
        """

    def __send(self):
        pass

    def send_email(self):
        self.__connect(" ")
        self.__prepare_body()  
        self.__send()  




    def __repr__(self) -> str:
        return f"{self.__class__.__name__}('{self.name}','{self.__price}','{self.quantity})"

