from item import Item


class Keyboard(Item):
    #all=[]
    pay_rate = 0.70
    def __init__(self,name : str,price: float, quantity = 0) -> None:  
        # Call to super function to have access to all attributes/methodds

        super().__init__(
            name, price, quantity
        )


