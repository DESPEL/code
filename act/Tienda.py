from functools import partial


def safe_input(msg, verif, errmsg="Ingrese algo válido: "):
    val = input(msg)
    while not verif(val):
        val = input(errmsg)
    return val


def is_convertible(type, value):
    try:
        type(value)
        return True
    except:
        return False
def make_range_verif(typ, minv, maxv):
    def range_verif(num):
        if not is_convertible(typ, num):
            return False
        return typ(num) >= minv and typ(num) <= maxv
    return range_verif

def type_verif(t):
    return partial(is_convertible, t)


class Tienda:
    def __init__(self):
        self.options = ["Comprar", "Ver carrito", "Configuracion", "Salir"]
        self.products = {
            "manzana": 0.5,
            "lechuga": 9.0,
            "escoba": 7.0,
            "jabón": 5.0,
            "pintura": 23.0,
            "brocha": 2.0,
            "encendedor": 3.0,
            "cubeta": 12.0,
            "foco": 5.0
        }
        self.indexed = list(self.products.keys())
        self.cart = Carrito()
        self.user = Usuario()

    def product_verif(self, product):
        if is_convertible(int, product):
            return int(product) > 0 or int(product) <= len(self.products)
        else:
            return product in self.products
    def amount_verif(self, amount):
        if is_convertible(int, amount):
            return int(amount) > 0
        return False

    def product_to_string(self, idx):
        return self.indexed[idx - 1]

    def printMenu(self):
        for idx, option in enumerate(self.options):
            print(str(idx + 1) + ") " + option)

    def printProducts(self):
        for idx, product in enumerate(self.products):
            cost = self.products[product]
            print(str(idx + 1) + ") " + product + "   $" + str(cost))

    def comprar(self):
        print("Bienvenido a la tienda")
        self.printProducts()

        while True:
            producto = safe_input(
                "Ingrese el producto que quiere comprar: ", self.product_verif, 
                errmsg="Ingrese un producto existente")
            if is_convertible(int, producto):
                producto = self.product_to_string(int(producto))
            cantidad = safe_input(
                "Ingrese la cantidad de producto que quiere comprar: ", self.amount_verif,
                errmsg="Ingrese una cantidad válida")

            print("El producto {} x {} ha sido agregado al carrito".format(
                producto, cantidad))
            self.cart.add_item(producto.lower(), int(
                cantidad), self.products[producto.lower()])
            command = input(
                "Ingrese 1 si desea seguir comprando, 2 si desea finalizar la compra y algo diferente para volver al menu principal: ")
            if command.strip() == "1":
                continue
            elif command.strip() == "2":
                self.pay()
                return
            else:
                return

    def pay(self):
        if not self.user.is_registered():
            print("Se ha detectado que no está registrado, se iniciará el registro para posteriormente realizar el pago")
            self.user.register()
        self.cart.print_items()
        option = input("Ingrese 1 para pagar")
        if option.strip() == "1":
            print("Ha pagado correctamente")
            self.cart = Carrito()
        else:
            print("Ha cancelado su compra")        


class Carrito:

    def __init__(self):
        self.items = {}
        self.cost = 0.0

    def add_item(self, name, amount, cost):
        self.cost += cost * amount
        if name in self.items:
            self.items[name][1] += amount
        else:
            self.items[name] = [cost, amount]

    def print_items(self):
        print("Productos en el carrito:")
        total = 0.0
        for name in self.items:
            cost, amount = self.items[name]
            total += cost*amount
            print(
                f"{name} ${str(cost)}c/u  cantidad:{str(amount)} total: ${str(cost*amount)}"
            )
        print("Total: $" + str(total))

    def get_cost(self):
        return self.cost


class Usuario:
    def __init__(self): 
        self.registered = False
        self.birth = {}
        self.card = {}
        self.months = [
            "enero", "febrero", "marzo",
            "abril", "mayo", "junio",
            "julio", "agosto", "septiembre",
            "octubre", "noviembre", "diciembre"]
        self.card_types = ["VISA", "MASTERCARD", "AMEX"]

    def make_day_verif(self, month):
        month_days = {
            "enero": 31, "febrero": 29, "marzo": 31,
            "abril": 30, "mayo": 31, "junio": 30,
            "julio": 31, "agosto": 31, "septiembre": 30,
            "octubre": 31, "noviembre": 30, "diciembre": 31}

        def verif_day(day):
            if not is_convertible(int, day):
                return False
            if int(day) > month_days[month] or int(day) < 1:
                return False
            return True
        return verif_day

    def month_verif(self, month):
        if is_convertible(int, month):
            if int(month) < 1 or int(month) > 12:
                return False
        elif month.lower() not in self.months:
            return False
        return True

    def month_to_string(self, month):
        return self.months[month - 1]

    def card_to_string(self, card):
        return self.card_types[card - 1]

    def card_type_verif(self, name):
        if is_convertible(int, name):
            return int(name) >= 1 and int(name) <= 3
        else:
            return name in self.card_types
        return False

    def card_number_verif(self, number):
        return len(number) == 16 and is_convertible(int, number)

    def input_birth(self):
        self.birth["year"] = safe_input(
            "Ingrese su año de nacimiento: ", type_verif(int))

        self.birth["month"] = safe_input(
            "Ingrese su mes de nacimiento: ", self.month_verif)
        if is_convertible(int, self.birth["month"]):
            self.birth["month"] = self.month_to_string(
                int(self.birth["month"]))

        self.birth["day"] = int(safe_input(
            "Ingrese su dia de nacimiento: ", self.make_day_verif(self.birth["month"])))

    def input_card(self):
        self.card["type"] = safe_input(
            "Ingrese el tipo de su tarjeta:\n" +
            "1) VISA\n" +
            "2) MasterCard\n"
            "3) AMEX\n", self.card_type_verif)
        if is_convertible(int, self.card["type"]):
            self.card["type"] = self.card_to_string(int(self.card["type"]))

        self.card["number"] = safe_input(
            "Ingrese su numero de tarjeta: ", self.card_number_verif)
        self.card["expire-month"] = safe_input(
            "Ingrese el mes de expiracion de su tarjeta: ", self.month_verif)
        self.card["expire-year"] = safe_input(
            "Ingrese el año de expiración de su tarjeta: ", type_verif(int))

    def register(self):
        self.nombre = input("Ingrese su nombre completo: ")
        self.ubicacion = input("Ingrese su ciudad: ") + \
        ", " + input("Ingrese su estado: ")

        self.input_birth()
        self.input_card()
        self.registered = True
    
    def is_registered(self):
        return self.registered

    def print(self):
        if not self.is_registered():
            print("Se ha detectado que no está registrado, se le creará una cuenta nueva")
            self.register()
        print(f"""
    Información:
    
    Personal:
    ----------------------------------
    Usuario: {self.nombre}
    Ubicación: {self.ubicacion}
    Fecha de nacimiento: {self.birth["day"]} / {self.birth["month"]} / {self.birth["year"]}
    
    Método de pago:
    ----------------------------------
    Tipo de tarjeta: {self.card["type"]}
    Numero: xxxx xxxx xxxx {self.card["number"][-4:]}
    Fecha de expiración: {self.card["expire-month"]} / {self.card["expire-year"]}
        """)
        input("Ingrese algo para regresar al menu principal")

tienda = Tienda()
options = ["Comprar", "Ver carrito", "Configuracion", "Salir"]
optstr = ""
for idx, option in enumerate(options):
    optstr += f"\n {str(idx + 1)}) {option}"

while True:
    opt = int(safe_input(
        f""" Bienvenido a la tienda
Seleccione una opción {optstr}
""", make_range_verif(int, 1, 4)
    ))
    if opt is 1:
        tienda.comprar()
    elif opt is 2:
        tienda.cart.print_items()
        opt = input("Ingrese 1 si desea pagar o otra cosa para regresar al menu principal")
        if opt.strip() == "1":
            tienda.pay()
    elif opt is 3:
        tienda.user.print()
    else:
        break
    

