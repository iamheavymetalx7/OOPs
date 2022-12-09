'''
1. When to use class methods vs when to use static?

'''

class Item:
    pass

    @staticmethod
    def is_integer(num): ##--> regular parameter
        '''
        This should do something that has a relationship
        with the class, but not something that must be unique
        per instance!
        '''

    @classmethod
    def instantiate_from_something(cls):
        '''
        This should also do something that has a relationship
        with the class, but usually, those are used to
        manipulate different structures of data to instantiate
        objects, like we have done with CSV.
        '''

# THE ONLY DIFFERENCE BETWEEN THOSE:
# Static methods are not passing the object reference as the first argument in the background!

# We stated that class methods and static method could only be called from class level, However:

# NOTE: However, those could be also called from instances. 


item1 = Item()
item1.is_integer()
item1.instantiate_from_something()

