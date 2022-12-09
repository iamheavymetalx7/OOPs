from item import Item


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

#print(phone1.calc_total_price())

## SUPER allows us to have full access to all attributes of the parent class.


phone2=Phone('nkPhone20',700,3,1)
#phone1.broken_phones = 0 
