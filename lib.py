from functools import partial

def is_convertible(type, val):
    try:
        type(val)
        return True
    except:
        return False

def make_is_convertible(type):
    return partial(is_convertible, type)

def is_type(type_name, value):
    return type(value) is type_name

def make_is_type(type_name):
    return partial(is_type, type_name)

def is_same_type(value1, value2):
    return type(value1) is type(value2)



def typed_input(type, msg="",errmsg="Ingrese algo válido", loop=True):
    val = input(msg)
    while loop and not is_convertible(type, val):
        val = input(msg)
    return type(val)

def safe_input(verifier, msg="", errmsg="Ingrese algo válido", loop=True, type=str):
    val = input(msg)
    while loop and not is_convertible(type, val) and not verifier(type(val)):
        val = input(errmsg)
    return type(val)


def make_verify_range(min, max, type=int):
    def verify_range(value):
        if not is_convertible(type, value):
            return False
        return type(value) >= min and type(value) <= max 
    return verify_range

def make_verify_greater(min, type=int):
    def verify_greater(value):
        if not is_convertible(type, value):
            return False
        return type(value) > min
    return verify_greater

def make_verify_less(max, type=int):
    def verify_less(value):
        if not is_convertible(type, value):
            return False
        return type(value) < max
    return verify_less

def make_verify_equal(value, type=int):
    def verify_equal(val):
        if not is_convertible(type, value):
            return False
        return type(val) == value
    return verify_equal

def make_verify_less_or_equal(value, type=int):
    less = make_verify_less(value, type)
    equal = make_verify_equal(value, type)
    def verify_less_or_equal(val):
        return less(val) or equal(val)
    return verify_less_or_equal

def make_verify_greater_or_equal(value, type=int):
    greater = make_verify_greater(value, type)
    equal = make_verify_equal(value, type)
    def verify_greater_or_equal(val):
        return greater(val) or equal(val)
    return verify_greater_or_equal

